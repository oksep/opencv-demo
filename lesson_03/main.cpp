#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <filesystem>
#include "main.h"

using namespace cv;
using namespace std;

// Mat 实例化
void MatDemo::mat_ops() {
    // Mat 介绍

    // 类型与深度
    Mat frame = imread("./test.png");
    cout << frame.type() << endl;
    cout << frame.depth() << endl;

    Rect rect(0, 0, 200, 200);
    Mat roi = frame(rect);

    imshow("src", frame);
    imshow("roi", roi);

    waitKey(0);
    destroyAllWindows();

    // 创建 Mat
    // Vec 是数值向量的模版类 （定义 typedef Vec<int, 3> Vec3i, 操作 v1 = v2 + v3, v2 - 3, v2 * scale, =-v2, +=v2）
    // Scalar 是 Vec 派生的模版类
    Mat m1(4, 4, CV_8UC1, Scalar(255));
    cout << "m1\n" << m1 << endl;

    Mat m2(Size(4, 4), CV_8UC3, Scalar(0, 0, 255));
    cout << "m2\n" << m2 << endl;

    Mat m3(Size(3, 3), CV_8UC3, Scalar::all(255));
    cout << "m3\n" << m3 << endl;

    // matlab style: zeros
    Mat m4 = Mat::zeros(Size(4, 4), CV_8UC3);
    cout << "m4\n" << m4 << endl;

    // matlab style: ones
    Mat m5 = Mat::ones(Size(4, 4), CV_8UC3);
    cout << "m5\n" << m5 << endl;

    // clone
    Mat m6 = m4.clone();
    cout << "m6\n" << m6 << endl;

    // copy
    Mat m7;
    m2.copyTo(m7);
    cout << "m7\n" << m7 << endl;

    // c++ 11 style
    Mat m8 = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cout << "m8\n" << m8 << endl;


    Point pt1(3, 4);
    Point pt2(5, 5);

    Point3d pt3(0, 0, 2);

    Size s(10, 20);

    Rect r(0, 0, 100, 100);

    RotatedRect rr(pt1, s, 90.0);

    cout << pt1 + pt2 << endl;

    cout << norm(pt1) << endl;
}

// Mat 数据遍历
void MatDemo::pixel_visit() {
    Mat src = imread("./test.png");

    int w = src.cols;
    int h = src.rows;
    int cn = src.channels();

    uchar table[256];

    for (int i = 0; i < 256; i++) {
        table[i] = (uchar) (16 * i / 16);
    }

    double t1 = getTickCount();

    // method 1
    for (int row = 0; row < h; row++) {
        for (int col = 0; col < w * cn; col++) {
            int pv = src.at<uchar>(row, col);
            src.at<uchar>(row, col) = table[pv];
        }
    }


    // method 2
    uchar *currentRow;
    for (int row = 0; row < h; row++) {
        currentRow = src.ptr<uchar>(row);
        for (int col = 0; col < w * cn; col++) {
            src.at<uchar>(row, col) = table[currentRow[col]];
        }
    }

    // iterator
    switch (cn) {
        case 1: {
            MatIterator_<uchar> it, end;
            for (it = src.begin<uchar>(), end = src.end<uchar>(); it != end; ++it)
                *it = table[*it];
            break;
        }
        case 3: {
            MatIterator_<Vec3b> it, end;
            for (it = src.begin<Vec3b>(), end = src.end<Vec3b>(); it != end; ++it) {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
        }
    }

    // use data, 使用指针完成遍历
    uchar *image_data = src.data;
    for (int row = 0; row < h; row++) {
        for (int col = 0; col < w * cn; col++) {
            *image_data = table[*image_data];
            image_data++;
        }
    }

    double t2 = getTickCount();
    double t = ((t2 - t1) / getTickFrequency()) * 1000;
    ostringstream ss;
    ss << "Execute time : " << std::fixed << std::setprecision(2) << t << " ms ";
    std::cout << ss.str() << std::endl;
    imshow("result", src);
}

// Mat 算数运算
void MatDemo::arithmetic_operations() {

    Mat a = (Mat_<int>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    Mat b = (Mat_<int>(3, 3) << 9, 8, 7, 6, 5, 4, 3, 2, 1);

    cout << "a\n" << a << endl;
    cout << "b\n" << b << endl;

    Mat add_result, sub_result, mul_result, div_result;

    add(a, b, add_result);
    subtract(a, b, sub_result);
    multiply(a, b, mul_result);
    divide(a, b, div_result);

    cout << "add\n" << add_result << endl;
    cout << "sub\n" << sub_result << endl;
    cout << "mul\n" << mul_result << endl;
    cout << "div\n" << div_result << endl;

    Mat src1 = imread("./windows.png");
    Mat src2 = imread("./linux.jpg");

    add(src1, src2, add_result);
    subtract(src1, src2, sub_result);
    multiply(src1, src2, mul_result);
    divide(src1, src2, div_result);
    imshow("windows", src1);
    imshow("linux", src2);
    imshow("add_result", add_result);
    imshow("sub_result", sub_result);
    imshow("mul_result", mul_result);
    imshow("div_result", div_result);
}

// Mat 位元算
void MatDemo::bitwise_demo() {
    Mat src1 = imread("./windows.png");
    Mat src2 = imread("./linux.jpg");

    cout << "src2\n" << src2 << endl;

    Mat invert_result, and_result, or_result, xor_result;

    // 实心圆
    Mat mask(src1.rows, src2.cols, CV_8UC1, Scalar(0, 0, 0));
    circle(mask, Point(src1.cols / 2, src1.rows / 2), 90, 255, -1);

    imshow("mask", mask);

    // 按位取反 1001 -> 0110
    bitwise_not(src1, invert_result, mask);
    // 按位与 1001 & 1100 -> 1000
    bitwise_and(src1, src2, and_result, mask);
    // 按位或 1001 ｜ 1100 -> 1101
    bitwise_or(src1, src2, or_result, mask);
    // 按位异或 1001 ^ 1100 -> 0101
    bitwise_xor(src1, src2, xor_result, mask);

    imshow("invert_result", invert_result);
    imshow("and_result", and_result);
    imshow("or_result", or_result);
    imshow("xor_result", xor_result);
}

// 调整亮度
void MatDemo::adjust_light(cv::Mat &image) {
    Mat constant_img = Mat::zeros(image.size(), image.type());
    constant_img.setTo(Scalar(50, 50, 50));
    Mat darkMat, lightMat;

    // 亮度增强
    add(image, constant_img, lightMat);
    // 亮度降低
    subtract(image, constant_img, darkMat);

    imshow("raw", image);
    imshow("lightMat", lightMat);
    imshow("darkMat", darkMat);
}

// 调整对比度
void MatDemo::adjust_contrast(cv::Mat &image) {

    // 定义三通道浮点型数据
    Mat constant_img = Mat::zeros(image.size(), CV_32FC3);
    constant_img.setTo(Scalar(0.3, 0.3, 0.3));
    Mat lowContrastMat, highContrastMat;

    // 低对比度
    multiply(image, constant_img, lowContrastMat, 1.0, CV_8U);
    // 高对比度
    divide(image, constant_img, highContrastMat, 1.0, CV_8U);

    imshow("raw", image);
    imshow("lowContrastMat", lowContrastMat);
    imshow("highContrastMat", highContrastMat);
}

// 类型转换
void MatDemo::type_convert(Mat &image) {
    Mat f;
    image.convertTo(f, CV_32F);
    f = f / 255.0;
    imshow("f32", f);
}

// 通道处理
void MatDemo::channels_demo(Mat &image) {

    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    imshow("gray", gray);

    // 通道拆分/取反/合并
    std::vector<Mat> mv;
    split(image, mv);
    for (auto &t: mv) {
        bitwise_not(t, t);
    }
    Mat dst;
    merge(mv, dst);
    imshow("merge channels", dst);

    // 调整数组顺序
    int from_to[] = {0, 2, 1, 1, 2, 0};
    mixChannels(&image, 1, &dst, 1, from_to, 3);
    imshow("mix channels", dst);
}

int main() {
    Mat mat = imread("./test.png");
    MatDemo::channels_demo(mat);
    waitKey(0);
    return 0;
}
