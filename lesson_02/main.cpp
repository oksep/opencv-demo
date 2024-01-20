#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <filesystem>

using namespace cv;
using namespace std;

int main() {

    // 打开摄像头
    // VideoCapture capture(0);

    // 打开文件
    VideoCapture capture;
    capture.open("./test.mp4", CAP_ANY);

    if (!capture.isOpened()) {
        cout << "Video Capture is not opened" << endl;
        return 1;
    }

    const int width = 640;
    const int height = 480;

    capture.set(CAP_PROP_FRAME_WIDTH, width);
    capture.set(CAP_PROP_FRAME_HEIGHT, height);

    Mat frame;

    VideoWriter writer(
            "./record.mp4",
            VideoWriter::fourcc('H', '2', '6', '4'),
            20,
            Size()
    );

    while (true) {
        bool ret = capture.read(frame);

        if (!ret) {
            cout << "end" << endl;
            break;
        }

        flip(frame, frame, 1);

        imshow("video capture", frame);

        writer.write(frame);

        int k = waitKey(30);

        if (k == 27) {
            cout << "exit" << endl;
            break;
        }
    }

    capture.release();
    writer.release();

    destroyAllWindows();

    return 0;
}
