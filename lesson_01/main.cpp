#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <filesystem>

using namespace cv;
using namespace std;

int main() {
    // 读取图像，展示图像，颜色转换，像素提取，写入图像

    string testImgPath = "./test.png";

    Mat image = imread(testImgPath);
    imshow("demo", image);
    waitKey(0);

    destroyAllWindows();

    Mat image2;
    cvtColor(image, image2, cv::COLOR_BGR2GRAY);

    imwrite("./test2.png", image2);

    Vec3b pixel = image.at<Vec3b>(image.cols - 1, image.rows - 1);
    cout << "Pixel(B, G, R): " << (int) pixel[0] << "," << (int) pixel[1] << "," << (int) pixel[2] << endl;

    return 0;
}
