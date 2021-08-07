#include "eliminated.h"

eliminated::eliminated(QWidget *parent) : QWidget(parent)
{
    setPiece('P', QIcon(":/icons/wp.png")); // pawn
    setPiece('K', QIcon(":/icons/wk.png")); // king
    setPiece('Q', QIcon(":/icons/wq.png")); // queen
    setPiece('R', QIcon(":/icons/wr.png")); // rook
    setPiece('N', QIcon(":/icons/wn.png")); // knight
    setPiece('B', QIcon(":/icons/wb.png")); // bishop

    setPiece('p', QIcon(":/icons/bp.png")); // pawn
    setPiece('k', QIcon(":/icons/bk.png")); // king
    setPiece('q', QIcon(":/icons/bq.png")); // queen
    setPiece('r', QIcon(":/icons/br.png")); // rook
    setPiece('n', QIcon(":/icons/bn.png")); // knight
    setPiece('b', QIcon(":/icons/bb.png")); // bishop
}
void eliminated::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    for (int r = 1;r <=2 ;r++ ) {
        for (int c = 1;c <= 15 ; c++) {
            painter.save();
            drawField(&painter, c, r);
            painter.restore();

        }
    }
        for (int c = 1;c < indexW ; c++) {
            drawPiece(&painter,c,1);

        }
        for (int c = 1;c < indexB ; c++) {
            drawPiece(&painter,c,2);

        }


}

void eliminated::drawField(QPainter *painter, int column, int rank)
{
     QRect rect = fieldRect(column, rank);
     QColor fillColor = (column + rank) % 2 ? palette().color(QPalette::Background) : palette().color(QPalette::Background);
     painter->setPen(palette().color(QPalette::Dark));
     painter->setBrush(fillColor);
     painter->drawRect(rect);

}

QRect eliminated::fieldRect(int column, int rank) const
{

    const QSize fs(40,40);
    QPoint topLeft((column - 1) * fs.width(),
                   (2 - rank) * fs.height());
    QRect fRect = QRect(topLeft, fs);

    return fRect/*.translated(offset + 4, 0)*/;


}

void eliminated::setPiece(char type, const QIcon &icon)
{
    m_pieces.insert(type, icon);
    update();

}

QIcon eliminated::piece(char type) const
{
    return m_pieces.value(type, QIcon());
}

void eliminated::elimP(char pice)
{
    if(isupper(pice))
    {
        whiteP.push_back(pice);
        indexW ++;
        last = 'w';
    }

    if(islower(pice))
    {
        blackP.push_back(pice);
        indexB ++;
        last = 'b';
    }
    update();
}

void eliminated::undo()
{
    if(last == 'w')
    {
        whiteP.pop_back();
        indexW --;
        last = 'n';
    }
    if(last == 'b')
    {
        blackP.pop_back();
        indexB --;
        last = 'n';

    }
    update();
}

void eliminated::reset()
{
    whiteP.clear();
    blackP.clear();
    indexB = 1;
    indexW = 1;
    update();
}

void eliminated::drawPiece(QPainter *painter, int column, int rank)
{
    QRect rect = fieldRect(column, rank);
    char value;
    if (rank == 1)
    {
        value = whiteP[column - 1];
    }
    if(rank == 2)
    {
        value = blackP[column - 1];
    }
    if (value != ' ')
    {
        QIcon icon = piece(value);
        if (!icon.isNull())
        {
            icon.paint(painter, rect, Qt::AlignCenter);
        }
    }


}
