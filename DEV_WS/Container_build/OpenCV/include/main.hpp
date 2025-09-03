#ifndef MAIN_H
#define MAIN_H

#include <opencv2/opencv.hpp>
#include <string>

// Function declarations
bool openCamera(cv::VideoCapture &cap, int cameraIndex = 0);
void streamVideo(cv::VideoCapture &cap, const std::string &windowName);

#endif // MAIN_H

