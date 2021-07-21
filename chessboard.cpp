#include "chessboard.h"

ChessBoard::ChessBoard(int rank, int columns, QObject *parent) : QObject(parent)
{
    //    setRanks(rank);
    //    setColumns(columns);
    this->m_columns = columns;
    this->m_ranks = rank;
    initBoard();
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

void ChessBoard::movePiece(int fromColumn, int fromRank,
                           int toColumn, int toRank)
{
    setData(toColumn, toRank, data(fromColumn, fromRank));
    setData(fromColumn, fromRank, ' ');
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
