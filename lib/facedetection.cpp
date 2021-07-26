#include <iostream>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "facedetection.h"

#include "facedetection.h"

using namespace std;
using namespace cv;

void facedetection::FaceDetect(string path)
{
    Mat img = imread(path);
    CascadeClassifier faceCascade;
    faceCascade.load("Resources/haarcascade_frontalface_alt.xml");

    if (faceCascade.empty())
    {
        cerr << "File Haarcascade not loaded" << endl;
    }

    vector<Rect> faces;
    faceCascade.detectMultiScale(img, faces, 1.1, 10);

    for (int i = 0; i < faces.size(); i++)
    {
        rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 255, 0), 3);
    }

    imshow("Face Detection", img);
    waitKey(0);
}
