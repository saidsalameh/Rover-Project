#ifndef VIDEO_IO_H
#define VIDEO_IO_H

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <filesystem>


bool openCamera(cv::VideoCapture &cap, int cameraIndex);
void streamVideo(cv::VideoCapture &cap, const std::string &windowName);
bool captureImage(int cameraIndex, const std::string &outputPath);

#endif