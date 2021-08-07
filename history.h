#ifndef HISTORY_H
#define HISTORY_H

#include <QObject>
//#include "chessalgback.h"
#include "coordinate.h"
struct log
{
    coordinate from;
    coordinate to;
    char pice;
    log(char pice,coordinate fromC,coordinate toC):from(fromC),to(toC)
    {
        this->pice = pice;
    }
};

class history : public QObject
{
    Q_OBJECT
public:
    explicit history(QObject *parent = nullptr);
    void addlog(char,coordinate,coordinate);
    log lastMove();
    log secondLastMove();
private:
    QVector <log> logs;


signals:

};

#endif // HISTORY_H
