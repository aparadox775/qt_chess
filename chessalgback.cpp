#include "chessalgback.h"
#include <iostream>
ChessAlGBack::ChessAlGBack(QObject *parent):QObject(parent)
{
    m_history = new class::history(this);
    this->setParent(parent);
}



bool ChessAlGBack::turnCheck(char input, ChessAlgorithm::Player theTurn)
{
    if (isupper( input) && theTurn == ChessAlgorithm::Player1)
        return true;
    if (isupper(input) == 0 && input != ' ' && theTurn == ChessAlgorithm::Player2)
        return true;
    else
        return false;
}

ChessAlgorithm::Player ChessAlGBack::switchPlayer(ChessAlgorithm::Player input)
{
    if (input == ChessAlgorithm::Player1)
        return ChessAlgorithm::Player2;
    if (input == ChessAlgorithm::Player2)
        return ChessAlgorithm::Player1;
    else
        return ChessAlgorithm::NoPlayer;
}



bool ChessAlGBack::moveKnight(int colFrom, int rankFrom, int colTo, int rankTo, ChessBoard *boardView)
{
    this->boardExtract(boardView);
    char color;
    isupper(boardView->data(colFrom,rankFrom))?color = 'w':color = 'b';
    coordinate * tempCor = new coordinate(colTo,rankTo);
    QVector<coordinate> al = knightPMoves(colFrom,rankFrom);
//    int st = this->knightPMoves(colFrom,rankFrom).indexOf(tempCor);
    for(coordinate & crT: al)
    {
        if (crT.col == tempCor->col && crT.rank == tempCor->rank)
        {
            if(boardView->data(colTo,rankTo) == ' ')
                return true;
            else if(isupper(boardView->data(colTo,rankTo)) && color == 'b')
                return true;
            else if(isupper(boardView->data(colTo,rankTo)) == 0 && color == 'w')
                return true;
        }
    }

//    if(colFrom == colTo || rankFrom == rankTo)
//        return false;


    delete tempCor;
    return false;

}

bool ChessAlGBack::moveRokh(int colFrom, int rankFrom, int colTo, int rankTo, ChessBoard *boardView)
{
    char color;
    isupper(boardView->data(colFrom,rankFrom))?color = 'w':color = 'b';
    QVector<coordinate> al = rokhPMoves(colFrom,rankFrom,boardView,color);
    for(coordinate & crT: al)
    {
        if (crT.col == colTo && crT.rank == rankTo)
        {
            return true;

        }

    }
    return false;

}

bool ChessAlGBack::moveBishop(int colFrom, int rankFrom, int colTo, int rankTo, ChessBoard *boardView)
{
    char color;
    isupper(boardView->data(colFrom,rankFrom))?color = 'w':color = 'b';
    QVector<coordinate> al = bishopPMoves(colFrom,rankFrom,boardView,color);
    for(coordinate & crT: al)
    {
        if (crT.col == colTo && crT.rank == rankTo)
        {
            return true;

        }

    }
    return false;

}

bool ChessAlGBack::moveKing(int colFrom, int rankFrom, int colTo, int rankTo, ChessBoard *boardView)
{
    char color;
    isupper(boardView->data(colFrom,rankFrom))?color = 'w':color = 'b';
    QVector<coordinate> al = kingPMoves(colFrom,rankFrom);
//    int st = this->knightPMoves(colFrom,rankFrom).indexOf(tempCor);
    for(coordinate & crT: al)
    {
        if (crT.col == colTo && crT.rank == rankTo)
        {
            if(boardView->data(colTo,rankTo) == ' ')
            {
                return true;
            }
            else if(isupper(boardView->data(colTo,rankTo)) && color == 'b')
            {

                return true;
            }
            else if(isupper(boardView->data(colTo,rankTo)) == 0 && color == 'w')
            {
                return true;
            }
        }
    }
    return false;
}

bool ChessAlGBack::movepawn(int colFrom, int rankFrom, int colTo, int rankTo, ChessBoard *boardView)
{
    char color;
    isupper(boardView->data(colFrom,rankFrom))?color = 'w':color = 'b';
    if (color == 'w') {
        if(colTo == colFrom&& rankTo-rankFrom == 1)
        {
            if(boardView->data(colTo,rankTo) == ' ')
            {
                return true;

            }
        }
        if(rankFrom == 2)
            if(colTo == colFrom&& rankTo-rankFrom == 2)
            {
                if(boardView->data(colTo,rankTo) == ' '&& boardView->data(colTo,rankTo - 1) == ' ' )
                {
                    return true;

                }
            }
//        boardView->data()
        bool cond1 = false;
        bool cond2 = false;
        bool cond3 = false;
        coordinate temp(colFrom - 1 , rankFrom + 1);
        if(temp.boundryCheck())
            cond1 = (boardView->data(colFrom - 1,rankFrom + 1)!= ' '&&isupper(boardView->data(colFrom - 1,rankFrom + 1)) == 0);
        temp.set(colFrom + 1,rankFrom + 1);
        if(temp.boundryCheck())
            cond2 = (boardView->data(colFrom + 1,rankFrom + 1)!= ' '&&isupper(boardView->data(colFrom + 1,rankFrom + 1)) == 0);
        cond3 = (rankTo == rankFrom + 1 && (colTo == colFrom - 1||colTo == colFrom + 1));
        if((cond1||cond2)&&cond3)
        {
            return true;

        }
        if(rankTo == 8)
        {
            emit changePawn('w');
        }
        return false;

    }
    if (color == 'b') {
        if(colTo == colFrom&& rankFrom-rankTo == 1)
        {
            if(boardView->data(colTo,rankTo) == ' ')
            {
                return true;

            }
        }
        if(rankFrom == 7)
            if(colTo == colFrom&& rankFrom-rankTo == 2 && boardView->data(colTo,rankTo + 1) == ' ')
            {
                if(boardView->data(colTo,rankTo) == ' ')
                {
                    return true;

                }
            }
        bool cond1 = false;
        bool cond2 = false;
        bool cond3 = false;
        coordinate temp(colFrom - 1 , rankFrom - 1);
        if(temp.boundryCheck())
            cond1 = (boardView->data(colFrom - 1,rankFrom - 1)!= ' '&&isupper(boardView->data(colFrom - 1,rankFrom - 1)));
        temp.set(colFrom + 1,rankFrom - 1);
        if(temp.boundryCheck())
            cond2 = (boardView->data(colFrom + 1,rankFrom - 1)!= ' '&&isupper(boardView->data(colFrom + 1,rankFrom - 1)));
        cond3 = (rankTo == rankFrom - 1 && (colTo == colFrom - 1||colTo == colFrom + 1));
        if((cond1||cond2)&&cond3)
        {
            std::cout << "st";
            return true;

        }
        if(rankTo == 1)
        {
            emit changePawn('b');
        }

        return false;
    }
    return false;
}

bool ChessAlGBack::moveQueen(int colFrom, int rankFrom, int colTo, int rankTo, ChessBoard *boardView)
{
    if(moveBishop( colFrom,  rankFrom,colTo, rankTo,boardView) || moveRokh(colFrom,  rankFrom,colTo, rankTo,boardView))
        return true;
    return false;
}



char ChessAlGBack::checkCheck(ChessBoard *boardView)
{
    bool w = false;
    bool b = false;
    for (int i = 1; i<=8 ;i++ ) {
        for (int j = 1;j<=8 ; j++) {
            for (int x = 1;x<=8 ;x++ ) {
                for (int y = 1;y<=8 ;y++ ) {
                    if(boardView->data(x,y) == 'k'||boardView->data(x,y) == 'K')
                    {
                        char piceType = tolower(boardView->data(i,j));
                        switch (piceType) {
                        case 'p':
                            if(movepawn(i,j,x,y,boardView))
                            {
                                if(boardView->data(x,y) == 'K')
                                    w = true;
                                if(boardView->data(x,y) == 'k')
                                    b = true;
                            }
                            break;
                        case 'r':
                            if(moveRokh(i,j,x,y,boardView))
                            {
                                if(boardView->data(x,y) == 'K')
                                    w = true;
                                if(boardView->data(x,y) == 'k')
                                    b = true;
                            }
                            break;
                        case 'n':
                            if(moveKnight(i,j,x,y,boardView))
                            {
                                if(boardView->data(x,y) == 'K')
                                    w = true;
                                if(boardView->data(x,y) == 'k')
                                    b = true;
                            }
                            break;
                        case 'b':
                            if(moveBishop(i,j,x,y,boardView))
                            {
                                if(boardView->data(x,y) == 'K')
                                    w = true;
                                if(boardView->data(x,y) == 'k')
                                    b = true;
                            }
                            break;
                        case'k':
                            if(moveKing(i,j,x,y,boardView))
                            {
                                if(boardView->data(x,y) == 'K')
                                    w = true;
                                if(boardView->data(x,y) == 'k')
                                    b = true;
                            }
                            break;
                        case'q':
                            if(moveQueen(i,j,x,y,boardView))
                            {
                                if(boardView->data(x,y) == 'K')
                                    w = true;
                                if(boardView->data(x,y) == 'k')
                                    b = true;
                            }
                            break;

                        }
                    }
                }
            }
        }
    }
//    if(b&&w)
//        return 'n';
    /*else*/ if(b)
        return 'b';
    else if(w)
        return 'w';
//    else
//        return 'n';

}

//bool ChessAlGBack::checkCheckW(ChessBoard *boardView)
//{
//    coordinate *kingP = nullptr;
//    for (int i = 1; i<=8 ;i++ ) {
//        for (int j = 1;j<=8 ; j++){
//            if(boardView->data(i,j)=='K')
//            {
//                if(kingP != nullptr)
//                    break;
//                kingP = new coordinate(i,j);
//                break;
//            }
//        }
//    }
//    for (int x = 1;x<=8 ;x++ ) {
//        for (int y = 1;y<=8 ;y++ ) {
//            if(islower( boardView->data(x,y)))
//            {
//                char piceType = tolower(boardView->data(x,y));
//                switch (piceType) {
//                case 'p':
//                    if(movepawn(i,j,x,y,boardView))
//                    {
//                        if(boardView->data(x,y) == 'K')
//                            w = true;
//                        if(boardView->data(x,y) == 'k')
//                            b = true;
//                    }
//                    break;
//                case 'r':
//                    if(moveRokh(i,j,x,y,boardView))
//                    {
//                        if(boardView->data(x,y) == 'K')
//                            w = true;
//                        if(boardView->data(x,y) == 'k')
//                            b = true;
//                    }
//                    break;
//                case 'n':
//                    if(moveKnight(i,j,x,y,boardView))
//                    {
//                        if(boardView->data(x,y) == 'K')
//                            w = true;
//                        if(boardView->data(x,y) == 'k')
//                            b = true;
//                    }
//                    break;
//                case 'b':
//                    if(moveBishop(i,j,x,y,boardView))
//                    {
//                        if(boardView->data(x,y) == 'K')
//                            w = true;
//                        if(boardView->data(x,y) == 'k')
//                            b = true;
//                    }
//                    break;
//                case'k':
//                    if(moveKing(i,j,x,y,boardView))
//                    {
//                        if(boardView->data(x,y) == 'K')
//                            w = true;
//                        if(boardView->data(x,y) == 'k')
//                            b = true;
//                    }
//                    break;
//                case'q':
//                    if(moveQueen(i,j,x,y,boardView))
//                    {
//                        if(boardView->data(x,y) == 'K')
//                            w = true;
//                        if(boardView->data(x,y) == 'k')
//                            b = true;
//                    }
//                    break;

//                }
//            }

//}



QVector<coordinate> ChessAlGBack::bishopPMoves(int col, int rank, ChessBoard *boardView, char color)
{
    QVector<coordinate> forRet;
    if (color == 'w') {
        for (int i = col + 1,j = rank + 1; i<= 8 && j <= 8 ;i++ ,j++ ) {
            if(isupper(boardView->data(i,j)))
                break;
            if(boardView->data(i,j) == ' ')
            {
                coordinate temp(i,j);
                forRet.push_back(temp);

            }
            else if(isupper(boardView->data(i,j)) == 0)
            {
                coordinate temp(i,j);
                forRet.push_back(temp);
                break;
            }

        }
        for (int i = col - 1,j = rank + 1; i > 0 && j <= 8 ;i-- ,j++ )
        {
            if(isupper(boardView->data(i,j)))
                break;
            if(boardView->data(i,j) == ' ')
            {
                coordinate temp(i,j);
                forRet.push_back(temp);

            }
            else if(isupper(boardView->data(i,j)) == 0)
            {
                coordinate temp(i,j);
                forRet.push_back(temp);
                break;
            }
        }
        for (int i = col - 1,j = rank - 1; i > 0 && j > 0 ;i-- ,j-- )
        {
            if(isupper(boardView->data(i,j)))
                break;
            if(boardView->data(i,j) == ' ')
            {
                coordinate temp(i,j);
                forRet.push_back(temp);

            }
            else if(isupper(boardView->data(i,j)) == 0)
            {
                coordinate temp(i,j);
                forRet.push_back(temp);
                break;
            }
        }
        for (int i = col + 1,j = rank - 1; i <= 8 && j > 0 ;i++ ,j-- )
        {
            if(isupper(boardView->data(i,j)))
                break;
            if(boardView->data(i,j) == ' ')
            {
                coordinate temp(i,j);
                forRet.push_back(temp);

            }
            else if(isupper(boardView->data(i,j)) == 0)
            {
                coordinate temp(i,j);
                forRet.push_back(temp);
                break;
            }
        }
    }
    else
    {
        for (int i = col + 1,j = rank + 1; i<= 8 && j <= 8 ;i++ ,j++ ) {
            if (isupper(boardView->data(i,j))){
                coordinate temp(i,j);
                forRet.push_back(temp);
                break;
            }
            if(boardView->data(i,j) == ' ')
            {
                coordinate temp(i,j);
                forRet.push_back(temp);
            }
            else if (isupper(boardView->data(i,j)) == 0)
                break;

        }
        for (int i = col - 1,j = rank + 1; i > 0 && j <= 8 ;i-- ,j++ ) {
            if (isupper(boardView->data(i,j))){
                coordinate temp(i,j);
                forRet.push_back(temp);
                break;
            }
            if(boardView->data(i,j) == ' ')
            {
                coordinate temp(i,j);
                forRet.push_back(temp);
            }
            else if (isupper(boardView->data(i,j)) == 0)
                break;

        }
        for (int i = col - 1,j = rank - 1; i > 0 && j > 0  ;i-- ,j-- ) {
            if (isupper(boardView->data(i,j))){
                coordinate temp(i,j);
                forRet.push_back(temp);
                break;
            }
            if(boardView->data(i,j) == ' ')
            {
                coordinate temp(i,j);
                forRet.push_back(temp);
            }
            else if (isupper(boardView->data(i,j)) == 0)
                break;

        }
        for (int i = col + 1,j = rank - 1; i<= 8 && j > 0  ;i++ ,j-- ) {
            if (isupper(boardView->data(i,j))){
                coordinate temp(i,j);
                forRet.push_back(temp);
                break;
            }
            if(boardView->data(i,j) == ' ')
            {
                coordinate temp(i,j);
                forRet.push_back(temp);
            }
            else if (isupper(boardView->data(i,j)) == 0)
                break;

        }

    }
    return forRet;

}

QVector<coordinate> ChessAlGBack::rokhPMoves(int col, int rank, ChessBoard * boardView,char color)
{
    QVector<coordinate> forRet;
    if (color == 'w'){

        for (int i = col + 1;i <= 8 ; i++) {

            if (isupper(boardView->data(i,rank)))
                break;
            if (boardView->data(i,rank) == ' ')
            {
                coordinate temp(i,rank);
                forRet.push_back(temp);
            }
            else if (isupper(boardView->data(i,rank)) == 0)
            {
                coordinate temp(i,rank);
                forRet.push_back(temp);
                break;
            }

        }
        for (int i = col - 1;i > 0 ; i--) {

            if (isupper(boardView->data(i,rank)))
                break;
            if (boardView->data(i,rank) == ' ')
            {
                coordinate temp(i,rank);
                forRet.push_back(temp);
            }
            else if (isupper(boardView->data(i,rank)) == 0)
            {
                coordinate temp(i,rank);
                forRet.push_back(temp);
                break;
            }
        }
        for (int i = rank + 1;i <= 8 ; i++) {

            if (isupper(boardView->data(col,i)))
                break;
            if (boardView->data(col,i) == ' ')
            {
                coordinate temp(col,i);
                forRet.push_back(temp);
            }
            else if (isupper(boardView->data(col,i)) == 0)
            {
                coordinate temp(col,i);
                forRet.push_back(temp);
                break;
            }
        }
        for (int i = rank - 1;i > 0 ; i--) {

            if (isupper(boardView->data(col,i)))
                break;
            if (boardView->data(col,i) == ' ')
            {
                coordinate temp(col,i);
                forRet.push_back(temp);
            }
            else if (isupper(boardView->data(col,i)) == 0)
            {
                coordinate temp(col,i);
                forRet.push_back(temp);
                break;
            }

        }
    }
    else
    {
        for (int i = col + 1;i <= 8 ; i++) {

            if (isupper(boardView->data(i,rank))){
                coordinate temp(i,rank);
                forRet.push_back(temp);
                break;
            }
            if(boardView->data(i,rank) == ' ')
            {
                coordinate temp(i,rank);
                forRet.push_back(temp);
            }
            else if (isupper(boardView->data(i,rank)) == 0)
                break;
        }
        for (int i = col - 1;i > 0 ; i--) {

            if (isupper(boardView->data(i,rank))){
                coordinate temp(i,rank);
                forRet.push_back(temp);
                break;
            }
            if(boardView->data(i,rank) == ' ')
            {
                coordinate temp(i,rank);
                forRet.push_back(temp);
            }
            else if (isupper(boardView->data(i,rank)) == 0)
            {

                break;
            }

        }
        for (int i = rank + 1;i < 8 ; i++) {

            if (isupper(boardView->data(col,i))){
                coordinate temp(col,i);
                forRet.push_back(temp);
                break;
            }
            if(boardView->data(col,i) == ' ')
            {
                coordinate temp(col,i);
                forRet.push_back(temp);
            }
            else if (isupper(boardView->data(col,i)) == 0)
            {
                break;
            }

        }
        for (int i = rank - 1;i > 0 ; i--) {

            if (isupper(boardView->data(col,i))){
                coordinate temp(col,i);
                forRet.push_back(temp);
                break;
            }
            if(boardView->data(col,i) == ' ')
            {
                coordinate temp(col,i);
                forRet.push_back(temp);
            }
            else if (isupper(boardView->data(col,i)) == 0)
            {
                break;
            }
        }
    }
    return forRet;

}

QVector<coordinate> ChessAlGBack::knightPMoves(int col, int rank)
{
    //it could be edited


    QVector <coordinate> forRet;
    coordinate temp(col-1,rank - 2);
    if(temp.boundryCheck())
    forRet.push_back(temp);


    temp.set(col + 1,rank - 2);
    if(temp.boundryCheck())
    forRet.push_back(temp);


    temp.set(col - 2,rank - 1);
    if(temp.boundryCheck())
    forRet.push_back(temp);


    temp.set(col + 2,rank - 1);
    if(temp.boundryCheck())
    forRet.push_back(temp);


    temp.set(col - 2,rank + 1);
    if(temp.boundryCheck())
    forRet.push_back(temp);


    temp.set(col + 2,rank + 1);
    if(temp.boundryCheck())
    forRet.push_back(temp);


    temp.set(col - 1,rank + 2);
    if(temp.boundryCheck())
    forRet.push_back(temp);


    temp.set(col + 1,rank + 2);
    if(temp.boundryCheck())
    forRet.push_back(temp);

    return forRet;
}

QVector<coordinate> ChessAlGBack::kingPMoves(int col, int rank)
{
    QVector <coordinate> forRet;
    coordinate temp(col + 1, rank + 1);
    if(temp.boundryCheck())
        forRet.push_back(temp);
    temp.set(col ,rank + 1);
    if(temp.boundryCheck())
        forRet.push_back(temp);
    temp.set(col - 1,rank + 1);
    if(temp.boundryCheck())
        forRet.push_back(temp);
    temp.set(col - 1,rank);
    if(temp.boundryCheck())
        forRet.push_back(temp);
    temp.set(col - 1 ,rank - 1);
    if(temp.boundryCheck())
        forRet.push_back(temp);
    temp.set(col ,rank - 1);
    if(temp.boundryCheck())
        forRet.push_back(temp);
    temp.set(col + 1,rank - 1);
    if(temp.boundryCheck())
        forRet.push_back(temp);
    temp.set(col + 1 ,rank);
    if(temp.boundryCheck())
        forRet.push_back(temp);
    return forRet;
}

void ChessAlGBack::boardExtract(ChessBoard *inputB)
{
    for (int i = 0; i < 8 ; i++) {
        for (int j = 0; j < 8 ; j++) {
        board[i][j] = inputB->data(i+1,j+1);
        }
    }
}

history *ChessAlGBack::getHistory()
{
    return m_history;
}



