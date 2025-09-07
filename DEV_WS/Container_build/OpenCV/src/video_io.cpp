#include "video_io.hpp"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <stdio.h>

bool openCamera(cv::VideoCapture &cap, int cameraIndex) {
    cap.open(cameraIndex);

    if (!cap.isOpened()) {
        return false;
    }

    // Optionally set resolution (e.g., 640x480)
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    return true;
}

void streamVideo(cv::VideoCapture &cap, const std::string &windowName) {
    cv::Mat frame;

    while (true) {
        cap >> frame; // Capture frame

        if (frame.empty()) {
            std::cerr << "Error: Empty frame grabbed." << std::endl;
            break;
        }

        // Show frame
        cv::imshow(windowName, frame);

        // Exit when 'q' is pressed
        char key = (char) cv::waitKey(30);
        if (key == 'q' || key == 27) { // 'q' or ESC
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
}
bool captureImage(int cameraIndex, const std::string &outputPath) {
    cv::VideoCapture cap(cameraIndex);
    std::cout << "1 " << std::endl;

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera " << cameraIndex << std::endl;
        return false;
    }

    std::cout << "2 " << std::endl;
    cv::Mat frame;
    for (int i = 0; i < 5; i++) {
        cap >> frame; // grab a few frames for auto-exposure
    }

    cap.release();
    std::cout << "3 " << std::endl;

    if (frame.empty()) {
        std::cerr << "Error: No frame captured." << std::endl;
        return false;
    }

    std::filesystem::path outPath(outputPath);
    std::string ext = outPath.extension().string();

    if (ext != ".jpg" && ext != ".png" && ext != ".bmp") {
        std::cerr << "Error: unsupported file format." << std::endl;
        return false;
    }

    if (!cv::imwrite(outputPath, frame)) {
        std::cerr << "Error: Couldn't save image at " << outputPath << std::endl;
        return false;
    }

    std::cout << "Image saved successfully at " << outputPath << std::endl;
    return true;
}


using namespace cv;
using namespace std;

//hide the local functions in an anon namespace
namespace {
    void help(char** av) {
        cout << "The program captures frames from a video file, image sequence (01.jpg, 02.jpg ... 10.jpg) or camera connected to your computer." << endl
             << "Usage:\n" << av[0] << " <video file, image sequence or device number>" << endl
             << "q,Q,esc -- quit" << endl
             << "space   -- save frame" << endl << endl
             << "\tTo capture from a camera pass the device number. To find the device number, try ls /dev/video*" << endl
             << "\texample: " << av[0] << " 0" << endl
             << "\tYou may also pass a video file instead of a device number" << endl
             << "\texample: " << av[0] << " video.avi" << endl
             << "\tYou can also pass the path to an image sequence and OpenCV will treat the sequence just like a video." << endl
             << "\texample: " << av[0] << " right%%02d.jpg" << endl;
    }

    int process(VideoCapture& capture) {
        int n = 0;
        char filename[200];
        string window_name = "video | q or esc to quit";
        cout << "press space to save a picture. q or esc to quit" << endl;
        namedWindow(window_name, WINDOW_KEEPRATIO); //resizable window;
        Mat frame;

        for (;;) {
            capture >> frame;
            if (frame.empty())
                break;

            imshow(window_name, frame);
            char key = (char)waitKey(30); //delay N millis, usually long enough to display and capture input

            switch (key) {
            case 'q':
            case 'Q':
            case 27: //escape key
                return 0;
            case ' ': //Save an image
                snprintf(filename,sizeof(filename),"filename%.3d.jpg",n++);
                imwrite(filename,frame);
                cout << "Saved " << filename << endl;
                break;
            default:
                break;
            }
        }
        return 0;
    }
}