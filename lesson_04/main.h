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

class ColorSpaceDemo {
public:
    static void bgr2rgb(Mat &image);

    static void color_range_demo(Mat &image);
};


#endif //DEMO_MAIN_H
