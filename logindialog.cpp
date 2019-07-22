#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMainWindow>
 QString lineString;
 extern QMainWindow w;
loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    ui->userNameLineEdit->setPlaceholderText("Type your name here");
    ui->pushButton->setEnabled(false);
    QObject::connect(this->ui->userNameLineEdit,SIGNAL(textChanged(QString)),this,SLOT(onNameTyped()));


}

loginDialog::~loginDialog()
{
    delete ui;
}



void loginDialog::onNameTyped()
{
   lineString=ui->userNameLineEdit->text();
    if(lineString.length()==0) ui->pushButton->setEnabled(false);
    if(lineString.length()>12)
    {
        ui->label_2->setStyleSheet("color: rgb(255, 0, 0);font: 16pt \"Agency FB\";");
        ui->label_2->setText("No more than 12 characters!");
        ui->pushButton->setEnabled(false);
    }
    else if(lineString.length()<=12&&lineString.length()!=0)
    {
        ui->label_2->setText("Acceptable");
        ui->label_2->setStyleSheet("color : rgb(0,0,0);font: 16pt \"Agency FB\"; ");
        ui->pushButton->setEnabled(true);
    }
}


void loginDialog::on_pushButton_clicked()
{
    emit nameTypedDone(lineString);
    this->close();
}
