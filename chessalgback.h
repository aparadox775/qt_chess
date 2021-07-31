#ifndef CHESSALGBACK_H
#define CHESSALGBACK_H

#include "chessalgorithm.h"
#include <QObject>
#include <array>
#include <QVector>
struct coordinate
{
    int col, rank;
    coordinate(int col,int rank) {this->col = col;this ->rank = rank;}
    bool boundryCheck()
    {
        if (col < 1 || rank < 1) {
            return false;
        }
        return true;
    }
};
class ChessAlGBack : public QObject
{
//    Q_OBJECT

public:
    explicit ChessAlGBack(QObject *parent = nullptr);
    bool turnCheck(char, ChessAlgorithm::Player);
    ChessAlgorithm::Player switchPlayer(ChessAlgorithm::Player);
    bool moveKnight(int,int,int,int,ChessBoard *);
    QVector <coordinate *> knightPMoves(int col,int rank);
private:
    void boardExtract(ChessBoard *);
    char board[8][8];
};

#endif // CHESSALGBACK_H
