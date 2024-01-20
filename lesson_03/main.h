//
// Created by Sep on 2024/1/21.
//

#ifndef DEMO_MAIN_H
#define DEMO_MAIN_H

#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class MatDemo {
public:
    static void mat_ops();

    static void pixel_visit();

    static void arithmetic_operations();

    static void bitwise_demo();

    static void type_convert(Mat &image);

    static void adjust_contrast(Mat &image);

    static void adjust_light(Mat &image);

    static void channels_demo(Mat &image);
};

#endif //DEMO_MAIN_H
