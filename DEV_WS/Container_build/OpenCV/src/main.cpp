#include "main.hpp"
#include "scan.hpp"
#include "video_io.hpp"
#include <iostream>


int main() {
    captureImage(0, "./images/capture.jpg");
    return 0;
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


