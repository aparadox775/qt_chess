#ifndef COORDINATE_H
#define COORDINATE_H


struct coordinate
{
    int col, rank;
    coordinate(int col,int rank);
    bool boundryCheck();
    void set(int col,int rank);
};

#endif // COORDINATE_H
