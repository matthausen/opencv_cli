#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#ifndef CPP_CMD_OPENCV_IMGPROC_H
#define CPP_CMD_OPENCV_IMGPROC_H

class Imgproc {
    public:
        void ImageShow(std::string path);
        void VideoCapture();
        void Resize(std::string path, double width, double height);
        void DocScan(std::string path);

    private:
        cv::Mat preProcess(cv::Mat image);
        std::vector<cv::Point> getContours(cv::Mat image);
        void drawPoints(std::vector<cv::Point> points, cv::Scalar color);
        std::vector<cv::Point> reorder(std::vector<cv::Point> points);
        cv::Mat warp(cv::Mat img, std::vector<cv::Point> points, float width, float heigth);
};


#endif //CPP_CMD_OPENCV_IMGPROC_H
