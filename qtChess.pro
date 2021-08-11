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
    eliminated.cpp \
    foxandhounds.cpp \
    history.cpp \
    log.cpp \
    main.cpp \
    mainwindow.cpp \
    pawntransformd.cpp \
    prochess.cpp \
    winerdialoge.cpp

HEADERS += \
    chessalgback.h \
    chessalgorithm.h \
    chessboard.h \
    chessview.h \
    configurationdialog.h \
    coordinate.h \
    eliminated.h \
    foxandhounds.h \
    history.h \
    log.h \
    mainwindow.h \
    pawntransformd.h \
    prochess.h \
    winerdialoge.h

FORMS += \
    configurationdialog.ui \
    mainwindow.ui \
    pawntransformd.ui \
    winerdialoge.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
