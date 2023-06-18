QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog.cpp \
    faceget.cpp \
    facerecognition.cpp \
    facetrain.cpp \
    main.cpp \
    qsqlitedb.cpp \
    widget.cpp

HEADERS += \
    dialog.h \
    faceget.h \
    facerecognition.h \
    facetrain.h \
    qsqlitedb.h \
    widget.h

FORMS += \
    dialog.ui \
    widget.ui

INCLUDEPATH += D:\OpenCV\opencv\qtbuild\install\include
INCLUDEPATH += D:\OpenCV\opencv\qtbuild\install\include\opencv2
LIBS += D:\OpenCV\opencv\qtbuild\lib\libopencv_*.a

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
