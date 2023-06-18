
#include "facerecognition.h"

FaceRecognition::FaceRecognition()
{
    face_cascade_.load("..\\haarcascades\\haarcascade_frontalface_alt.xml");
    modelPCA = face::EigenFaceRecognizer::create();
    modelPCA->read("..\\model\\MyFacePCAModel.xml");
    init_map();
}

FaceRecognition::~FaceRecognition(){}

string FaceRecognition::gettime()
{   string times;
    time_t rawtime;
    struct tm *ptminfo;
    time(&rawtime);
    ptminfo = localtime(&rawtime);
    times= to_string(ptminfo->tm_year + 1900)+"-"
            + to_string(ptminfo->tm_mon + 1)+"-"
            + to_string(ptminfo->tm_mday)+" "
            + to_string(ptminfo->tm_hour)+":"
            + to_string(ptminfo->tm_min)+":"
            + to_string(ptminfo->tm_sec);
    return times;
}

void FaceRecognition::init_map(){
    int key=0;
    string filen;
    for (auto& i : filesystem::directory_iterator("..\\ORL_Faces\\")){
        if(i.is_directory()){
            filen=i.path().string().substr(i.path().string().find_last_of("\\/")+1);
            if(filen.find_last_of("_")<=filen.size()){
                filen=filen.substr(filen.find_last_of("_")+1);
            }
            filedn.insert(map<int,string>::value_type(key,filen));
            key++;
        }
    }
}

Mat FaceRecognition::getFrame(Mat frame){

    int predictPCA = 0;

    if (frame.empty())
    {
        cerr << "ERROR: Blank frame." << endl;
    }

    // ½«Í¼Ïñ×ª»»Îª»Ò¶ÈÍ¼
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    equalizeHist(gray,gray);
    // ¼ì²âÈËÁ³
    vector<Rect> faces;
    face_cascade_.detectMultiScale(gray, faces);
    Mat face;
    Point text_lb;


    face = gray(faces[0]);
    text_lb = Point(faces[0].x, faces[0].y);

    rectangle(frame, faces[0], Scalar(0, 255, 0), 3);


    Mat face_test;


    resize(face, face_test, Size(92, 112));


    if (!face_test.empty())
    {
        //²âÊÔÍ¼ÏñÓ¦¸ÃÊÇ»Ò¶ÈÍ¼
        predictPCA = modelPCA->predict(face_test);
    }

    putText(frame, filedn[predictPCA], text_lb, FONT_HERSHEY_COMPLEX, 2, Scalar(0, 0, 255),3);

    return frame;
}

int FaceRecognition::getPredictPCA(Mat frame){
    int predictPCA = 0;

    if (frame.empty())
    {
        cerr << "ERROR: Blank frame." << endl;
    }

    // ½«Í¼Ïñ×ª»»Îª»Ò¶ÈÍ¼
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    equalizeHist(gray,gray);
    // ¼ì²âÈËÁ³
    vector<Rect> faces;
    face_cascade_.detectMultiScale(gray, faces);
    Mat face;

    face = gray(faces[0]);

    Mat face_test;

    resize(face, face_test, Size(92, 112));

    if (!face_test.empty())
    {
        //²âÊÔÍ¼ÏñÓ¦¸ÃÊÇ»Ò¶ÈÍ¼
        predictPCA = modelPCA->predict(face_test);
    }else{
        return -1;
    }

    return predictPCA;
}

map<int,string> FaceRecognition::getMap(){
    return filedn;
}
