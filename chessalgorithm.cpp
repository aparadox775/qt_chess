#include "chessalgorithm.h"

ChessAlgorithm::ChessAlgorithm(QObject *parent) : QObject(parent)
{
    m_board = nullptr;

}

ChessBoard *ChessAlgorithm::board() const
{
    return this->m_board;
}

void ChessAlgorithm::newGame()
{
    setupBoard();
    board()->setFen(
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
    );
}

void ChessAlgorithm::setupBoard()
{
    setBoard(new ChessBoard(8, 8, this));
}

void ChessAlgorithm::setBoard(ChessBoard *board)
{
    if(board == m_board) {
    return;
    }
    delete m_board;
    m_board = board;
    emit boardChanged(m_board);
}