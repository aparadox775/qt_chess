#ifndef WINERDIALOGE_H
#define WINERDIALOGE_H

#include <QDialog>

namespace Ui {
class winerDialoge;
}

class winerDialoge : public QDialog
{
    Q_OBJECT

public:
    explicit winerDialoge(QWidget *parent = nullptr);
    void setWiner(QString);
    ~winerDialoge();

private:
    Ui::winerDialoge *ui;
};

#endif // WINERDIALOGE_H
