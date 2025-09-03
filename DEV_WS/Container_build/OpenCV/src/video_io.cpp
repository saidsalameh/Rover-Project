#include "video_io.hpp"

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

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera " << cameraIndex << std::endl;
        return false;
    }

    cv::Mat frame;
    cap >> frame;

    if (frame.empty()) {
        std::cerr << "Error: No frame captured." << std::endl;
        return false;
    }

    if (!cv::imwrite(outputPath, frame)) {
        std::cerr << "Error: Couldn't save image at " << outputPath << std::endl;
        return false;
    }

    std::cout << "Image saved successfully at " << outputPath << std::endl;
    return true;
}