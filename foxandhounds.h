#ifndef FOXANDHOUNDS_H
#define FOXANDHOUNDS_H


#include "chessalgorithm.h"

#include <QPoint>

class FoxAndHounds : public ChessAlgorithm
{
public:
    FoxAndHounds(QObject *parent = 0);
    void newGame();
    bool move(int colFrom, int rankFrom, int colTo, int rankTo);
private:
    bool foxCanMove() const;
    bool emptyByOffset(int x, int y) const;
    QPoint m_fox;
};
#endif // FOXANDHOUNDS_H
