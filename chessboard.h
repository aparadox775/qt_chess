#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include <QVector>

struct move
{
  int formerCol = 1;
    int formerRank = 1;
    int toCol = 1;
    int toRank = 1;
};

class ChessBoard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ranks READ ranks NOTIFY ranksChanged)
    Q_PROPERTY(int columns READ columns NOTIFY columnsChanged)
public:
    explicit ChessBoard(int rank,int columns,QObject *parent = nullptr);
    int ranks() const;
    int columns() const;
    void initBoard();
    char data(int column, int rank) const;
    void setData(int column, int rank, char value);
    void movePiece(int fromColumn, int fromRank,
                   int toColumn, int toRank);
    void setFen(const QString &fen);
    move undoMove();
    void setUndoable(bool);
    bool getUndoable() const;
public slots:
    void undo();


signals:
    void ranksChanged(int);
    void columnsChanged(int);
    void dataChanged(int c,int r);
    void boardReset();
private:
    int m_ranks;
    int m_columns;
    QVector<char> m_boardData;
    QVector<char> m_lastBoardData;
    bool setDataInternal(int column, int rank, char value);
    move m_undoMove;
    bool undoable = false;
protected:
    void setRanks(int newRanks);
    void setColumns(int newColumns);

};

#endif // CHESSBOARD_H
