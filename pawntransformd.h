#ifndef PAWNTRANSFORMD_H
#define PAWNTRANSFORMD_H

#include <QDialog>

namespace Ui {
class pawnTransformD;
}

class pawnTransformD : public QDialog
{
    Q_OBJECT

public:
    explicit pawnTransformD(QWidget *parent = nullptr);
    ~pawnTransformD();
    void black();
    void white();

private slots:
    void queenS();
    void bishopS();
    void rokhS();
    void knightS();
signals:
    void convert(char);
private:
    Ui::pawnTransformD *ui;
};

#endif // PAWNTRANSFORMD_H
