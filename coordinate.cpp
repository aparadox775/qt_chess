#include "coordinate.h"

coordinate::coordinate(int col, int rank) {this->col = col;this ->rank = rank;}

bool coordinate::boundryCheck()
{
    if (col < 1 || rank < 1)
        return false;
    else if(col > 8 || rank > 8)
        return false;
    return true;
}

void coordinate::set(int col, int rank) {this->col = col;this ->rank = rank;}
