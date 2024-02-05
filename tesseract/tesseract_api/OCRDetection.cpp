#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <tesseract/baseapi.h>

using namespace tesseract;
using namespace std;
using namespace cv;

// int main()
// {
//     string outText;
//     Mat im = imread("/home/ubilinux/Desktop/git_workplace/projects/tesseract/justified_text.png", IMREAD_COLOR);
//     TessBaseAPI *api = new TessBaseAPI();

//     api->Init(NULL, "eng", OEM_DEFAULT);
//     api->SetPageSegMode(PSM_AUTO);
//     api->SetImage(im.data, im.cols, im.rows, 3, im.step);
//     outText = string(api->GetUTF8Text());
//     cout << outText;
//     api->End();
//     delete api;
//     return 0;
// }