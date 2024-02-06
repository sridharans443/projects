#include <opencv2/opencv.hpp>
#include <hikv_camera.hpp>

int main()
{
    HIKVCamera camera;

    camera.openCamera(0);
    camera.configureCapture(0, 8000, 3000, 0, 0, 0, 5, 0, 255, 0);
    camera.startCapture();
    Mat src;
    namedWindow("output", WINDOW_NORMAL);

    // while ((true))
    // {
        camera.getImage(src);
        imwrite("pngOut.jpeg",src);
        imshow("output", src);
        if (waitKey(27) == 27)
        {
            camera.~HIKVCamera();
            destroyAllWindows();
        }
    // }
}
