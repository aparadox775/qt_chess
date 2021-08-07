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
    if(logs.size() != 0){
        int tempi = logs.size();
        log temp(logs.at(logs.size()-1));
        return temp;
    }

}

log history::secondLastMove()
{
    if(logs.size() >= 2){
        log temp(logs.at(logs.size() - 2));
        return temp;
    }
}

