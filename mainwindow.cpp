#include "foxandhounds.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "prochess.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_selectedField = nullptr;


    m_algorithm = new ProChess(this);
    m_back = dynamic_cast<ProChess *> (m_algorithm)->back();
    m_history = dynamic_cast<ProChess *> (m_algorithm)->historyGet();


    m_algorithm->newGame();
    ui->widget->setBoard(m_algorithm->board());
    ui->widget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    ui->widget->setFieldSize(QSize(70, 70));

    ui->widget->setPiece('P', QIcon(":/icons/wp.png")); // pawn
    ui->widget->setPiece('K', QIcon(":/icons/wk.png")); // king
    ui->widget->setPiece('Q', QIcon(":/icons/wq.png")); // queen
    ui->widget->setPiece('R', QIcon(":/icons/wr.png")); // rook
    ui->widget->setPiece('N', QIcon(":/icons/wn.png")); // knight
    ui->widget->setPiece('B', QIcon(":/icons/wb.png")); // bishop

    ui->widget->setPiece('p', QIcon(":/icons/bp.png")); // pawn
    ui->widget->setPiece('k', QIcon(":/icons/bk.png")); // king
    ui->widget->setPiece('q', QIcon(":/icons/bq.png")); // queen
    ui->widget->setPiece('r', QIcon(":/icons/br.png")); // rook
    ui->widget->setPiece('n', QIcon(":/icons/bn.png")); // knight
    ui->widget->setPiece('b', QIcon(":/icons/bb.png")); // bishop
    layout()->setSizeConstraint(QLayout::SetFixedSize);


    //for asking for name at begining
    //    initNewGame();
    ui->undoButt->setDisabled(true);

    //seting width fo push buttons
    ui->quit->setFixedWidth(ui->newGame->width());
    ui->newGame->setFixedWidth(ui->newGame->width());

    //connect signal and slots
    connect(ui->newGame, &QPushButton::clicked, this, &MainWindow::initNewGame);
    connect(ui->quit, &QPushButton::clicked, this, &MainWindow::quit);
    connect(ui->startNewGmae, &QAction::triggered, this, &MainWindow::initNewGame);
    connect(ui->quitMenu, &QAction::triggered, this, &MainWindow::quit);
    connect(ui->widget, &ChessView::clicked,this,&MainWindow::viewClicked);
    connect(ui->undoButt,&QPushButton::clicked,ui->widget,&ChessView::undo);
    connect(ui->undoButt,&QPushButton::clicked,this,&MainWindow::restorePice);
    connect(ui->undoButt,&QPushButton::clicked,dynamic_cast<ProChess *>(m_algorithm),&ProChess::switchPlayer);
    connect(ui->undoButt,&QPushButton::clicked,m_history,&history::popBack);
    connect(ui->actionundo,&QAction::triggered,ui->widget,&ChessView::undo);
    connect(dynamic_cast<ProChess *>(m_algorithm),&ProChess::moveMade,this,&MainWindow::moved);
    connect(ui->undoButt,&QPushButton::clicked,this,&MainWindow::undo);
    connect(dynamic_cast<ProChess *>(m_algorithm),&ProChess::check,this,&MainWindow::Check);
    connect(dynamic_cast<ProChess *>(m_algorithm),&ProChess::elimPice,this,&MainWindow::elimPice);
    connect(dynamic_cast<ProChess *>(m_algorithm),&ProChess::elimPice,ui->widget_2,&eliminated::elimP);
    connect(dynamic_cast<ProChess *>(m_algorithm),&ProChess::gameOver,this,&MainWindow::checkmatePoint);
    connect(dynamic_cast<ProChess *>(m_algorithm),&ProChess::repetitive,this,&MainWindow::repetitiveMove);
    connect(dynamic_cast<ProChess *>(m_algorithm),&ProChess::pawnPasedMid,this,&MainWindow::pawnPassed);
//    connect(m_back,&ChessAlGBack::elimPice,this,&MainWindow::thread);
    this->setWindowTitle("chess");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initNewGame()
{
    configurationdialog dialog(this);
//    pawnTransformD ddd(this);
//    pawnTransformD ddd(this);
//    ddd.
//    ddd.black();

    if (dialog.exec() == QDialog::Rejected) //if user click on cancel it will do nothing
    {
        return;
    }
    else if (dialog.player1Name() != "" && dialog.player2Name() != "")
    {
        // set names frome the dialog box
        ui->player1PScores->setText(dialog.player1Name() + "\'s scores :");
        ui->player1NScores->setText(dialog.player1Name() + "\'s negative :");
        ui->player2PScores->setText(dialog.player2Name() + "\'s scores :");
        ui->player2NScores->setText(dialog.player2Name() + "\'s negative :");
    }

    //reset scores
    p1p = 0;
    p1n = 0;
    p2p = 0;
    p2n = 0;


    ui->player1PScoresO->setText(QString::number(0));
    ui->player1NScoresO->setText(QString::number(0));
    ui->player2PScoresO->setText(QString::number(0));
    ui->player2NScoresO->setText(QString::number(0));

    m_algorithm->newGame();
    ui->widget->setBoard(m_algorithm->board());
    ui->widget_2->reset();
    return;
}

void MainWindow::quit()
{
    this->close();
}


void MainWindow::viewClicked(const QPoint &field)
{

    m_undoView = ui->widget;
    if(m_clickPoint.isNull())
    {
        if(ui->widget->board()->data(field.x(), field.y()) != ' '&& m_back->turnCheck(ui->widget->board()->data(field.x(), field.y()),m_algorithm->currentPlayer()))
        {

            m_clickPoint = field;
            m_selectedField = new ChessView::FieldHighlight(
            field.x(), field.y(), QColor(255, 0, 0, 75)
            );
            ui->widget->addHighlight(m_selectedField);
//
            highlight(field.x(),field.y());
            m_clickPoint.setX(field.x());
            m_clickPoint.setY(field.y());

        }
    } else
    {
        if(field != m_clickPoint)
        {
            bool tr = false;
            if(dynamic_cast<ProChess *>(m_algorithm)->moveP(m_clickPoint.x(), m_clickPoint.y(), field.x(), field.y()))
                tr = true;
              lastElimedPice = ' ';
              m_algorithm->move(m_clickPoint, field);
//            ui->widget->board()->movePiece(
//            m_clickPoint.x(), m_clickPoint.y(), field.x(), field.y()
//            );
//              posible(field.x(),field.y(),true);
                if(tr)
              thread(field.x(),field.y());
              updatePoints();
        };
        m_clickPoint = QPoint();
        ui->widget->removeHighlight(m_selectedField);

        removeHighlight();
        delete m_selectedField;
        m_selectedField = nullptr;

        updateUndo();
        updatePoints();
    }


}

void MainWindow::undo()
{
//    ui->widget = m_undoView;
    moveCount  = 0;
    if(m_algorithm->currentPlayer() == ChessAlgorithm::Player1)
    {
        p1n -= 5;
    }
    else if(m_algorithm->currentPlayer() == ChessAlgorithm::Player2)
    {
        p2n -= 5;
    }
    updatePoints();
    updateUndo();

}

void MainWindow::moved()
{
    moveCount ++;
}

void MainWindow::updateUndo()
{
    if(moveCount == 0)
    {
        ui->undoButt->setDisabled(true);
    }
    else
    {
        ui->undoButt->setEnabled(true);
    }

}

void MainWindow::updatePoints()
{
    ui->player1NScoresO->setText(QString::number(p1n));
    ui->player1PScoresO->setText(QString::number(p1p));
    ui->player2NScoresO->setText(QString::number(p2n));
    ui->player2PScoresO->setText(QString::number(p2p));
}

void MainWindow::Check(char ch)
{
    if(ch == 'b')
    {
        p1p += 10;
    }
    if(ch == 'w')
    {
        p2p += 10;
    }
    updatePoints();
}

void MainWindow::elimPice(char pice)
{
    lastElimedPice = pice;
    switch (pice) {
    case 'p':
        p1p +=2;
        break;
    case 'r':
        p1p +=8;
        break;
    case 'n':
        p1p +=8;
        break;
    case 'b':
        p1p +=8;
        break;
    case 'q':
        p1p +=15;
        break;
    case 'P':
        p2p +=2;
        break;
    case 'R':
        p2p +=8;
        break;
    case 'N':
        p2p +=8;
        break;
    case 'B':
        p2p +=8;
        break;
    case 'Q':
        p2p +=15;
        break;
    case ' ':
        break;

    }
    //    updatePoints();
}

void MainWindow::threadPoint(char pice)
{
    switch (pice) {
    case 'p':
        p1p +=1;
        break;
    case 'r':
        p1p +=2;
        break;
    case 'n':
        p1p +=2;
        break;
    case 'b':
        p1p +=2;
        break;
    case 'q':
        p1p +=5;
        break;
    case 'P':
        p2p +=1;
        break;
    case 'R':
        p2p +=2;
        break;
    case 'N':
        p2p +=2;
        break;
    case 'B':
        p2p +=2;
        break;
    case 'Q':
        p2p +=5;
        break;
    case ' ':
        break;

    }
//    updatePoints();
}

void MainWindow::checkmatePoint(char color)
{
    color == 'w'? p1p += 40:p2p += 40;
}

void MainWindow::restorePice()
{
    if(lastElimedPice != ' ')
    {
        ui->widget_2->undo();
    }
}

void MainWindow::repetitiveMove()
{
    if(m_algorithm->currentPlayer() == ChessAlgorithm::Player1)
    {
        p1n--;
        updatePoints();
    }
    if(m_algorithm->currentPlayer() == ChessAlgorithm::Player2)
    {
        p2n--;
        updatePoints();
    }
}

void MainWindow::pawnPassed(char color)
{
    switch (color) {
    case 'w':
        p1p +=1;
        break;
    case 'b':
        p2p +=1;
        break;

    }
    updatePoints();

}

void MainWindow::posible(int col, int rank)
{
    int p1p = this->p1p,p1n= this->p1n,p2p= this->p2p,p2n= this->p2n;

//    char color;s
//    isupper(m_algorithm->board()->data(col,rank))?color = 'w':color = 'b';
    for (int i = 1; i <=8 ; i++) {
        for (int j = 1; j <=8 ; j++) {
            if(dynamic_cast<ProChess *>(m_algorithm)->moveP(col,rank,i,j))
            {

                ChessView::FieldHighlight *temp = new ChessView::FieldHighlight(
                            i, j, QColor(255, 0, 0, 50));
                m_selectedFields.push_back(temp);

            }

        }
    }
        m_selectedFieldsCopy = m_selectedFields;
        m_selectedFields.clear();
        this->p1p = p1p;
        this->p1n = p1n;
        this->p2p = p2p;
        this->p2n = p2n;

}

void MainWindow::highlight(int col,int rank)
{
    posible(col,rank);
    for (ChessView::FieldHighlight *temp : qAsConst(m_selectedFieldsCopy)) {
        ui->widget->addHighlight(temp);
    }
}

void MainWindow::removeHighlight()
{
    for (ChessView::FieldHighlight *temp : qAsConst(m_selectedFieldsCopy)) {
        ui->widget->removeHighlight(temp);
        delete temp;
    }
//    m_selectedFields.clear();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    int smol;
    ui->widget->width() <= ui->widget->height()? smol = ui->widget->width() : smol = ui->widget->height();
    QSize temp;
//    temp.setHeight((smol-12)/8);
//    temp.setWidth((smol-12)/8);
    temp.scale(ui->widget->size()/8,Qt::KeepAspectRatio);
    //    smol -= 5;

    //    ui->widget->setFieldSize(temp);
}

void MainWindow::thread(int col, int rank)
{
    for(int i = 1;i<=8;i++)
    {
        for(int j = 1;j<=8;j++)
        {
            if(dynamic_cast<ProChess *>(m_algorithm)->moveP(col,rank,i,j))
            {
                if(m_algorithm->board()->data(i,j) != ' ')
                {
                    threadPoint(m_algorithm->board()->data(i,j));
                    updatePoints();
                }
            }

        }
    }

}

