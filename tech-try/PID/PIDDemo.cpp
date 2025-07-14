#include "PID.hpp"
#include <iostream>
#include <vector>
#include <chrono>   // For time measurement
#include <thread>   // For simulating loop delay (sleep)
#include <random>   // For simulating sensor noise
#include <cmath>    // For std::sin, std::cos, std::sqrt

// --- Simulation Helper Functions ---

// 模拟从 Realsense/YOLO 获取相对位置 (带噪声)
Vector3d get_simulated_relative_position(const Vector3d& drone_pos, const Vector3d& target_pos) {
    // 静态变量用于随机数生成器，只初始化一次
    static std::random_device rd;
    static std::mt19937 gen(rd());
    // 模拟传感器噪声，均值为0，标准差为 0.01 米
    static std::normal_distribution<> noise_dist(0.0, 0.01);

    Vector3d relative_pos;
    relative_pos.x = (target_pos.x - drone_pos.x) + noise_dist(gen);
    relative_pos.y = (target_pos.y - drone_pos.y) + noise_dist(gen);
    relative_pos.z = (target_pos.z - drone_pos.z) + noise_dist(gen);
    return relative_pos;
}

// 模拟应用速度指令更新无人机位置
Vector3d apply_velocity_command(const Vector3d& current_pos, const Vector3d& velocity_cmd, double dt) {
    Vector3d next_pos;
    next_pos.x = current_pos.x + velocity_cmd.x * dt;
    next_pos.y = current_pos.y + velocity_cmd.y * dt;
    next_pos.z = current_pos.z + velocity_cmd.z * dt;
    return next_pos;
}

// 获取两次循环之间的时间间隔 (delta time)
double get_dt(std::chrono::steady_clock::time_point& last_time) {
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = now - last_time;
    last_time = now;
    return elapsed.count();
}

// --- Main Simulation ---

int main() {
    // --- Simulation Parameters ---
    const double SIMULATION_TIME_S = 20.0; // 模拟总时长 (秒)
    const double LOOP_RATE_HZ = 30.0;     // 控制循环频率 (Hz)
    const double DT_TARGET = 1.0 / LOOP_RATE_HZ; // 目标时间间隔

    Vector3d drone_position = {0.0, 0.0, 1.0};   // 无人机初始位置 (米)
    Vector3d target_position = {2.0, 1.0, 1.5}; // 目标初始位置 (米)
    Vector3d previous_velocity_command = {0, 0, 0}; // 上一次的速度指令

    // --- PID and Filter Initialization ---
    // 滤波器参数 (alpha 越小越平滑)
    double filter_alpha = 0.6;
    LowPassFilter filterX(filter_alpha);
    LowPassFilter filterY(filter_alpha);
    LowPassFilter filterZ(filter_alpha);

    // PID 参数 (这些值需要根据实际系统仔细整定！)
    // Kp, Ki, Kd, minOutput, maxOutput, minIntegral, maxIntegral, deadband
    PIDController pidX(1.2, 0.1, 0.05, -1.5, 1.5, -0.5, 0.5, 0.02);
    PIDController pidY(1.2, 0.1, 0.05, -1.5, 1.5, -0.5, 0.5, 0.02);
    PIDController pidZ(1.5, 0.2, 0.08, -1.0, 1.0, -0.4, 0.4, 0.03);

    // 平滑处理参数 (最大速度变化率 m/s^2)
    double max_rate_xy = 3.0;
    double max_rate_z = 2.0;

    // --- Simulation Loop ---
    auto last_update_time = std::chrono::steady_clock::now();
    double current_time = 0.0;

    std::cout << "Time (s), Drone X, Drone Y, Drone Z, Target X, Target Y, Target Z, Error X, Error Y, Error Z, Cmd Vx, Cmd Vy, Cmd Vz" << std::endl;

    while (current_time < SIMULATION_TIME_S) {
        // 1. 计算实际时间间隔 dt
        double dt = get_dt(last_update_time);
        current_time += dt;

        // 2. 模拟目标移动 (例如: 简单的圆周运动)
        double target_move_speed = 0.2;
        target_position.x = 2.0 + 0.5 * std::cos(target_move_speed * current_time);
        target_position.y = 1.0 + 0.5 * std::sin(target_move_speed * current_time);
        // target_position.z 不变

        // 3. 获取模拟的相对位置 (即误差, 带噪声)
        Vector3d relative_pos_raw = get_simulated_relative_position(drone_position, target_position);

        // 4. 滤波 (减少噪声影响)
        double filtered_error_x = filterX.update(relative_pos_raw.x);
        double filtered_error_y = filterY.update(relative_pos_raw.y);
        double filtered_error_z = filterZ.update(relative_pos_raw.z);

        // 5. PID 计算 (获取原始速度指令)
        double vx_raw = pidX.update(filtered_error_x, dt);
        double vy_raw = pidY.update(filtered_error_y, dt);
        double vz_raw = pidZ.update(filtered_error_z, dt);

        // 6. 平滑处理 (速率限制)
        double vx_smoothed = std::clamp(vx_raw,
                                        previous_velocity_command.x - max_rate_xy * dt,
                                        previous_velocity_command.x + max_rate_xy * dt);
        double vy_smoothed = std::clamp(vy_raw,
                                        previous_velocity_command.y - max_rate_xy * dt,
                                        previous_velocity_command.y + max_rate_xy * dt);
        double vz_smoothed = std::clamp(vz_raw,
                                        previous_velocity_command.z - max_rate_z * dt,
                                        previous_velocity_command.z + max_rate_z * dt);

        // 7. 得到最终的速度指令
        Vector3d velocity_command = {vx_smoothed, vy_smoothed, vz_smoothed};

        // 8. 应用速度指令更新无人机位置 (模拟执行)
        drone_position = apply_velocity_command(drone_position, velocity_command, dt);

        // 9. 记录和打印信息 (可以输出到 CSV 文件以便绘图分析)
        printf("%.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f\n",
               current_time,
               drone_position.x, drone_position.y, drone_position.z,
               target_position.x, target_position.y, target_position.z,
               relative_pos_raw.x, relative_pos_raw.y, relative_pos_raw.z, // 可以打印滤波前后误差对比
               velocity_command.x, velocity_command.y, velocity_command.z);

        // 10. 更新状态
        previous_velocity_command = velocity_command;

        // 11. 模拟循环延时，保持大致的循环频率
        auto process_time = std::chrono::steady_clock::now() - last_update_time; // last_update_time 在 get_dt 更新了
        std::chrono::duration<double> sleep_duration(DT_TARGET - process_time.count());
        if (sleep_duration.count() > 0) {
            std::this_thread::sleep_for(sleep_duration);
        } else {
            // 如果处理时间超过目标间隔，可能需要警告
            // std::cerr << "Warning: Loop took longer than target DT!" << std::endl;
        }
        // 更新 last_update_time 以准备下一次 dt 计算 (因为 sleep 之后时间又过去了)
        // last_update_time = std::chrono::steady_clock::now(); // 这句不需要，因为 get_dt 每次开始会更新
    }

    std::cout << "Simulation finished." << std::endl;

    return 0;
}
