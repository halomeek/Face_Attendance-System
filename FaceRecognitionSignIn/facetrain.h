
#ifndef FACETRAIN_H
#define FACETRAIN_H

#include <opencv2/opencv.hpp>
#include <opencv2/face/facerec.hpp>
#include <opencv2/face.hpp>
#include <iostream>

#include <fstream>
#include <sstream>
#include <filesystem>

#include <direct.h>
#include <string>
using namespace cv;
using namespace std;

class FaceTrain
{
public:
    FaceTrain();
    ~FaceTrain();
    void run();
private:
    string csvfname;
    vector<Mat> images;
    vector<int> labels;
};

#endif // FACETRAIN_H
