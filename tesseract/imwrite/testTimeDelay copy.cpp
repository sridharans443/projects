#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int time()
{
    unsigned int start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return start;
}

void bmp()
{
    unsigned int start = time();
    // std::cout << start << std::endl;

    Mat bitMapSrc = imread("flower.bmp", IMREAD_COLOR);
    imwrite("bitMapOut.bmp", bitMapSrc);

    unsigned int endTime = time();
    // std::cout << endTime << std::endl;

    int diff = endTime - start;
    std::cout << "time for bmp in milli second " << diff << endl;
}

void jpeg()
{
    unsigned int start = time();
    // std::cout << start << std::endl;

    Mat jpegMapSrc = imread("car.jpeg", IMREAD_COLOR);
    imwrite("jpegOut.jpeg", jpegMapSrc);

    unsigned int endTime = time();
    // std::cout << endTime << std::endl;

    int diff = endTime - start;
    std::cout << "time for jpeg in milli second " << diff << endl;
}

void jpg()
{
    unsigned int start = time();
    // std::cout << start << std::endl;

    Mat bitMapSrc = imread("camp.jpg", IMREAD_COLOR);
    imwrite("jpgMapOut.jpg", bitMapSrc);

    unsigned int endTime = time();
    // std::cout << endTime << std::endl;

    int diff = endTime - start;
    std::cout << "time for jpg in milli second " << diff << endl;
}
int main()
{
    // bmp();
    // jpeg();
    // jpg();
    unsigned int start = time();
    // std::cout << start << std::endl;

    Mat bitMapSrc = imread("camp.jpg", IMREAD_COLOR);
    imwrite("jpgMapOut.png", bitMapSrc);

    unsigned int endTime = time();
    // std::cout << endTime << std::endl;

    int diff = endTime - start;
    std::cout << "time for jpg in milli second " << diff << endl;
    return 0;
}