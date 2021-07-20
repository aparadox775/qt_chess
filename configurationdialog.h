#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>
#include <QPushButton>
namespace Ui {
class configurationdialog;
}

class configurationdialog : public QDialog
{
    Q_OBJECT

public:
    explicit configurationdialog(QWidget *parent = nullptr);
    ~configurationdialog();
    QString player1Name() const;
    QString player2Name() const;

private:
    Ui::configurationdialog *ui;
private slots:
    void updateOKStatus();
};

#endif // CONFIGURATIONDIALOG_H
