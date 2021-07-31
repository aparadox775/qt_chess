#ifndef PROCHESS_H
#define PROCHESS_H

#include "chessalgorithm.h"
#include "chessalgback.h"
#include <QObject>

class ProChess : public ChessAlgorithm
{
public:
    explicit ProChess(QObject *parent = nullptr);
    void newGame();
    bool move(int colFrom, int rankFrom, int colTo, int rankTo);
private:
    ChessAlGBack *m_back;
//    bool foxCanMove() const;
//    bool emptyByOffset(int x, int y) const;
public slots:
    void switchPlayer();
signals:

};

#endif // PROCHESS_H
