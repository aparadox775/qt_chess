#include "chessboard.h"

ChessBoard::ChessBoard(int rank, int columns, QObject *parent) : QObject(parent)
{
    //    setRanks(rank);
    //    setColumns(columns);
    this->m_columns = columns;
    this->m_ranks = rank;
    initBoard();
}

ChessBoard::ChessBoard(ChessBoard *clone)
{
    this->setRanks(clone->ranks());
    this->setColumns(clone->columns());
    initBoard();
    this->m_boardData = clone->m_boardData;
//    this->
}

int ChessBoard::ranks() const
{
    return this->m_ranks;
}

int ChessBoard::columns() const
{
    return this->m_columns;
}

void ChessBoard::setRanks(int newRanks)
{
    if (ranks() == newRanks)
    {
        return;
    }
    m_ranks = newRanks;
    initBoard();
    emit ranksChanged(m_ranks);
}

void ChessBoard::setColumns(int newColumns)
{
    if (columns() == newColumns)
    {
        return;
    }
    m_columns = newColumns;
    initBoard();
    emit columnsChanged(m_columns);
}
void ChessBoard::initBoard()
{
    m_boardData.fill(' ', ranks() * columns());
    emit boardReset();
}

char ChessBoard::data(int column, int rank) const
{
    return m_boardData.at((rank - 1) * columns() + (column - 1));
}

void ChessBoard::setData(int column, int rank, char value)
{
    if (setDataInternal(column, rank, value))
    {
        emit dataChanged(column, rank);
    }
}

bool ChessBoard::setDataInternal(int column, int rank, char value)
{
    int index = (rank - 1) * columns() + (column - 1);
    if (m_boardData.at(index) == value)
    {
        return false;
    }
    m_boardData[index] = value;
    return true;
}

bool ChessBoard::getUndoable() const
{
    return undoable;
}

void ChessBoard::undo()
{
    m_boardData = m_lastBoardData;
    setUndoable(false);
    emit dataChanged(m_undoMove.toCol,m_undoMove.toRank);
    emit dataChanged(m_undoMove.formerCol,m_undoMove.formerRank);
}

void ChessBoard::movePiece(int fromColumn, int fromRank,
                           int toColumn, int toRank)
{
    //last Board data for undo;
    m_lastBoardData = m_boardData;

    setData(toColumn, toRank, data(fromColumn, fromRank));
    setData(fromColumn, fromRank, ' ');

    //we store the last move for emiting dataChanged signal in undo slot
    m_undoMove.toCol = fromColumn;
    m_undoMove.toRank = fromRank;
    m_undoMove.formerCol = toColumn;
    m_undoMove.formerRank = toRank;
//    QObject * temp = this->parent();
//    dynamic_cast<>()
//    this->parent()->hi()
    undoable = true;
}
void ChessBoard::setFen(const QString &fen)
{
    int index = 0;
    int skip = 0;
    const int columnCount = columns();
    QChar ch;
    for (int rank = ranks(); rank > 0; --rank)
    {
        for (int column = 1; column <= columnCount; ++column)
        {
            if (skip > 0)
            {
                ch = ' ';
                skip--;
            }
            else
            {
                ch = fen.at(index++);
                if (ch.isDigit())
                {
                    skip = ch.toLatin1() - '0';
                    ch = ' ';
                    skip--;
                }
            }
            setDataInternal(column, rank, ch.toLatin1());
        }
        QChar next = fen.at(index++);
        if (next != '/' && next != ' ')
        {
            initBoard();
            return; // fail on error
        }
    }
    emit boardReset();
}

move ChessBoard::undoMove()
{
    return m_undoMove;
}

void ChessBoard::setUndoable(bool isUndoable)
{
    undoable = isUndoable;
}
