#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    VideoCapture video(0);
    Mat img;
    CascadeClassifier facedetect;
    facedetect.load("haarcascade_frontalface_default.xml");

    while (true)
    {
        video.read(img);

        vector<Rect> faces;

        facedetect.detectMultiScale(img, faces, 1.3, 5);

        cout << faces.size() << endl;

        for (size_t i = 0; i < faces.size(); i++)
        {
            rectangle(img, faces[i].tl(), faces[i].br(), Scalar(50, 50, 255), 3);
            rectangle(img, Point(0, 0), Point(250, 70), Scalar(50, 50, 255), FILLED);
            putText(img, to_string(faces.size()) + " Face Found", Point(10, 40), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 1);
        }

        imshow("Frame", img);
        
        waitKey(1);
        if (waitKey(15) == 27)
        {
            break;
        }
    }
    return 0;
}