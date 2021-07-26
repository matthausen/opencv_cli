#include <iostream>
#include "cli.hpp"
#include "imgproc.hpp"
#include "facedetection.h"

/* 
* The cli commands are
* --help or -h -> prints description + all possible commands
* --resize or -r -> resize image. Usage: cli --resize [path/to/image.jpeg] [200(width) 200(height)]
* --docscan or -d -> warps and generate a scan of a document. Usage: cli --docscan [/path/to/file.jpg]
* --face or -f -> detects face in a photo. Usage: cli --face [/path/to/file.jpg]
*/

// PrintHelp -> prints all options and commands
void Cli::PrintHelp()
{
    std::cout << "To start, type:\ncli --command [required] path_to_file [optional] width X height [optional]" << std::endl;
}

// View -> view the image from specified path
void Cli::View(std::string path)
{
    Imgproc processor;
    processor.ImageShow(path);
}

// ResizeImage() -> resize image to width and height specified
void Cli::Resize(std::string path, double width, double height)
{
    Imgproc processor;
    processor.Resize(path, width, height);
}

// DocScan -> scan document
void Cli::DocScan(std::string path)
{
    Imgproc processor;
    processor.DocScan(path);
}

// FaceDetect -> detect face given an image path
void Cli::FaceDetect(std::string path)
{
    facedetection faceDetection;
    faceDetection.FaceDetect(path);
}
