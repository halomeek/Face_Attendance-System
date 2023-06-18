
#ifndef FACEGET_H
#define FACEGET_H

#include <string>
#include <opencv2/opencv.hpp>
#include <direct.h>

using namespace std;
using namespace cv;

class FaceGet
{
public:
    FaceGet();
    ~FaceGet();
    Mat getFrame(Mat frame);
    void savePic(string name,int face_count,Mat frame);
private:
    CascadeClassifier face_cascade_;
};

#endif // FACEGET_H
