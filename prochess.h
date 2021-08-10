#ifndef PROCHESS_H
#define PROCHESS_H

#include "chessalgorithm.h"
#include "chessalgback.h"
#include "history.h"
#include "pawntransformd.h"
#include <QObject>

class ProChess : public ChessAlgorithm
{
    Q_OBJECT
public:
    explicit ProChess(QObject *parent = nullptr);
    void newGame();
    bool move(int colFrom, int rankFrom, int colTo, int rankTo);
    ChessAlGBack *back() const;

private:
    ChessAlGBack *m_back;
    history *m_history;
    bool checkMate(char color);
    coordinate *pawnChache;
    bool repeatedMove(int colFrom, int rankFrom, int colTo, int rankTo);
    pawnTransformD *transform;
//    bool foxCanMove() const;
//    bool emptyByOffset(int x, int y) const;
public slots:
    void switchPlayer();
private slots:
    void changePawn(char);

signals:
    void moveMade();
    void check(char);
    void elimPice(char);
    void gameOver(char);
    void repetitive();
    void pawnPasedMid(char);
};

#endif // PROCHESS_H
