#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>

int main() {
    // Open default camera
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Cannot open camera" << std::endl;
        return -1;
    }

    // Prepare ArUco dictionary and detector parameters
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
    cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) break;

        std::vector<int> markerIds;
        std::vector<std::vector<cv::Point2f>> markerCorners;
        cv::aruco::detectMarkers(frame, dictionary, markerCorners, markerIds, parameters);

        // Draw detected markers and their IDs
        if (!markerIds.empty()) {
            cv::aruco::drawDetectedMarkers(frame, markerCorners, markerIds);
            std::cout << "Detected IDs: ";
            for (int id : markerIds) std::cout << id << " ";
            std::cout << std::endl;
        }

        cv::imshow("ArUco Detection", frame);
        if (cv::waitKey(1) == 27) break; // Exit on ESC
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}