#include "main.hpp"
#include <iostream>
#include <filesystem>

int main(int ac, char** av) {
    cv::CommandLineParser parser(ac, av, "{help h||}{@input||}");
    if (parser.has("help"))
    {
        help(av);
        return 0;
    }
    std::string arg = parser.get<std::string>("@input");
    if (arg.empty()) {
        help(av);
        return 1;
    }
    VideoCapture capture(arg); //try to open string, this will attempt to open it as a video file or image sequence
    if (!capture.isOpened()) //if this fails, try to open as a video camera, through the use of an integer param
        capture.open(atoi(arg.c_str()));
    if (!capture.isOpened()) {
        cerr << "Failed to open the video device, video file or image sequence!\n" << endl;
        help(av);
        return 1;
    }
    return process(capture);
}

/* 
int main() {
    // Create a VideoCapture object
    cv::VideoCapture cap;

    // Try to open the default camera (index 0)
    if (!openCamera(cap, 0)) {
        std::cerr << "Error: Could not open the camera." << std::endl;
        return -1;
    }

    // Stream video
    streamVideo(cap, "Camera Stream");

    return 0;
}

*/


