#ifndef CHESSALGBACK_H
#define CHESSALGBACK_H

#include "chessalgorithm.h"
#include "history.h"
#include <QObject>
#include <array>
#include <QVector>
#include "coordinate.h"
//struct coordinate
//{
//    int col, rank;
//    coordinate(int col,int rank) {this->col = col;this ->rank = rank;}
//    bool boundryCheck()
//    {
//        if (col < 1 || rank < 1)
//            return false;
//        else if(col > 8 || rank > 8)
//            return false;
//        return true;
//    }
//    void set(int col,int rank) {this->col = col;this ->rank = rank;}
//};
class ChessAlGBack : public QObject
{
    Q_OBJECT

public:
    explicit ChessAlGBack(QObject *parent = nullptr);
    bool turnCheck(char, ChessAlgorithm::Player);
    ChessAlgorithm::Player switchPlayer(ChessAlgorithm::Player);
    bool moveKnight(int,int,int,int,ChessBoard *);
    bool moveRokh(int,int,int,int,ChessBoard *);
    bool moveBishop(int,int,int,int,ChessBoard *);
    bool moveKing(int,int,int,int,ChessBoard *);
    bool movepawn(int,int,int,int,ChessBoard *);
    bool moveQueen(int,int,int,int,ChessBoard *);
    char checkCheck(ChessBoard *);
    bool checkCheckW(ChessBoard *);
    QVector <coordinate> bishopPMoves(int col,int rank,ChessBoard *,char color);
    QVector <coordinate> rokhPMoves(int col,int rank,ChessBoard *,char color);
    QVector <coordinate> knightPMoves(int col,int rank);
    QVector <coordinate> kingPMoves(int col,int rank);


    history *getHistory();

private:
    void boardExtract(ChessBoard *);
    class::history *m_history;
    char board[8][8];
signals:
    void changePawn(char);
    void elimPice(char);
};

#endif // CHESSALGBACK_H
