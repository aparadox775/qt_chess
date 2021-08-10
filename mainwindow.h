#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVector>
#include "chessalgorithm.h"
#include "chessview.h"
#include "configurationdialog.h"
#include "chessalgback.h"
#include "pawntransformd.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void initNewGame();
    void quit();
    void viewClicked(const QPoint &field);
    void undo();
    void moved();
    void updateUndo();
    void updatePoints();
    void Check(char ch);
    void elimPice(char pice);
    void thread(char pice);
    void checkmatePoint(char);
    void restorePice();
    void repetitiveMove();
    void pawnPassed(char);
private:
    Ui::MainWindow *ui;
    ChessView *m_undoView;
    ChessAlgorithm *m_algorithm;
    ChessAlGBack *m_back;
    QPoint m_clickPoint;
    char lastElimedPice = ' ';
    ChessView::FieldHighlight *m_selectedField;
    QVector <ChessView::FieldHighlight *> m_selectedFields;
    QVector <ChessView::FieldHighlight *> m_selectedFieldsCopy;
    int moveCount = 0;
    void posible(int col,int rank,bool thread);
    void highlight(int col,int rank);
    void removeHighlight();
    int p1p = 0,p1n = 0,p2p = 0,p2n = 0;
    void resizeEvent(QResizeEvent* event);


};
#endif // MAINWINDOW_H
