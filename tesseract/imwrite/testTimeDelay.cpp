#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <fstream>

using namespace std;
using namespace cv;

// Use std::chrono::steady_clock for accurate timing
unsigned int time()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

int bmp(Mat src)
{
    unsigned int start = time();
    // std::cout << start << std::endl;

    Mat bitMapSrc = src;
    imwrite("bitMapOut.bmp", bitMapSrc);

    unsigned int endTime = time();
    Mat out = imread("bitMapOut.bmp", IMREAD_COLOR);

    // std::cout << endTime << std::endl;

    int diff = endTime - start;
    // std::cout << "time for bmp " << diff << "ms" << endl;
    return diff;
}

int jpeg(Mat src)
{
    unsigned int start = time();
    // std::cout << start << std::endl;

    Mat jpegMapSrc = src;
    imwrite("jpegOut.jpeg", jpegMapSrc);

    unsigned int endTime = time();
    // std::cout << endTime << std::endl;

    int diff = endTime - start;
    // std::cout << "time for jpeg " << diff << "ms" << endl;
    return diff;
}

int jpg(Mat src)
{
    unsigned int start = time();
    // std::cout << start << std::endl;

    Mat bitMapSrc = src;
    imwrite("jpgOut.jpg", bitMapSrc);

    unsigned int endTime = time();
    // std::cout << endTime << std::endl;

    int diff = endTime - start;
    // std::cout << "time for jpg " << diff << "ms" << endl;
    return diff;
}

int png(Mat src)
{
    unsigned int start = time();
    // std::cout << start << std::endl;

    Mat bitMapSrc = src;
    imwrite("pngOut.png", bitMapSrc);

    unsigned int endTime = time();
    // std::cout << endTime << std::endl;

    int diff = endTime - start;
    // std::cout << "time for png " << diff << "ms" << endl;
    return diff;
}

int main()
{
    Mat src;
    string imgPath = "/home/ubilinux/Desktop/git_workplace/projects/tesseract/imwrite/pngOut_resized.png";
    src=imread(imgPath,IMREAD_COLOR);
    int bmpVals[50] = {};
    int jpegVals[50] = {};
    int jpgVals[50] = {};
    int pngVals[50] = {};

    for (int i = 0; i < 50; i++)
    {
        bmpVals[i] = bmp(src);
        jpegVals[i] = jpeg(src);
        jpgVals[i] = jpg(src);
        pngVals[i] = png(src);
    }
    int bmpAvg = 0;
    int jpegAvg = 0;
    int jpgAvg = 0;
    int pngAvg = 0;

    ifstream f;

    cout << endl
         << "source image" << imgPath << endl;

    for (int x : bmpVals)
    {
        bmpAvg += x;
    }
    string bitOut = "/home/ubilinux/Desktop/git_workplace/projects/tesseract/imwrite/bitMapOut.bmp";
    f.open(bitOut, ios::in);
    f.seekg(0, std::ios::end);
    std::streampos fileSize = f.tellg();
    f.seekg(0, std::ios::beg);
    f.close();

    std::cout << endl
              << "file name bitMapOut.bmp image size " << (float)fileSize / (1000 * 1000) << "MB" << endl
              << " average time to convert " << bmpAvg / 50 << "ms" << endl;

    for (int x : jpegVals)
    {
        jpegAvg += x;
    }
    string jpegOut = "/home/ubilinux/Desktop/git_workplace/projects/tesseract/imwrite/jpegOut.jpeg";
    f.open(jpegOut, ios::in);
    f.seekg(0, std::ios::end);
    fileSize = f.tellg();
    f.seekg(0, std::ios::beg);
    f.close();
    cout << "file name jpegOut.jpeg image size " << (float)fileSize / (1000 * 1000) << "MB" << endl
         << " average time to convert " << jpegAvg / 50 << "ms" << endl;

    for (int x : jpgVals)
    {
        jpgAvg += x;
    }
    string jpgOut = "/home/ubilinux/Desktop/git_workplace/projects/tesseract/imwrite/jpgOut.jpg";
    f.open(jpgOut, ios::in);
    f.seekg(0, std::ios::end);
    fileSize = f.tellg();
    f.seekg(0, std::ios::beg);
    f.close();
    cout << "file name jpgOut.jpg image size " << (float)fileSize / (1000 * 1000) << "MB" << endl
         << " average time to convert " << jpgAvg / 50 << "ms" << endl;

    for (int x : pngVals)
    {
        pngAvg += x;
    }
    string pngOut = "/home/ubilinux/Desktop/git_workplace/projects/tesseract/imwrite/pngOut.png";
    f.open(pngOut, ios::in);
    f.seekg(0, std::ios::end);
    fileSize = f.tellg();
    f.seekg(0, std::ios::beg);
    f.close();
    cout << "file name pngOut.png image size " << (float)fileSize / (1000 * 1000) << "MB" << endl
         << " average time to convert " << pngAvg / 50 << "ms" << endl;

    return 0;
}
