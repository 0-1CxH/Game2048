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
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();

private:
    Ui::loginDialog *ui;
signals:
    void nameTypedDone(QString);
private slots:
    void onNameTyped();


    void on_pushButton_clicked();
};

#endif // LOGINDIALOG_H
