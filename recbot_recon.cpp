
#include <iostream>
#include <filesystem>
#include <cstdlib>

#include <opencv2/core/utils/logger.hpp>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/face/mace.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

#define MODEL_FILE "./model/face_recognition_sface_2021dec.onnx"
#define MODEL_COS_THRESHOLD 0.363f

#define CAMERA_INDEX 0

int main(int, char**) {
    // disable info and harmless warnings coming from opencv
    utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);
    
    CascadeClassifier face_detector;
    face_detector.load(samples::findFile("haarcascades/haarcascade_frontalface_alt.xml"));
    
    Ptr<FaceRecognizerSF> faceRecognizer = FaceRecognizerSF::create(MODEL_FILE, "");
    
    vector<Mat> frame_features;
    Mat frame_feature, frame;

    for (const auto & entry : filesystem::directory_iterator("./dataset/")){
        frame = imread(filesystem::absolute(entry.path()));
        
        faceRecognizer->feature(frame, frame_feature);
        frame_feature = frame_feature.clone();
        frame_features.push_back(frame_feature);        
    }


    VideoCapture cam;
    cam.open(CAMERA_INDEX, cv::CAP_ANY);
     if (!cam.isOpened()) {
        std::cerr << "Error! Frame Not Found!";
        return -1;
     }
    
    vector<Rect> faces;
    
    bool detected = false;
    int count = 0;
    do{
        cam.read(frame);        
        
        if (frame.empty()) {
            std::cerr << "Error! Frame Not Found!";
            return false;
        }
        
        face_detector.detectMultiScale( frame, faces, 1.1, 2, 
        CASCADE_SCALE_IMAGE|CASCADE_DO_ROUGH_SEARCH|CASCADE_FIND_BIGGEST_OBJECT,  
        Size(100, 100));

        for (auto r: faces) {
            
            faceRecognizer->feature(frame(Range(r.y,r.y+r.height),Range(r.x,r.x+r.width)), frame_feature);
            frame_feature = frame_feature.clone();

            for (auto &ffs : frame_features){
                double cos_score = faceRecognizer->match(ffs, frame_feature, FaceRecognizerSF::DisType::FR_COSINE);
                if(cos_score > MODEL_COS_THRESHOLD){
                    detected = true;
                    break;
                }

            }

        }

        count ++;

        // use 5 samples at most
    }while (count < 5 && !detected);
    cam.release();

    if(detected){
        cout << "PASS" << endl;
        return 0;
    }else{
        cerr << "FAIL" << endl;
        return 1;
    }

}