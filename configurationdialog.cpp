#include "configurationdialog.h"
#include "ui_configurationdialog.h"

configurationdialog::configurationdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configurationdialog)
{


    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);


    connect(ui->player1Name,&QLineEdit::textChanged,this,&configurationdialog::updateOKStatus);
    connect(ui->player2Name,&QLineEdit::textChanged,this,&configurationdialog::updateOKStatus);

    this->setWindowTitle("New Game");
}

configurationdialog::~configurationdialog()
{
    delete ui;
}

QString configurationdialog::player1Name() const
{
    return this->ui->player1Name->text();
}

QString configurationdialog::player2Name() const
{
    return this->ui->player2Name->text();

}

void configurationdialog::updateOKStatus()
{
    auto *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setEnabled(!ui->player1Name->text().isEmpty() && !ui->player2Name->text().isEmpty());
}
