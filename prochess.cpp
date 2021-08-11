#include "prochess.h"

ProChess::ProChess(QObject *parent)
{
    this->setParent(parent);
    m_back = new ChessAlGBack(this);
    m_history = m_back->getHistory();
    transform = new pawnTransformD;
    connect(transform,&pawnTransformD::convert,this,&ProChess::changePawn);
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
    char color;
    isupper(board()->data(colFrom,rankFrom))?color = 'w':color = 'b';
    char toPice = board()->data(colTo,rankTo);
    bool moveAccepted = false;
    char check;
    ChessBoard *temp = new ChessBoard(board());
    char chache = board()->data(colFrom,rankFrom);
//    char piceType = tolower(board()->data(colFrom,rankFrom));
    if (m_back->turnCheck(chache,currentPlayer()))
    {
        //we should check the check stasus first......

    if(moveP(colFrom,rankFrom,colTo,rankTo))
    {
        moveAccepted = true;
    }
    if(moveAccepted)
    {
        board()->movePiece(colFrom,rankFrom,colTo,rankTo);
        //specia moves
        if(chache == 'K' && rankFrom == rankTo && colFrom == 5 && colTo == 7)
        {
            board()->setData(8,1,' ');
            board()->setData(6,1,'R');
        }
        if(chache == 'K' && rankFrom == rankTo && colFrom == 5 && colTo == 3)
        {
            board()->setData(1,1,' ');
            board()->setData(4,1,'R');
        }
        if(chache == 'k' && rankFrom == rankTo && colFrom == 5 && colTo == 7)
        {
            board()->setData(8,8,' ');
            board()->setData(6,8,'r');
        }
        if(chache == 'k' && rankFrom == rankTo && colFrom == 5 && colTo == 3)
        {
            board()->setData(1,8,' ');
            board()->setData(4,8,'r');
        }
        if(chache == 'P'&& rankTo == 8)
        {
            pawnChache = new coordinate(colTo,rankTo);
            transform->white();
        }
        if(chache == 'p'&& rankTo == 1)
        {
            pawnChache = new coordinate(colTo,rankTo);
            transform->black();

        }
        if(chache == 'P')
        {
            if(rankFrom == 5)
            {
                if(m_history->lastMove().pice == 'p' && m_history->lastMove().to.rank == 5 && m_history->lastMove().to.col == colFrom - 1)
                {
                    if(m_history->lastMove().from.rank == 7 && m_history->lastMove().to.col == colFrom - 1)
                    {
                        board()->setData(colFrom - 1,rankTo -1,' ');
                        emit elimPice('p');
                    }

                }
                if(m_history->lastMove().pice == 'p' && m_history->lastMove().to.rank == 5 && m_history->lastMove().to.col == colFrom + 1)
                {
                    if(m_history->lastMove().from.rank == 7 && m_history->lastMove().to.col == colFrom + 1)
                    {
                        board()->setData(colFrom + 1,rankTo -1,' ');
                        emit elimPice('p');
                    }

                }
            }
        }
        if(chache == 'p')
        {
            if(rankFrom == 4)
            {
                if(m_history->lastMove().pice == 'P' && m_history->lastMove().to.rank == 4 && m_history->lastMove().to.col == colFrom - 1)
                {
                    if(m_history->lastMove().from.rank == 2 && m_history->lastMove().to.col == colFrom - 1)
                    {
                        board()->setData(colFrom - 1,rankTo + 1,' ');
                        emit elimPice('P');
                    }

                }
                if(m_history->lastMove().pice == 'P' && m_history->lastMove().to.rank == 4 && m_history->lastMove().to.col == colFrom + 1)
                {
                    if(m_history->lastMove().from.rank == 2 && m_history->lastMove().to.col == colFrom + 1)
                    {
                        board()->setData(colFrom + 1,rankTo + 1,' ');
                        emit elimPice('P');
                    }

                }
            }
        }
        repeatedMove(colFrom,rankFrom,colTo,rankTo);
        check = m_back->checkCheck(board());

        if(check != 'n')
        {
            emit this->check(check);
        }


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
    delete temp;
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

bool ProChess::repeatedMove(int colFrom, int rankFrom, int colTo, int rankTo)
{
    if (m_history->secondLastMove().from.col == colTo && m_history->secondLastMove().from.rank == rankTo && m_history->secondLastMove().to.col == colFrom && m_history->secondLastMove().to.rank == rankFrom ){
        emit repetitive();
        return true;
    }
    return false;
}

bool ProChess::moveP(int colFrom, int rankFrom, int colTo, int rankTo)
{
        if (currentPlayer() == NoPlayer)
        {
            return false;
        }
        char color;
        isupper(board()->data(colFrom,rankFrom))?color = 'w':color = 'b';
        char toPice = board()->data(colTo,rankTo);
//        char fromPice = board()->data(colFrom,rankFrom);
        bool moveAccepted = false;
        char check;
        ChessBoard *temp = new ChessBoard(board());
//        char chache = board()->data(colFrom,rankFrom);
        char piceType = tolower(board()->data(colFrom,rankFrom));
//        if (m_back->turnCheck(chache,currentPlayer()))
        {
            //we should check the check stasus first......
            temp->movePiece(colFrom,rankFrom,colTo,rankTo);
            if((currentPlayer() == Player1 && m_back->checkCheck(temp) != 'w'&& m_back->checkCheck(temp) != 'd')||(currentPlayer() == Player2 && m_back->checkCheck(temp) != 'b'&& m_back->checkCheck(temp) != 'd'))
            {
            switch (piceType) {
            case 'p':
                if(m_back->movepawn(colFrom, rankFrom, colTo, rankTo,board()))
                {
                    return true;
                    moveAccepted = true;

                }
                    if (color == 'w')
                    {
                        if(rankFrom == 5)
                        {
                            if(board()->data(colFrom - 1,rankFrom) == 'p'||board()->data(colFrom + 1,rankFrom) == 'p')
                            {
                                if(colTo == colFrom -1 && rankTo == rankFrom +1)
                                {
                                    if(m_history->lastMove().pice == 'p'&& m_history->lastMove().to.col == colFrom - 1&&m_history->lastMove().to.rank == rankFrom&& m_history->lastMove().from.rank == 7){
                                        return true;
                                        moveAccepted = true;
                                    }

                                }
                                if(colTo == colFrom +1 && rankTo == rankFrom +1)
                                {
                                    if(m_history->lastMove().pice == 'p'&& m_history->lastMove().to.col == colFrom +1 &&m_history->lastMove().to.rank == rankFrom&& m_history->lastMove().from.rank == 7){
                                        return true;
                                        moveAccepted = true;
                                    }
                                }
                            }
                        }

                    }
                    if (color == 'b')
                    {
                        if(rankFrom == 4)
                        {
                            if(board()->data(colFrom - 1,rankFrom) == 'P'||board()->data(colFrom + 1,rankFrom) == 'P')
                            {
                                if(colTo == colFrom -1 && rankTo == rankFrom - 1)
                                {
                                    if(m_history->lastMove().pice == 'P'&& m_history->lastMove().to.col == colFrom - 1&&m_history->lastMove().to.rank == rankFrom&& m_history->lastMove().from.rank == 2){
                                        return true;
                                        moveAccepted = true;
                                    }

                                }
                                if(colTo == colFrom +1 && rankTo == rankFrom - 1)
                                {
                                    if(m_history->lastMove().pice == 'P'&& m_history->lastMove().to.col == colFrom +1 &&m_history->lastMove().to.rank == rankFrom&& m_history->lastMove().from.rank == 2){
                                        return true;
                                        moveAccepted = true;
                                    }
                                }
                            }
                        }

                    }

                break;
            case 'r':
                if(m_back->moveRokh(colFrom, rankFrom, colTo, rankTo,board()))
                {
                    return true;
                        moveAccepted = true;

                }
                break;
            case 'n':
                if(m_back->moveKnight( colFrom, rankFrom, colTo, rankTo,board()))
                {
                    return true;
                    moveAccepted = true;

                }
                break;
            case 'k':
            {
                if(m_back->moveKing( colFrom, rankFrom, colTo, rankTo,board()))
                {

                    return true;
                    moveAccepted = true;
                }



                QVector <bool> rokhMoved;

                switch (color) {

                case 'w':
                    if(m_history->kingHasMoved(color))
                    {
                        break;
                    }
                    rokhMoved = m_history->rokhHasMoved(color);
                    if(!rokhMoved[0])
                    {
                        if(colTo == 3)
                        {
                            for(int i = 2;i <= 4;i++)
                            {
                                if(board()->data(i,1) != ' ')
                                {return false;}
                            }
                                    if(colTo == 3 && rankTo == 1){
                                        bool isClear = true;
                                        for(int x = 1;x <=5;x++)
                                        {
                                            if(thread(x,1,'w'))
                                            {
                                                isClear =false;
                                                break;
                                            }
                                        }
                                        if(isClear){
                                            return true;
                                            moveAccepted = true;
                                        }
                                    }
                                    //                                    board()->movePiece(1,1,4,1);



                        }
                    }
                    if(!rokhMoved[1])
                    {
                        if(colTo == 7)
                        {
                            for(int i = 6;i <= 7;i++)
                            {
                                if(board()->data(i,1) != ' ')
                                {return false;}
                                }
                                    if(rankTo == 1 && colTo == 7)
                                    {
                                        bool isClear = true;
                                        for(int x = 5;x <=8;x++)
                                        {
                                            if(thread(x,1,'w'))
                                            {
                                                isClear =false;
                                                break;
                                            }
                                        }
                                        if(isClear){
                                            return true;
                                            moveAccepted = true;
                                        }
                                    }
                                    //                                    board()->movePiece(1,1,4,1);



                        }
                    }

                    break;

                case 'b':
                    if(m_history->kingHasMoved(color))
                    {
                        break;
                    }
                    rokhMoved = m_history->rokhHasMoved(color);
                    if(!rokhMoved[0])
                    {
                        if(colTo == 3)
                        {
                            for(int i = 2;i <= 4;i++)
                            {
                                if(board()->data(i,8) != ' ')
                                {return false;}
                            }
                                    if(colTo == 3 & rankTo == 8)
                                    {
                                        bool isClear = true;
                                        for(int x = 1;x <=5;x++)
                                        {
                                            if(thread(x,8,'b'))
                                            {
                                                isClear =false;
                                                break;
                                            }
                                        }
                                        if(isClear){
                                            return true;
                                            moveAccepted = true;
                                        }

                                    }//                                    board()->movePiece(1,1,4,1);



                        }
                    }
                    if(!rokhMoved[1])
                    {
                        if(colTo == 7)
                        {
                            for(int i = 6;i <= 7;i++)
                            {
                                if(board()->data(i,8) != ' ')
                                {return false;}
                            }
                                    if(colTo == 7 && rankTo == 8){
                                        bool isClear = true;
                                        for(int x = 5;x <=8;x++)
                                        {
                                            if(thread(x,8,'b'))
                                            {
                                                isClear =false;
                                                break;
                                            }
                                        }
                                        if(isClear){
                                            return true;
                                            moveAccepted = true;
                                        }
                                    }
                                    //                                    board()->movePiece(1,1,4,1);



                        }
                    }

                    break;


                }

            }

                break;
            case 'q':

                if(m_back->moveQueen(colFrom, rankFrom, colTo, rankTo,board()))
                {
                    return true;
                        moveAccepted = true;
                }

                break;
            case 'b':
                if(m_back->moveBishop(colFrom, rankFrom, colTo, rankTo,board()))
                {
                    return true;

                        board()->movePiece(colFrom,rankFrom,colTo,rankTo);
                        moveAccepted = true;


                }
                break;
            default:
                break;

            }
        if(moveAccepted)
        {
            repeatedMove(colFrom,rankFrom,colTo,rankTo);
            check = m_back->checkCheck(board());

            if(check != 'n')
            {
//                emit this->check(check);
            }


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

        }
        }
        delete  temp;
        return false;



}

bool ProChess::thread(int col, int rank, char color)
{
    for(int i = 1;i <= 8;i++)
    {
        for(int j = 1;j<= 8;j++)
        {
            if(color == 'w')
            {
                if(islower(board()->data(i,j)))
                {
                    if(moveP(i,j,col,rank))
                    {
                        return true;
                    }

                }
            }
            if(color == 'b')
            {
                if(isupper(board()->data(i,j)))
                {
                    if(moveP(i,j,col,rank))
                    {
                        return true;
                    }

                }
            }
        }
    }
    return false;

}

history *ProChess::historyGet() const
{
    return m_history;
}

void ProChess::randomMove(char color)
{

    QVector <Plog> pices;
    QVector <coordinate> toRand;
    for (int i = 1;i <= 8 ;i++ ) {
        for(int j = 1; j <= 8;j++)
        {
            if(color == 'w')
            {
                if(isupper(board()->data(i,j)))
                {
                    pices.push_back(Plog(board()->data(i,j),coordinate(i,j),coordinate(i,j)));
                }
            }
            if(color == 'b')
            {
                if(islower(board()->data(i,j)))
                {
                    pices.push_back(Plog(board()->data(i,j),coordinate(i,j),coordinate(i,j)));
                }
            }
        }

    }
    int pNumber = pices.size();
//    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
    QRandomGenerator rand;
    rand.seed(QDateTime::currentMSecsSinceEpoch());
    int index =rand.global()->generate()%pNumber;
    for(int i = 1; i<=8;i++)
    {
        for(int j = 1;j <= 8 ;j++)
        {
            if(moveP(pices[index].from.col,pices[index].from.rank,i,j))
            {
                toRand.push_back(coordinate(i,j));
            }
        }
    }
    int moveCount = toRand.size();
    rand.seed(QDateTime::currentMSecsSinceEpoch());
    int coordinateIndex;
    if(moveCount != 0){
        coordinateIndex=rand.global()->generate()%moveCount;

        move(pices[index].from.col,pices[index].from.rank,toRand[coordinateIndex].col,toRand[coordinateIndex].rank);
    }


//    QRandomGenerator

}

void ProChess::switchPlayer()
{
    setCurrentPlayer(m_back->switchPlayer(currentPlayer()));
}

void ProChess::changePawn(char to)
{
    if(pawnChache->rank == 8)
    {
        char temp = toupper(to);
        board()->setData(pawnChache->col,pawnChache->rank,temp);
        delete  pawnChache;
    }
    if(pawnChache->rank == 1)
    {
        board()->setData(pawnChache->col,pawnChache->rank,to);
        delete  pawnChache;
    }
    transform->close();
}
