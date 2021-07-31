#ifndef CHESSVIEW_H
#define CHESSVIEW_H

#include "chessboard.h"
#include <QIcon>
#include <QList>
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
    class Highlight
    {
    public:
        Highlight() {}
        virtual ~Highlight() {}
        virtual int type() const { return 0; }
    };

    class FieldHighlight : public Highlight
    {
    public:
        enum
        {
            Type = 1
        };
        FieldHighlight(int column, int rank, QColor color)
            : m_field(column, rank), m_color(color) {}
        inline int column() const { return m_field.x(); }
        inline int rank() const { return m_field.y(); }
        inline QColor color() const { return m_color; }
        int type() const { return Type; }

    private:
        QPoint m_field;
        QColor m_color;
    };

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

    void addHighlight(Highlight *hl);
    void removeHighlight(Highlight *hl);
    inline Highlight *highlight(int index) const
    {
        return m_highlights.at(index);
    }
    inline int highlightCount() const
    {
        return m_highlights.size();
    }

private:
    QPointer<ChessBoard> m_board;
    QMap<char, QIcon> m_pieces;
    QSize m_fieldSize;
    void drawPiece(QPainter *painter, int column, int rank);
    QList<Highlight *> m_highlights;
    void drawHighlights(QPainter *painter);
signals:
    void clicked(const QPoint &);
    void fieldSizeChanged();
public slots:
    void undo();
};

#endif // CHESSVIEW_H
