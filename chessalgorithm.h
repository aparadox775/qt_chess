#ifndef CHESSALGORITHM_H
#define CHESSALGORITHM_H

#include "chessboard.h"

#include <QObject>

class ChessAlgorithm : public QObject
{
    Q_OBJECT
public:
    explicit ChessAlgorithm(QObject *parent = nullptr);
    ChessBoard* board() const;

public slots:
    virtual void newGame();


signals:
    void boardChanged(ChessBoard*);


protected:
    virtual void setupBoard();
    void setBoard(ChessBoard *board);



private:
    ChessBoard* m_board;
};

#endif // CHESSALGORITHM_H
