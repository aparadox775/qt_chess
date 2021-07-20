#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //for asking for name at begining
    initNewGame();

    //seting width fo push buttons
    ui->quit->setFixedWidth(ui->newGame->width());
    ui->newGame->setFixedWidth(ui->newGame->width());


    //connect signal and slots
    connect(ui->newGame,&QPushButton::clicked,this,&MainWindow::initNewGame);
    connect(ui->quit,&QPushButton::clicked,this,&MainWindow::quit);
    connect(ui->startNewGmae,&QAction::triggered,this,&MainWindow::initNewGame);
    connect(ui->quitMenu,&QAction::triggered,this,&MainWindow::quit);
    this->setWindowTitle("chess");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initNewGame()
{
    configurationdialog dialog(this);

    if (dialog.exec() == QDialog::Rejected)     //if user click on cancel it will do nothing
    {
        return;
    }
    else if(dialog.player1Name() != "" && dialog.player2Name() != "")
    {
        // set names frome the dialog box
        ui->player1PScores->setText(dialog.player1Name()+ "\'s scores :");
        ui->player1NScores->setText(dialog.player1Name()+ "\'s negative :");
        ui->player2PScores->setText(dialog.player2Name()+ "\'s scores :");
        ui->player2NScores->setText(dialog.player2Name()+ "\'s negative :");

    }

    //reset scores
    ui->player1PScoresO->setText(QString::number(0));
    ui->player1NScoresO->setText(QString::number(0));
    ui->player2PScoresO->setText(QString::number(0));
    ui->player2NScoresO->setText(QString::number(0));
    return;

}

void MainWindow::quit()
{
    this->close();
}




