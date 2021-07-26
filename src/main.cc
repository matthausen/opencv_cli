
#include <iostream>
#include <string>
#include "../lib/cli.hpp"
#include "../lib/imgproc.hpp"

int main(int argc, char *argv[])
{
    Cli cli;

    std::string cmd = argv[1];
    std::string imgPath = argv[2];
//    std::string widthArg = argv[3];
//    std::string heightArg = argv[4];
//
//    std::string::size_type sz;
//    double width = std::stod(widthArg, &sz);
//    double height = std::stod(heightArg, &sz);

    if (cmd == "--help" || cmd == "-h")
    {
        cli.PrintHelp();
    };

    if (cmd == "--view" || cmd == "-v")
    {
        cli.View(imgPath);
    };

//    if (cmd == "--resize" || cmd == "-r")
//    {
//        cli.Resize(imgPath, width, height);
//    };

    if (cmd == "--docscan" || cmd == "-d")
    {
        cli.DocScan(imgPath);
    };

    if (cmd == "--facedetect" || cmd == "-fd")
    {
        cli.FaceDetect(imgPath);
    };

    return 0;
}