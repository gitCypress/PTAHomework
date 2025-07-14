#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
int main() {
    // 1. 加载原始图像
    cv::Mat src_image = cv::imread(R"(D:\Code\C++\PTAHomework\original_capture.jpg)"); // 替换成你的图像路径
    if (src_image.empty()) {
        std::cerr << "Error: Could not load image!" << std::endl;
        return -1;
    }

    auto test = std::make_unique<int>(10);

    // --- 标定过程 ---
    // 2. 定义源点 (原始图像中的梯形区域角点)
    // !!! 这些是示例值，你需要根据你的摄像头和场景进行标定 !!!
    std::vector<cv::Point2f> src_pts;
    src_pts.push_back(cv::Point2f(104, 164));    // 左上角 (靠近图像顶部的左侧点)
    src_pts.push_back(cv::Point2f(215, 164));    // 右上角 (靠近图像顶部的右侧点)
    src_pts.push_back(cv::Point2f(248, 239));  // 右下角 (靠近图像底部的右侧点)
    src_pts.push_back(cv::Point2f(76, 239));    // 左下角 (靠近图像底部的左侧点)
    // 注意：点的顺序必须与 dst_pts 对应

    // 3. 定义目标点 (输出俯视图中的矩形区域角点)
    // 定义输出俯视图的尺寸
    int output_width = 1000;  // 例如，与原始宽度相似
    int output_height = 1000; // 可以根据需要调整，表示俯视的深度范围
    int LHx = 250;
    int LHy = 250;
    int RBx = 750;
    int RBy = 750;
    std::vector<cv::Point2f> dst_pts;
    
    // 映射到输出图像的完整边界
    dst_pts.push_back(cv::Point2f(LHx, LHy));                            // 左上角 -> (0, 0)
    dst_pts.push_back(cv::Point2f(RBx, LHy));             // 右上角 -> (宽度-1, 0)
    dst_pts.push_back(cv::Point2f(RBx, RBy)); // 右下角 -> (宽度-1, 高度-1)
    dst_pts.push_back(cv::Point2f(LHx, RBy));             // 左下角 -> (0, 高度-1)
    // 注意：点的顺序必须与 src_pts 对应

    // 4. 计算透视变换矩阵 M
    cv::Mat M = cv::getPerspectiveTransform(src_pts, dst_pts);
    // 你也可以计算逆矩阵 M_inv = cv::getPerspectiveTransform(dst_pts, src_pts); 用于将俯视坐标转回原始坐标

    // 5. 定义输出图像尺寸
    cv::Size output_size(output_width, output_height);

    // 6. 应用 warpPerspective 进行逆透视变换
    cv::Mat ipm_image; // 用于存储生成的 IPM 图像
    cv::warpPerspective(src_image,        // 输入原始图像
                        ipm_image,        // 输出 IPM 图像
                        M,                // 透视变换矩阵
                        output_size,      // 输出图像尺寸
                        cv::INTER_LINEAR, // 插值方法，线性插值常用
                        cv::BORDER_CONSTANT, // 边界填充模式（可选）
                        cv::Scalar(0,0,0) // 边界填充颜色（可选，黑色）
                       );

    // 7. 显示结果
    cv::namedWindow("Source Image", cv::WINDOW_FREERATIO);
    cv::namedWindow("IPM Image (warpPerspective)", cv::WINDOW_FREERATIO);
    cv::imshow("Source Image", src_image);
    cv::imshow("IPM Image (warpPerspective)", ipm_image);

    while (cv::waitKey(0) != 113){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}