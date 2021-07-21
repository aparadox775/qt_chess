#ifndef CHESSVIEW_H
#define CHESSVIEW_H

#include "chessboard.h"
#include <QIcon>
#include <QMap>
#include <QMouseEvent>
#include <QPainter>
#include <QPointer>
#include <QVector>
#include <QWidget>

class ChessView : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QSize fieldSize
                READ fieldSize WRITE setFieldSize
                NOTIFY fieldSizeChanged)
public:
    explicit ChessView(QWidget *parent = nullptr);
    void setBoard(ChessBoard *);
    ChessBoard *board() const;
    QSize sizeHint() const;
    const QSize &fieldSize() const;
    void setFieldSize(const QSize &newFieldSize);
    QRect fieldRect(int column, int rank) const;
    void paintEvent(QPaintEvent *);
    void drawRank(QPainter *painter, int rank);
    void drawColumn(QPainter *painter, int column);
    void drawField(QPainter *painter, int column, int rank);
    void setPiece(char type, const QIcon &icon);
    QIcon piece(char type) const;
    QPoint fieldAt(const QPoint &pt) const;
    void mouseReleaseEvent(QMouseEvent *event);
private:
    QPointer<ChessBoard> m_board;
    QMap<char, QIcon> m_pieces;
    QSize m_fieldSize;
    void drawPiece(QPainter *painter, int column, int rank);
signals:
    void clicked(const QPoint &);
    void fieldSizeChanged();
};

#endif // CHESSVIEW_H
