#include "leaderboard.h"
#include "players.h"
#include "ui_leaderboard.h"
extern UNode * headofUList;


leaderboard::leaderboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::leaderboard)
{
    ui->setupUi(this);
}

void leaderboard::setlabeltexts()
{
    UNode * reader=headofUList->next;
    if(reader)
    {ui->label1->setText("<font face='Cabin Sketch' size=28 color='#000000'> Champion:</font> <font face='Cabin Sketch' size=28 color='#aa5500'>"+QString(reader->name)+"  <font face='Cabin Sketch' size=28 color='#000000'> Score:</font><font face='Cabin Sketch' size=28 color='#aa5500'>"+QString::number(reader->highestScore) +"</font>");
    reader=reader->next;}
    if(reader)
    {ui->label2->setText("<font face='Cabin Sketch' size=28 color='#000000'> Runner-up:</font> <font face='Cabin Sketch' size=28 color='#aa5500'>"+QString(reader->name)+"  <font face='Cabin Sketch' size=28 color='#000000'> Score:</font><font face='Cabin Sketch' size=28 color='#aa5500'>"+QString::number(reader->highestScore) +"</font>");
        reader=reader->next;}
    if(reader){
     ui->label3->setText("<font face='Cabin Sketch' size=28 color='#000000'> 3rd:</font> <font face='Cabin Sketch' size=28 color='#aa5500'>"+QString(reader->name)+"  <font face='Cabin Sketch' size=28 color='#000000'> Score:</font><font face='Cabin Sketch' size=28 color='#aa5500'>"+QString::number(reader->highestScore) +"</font>");
     reader=reader->next;}
    if(reader) {
     ui->label4->setText("<font face='Cabin Sketch' size=28 color='#000000'> 4th:</font> <font face='Cabin Sketch' size=28 color='#aa5500'>"+QString(reader->name)+"  <font face='Cabin Sketch' size=28 color='#000000'> Score:</font><font face='Cabin Sketch' size=28 color='#aa5500'>"+QString::number(reader->highestScore) +"</font>");
     reader=reader->next;}
    if(reader){
     ui->label5->setText("<font face='Cabin Sketch' size=28 color='#000000'> 5th:</font> <font face='Cabin Sketch' size=28 color='#aa5500'>"+QString(reader->name)+"  <font face='Cabin Sketch' size=28 color='#000000'> Score:</font><font face='Cabin Sketch' size=28 color='#aa5500'>"+QString::number(reader->highestScore) +"</font>");
               }
}

leaderboard::~leaderboard()
{
    delete ui;
}
