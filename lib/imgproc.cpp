#include "imgproc.hpp"
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

Mat imgOriginal, imgGray, imgBlur, imgCanny, imgThreshold, imgDil, imgWarp;
vector<Point> initialPoints, docPoints;

float w = 3024, h = 4032;

void Imgproc::ImageShow(std::string path)
{
    std::cout << path << std::endl;

    Mat img = cv::imread(path);
    if (img.empty()) {
        std::cerr << "Image not found\n";
    }

    imshow("Image", img);
    waitKey(0);
}

// Resize -> resize image to specified size
void Imgproc::Resize(string path, double width, double height)
{
    Mat img = imread(path);
    resize(img, img,Size(),width,height);

    imshow("resized image", img);
    waitKey(0);
}

// VideoCapture -> show webcam video frame by frame
void Imgproc::VideoCapture()
{
    class VideoCapture cap(0);
    Mat frame;

    while(true)
    {
        cap.read(frame);

        imshow("frame", frame);
        if (frame.empty()) {
            std::cerr << "Cannot read frame\n";
        }
        waitKey(1);
    }
}

// DocScan -> scan a document
void Imgproc::DocScan(std::string path)
{
    Mat img = imread( path);
    imgOriginal = img;
    //resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);

    imgThreshold = preProcess(imgOriginal);
    initialPoints = getContours(imgThreshold);
    docPoints = reorder(initialPoints);
    drawPoints(docPoints, Scalar(0,255,0));
    imgWarp = warp(imgOriginal, docPoints, w, h);

    imshow("Image Original", imgOriginal);
    imshow("Image Dilate", imgThreshold);
    imshow("Image warp", imgWarp);
    waitKey(0);
}

/*
 * Private methods
 */

// preProcess -> pre process image for document scan
Mat Imgproc::preProcess(Mat img)
{
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, imgCanny, 25, 75);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDil, kernel);

    return imgDil;
}

// getContours -> get contours of an image for doc scanning
vector<Point> Imgproc::getContours(Mat img)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());

    vector<Point> biggest;
    int maxArea;

    for (int i =0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        cout << area << endl;

        string objectType;
        if (area >  1000)
        {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);


            if (area > maxArea && conPoly[i].size() == 4)
            {
                biggest = {conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3]};
                maxArea = area;
            }

            drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 2);
        }
    }
    return biggest;
}

// drawPoints -> show points on contour
void Imgproc::drawPoints(vector<Point> points, Scalar color)
{
    for (int i = 0; i < points.size(); i++)
    {
        circle(imgOriginal, points[i], 10, color, FILLED);
        putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color, 4);
    };
}

// reorder -> reorder edges of documents
vector<Point> Imgproc::reorder(vector<Point> points)
{
    vector<Point> newPoints;
    vector<int> sumPoints, subPoints;

    for (int i = 0; i < 4; i++)
    {
        sumPoints.push_back(points[i].x + points[i].y);
        subPoints.push_back(points[i].x + points[i].y);
    }

    newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // point 0
    newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // point 1
    newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // point 2
    newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // point 3

    return newPoints;
}

//warp -> warp the image given reordered contour points
Mat Imgproc::warp(Mat img, vector<Point> points, float w, float h)
{
    Point2f src[4] = {points[0], points[1], points[2], points[3]};
    Point2f dst[4] = { {0.0f,0.0f}, {w,0.0f}, {0.0f,h}, {w,h}};

    Mat matrix = getPerspectiveTransform(src, dst);
    warpPerspective(img, imgWarp, matrix, Point(w, h));

    return imgWarp;
}