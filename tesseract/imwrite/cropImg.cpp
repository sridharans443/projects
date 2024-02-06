#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat src=imread("pngOut.jpg",IMREAD_COLOR);
    Mat out;
    resize(src,out,Size(1080,720));
    imwrite("pngOut_resized.jpg",out);

}