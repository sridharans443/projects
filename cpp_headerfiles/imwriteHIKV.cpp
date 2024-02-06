#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <fstream>
#include <hikv_camera.hpp>

using namespace std;
using namespace cv;

unsigned int time()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

int main()
{
    Mat cam;

    HIKVCamera camera;

    camera.openCamera();
    camera.configureCapture(0, 1080, 720, 0, 0, 0, 5, 0, 255, 0);

    camera.startCapture();

    int avgTime[50] = {};
    unsigned int start, endTime;
    int diff;
    for (int i = 0; i < 50; i++)
    {
        camera.getImage(cam);
        start = time();
        imwrite("srcOut.jpg", cam);
        endTime = time();

        diff = endTime - start;

        avgTime[i] = diff;

        if (waitKey(27) == 27)
        {
            camera.~HIKVCamera();
            destroyAllWindows();
        }
        Mat src = imread("srcOut.jpg", IMREAD_COLOR);
        namedWindow("output", WINDOW_FREERATIO);
        imshow("output", src);
    }
    camera.~HIKVCamera();
    destroyAllWindows();

    ifstream f;

    string fSize = "/home/ubilinux/Desktop/git_workplace/projects/cpp_headerfiles/srcOut.jpg";
    f.open(fSize, ios::in);
    f.seekg(0, std::ios::end);
    std::streampos fileSize = f.tellg();
    f.seekg(0, std::ios::beg);
    f.close();

    int sum = 0;
    for (int x : avgTime)
    {
        sum += x;
    }
    std::cout << endl
              << " image size " << (float)fileSize / (1000 * 1000) << "MB" << endl
              << " average time to convert " << sum / 50 << "ms" << endl;
}