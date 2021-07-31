#ifndef CHESSALGORITHM_H
#define CHESSALGORITHM_H

#include "chessboard.h"

#include <QObject>

class ChessAlgorithm : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Result result READ result)
    Q_PROPERTY(Player currentPlayer
                      READ currentPlayer
                      NOTIFY currentPlayerChanged)
public:

    enum Result { NoResult, Player1Wins, Draw, Player2Wins };
    Q_ENUM(Result)
    enum Player { NoPlayer, Player1, Player2 };
    Q_ENUM(Player)

    explicit ChessAlgorithm(QObject *parent = nullptr);
    ChessBoard* board() const;
    inline Result result() const {
        return m_result;
    }
    inline Player currentPlayer() const {
        return m_currentPlayer;
    }



public slots:
    virtual void newGame();
    virtual bool move(int colFrom, int rankFrom, int colTo, int rankTo);
    bool move(const QPoint &from, const QPoint &to);
    void hi();

signals:
    void boardChanged(ChessBoard*);
    void gameOver(Result);
    void currentPlayerChanged(Player);


protected:
    virtual void setupBoard();
    void setBoard(ChessBoard *board);
    void setResult(Result);
    void setCurrentPlayer(Player);




private:
    ChessBoard* m_board;
    Player m_currentPlayer;
    Result m_result;
};

#endif // CHESSALGORITHM_H
