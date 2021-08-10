#include "history.h"

history::history(QObject *parent) : QObject(parent)
{
    for(bool &temp:rokh)
    {
        temp = false;
    }

}

void history::addlog(char pice, coordinate from, coordinate to)
{
    if(pice == 'R')
    {
        if(from.col == 1)
        {
            rokh[0] = true;
        }
        if(from.col == 8)
        {
            rokh[1] = true;
        }
    }
    if(pice == 'r')
    {
        if(from.col == 1)
        {
            rokh[2] = true;
        }
        if(from.col == 8)
        {
            rokh[3] = true;
        }
    }
    log temp(pice,from,to);
    logs.push_back(temp);


}

bool history::kingHasMoved(char color)
{
    switch (color) {
    case 'w':
        for(log temp:qAsConst(logs))
        {
            if(temp.pice == 'K')
                return true;

        }
        return false;
        break;
    case 'b':
        for(log temp:qAsConst(logs))
        {
            if(temp.pice == 'k')
                return true;

        }
        return false;

    }
    return true;
}

QVector<bool> history::rokhHasMoved(char color)
{
    QVector<bool> forRet;
    switch (color) {
    case 'w':
        forRet.push_back(rokh[0]);
        forRet.push_back(rokh[1]);
        break;
    case 'b':
        forRet.push_back(rokh[2]);
        forRet.push_back(rokh[3]);
        break;
    }
    return forRet;

}

log history::lastMove()
{
    if(logs.size() != 0){
//        int tempi = logs.size();
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

