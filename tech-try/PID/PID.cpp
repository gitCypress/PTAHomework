#include "PID.hpp"
#include <stdexcept> // For potential exceptions
#include <limits>    // For numeric limits if needed

// --- LowPassFilter Implementation ---

LowPassFilter::LowPassFilter(double alpha)
    : alpha_(alpha), filteredValue_(0.0), initialized_(false) {
    // 检查 alpha 值的有效性 (可选但推荐)
    if (alpha_ <= 0.0 || alpha_ > 1.0) {
        // 可以选择抛出异常或钳位到一个安全值
        // throw std::invalid_argument("LowPassFilter alpha must be between 0 and 1");
        alpha_ = std::clamp(alpha, 0.001, 1.0); // 钳位到一个有效的小值或1
        // 或者设置默认值
        // alpha_ = 0.5;
    }
}

double LowPassFilter::update(double measurement) {
    if (!initialized_) {
        filteredValue_ = measurement;
        initialized_ = true;
    } else {
        filteredValue_ = alpha_ * measurement + (1.0 - alpha_) * filteredValue_;
    }
    return filteredValue_;
}

void LowPassFilter::reset(double value) {
    filteredValue_ = value;
    initialized_ = false; // 重置后需要重新初始化
}

// --- PIDController Implementation ---

PIDController::PIDController(double Kp, double Ki, double Kd,
                             double minOutput, double maxOutput,
                             double integratorMin, double integratorMax,
                             double deadband)
    : Kp_(Kp), Ki_(Ki), Kd_(Kd),
      minOutput_(minOutput), maxOutput_(maxOutput),
      integratorMin_(integratorMin), integratorMax_(integratorMax),
      deadband_(std::abs(deadband)), // 确保死区值为非负
      integral_(0.0), previousError_(0.0), firstUpdate_(true) {
    // 可以在这里添加更多参数验证，例如确保 min < max
    if (minOutput_ >= maxOutput_) {
        // throw std::invalid_argument("PIDController minOutput must be less than maxOutput");
        // 或者交换它们或设置默认值
    }
    if (integratorMin_ >= integratorMax_) {
        // throw std::invalid_argument("PIDController integratorMin must be less than integratorMax");
        // 或者交换它们或设置默认值
    }
}

double PIDController::update(double error, double dt) {
    // 处理首次调用，避免微分项计算错误
    if (firstUpdate_) {
        previousError_ = error; // 使用当前误差初始化 previousError
        firstUpdate_ = false;
    }

    // --- 死区检查 ---
    if (std::abs(error) < deadband_) {
        // 在死区内，可以选择重置积分项以防止微小漂移累积
        // integral_ = 0.0;
        previousError_ = error; // 仍然需要更新 previousError
        return 0.0; // 输出 0
    }

    // --- 比例项 ---
    double p_term = Kp_ * error;

    // --- 积分项 (带抗饱和处理) ---
    double potential_integral = integral_ + error * dt;
    integral_ = std::clamp(potential_integral, integratorMin_, integratorMax_); // 钳位积分累积值
    double i_term = Ki_ * integral_;

    // --- 微分项 ---
    double derivative = 0.0;
    // 检查 dt 是否有效且足够大，以避免数值问题
    if (dt > std::numeric_limits<double>::epsilon()) { // 检查 dt 是否大于最小的正数
        derivative = (error - previousError_) / dt;
    } else {
        // 如果 dt 过小，可以选择不更新微分项或返回0
        derivative = 0.0;
    }
    double d_term = Kd_ * derivative;

    // --- 计算原始输出 ---
    double output_raw = p_term + i_term + d_term;

    // --- 输出限幅 (饱和) ---
    double output_clamped = std::clamp(output_raw, minOutput_, maxOutput_);

    // --- 积分抗饱和 (更精确的方法 - 可选) ---
    // 如果输出被饱和了，可能需要调整积分项以避免 windup
    // 例如：Back-Calculation
    // double anti_windup_gain = 1.0; // 可调参数
    // if (Ki_ > std::numeric_limits<double>::epsilon() && dt > std::numeric_limits<double>::epsilon()) {
    //     double saturation_error = output_clamped - output_raw;
    //     integral_ -= (anti_windup_gain / Ki_) * saturation_error * dt;
    //     // 再次钳位积分项以防万一
    //     integral_ = std::clamp(integral_, integratorMin_, integratorMax_);
    // }
    // 注意：上面这种 Back-Calculation 比较复杂，简单的积分值钳位通常足够。

    // --- 更新状态，为下一次迭代做准备 ---
    previousError_ = error; // 保存当前误差

    return output_clamped; // 返回最终限制后的控制输出
}

void PIDController::reset() {
    integral_ = 0.0;
    previousError_ = 0.0;
    firstUpdate_ = true;
}

void PIDController::setKp(double Kp) {
    Kp_ = Kp;
}

void PIDController::setKi(double Ki) {
    Ki_ = Ki;
}

void PIDController::setKd(double Kd) {
    Kd_ = Kd;
}

void PIDController::setOutputLimits(double min, double max) {
    if (min < max) {
        minOutput_ = min;
        maxOutput_ = max;
    }
    // else: 考虑报错或记录日志
}

void PIDController::setIntegratorLimits(double min, double max) {
    if (min < max) {
        integratorMin_ = min;
        integratorMax_ = max;
        // 重置或钳位当前积分值以符合新限制 (可选)
        integral_ = std::clamp(integral_, integratorMin_, integratorMax_);
    }
    // else: 考虑报错或记录日志
}

void PIDController::setDeadband(double deadband) {
    deadband_ = std::abs(deadband); // 保证为非负
}

// Vector3d 结构体没有需要在此处实现的方法
