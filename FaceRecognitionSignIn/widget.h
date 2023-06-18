
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <QTimer>
#include "dialog.h"
#include <string>
#include <iostream>
#include "faceget.h"
#include "facetrain.h"
#include "facerecognition.h"
#include "qsqlitedb.h"

using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void importFrame();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void updateData(QString data);

private:
    Ui::Widget *ui;
    VideoCapture capture;
    QTimer *timer;
    Mat frame;
    std::string name;
    Dialog *newdialog;
    int model;
    FaceGet face_get;
    FaceTrain face_train;
    FaceRecognition face_sign;
    QSqlitedb sqlitedb;
};

#endif // WIDGET_H
