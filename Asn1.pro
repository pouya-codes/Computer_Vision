QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    linearinterpolation.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    linearinterpolation.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

unix {
unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv
}
win32 {
INCLUDEPATH += C:\Develop\Opencv\opencv-4.1.2\build\install\include

#LIBS += D:\Develop\opencv\build\install\x64\vc15\lib\lopencv_core412d
#LIBS += D:\Develop\opencv\build\install\x64\vc15\lib\lopencv_highgui412d
#LIBS += D:\Develop\opencv\build\install\x64\vc15\lib\lopencv_imgproc412d

        LIBS += C:\Develop\Opencv\opencv-4.1.2\build\install\x64\vc15\lib\opencv_core412.lib
        LIBS += C:\Develop\Opencv\opencv-4.1.2\build\install\x64\vc15\lib\opencv_highgui412.lib
        LIBS += C:\Develop\Opencv\opencv-4.1.2\build\install\x64\vc15\lib\opencv_imgproc412.lib
        LIBS += C:\Develop\Opencv\opencv-4.1.2\build\install\x64\vc15\lib\opencv_imgcodecs412.lib
        LIBS += C:\Develop\Opencv\opencv-4.1.2\build\install\x64\vc15\lib\opencv_photo412.lib
}



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
