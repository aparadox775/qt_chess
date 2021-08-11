#ifndef LOG_H
#define LOG_H

#include "coordinate.h"
struct Plog
{
    coordinate from;
    coordinate to;
    char pice;
    Plog(char pice,coordinate fromC,coordinate toC);
};
#endif // LOG_H
