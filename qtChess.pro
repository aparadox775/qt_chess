QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chessalgback.cpp \
    chessalgorithm.cpp \
    chessboard.cpp \
    chessview.cpp \
    configurationdialog.cpp \
    coordinate.cpp \
    foxandhounds.cpp \
    history.cpp \
    main.cpp \
    mainwindow.cpp \
    prochess.cpp

HEADERS += \
    chessalgback.h \
    chessalgorithm.h \
    chessboard.h \
    chessview.h \
    configurationdialog.h \
    coordinate.h \
    foxandhounds.h \
    history.h \
    mainwindow.h \
    prochess.h

FORMS += \
    configurationdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
