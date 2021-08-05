#include "prochess.h"

ProChess::ProChess(QObject *parent)
{
    this->setParent(parent);
    m_back = new ChessAlGBack(this);
    m_history = m_back->getHistory();
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
    bool moveAccepted = false;
    char check;
    ChessBoard *temp = new ChessBoard(board());
    char chache = board()->data(colFrom,rankFrom);
    char piceType = tolower(board()->data(colFrom,rankFrom));
    if (m_back->turnCheck(chache,currentPlayer()))
    {
        //we should check the check stasus first......

        switch (piceType) {
        case 'p':
            if(m_back->movepawn(colFrom, rankFrom, colTo, rankTo,board()))
            {
                temp->movePiece(colFrom,rankFrom,colTo,rankTo);
                if((currentPlayer() == Player1 && m_back->checkCheck(temp) != 'w')||(currentPlayer() == Player2 && m_back->checkCheck(temp) != 'b'))
                {
                    board()->movePiece(colFrom,rankFrom,colTo,rankTo);
                    moveAccepted = true;
                }
            }
            break;
        case 'r':
            if(m_back->moveRokh(colFrom, rankFrom, colTo, rankTo,board()))
            {
                temp->movePiece(colFrom,rankFrom,colTo,rankTo);
                if((currentPlayer() == Player1 && m_back->checkCheck(temp) != 'w')||(currentPlayer() == Player2 && m_back->checkCheck(temp) != 'b'))
                {
                    board()->movePiece(colFrom,rankFrom,colTo,rankTo);
                    moveAccepted = true;

                }
            }
            break;
        case 'n':
            if(m_back->moveKnight( colFrom, rankFrom, colTo, rankTo,board()))
            {
                temp->movePiece(colFrom,rankFrom,colTo,rankTo);
                if((currentPlayer() == Player1 && m_back->checkCheck(temp) != 'w')||(currentPlayer() == Player2 && m_back->checkCheck(temp) != 'b'))
                {
                    board()->movePiece(colFrom,rankFrom,colTo,rankTo);
                    moveAccepted = true;
                }
            }
            break;
        case 'k':
            if(m_back->moveKing( colFrom, rankFrom, colTo, rankTo,board()))
            {
                temp->movePiece(colFrom,rankFrom,colTo,rankTo);
                if((currentPlayer() == Player1 && m_back->checkCheck(temp) != 'w')||(currentPlayer() == Player2 && m_back->checkCheck(temp) != 'b'))
                {
                    board()->movePiece(colFrom,rankFrom,colTo,rankTo);
                    moveAccepted = true;
                }
            }
            break;
        case 'q':

            if(m_back->moveQueen(colFrom, rankFrom, colTo, rankTo,board()))
            {
                temp->movePiece(colFrom,rankFrom,colTo,rankTo);
                if((currentPlayer() == Player1 && m_back->checkCheck(temp) != 'w')||(currentPlayer() == Player2 && m_back->checkCheck(temp) != 'b'))

                {
                    board()->movePiece(colFrom,rankFrom,colTo,rankTo);
                    moveAccepted = true;
                }
            }

            break;
        case 'b':
            if(m_back->moveBishop(colFrom, rankFrom, colTo, rankTo,board()))
            {
                temp->movePiece(colFrom,rankFrom,colTo,rankTo);
                if((currentPlayer() == Player1 && m_back->checkCheck(temp) != 'w')||(currentPlayer() == Player2 && m_back->checkCheck(temp) != 'b'))
                {
                    board()->movePiece(colFrom,rankFrom,colTo,rankTo);
                    moveAccepted = true;
                }

            }
            break;
        default:
            break;

        }
    if(moveAccepted)
    {
        check = m_back->checkCheck(board());
        if(check != 'n')
        {
            emit this->check(check);
        }

        switchPlayer();
        emit moveMade();
        coordinate to(colTo,rankTo);
        coordinate from(colFrom,rankFrom);
        m_history->addlog(board()->data(colTo,rankTo),from,to);

    }

//        setCurrentPlayer(m_back->switchPlayer(currentPlayer()));
    }
//    else if(isupper(chache))
    return true;
}

ChessAlGBack *ProChess::back() const
{
    return m_back;
}

void ProChess::switchPlayer()
{
    setCurrentPlayer(m_back->switchPlayer(currentPlayer()));
}
