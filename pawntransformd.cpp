#include "pawntransformd.h"
#include "ui_pawntransformd.h"

pawnTransformD::pawnTransformD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pawnTransformD)
{
    ui->setupUi(this);
//    QIcon temp(QIcon(":/icons/wq.png"));
    connect(ui->queen,&QPushButton::clicked,this,&pawnTransformD::queenS);
    connect(ui->knight,&QPushButton::clicked,this,&pawnTransformD::knightS);
    connect(ui->bishop,&QPushButton::clicked,this,&pawnTransformD::bishopS);
    connect(ui->rokh,&QPushButton::clicked,this,&pawnTransformD::rokhS);


}

pawnTransformD::~pawnTransformD()
{
    delete ui;
}

void pawnTransformD::black()
{

    ui->queen->setIcon(QIcon(":/icons/bq.png"));
    ui->queen->setIconSize(ui->queen->size());

    ui->bishop->setIcon(QIcon(":/icons/bb.png"));
    ui->bishop->setIconSize(ui->bishop->size());

    ui->knight->setIcon(QIcon(":/icons/bn.png"));
    ui->knight->setIconSize(ui->knight->size());

    ui->rokh->setIcon(QIcon(":/icons/br.png"));
    ui->rokh->setIconSize(ui->rokh->size());
    this->show();
}

void pawnTransformD::white()
{

    ui->queen->setIcon(QIcon(":/icons/wq.png"));
    ui->queen->setIconSize(ui->queen->size()*2);

    ui->bishop->setIcon(QIcon(":/icons/wb.png"));
    ui->bishop->setIconSize(ui->bishop->size()*2);

    ui->knight->setIcon(QIcon(":/icons/wn.png"));
    ui->knight->setIconSize(ui->knight->size()*2);

    ui->rokh->setIcon(QIcon(":/icons/wr.png"));
    ui->rokh->setIconSize(ui->rokh->size()*2);
    this->show();

}

void pawnTransformD::queenS()
{
    emit convert('q');

}

void pawnTransformD::bishopS()
{
    emit convert('b');

}

void pawnTransformD::rokhS()
{
    emit convert('r');

}

void pawnTransformD::knightS()
{
    emit convert('n');
}
