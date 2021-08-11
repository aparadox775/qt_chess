#include "winerdialoge.h"
#include "ui_winerdialoge.h"

winerDialoge::winerDialoge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::winerDialoge)
{
    ui->setupUi(this);
}

void winerDialoge::setWiner(QString winerName)
{
    ui->winerName->setText(winerName);
    this->show();

}

winerDialoge::~winerDialoge()
{
    delete ui;
}
