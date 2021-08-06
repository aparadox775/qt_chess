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
    char toPice = board()->data(colTo,rankTo);
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
                if((currentPlayer() == Player1 && m_back->checkCheck(temp) != 'w'&& m_back->checkCheck(temp) != 'd')||(currentPlayer() == Player2 && m_back->checkCheck(temp) != 'b'&& m_back->checkCheck(temp) != 'd'))
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
                if((currentPlayer() == Player1 && m_back->checkCheck(temp) != 'w'&& m_back->checkCheck(temp) != 'd')||(currentPlayer() == Player2 && m_back->checkCheck(temp) != 'b'&& m_back->checkCheck(temp) != 'd'))
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
                if((currentPlayer() == Player1 && m_back->checkCheck(temp) != 'w'&& m_back->checkCheck(temp) != 'd')||(currentPlayer() == Player2 && m_back->checkCheck(temp) != 'b'&& m_back->checkCheck(temp) != 'd'))
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
                if((currentPlayer() == Player1 && m_back->checkCheck(temp) != 'w' && m_back->checkCheck(temp) != 'd')||(currentPlayer() == Player2 && m_back->checkCheck(temp) != 'b'&& m_back->checkCheck(temp) != 'd'))
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
                if((currentPlayer() == Player1 && m_back->checkCheck(temp) != 'w'&& m_back->checkCheck(temp) != 'd')||(currentPlayer() == Player2 && m_back->checkCheck(temp) != 'b'&& m_back->checkCheck(temp) != 'd'))

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
                if((currentPlayer() == Player1 && m_back->checkCheck(temp) != 'w'&& m_back->checkCheck(temp) != 'd')||(currentPlayer() == Player2 && m_back->checkCheck(temp) != 'b'&& m_back->checkCheck(temp) != 'd'))
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
//        bool wcheckMate = false,wcheckMate false;
//        currentPlayer() == Player1?
        if(currentPlayer() == Player1)
        {
            if(checkMate('b'))
            {
                emit this->gameOver('w');
            }

        }
        else{
            if(checkMate('w'))
            {
                emit this->gameOver('b');
            }

        }

        switchPlayer();
        emit moveMade();
        emit elimPice(toPice);

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

bool ProChess::checkMate(char color)
{
    ChessBoard *temp ;
    QVector <coordinate> posibleMoves;
    if(color == 'w')
    {
        for(int i = 1;i <= 8 ; i++)
        {
            for(int j = 1;j <= 8 ; j++)
            {
                if(isupper(board()->data(i,j)))
                {
                    for (int x = 1;x <= 8;x++ ) {
                        for (int y = 1;y <= 8;y++ ){
                            switch (board()->data(i,j)) {
                            case 'P':
                                temp = new ChessBoard (board());
                                if(m_back->movepawn(i,j,x,y,board())){
                                    temp->movePiece(i,j,x,y);
                                    if(m_back->checkCheck(temp) != 'w'&& m_back->checkCheck(temp) != 'd')
                                    return false;

                                }
                                delete  temp;
                                break;
                            case 'R':
                                temp = new ChessBoard (board());
                                if(m_back->moveRokh(i,j,x,y,board())){
                                    temp->movePiece(i,j,x,y);
                                    if(m_back->checkCheck(temp) != 'w'&& m_back->checkCheck(temp) != 'd')
                                    return false;

                                }
                                delete  temp;
                                break;
                            case 'N':
                                temp = new ChessBoard (board());
                                if(m_back->moveKnight(i,j,x,y,board())){
                                    temp->movePiece(i,j,x,y);
                                    if(m_back->checkCheck(temp) != 'w'&& m_back->checkCheck(temp) != 'd')
                                    return false;

                                }
                                delete  temp;
                                break;
                            case 'B':
                                temp = new ChessBoard (board());
                                if(m_back->moveBishop(i,j,x,y,board())){
                                    temp->movePiece(i,j,x,y);
                                    if(m_back->checkCheck(temp) != 'w'&& m_back->checkCheck(temp) != 'd')
                                    return false;

                                }
                                delete  temp;
                                break;
                            case 'Q':
                                temp = new ChessBoard (board());
                                if(m_back->moveQueen(i,j,x,y,board())){
                                    temp->movePiece(i,j,x,y);
                                    if(m_back->checkCheck(temp) != 'w'&& m_back->checkCheck(temp) != 'd')
                                    return false;

                                }
                                delete  temp;
                                break;
                            case 'K':
                                temp = new ChessBoard (board());
                                if(m_back->moveKing(i,j,x,y,board())){
                                    temp->movePiece(i,j,x,y);
                                    if(m_back->checkCheck(temp) != 'w'&& m_back->checkCheck(temp) != 'd')
                                    return false;

                                }
                                delete  temp;
                                break;
                            }
                        }
                    }
                }

            }
        }
        return true;
    }
    if(color == 'b')
    {
        for(int i = 1;i <= 8 ; i++)
        {
            for(int j = 1;j <= 8 ; j++)
            {
                if(islower(board()->data(i,j)))
                {
                    for (int x = 1;x <= 8;x++ ) {
                        for (int y = 1;y <= 8;y++ ){
                            switch (board()->data(i,j)) {
                            case 'p':
                                temp = new ChessBoard (board());
                                if(m_back->movepawn(i,j,x,y,board())){
                                    temp->movePiece(i,j,x,y);
                                    if(m_back->checkCheck(temp) != 'b'&& m_back->checkCheck(temp) != 'd')
                                    return false;

                                }
                                delete  temp;
                                break;
                            case 'r':
                                temp = new ChessBoard (board());
                                if(m_back->moveRokh(i,j,x,y,board())){
                                    temp->movePiece(i,j,x,y);
                                    if(m_back->checkCheck(temp) != 'b'&& m_back->checkCheck(temp) != 'd')
                                    return false;

                                }
                                delete  temp;
                                break;
                            case 'n':
                                temp = new ChessBoard (board());
                                if(m_back->moveKnight(i,j,x,y,board())){
                                    temp->movePiece(i,j,x,y);
                                    if(m_back->checkCheck(temp) != 'b'&& m_back->checkCheck(temp) != 'd')
                                    return false;

                                }
                                delete  temp;
                                break;
                            case 'b':
                                temp = new ChessBoard (board());
                                if(m_back->moveBishop(i,j,x,y,board())){
                                    temp->movePiece(i,j,x,y);
                                    if(m_back->checkCheck(temp) != 'b'&& m_back->checkCheck(temp) != 'd')
                                    return false;

                                }
                                delete  temp;
                                break;
                            case 'q':
                                temp = new ChessBoard (board());
                                if(m_back->moveQueen(i,j,x,y,board())){
                                    temp->movePiece(i,j,x,y);
                                    if(m_back->checkCheck(temp) != 'b'&& m_back->checkCheck(temp) != 'd')
                                    return false;

                                }
                                delete  temp;
                                break;
                            case 'k':
                                temp = new ChessBoard (board());
                                if(m_back->moveKing(i,j,x,y,board())){
                                    temp->movePiece(i,j,x,y);
                                    if(m_back->checkCheck(temp) != 'b'&& m_back->checkCheck(temp) != 'd')
                                    return false;

                                }
                                delete  temp;
                                break;
                            }
                        }
                    }
                }

            }
        }
        return true;
    }
}

void ProChess::switchPlayer()
{
    setCurrentPlayer(m_back->switchPlayer(currentPlayer()));
}
