#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <filesystem>
#include "main.h"

using namespace cv;
using namespace std;

void ColorSpaceDemo::bgr2rgb(cv::Mat &image) {
    Mat dst;
    cvtColor(image, dst, COLOR_BGR2GRAY);
    imshow("gray", dst);
}

void ColorSpaceDemo::color_range_demo(cv::Mat &image) {
    // RGB to HSV
    Mat hsv;
    cvtColor(image, hsv, COLOR_BGR2HSV);
    imshow("hsv", hsv);

    // RGB to LAB
    Mat lab;
    cvtColor(image, lab, COLOR_BGR2Lab);
    imshow("lab", lab);

    // 提取前景对象
    Mat mask;
    inRange(hsv, Scalar(35, 43, 46), Scalar(99, 255, 255), mask);
    imshow("mask", mask);

    Mat dst;
    bitwise_not(mask, mask);
    bitwise_and(image, image, dst, mask);
    imshow("dst", dst);
}

int main() {
    Mat mat = imread("./img.png");
    ColorSpaceDemo::color_range_demo(mat);
    waitKey(0);
    return 0;
}
