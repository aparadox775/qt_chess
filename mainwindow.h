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
#include "history.h"
#include "winerdialoge.h"
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
    void threadPoint(char pice);
    void checkmatePoint(char);
    void restorePice();
    void repetitiveMove();
    void pawnPassed(char);
    void extraTurn();
    void updateExtra();
private:
    Ui::MainWindow *ui;
    ChessView *m_undoView;
    ChessAlgorithm *m_algorithm;
    ChessAlGBack *m_back;
    history *m_history;
    QPoint m_clickPoint;
    char lastElimedPice = ' ';
    QString player1 = "null";
    QString player2 = "null";
    ChessView::FieldHighlight *m_selectedField;
    QVector <ChessView::FieldHighlight *> m_selectedFields;
    QVector <ChessView::FieldHighlight *> m_selectedFieldsCopy;
    int moveCount = 0;
    void posible(int col,int rank);
    void highlight(int col,int rank);
    void removeHighlight();
    int p1p = 0,p1n = 0,p2p = 0,p2n = 0;
    void resizeEvent(QResizeEvent* event);
    void thread(int col,int rank);
    int extra = 1;
    void decresPoint();


};
#endif // MAINWINDOW_H
