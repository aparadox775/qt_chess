#include "chessalgback.h"

ChessAlGBack::ChessAlGBack(QObject *parent):QObject(parent)
{

}

bool ChessAlGBack::turnCheck(char input, ChessAlgorithm::Player theTurn)
{
    if (isupper( input) && theTurn == ChessAlgorithm::Player1)
        return true;
    if (isupper(input) == 0 && theTurn == ChessAlgorithm::Player2)
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
    QVector<coordinate *> al = knightPMoves(colFrom,rankFrom);
//    int st = this->knightPMoves(colFrom,rankFrom).indexOf(tempCor);
    for(coordinate * crT: al)
    {
        if (crT->col == tempCor->col && crT->rank == tempCor->rank)
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

QVector<coordinate *> ChessAlGBack::knightPMoves(int col, int rank)
{
    //it could be edited


    QVector <coordinate *> forRet;
    coordinate * temp = new coordinate(col-1,rank - 2);
    if(temp->boundryCheck())
    forRet.push_back(temp);


    temp = new coordinate(col + 1,rank - 2);
    if(temp->boundryCheck())
    forRet.push_back(temp);


    temp = new coordinate(col - 2,rank - 1);
    if(temp->boundryCheck())
    forRet.push_back(temp);


    temp = new coordinate(col + 2,rank - 1);
    if(temp->boundryCheck())
    forRet.push_back(temp);


    temp = new coordinate(col - 2,rank + 1);
    if(temp->boundryCheck())
    forRet.push_back(temp);


    temp = new coordinate(col + 2,rank + 1);
    if(temp->boundryCheck())
    forRet.push_back(temp);


    temp = new coordinate(col - 1,rank + 2);
    if(temp->boundryCheck())
    forRet.push_back(temp);


    temp = new coordinate(col + 1,rank + 2);
    if(temp->boundryCheck())
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
