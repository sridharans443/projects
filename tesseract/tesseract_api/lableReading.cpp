#include <opencv2/opencv.hpp>
#include <hikv_camera.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

int main()
{
    HIKVCamera camera;
    Mat src;
    std::string output;
    namedWindow("output",WINDOW_NORMAL);


    camera.openCamera();
    camera.configureCapture(0, 1080, 720, 0, 0, 1, 7, 0, 10, 5);
    camera.startCapture();

    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    api->Init(NULL, "eng",tesseract::OEM_LSTM_ONLY);
    api->SetPageSegMode(tesseract::PSM_AUTO);

    while (true)
    {
        camera.getImage(src);
        imwrite("camImg.png",src);
        Mat img=imread("camImg.png",IMREAD_COLOR);
        api->SetImage(img.data, img.cols, img.rows, 3, img.step);
        api->SetRectangle(30, 86, 590, 100);
        
        cv::rectangle(img,Point(30,86),Point(590,100),Scalar(0,0,255),2);
        output = std::string(api->GetUTF8Text());
        putText(img,output,Point(30,40),FONT_HERSHEY_DUPLEX,2,Scalar(0,0,255),3);
        imshow("output",img);
        std::cout << output << std::endl;
        if(waitKey(27)==27){
            destroyAllWindows();
            break;
        }
    }
    camera.stopCapture();
    camera.closeCamera();
    api->End();
    delete api;


}
