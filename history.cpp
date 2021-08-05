#include "history.h"

history::history(QObject *parent) : QObject(parent)
{

}

void history::addlog(char pice, coordinate from, coordinate to)
{
    log temp(pice,from,to);
    logs.push_back(temp);

}

log history::lastMove()
{
    log temp(*logs.end());
    return temp;
}
