
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    model=0;
    face_get=FaceGet();
    face_train=FaceTrain();
    face_sign=FaceRecognition();
    sqlitedb=QSqlitedb();

    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(importFrame()));
    capture.open(0);
    timer->start(33);
}

Widget::~Widget()
{
    timer->stop();
    capture.release();
    sqlitedb.closeDb();
    delete ui;
}

void Widget::updateData(QString data){
    name=data.toStdString();
    std::cout<<"name:"<<name<<std::endl;
    for(size_t i=0;i<10;i++){
        if(!frame.empty()){
            face_get.savePic(name,i,frame);
        }else{
            i--;
        }
    }
    std::cout<<"人脸图像获取完毕"<<std::endl;
    face_train.run();
    std::cout<<"重新载入识别模型中"<<std::endl;
    face_sign=FaceRecognition();
    std::cout<<"识别模型载入完毕"<<std::endl;
    model=0;
}

void Widget::on_pushButton_clicked()
{
    model=1;
    newdialog=new Dialog;
    connect(newdialog,SIGNAL(sendData(QString)),this,SLOT(updateData(QString)));
    if(newdialog->exec()==QDialog::Accepted){
    }
    delete newdialog;
}


void Widget::on_pushButton_2_clicked()
{
    model=2;

    int predictPCA_first=face_sign.getPredictPCA(frame);
    int predictPCA_last=predictPCA_first;

    for(size_t i=0;i<10;i++){
        if(predictPCA_first==-1){
            capture>>frame;
            predictPCA_first=face_sign.getPredictPCA(frame);
            predictPCA_last=predictPCA_first;
            i=0;
        }else if(predictPCA_last!=predictPCA_first){
            predictPCA_first=face_sign.getPredictPCA(frame);
            predictPCA_last=predictPCA_first;
            i=0;
        }else{
            predictPCA_first=face_sign.getPredictPCA(frame);
        }
    }
    string timedb=face_sign.gettime();
    sqlitedb.singleInsertData(face_sign.getMap()[predictPCA_first],timedb);
    std::cout<<face_sign.getMap()[predictPCA_first]<<"签到成功"<<std::endl;
    model=0;
}


void Widget::on_pushButton_3_clicked()
{
    std::cout<<"签到记录："<<std::endl;
    for(auto &[key,value] : sqlitedb.queryTable()){
        cout<<key<<" "<<value<<endl;
    }
}

void Widget::importFrame(){
    capture>>frame;
    Mat pframe;
    capture>>pframe;

    cvtColor(face_get.getFrame(pframe), pframe, COLOR_BGR2RGB);//only RGB of Qt
    QImage srcQImage = QImage((uchar*)(pframe.data), pframe.cols, pframe.rows, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(srcQImage));
    ui->label->resize(srcQImage.size());
    ui->label->show();
}

