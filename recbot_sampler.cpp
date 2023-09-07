
#include <iostream>
#include <filesystem>

#include <opencv2/core/utils/logger.hpp>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/face/mace.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

#define CAMERA_INDEX 0

int main(int, char**) {
    // disable info and harmless warnings coming from opencv
    utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

    CascadeClassifier face_detector;
    face_detector.load(samples::findFile("haarcascades/haarcascade_frontalface_alt.xml"));
    
    VideoCapture cam;
    cam.open(CAMERA_INDEX, cv::CAP_ANY);
     if (!cam.isOpened()) {
        std::cerr << "Error! Cam Not Found!";
        return -1;
     }
    
    Mat frame;
    vector<Rect> faces;

    if( ! filesystem::exists("./dataset/")){        
        filesystem::create_directory("./dataset/");
    }
    string filePrefix = "./dataset/face_";
    int count = 0;
    do{
        cam.read(frame);
        if (frame.empty()) {
            std::cerr << "Error! Frame Empty!";
            return false;
        }

        face_detector.detectMultiScale( frame, faces, 1.1, 2, 
        CASCADE_SCALE_IMAGE|CASCADE_FIND_BIGGEST_OBJECT,  
        Size(100, 100));

        for (auto r: faces) {
            imwrite(filePrefix + to_string(count) + ".jpg", 
                frame(Range(r.y,r.y+r.height),Range(r.x,r.x+r.width)));

            rectangle( frame, Point(cvRound(r.x), cvRound(r.y)),
                Point(cvRound((r.x + r.width-1)), cvRound((r.y + r.height-1))),
                 Scalar(255,0,0), 3, 8, 0);            
            count ++;
        }
        // wait 100ms between samples
        waitKey(100);
        imshow("Samples", frame);

    }while (count < 10);

    return 0;
}