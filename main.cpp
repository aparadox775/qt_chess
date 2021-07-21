#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
//    QApplication a(argc, argv);
//    QGraphicsScene scene;
//    scene.addLine(-100, 0, 100, 0);
//    scene.addLine(0, -100, 0, 100);
//    QGraphicsRectItem* rectItem = scene.addRect(50, 50, 50, 100);
//    rectItem->setRotation(45);
////    scene.setSceneRect(0, -100, 100, 100);
//    QGraphicsView view(&scene);

//    view.show();
    return a.exec();
}
