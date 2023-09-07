
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/face/mace.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    
    CascadeClassifier face_detector;
    face_detector.load(samples::findFile("haarcascades/haarcascade_frontalface_alt.xml"));
    VideoCapture cam;
    cam.open(0, cv::CAP_ANY);
     if (!cam.isOpened()) {
        std::cerr << "Error! Cam Not Found!";
        return -1;
     }
    
    Mat frame;
    vector<Rect> faces;
    do{
        cam.read(frame);
        
        if (frame.empty()) {
            std::cerr << "Error! Frame Empty!";
            return -1;
        }
        face_detector.detectMultiScale( frame, faces, 1.1, 2, 
        CASCADE_SCALE_IMAGE|CASCADE_DO_ROUGH_SEARCH|CASCADE_FIND_BIGGEST_OBJECT,  
        Size(100, 100));

        for (auto r: faces) {
             rectangle( frame, Point(cvRound(r.x), cvRound(r.y)),
                Point(cvRound((r.x + r.width-1)), cvRound((r.y + r.height-1))),
                 Scalar(255,0,0), 3, 8, 0);
        }

        imshow("samples", frame);

    }while (waitKey(50) != 'q');

    return 0;
}