
#include "facetrain.h"
static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels);
FaceTrain::FaceTrain()
{
    csvfname="..\\ORL_Faces\\at.txt";

}

FaceTrain::~FaceTrain(){}

void FaceTrain::run(){

    //生成at.txt文件
    ofstream outFile(csvfname,ios::out);
    int countfiles=0;
    for(auto& i : filesystem::directory_iterator("..\\ORL_Faces\\")){
        if(i.is_directory()){
            for(auto& j : filesystem::directory_iterator(i)){
                outFile<<j.path().string()<<" "<<countfiles<<endl;
            }
            countfiles++;
        }
    }
    outFile.close();
    cout<<"ORL_Faces目录索引文件生成完毕"<<endl;
    cout<<"读取图像中"<<endl;
    read_csv(csvfname,images,labels);
    cout<<"读取完毕"<<endl;
    cout<<"开始训练人脸识别模型"<<endl;
    Mat testSample = images[labels.size() - 1];
    int testLabel = labels[labels.size() - 1];

    images.pop_back();
    labels.pop_back();

    Ptr<face::FaceRecognizer> model = face::EigenFaceRecognizer::create();
    model->train(images, labels);
    model->write("..\\model\\MyFacePCAModel.xml");

//    Ptr<face::FaceRecognizer> model1 = face::FisherFaceRecognizer::create();
//    model1->train(images, labels);
//    model1->write("..\\model\\MyFaceFisherModel.xml");

//    Ptr<face::FaceRecognizer> model2 = face::LBPHFaceRecognizer::create();
//    model2->train(images, labels);
//    model2->write("..\\model\\MyFaceLBPHModel.xml");



    // 下面对测试图像进行预测，predictedLabel是预测标签结果
    int predictedLabel = model->predict(testSample);
//    int predictedLabel1 = model1->predict(testSample);
//    int predictedLabel2 = model2->predict(testSample);

    // 还有一种调用方式，可以获取结果同时得到阈值:
    //      int predictedLabel = -1;
    //      double confidence = 0.0;
    //      model->predict(testSample, predictedLabel, confidence);

    string result_message = format("Predicted class = %d / Actual class = %d.", predictedLabel, testLabel);
//    string result_message1 = format("Predicted class = %d / Actual class = %d.", predictedLabel1, testLabel);
//   string result_message2 = format("Predicted class = %d / Actual class = %d.", predictedLabel2, testLabel);
    cout<<"人脸识别模型训练完毕，模型预测结果："<<result_message <<endl;
//    cout << result_message1 << endl;
//    cout << result_message2 << endl;
}

//使用CSV文件去读图像和标签，主要使用stringstream和getline方法
static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels) {
    ifstream file(filename,ios::in);
    if(!file.is_open()){
        cout<<"File does not exist"<<endl;
        return;
    }
    string line,path,classlabel;
    while(getline(file,line)){
        stringstream liness(line);
        getline(liness,path,' ');
        getline(liness,classlabel);

        if (!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
    file.close();
}
