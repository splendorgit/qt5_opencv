QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += D:\opencv-4.5.4\Build\install\include

LIBS += -LD:/opencv-4.5.4/Build/bin  \
-Llibopencv_calib3d454.dll  \
-Llibopencv_core454.dll \
-Llibopencv_dnn454.dll  \
-Llibopencv_features2d454.dll \
-Libopencv_flann454.dll \
-Llibopencv_gapi454.dll \
-Llibopencv_highgui454.dll  \
-Llibopencv_imgcodecs454.dll    \
-Llibopencv_imgproc454.dll  \
-Llibopencv_ml454.dll   \
-Llibopencv_objdetect454.dll    \
-Llibopencv_photo454.dll    \
-Llibopencv_stitching454.dll    \
-Llibopencv_video454.dll    \
-Llibopencv_videoio454.dll

TEMPLATE = app
TARGET =   ImageViewer



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
