#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_selectedField = nullptr;
    m_view = new ChessView;
    m_algorithm = new ChessAlgorithm(this);
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

    //seting width fo push buttons
    ui->quit->setFixedWidth(ui->newGame->width());
    ui->newGame->setFixedWidth(ui->newGame->width());

    //connect signal and slots
    connect(ui->newGame, &QPushButton::clicked, this, &MainWindow::initNewGame);
    connect(ui->quit, &QPushButton::clicked, this, &MainWindow::quit);
    connect(ui->startNewGmae, &QAction::triggered, this, &MainWindow::initNewGame);
    connect(ui->quitMenu, &QAction::triggered, this, &MainWindow::quit);
    connect(ui->widget, &ChessView::clicked,
            this,
            &MainWindow::viewClicked);
    connect(ui->undoButt,&QPushButton::clicked,ui->widget,&ChessView::undo);
    connect(ui->actionundo,&QAction::triggered,ui->widget,&ChessView::undo);
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
    ui->player1PScoresO->setText(QString::number(0));
    ui->player1NScoresO->setText(QString::number(0));
    ui->player2PScoresO->setText(QString::number(0));
    ui->player2NScoresO->setText(QString::number(0));

    m_algorithm->newGame();
    ui->widget->setBoard(m_algorithm->board());
    return;
}

void MainWindow::quit()
{
    this->close();
}


void MainWindow::viewClicked(const QPoint &field)
{
    if(m_clickPoint.isNull())
    {
        if(ui->widget->board()->data(field.x(), field.y()) != ' ')
        {
            m_clickPoint = field;
            m_selectedField = new ChessView::FieldHighlight(
            field.x(), field.y(), QColor(255, 0, 0, 50)
            );
            ui->widget->addHighlight(m_selectedField);
        }
    } else
    {
        if(field != m_clickPoint)
        {
            ui->widget->board()->movePiece(
            m_clickPoint.x(), m_clickPoint.y(), field.x(), field.y()
            );
        };
        m_clickPoint = QPoint();
        ui->widget->removeHighlight(m_selectedField);
        delete m_selectedField;
        m_selectedField = nullptr;
    }
}

