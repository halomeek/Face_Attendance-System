
#ifndef FACERECOGNITION_H
#define FACERECOGNITION_H

#include <iostream>
#include <string>
#include <direct.h>
#include <opencv2/opencv.hpp>
#include <opencv2/face/facerec.hpp>

#include <filesystem>
#include <map>
#include <ctime>

using namespace std;
using namespace cv;


class FaceRecognition
{
public:
    FaceRecognition();
    ~FaceRecognition();
    Mat getFrame(Mat frame);
    string gettime();
    void init_map();
    int getPredictPCA(Mat frame);
    map<int,string> getMap();
private:
    CascadeClassifier face_cascade_;
    Ptr<face::FaceRecognizer> modelPCA;
    map<int,string> filedn;
};

#endif // FACERECOGNITION_H
