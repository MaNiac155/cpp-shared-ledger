#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();
    bool canLog();
    QString name;

private slots:


    void on_logButton_released();

    void on_signButton_released();

    void on_retnButton_released();

    void on_signButton_1_released();

private:
    Ui::loginDialog *ui;
    bool _canLog;
};

#endif // LOGINDIALOG_H
