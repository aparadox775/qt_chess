#include "prochess.h"

ProChess::ProChess(QObject *parent)
{
    this->setParent(parent);
    m_back = new ChessAlGBack();
}

void ProChess::newGame()
{
    setupBoard();
    board()->setFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w");
    // 'w' - white to move
//    m_fox = QPoint(5, 8);
    setResult(NoResult);
    setCurrentPlayer(Player1);
}

bool ProChess::move(int colFrom, int rankFrom, int colTo, int rankTo)
{
    if (currentPlayer() == NoPlayer)
    {
        return false;
    }
    char chache = board()->data(colFrom,rankFrom);
    char piceType = tolower(board()->data(colFrom,rankFrom));
    if (m_back->turnCheck(chache,currentPlayer()))
    {
        //we should check the check stasus first......

        switch (piceType) {
        case 'p':
            break;
        case 'r':
            break;
        case 'n':
            if(m_back->moveKnight( colFrom, rankFrom, colTo, rankTo,board()))
            {
                board()->movePiece(colFrom,rankFrom,colTo,rankTo);
                switchPlayer();
            }
            break;
        case 'k':
            break;
        case 'q':
            break;
        case 'b':
            break;
        default:
            break;

        }


//        setCurrentPlayer(m_back->switchPlayer(currentPlayer()));
    }
//    else if(isupper(chache))
    return true;
}

void ProChess::switchPlayer()
{
    setCurrentPlayer(m_back->switchPlayer(currentPlayer()));
}
