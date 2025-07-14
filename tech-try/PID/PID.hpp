#ifndef PID_HPP
#define PID_HPP

#include <cmath>
#include <algorithm> // 使用 std::clamp (C++17) 或手动实现
#include <vector>    // 可能用于滤波器或历史记录

/**
 * @brief 简单的三维向量结构体
 * @details 用于存储和传递三维坐标或速度等数据。
 */
struct Vector3d {
    double x = 0.0; ///< X 分量
    double y = 0.0; ///< Y 分量
    double z = 0.0; ///< Z 分量
};

/**
 * @brief 简单低通滤波器类 (示例: 指数移动平均 EMA)
 * @details 用于平滑输入信号，减少噪声和抖动。
 *          这是一个基础实现，可以根据需要替换为更复杂的滤波器。
 */
class LowPassFilter {
public:
    /**
     * @brief 构造函数
     * @param alpha 平滑因子 (0 < alpha <= 1)。alpha 越小，平滑效果越强，但延迟越大。
     *              alpha = 1 时，无滤波效果。
     */
    explicit LowPassFilter(double alpha = 0.5);

    /**
     * @brief 使用新的测量值更新滤波器状态
     * @param measurement 当前的原始测量值
     * @return double 滤波后的值
     * @details 实现指数移动平均 (EMA) 算法:
     *          filtered = alpha * current + (1 - alpha) * previous_filtered
     *          首次调用时，直接使用测量值初始化。
     */
    double update(double measurement);

    /**
     * @brief 重置滤波器状态
     * @param value 可选的重置值，默认为 0.0
     * @details 将滤波器的内部状态恢复到初始或指定值。
     */
    void reset(double value = 0.0);

private:
    double alpha_;         ///< 平滑因子
    double filteredValue_; ///< 当前存储的滤波后值
    bool initialized_;     ///< 标记滤波器是否已用第一个值初始化
};


/**
 * @brief 通用 PID 控制器类
 * @details 实现了一个标准的 PID 控制算法，包含比例(P)、积分(I)、微分(D)环节，
 *          并集成了积分抗饱和、输出限幅和死区处理功能。
 *          适用于需要将系统状态（如位置、速度、角度）调节至目标值的场景。
 */
class PIDController {
public:
    /**
     * @brief 构造函数
     * @param Kp 比例增益 (Proportional Gain)
     * @param Ki 积分增益 (Integral Gain)
     * @param Kd 微分增益 (Derivative Gain)
     * @param minOutput 输出值的下限
     * @param maxOutput 输出值的上限
     * @param integratorMin 积分项累积值的下限 (用于积分抗饱和)
     * @param integratorMax 积分项累积值的上限 (用于积分抗饱和)
     * @param deadband 死区范围。当误差绝对值小于此值时，输出为 0。默认为 0 (无死区)。
     * @details 初始化 PID 控制器的所有参数和内部状态。
     *          积分项的限制 (integratorMin, integratorMax) 是实现积分抗饱和的关键。
     *          输出限制 (minOutput, maxOutput) 定义了控制器最终输出的范围。
     */
    PIDController(double Kp, double Ki, double Kd,
                  double minOutput, double maxOutput,
                  double integratorMin, double integratorMax,
                  double deadband = 0.0);

    /**
     * @brief 更新 PID 控制器状态并计算输出
     * @param error 当前的误差 (目标值 - 实际值)
     * @param dt 上次调用 update 到本次调用的时间间隔 (秒)
     * @return double 计算得到的控制器输出值 (被限制在 minOutput 和 maxOutput 之间)
     * @details 执行一次 PID 计算循环:
     *          1. 处理首次调用，初始化 previousError_。
     *          2. 检查误差是否在死区范围内，如果是则直接返回 0。
     *          3. 计算比例项 P = Kp * error。
     *          4. 计算积分项 I:
     *             a. 累积当前误差: potential_integral = integral + error * dt。
     *             b. 将累积结果限制在 [integratorMin_, integratorMax_] 范围内 (积分抗饱和)。
     *             c. 计算最终积分项: i_term = Ki * integral_。
     *          5. 计算微分项 D:
     *             a. derivative = (error - previousError_) / dt (注意处理 dt 过小的情况)。
     *             b. d_term = Kd * derivative。
     *          6. 计算未加限制的原始输出: output_raw = P + I + D。
     *          7. 将原始输出限制在 [minOutput_, maxOutput_] 范围内 (输出饱和)。
     *          8. 更新 previousError_ 状态，为下次计算微分项做准备。
     *          9. 返回最终限制后的输出值。
     */
    double update(double error, double dt);

    /**
     * @brief 重置 PID 控制器的内部状态
     * @details 将积分累积项和上一次误差清零，并将控制器置于首次更新状态。
     *          通常在目标值发生较大跳变或需要重新开始控制过程时调用。
     */
    void reset();

    // --- 可选: 动态调整参数的方法 ---
    /** @brief 设置比例增益 Kp */
    void setKp(double Kp);
    /** @brief 设置积分增益 Ki */
    void setKi(double Ki);
    /** @brief 设置微分增益 Kd */
    void setKd(double Kd);
    /** @brief 设置输出上下限 */
    void setOutputLimits(double min, double max);
    /** @brief 设置积分器累积值的上下限 (用于抗饱和) */
    void setIntegratorLimits(double min, double max);
    /** @brief 设置死区范围 */
    void setDeadband(double deadband);


private:
    // --- 控制器参数 ---
    double Kp_; ///< 比例增益
    double Ki_; ///< 积分增益
    double Kd_; ///< 微分增益
    double minOutput_; ///< 输出下限
    double maxOutput_; ///< 输出上限
    double integratorMin_; ///< 积分累积下限
    double integratorMax_; ///< 积分累积上限
    double deadband_;      ///< 死区范围 (误差绝对值)

    // --- 控制器状态 ---
    double integral_;      ///< 积分累积值
    double previousError_; ///< 上一次的误差值 (用于计算微分项)
    bool firstUpdate_;     ///< 标记是否是第一次调用 update 方法
};

#endif // PID_HPP
