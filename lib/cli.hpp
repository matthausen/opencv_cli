#include <iostream>

class Cli {
    public:
        void PrintHelp();
        void View(std::string path);
        void Resize(std::string path, double width, double height);
        void DocScan(std::string path);
        void FaceDetect(std:: string path);
};