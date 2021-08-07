#include "foxandhounds.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "prochess.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_selectedField = nullptr;
//    m_view = new ChessView;
    m_algorithm = new ProChess(this);
    m_back = dynamic_cast<ProChess *> (m_algorithm)->back();
//    ui->widget_2->setFieldSize(QSize(10,10));


    m_algorithm->newGame();
    ui->widget->setBoard(m_algorithm->board());
    ui->widget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    ui->widget->setFieldSize(QSize(60, 60));

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
    connect(ui->actionundo,&QAction::triggered,ui->widget,&ChessView::undo);
    connect(dynamic_cast<ProChess *>(m_algorithm),&ProChess::moveMade,this,&MainWindow::moved);
    connect(ui->undoButt,&QPushButton::clicked,this,&MainWindow::undo);
    connect(dynamic_cast<ProChess *>(m_algorithm),&ProChess::check,this,&MainWindow::Check);
    connect(dynamic_cast<ProChess *>(m_algorithm),&ProChess::elimPice,this,&MainWindow::elimPice);
    connect(dynamic_cast<ProChess *>(m_algorithm),&ProChess::elimPice,ui->widget_2,&eliminated::elimP);
    connect(dynamic_cast<ProChess *>(m_algorithm),&ProChess::gameOver,this,&MainWindow::checkmatePoint);
    connect(dynamic_cast<ProChess *>(m_algorithm),&ProChess::repetitive,this,&MainWindow::repetitiveMove);
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

        }
    } else
    {
        if(field != m_clickPoint)
        {
              lastElimedPice = ' ';
              m_algorithm->move(m_clickPoint, field);
//            ui->widget->board()->movePiece(
//            m_clickPoint.x(), m_clickPoint.y(), field.x(), field.y()
//            );
              posible(field.x(),field.y(),true);
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

void MainWindow::thread(char pice)
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

void MainWindow::posible(int col, int rank,bool thread)
{
    int p1p = this->p1p,p1n= this->p1n,p2p= this->p2p,p2n= this->p2n;

    char color;
    isupper(m_algorithm->board()->data(col,rank))?color = 'w':color = 'b';
    for (int i = 1; i <=8 ; i++) {
        for (int j = 1; j <=8 ; j++) {

            char piceType = tolower(ui->widget->board()->data(col,rank));
            switch (piceType) {
            case 'p':
                if(dynamic_cast <ProChess *> (m_algorithm) ->back()->movepawn(col,rank,i,j,ui->widget->board()))
                {
                    ChessBoard * temp = new ChessBoard(m_algorithm->board());
                    temp->movePiece(col,rank,i,j);
                    if((m_back->checkCheck(temp) != 'w' && color == 'w'&& m_back->checkCheck(temp) != 'd')||(m_back->checkCheck(temp) != 'b' && color == 'b'&& m_back->checkCheck(temp) != 'd'))
                    {
                        ChessView::FieldHighlight *temp = new ChessView::FieldHighlight(
                                    i, j, QColor(255, 0, 0, 50));
                        m_selectedFields.push_back(temp);
                    }
                    delete temp;
                }
            break;
            case 'r':
                if(dynamic_cast <ProChess *> (m_algorithm) ->back()->moveRokh(col,rank,i,j,ui->widget->board()))
                {
                    ChessBoard * temp = new ChessBoard(m_algorithm->board());
                    temp->movePiece(col,rank,i,j);
                    if((m_back->checkCheck(temp) != 'w' && color == 'w'&& m_back->checkCheck(temp) != 'd')||(m_back->checkCheck(temp) != 'b' && color == 'b'&& m_back->checkCheck(temp) != 'd')){
                        ChessView::FieldHighlight *temp = new ChessView::FieldHighlight(
                                    i, j, QColor(255, 0, 0, 50));
                        m_selectedFields.push_back(temp);
                    }
                }
                break;
            case 'n':
                if(dynamic_cast <ProChess *> (m_algorithm) ->back()->moveKnight(col,rank,i,j,ui->widget->board()))
                {
                    ChessBoard * temp = new ChessBoard(m_algorithm->board());
                    temp->movePiece(col,rank,i,j);
                    if((m_back->checkCheck(temp) != 'w' && color == 'w'&& m_back->checkCheck(temp) != 'd')||(m_back->checkCheck(temp) != 'b' && color == 'b'&& m_back->checkCheck(temp) != 'd')){
                        ChessView::FieldHighlight *temp = new ChessView::FieldHighlight(
                                    i, j, QColor(255, 0, 0, 50));
                        m_selectedFields.push_back(temp);
                    }
                }
                break;
            case 'b':
                if(dynamic_cast <ProChess *> (m_algorithm) ->back()->moveBishop(col,rank,i,j,ui->widget->board()))
                {
                    ChessBoard * temp = new ChessBoard(m_algorithm->board());
                    temp->movePiece(col,rank,i,j);
//                    char temp1 = m_back->checkCheck(temp),temp2 = color == 'w';
                    if((m_back->checkCheck(temp) != 'w' && color == 'w'&& m_back->checkCheck(temp) != 'd')||(m_back->checkCheck(temp) != 'b' && color == 'b'&& m_back->checkCheck(temp) != 'd'))
                    {
                        ChessView::FieldHighlight *temp = new ChessView::FieldHighlight(
                                    i, j, QColor(255, 0, 0, 50));
                        m_selectedFields.push_back(temp);
                    }
                }
                break;
            case'k':
                if(dynamic_cast <ProChess *> (m_algorithm) ->back()->moveKing(col,rank,i,j,ui->widget->board()))
                {
                    ChessBoard * temp = new ChessBoard(m_algorithm->board());
                    temp->movePiece(col,rank,i,j);
                    if((m_back->checkCheck(temp) != 'w' && color == 'w'&& m_back->checkCheck(temp) != 'd')||(m_back->checkCheck(temp) != 'b' && color == 'b'&& m_back->checkCheck(temp) != 'd')){
                        ChessView::FieldHighlight *temp = new ChessView::FieldHighlight(
                                    i, j, QColor(255, 0, 0, 50));
                        m_selectedFields.push_back(temp);
                    }
                }
                break;
            case'q':
                if(dynamic_cast <ProChess *> (m_algorithm) ->back()->moveQueen(col,rank,i,j,ui->widget->board()))
                {
                    ChessBoard * temp = new ChessBoard(m_algorithm->board());
                    temp->movePiece(col,rank,i,j);
                    if((m_back->checkCheck(temp) != 'w' && color == 'w'&& m_back->checkCheck(temp) != 'd')||(m_back->checkCheck(temp) != 'b' && color == 'b'&& m_back->checkCheck(temp) != 'd')){
                        ChessView::FieldHighlight *temp = new ChessView::FieldHighlight(
                                    i, j, QColor(255, 0, 0, 50));
                        m_selectedFields.push_back(temp);
                    }
                }
                break;

            }

        }
    }
    if(thread == false){
        m_selectedFieldsCopy = m_selectedFields;
        m_selectedFields.clear();
        this->p1p = p1p;
        this->p1n = p1n;
        this->p2p = p2p;
        this->p2n = p2n;
    }
    else {
        for (ChessView::FieldHighlight *temp : qAsConst(m_selectedFields)) {
            if(m_algorithm->board()->data(temp->column(),temp->rank())!=' ')
            {
                this->thread(m_algorithm->board()->data(temp->column(),temp->rank()));
            }
//            ui->widget->addHighlight(temp);
        }
        m_selectedFields.clear();
    }
}

void MainWindow::highlight(int col,int rank)
{
    posible(col,rank,false);
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
    m_selectedFields.clear();
}

