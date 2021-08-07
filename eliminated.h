#ifndef ELIMINATED_H
#define ELIMINATED_H

#include <QWidget>
#include <QIcon>
#include <QList>
#include <QMap>
#include <QMouseEvent>
#include <QPainter>
#include <QPointer>
#include <QVector>
#include <QWidget>
#include "coordinate.h"

//struct

class eliminated : public QWidget
{
    Q_OBJECT
public:
    explicit eliminated(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void drawField(QPainter *painter, int column, int rank);
    QRect fieldRect(int column, int rank) const;
    void setPiece(char type, const QIcon &icon);
     QIcon piece(char type) const;

public slots:
     void elimP(char);
     void undo();
     void reset();
private:
    QMap<char, QIcon> m_pieces;
    void drawPiece(QPainter *painter, int column, int rank);
    QVector <char> blackP;
    QVector <char> whiteP;
    char last = 'n';
    int indexB = 1;
    int indexW = 1;
signals:

};

#endif // ELIMINATED_H
