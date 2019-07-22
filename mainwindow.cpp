#include "mainwindow.h"
#include "board.h"
#include "logindialog.h"
#include "players.h"
#include "ui_mainwindow.h"
#include "QAction"
#include "QDebug"
#include <QMessageBox>
#include "leaderboard.h"
#include <QMessageBox>
#include <QFileDialog>
#include <trace.h>
#include <QFileInfo>
extern int board[4][4];
extern int scores;
extern int steps;
extern QString loggedUsername;
extern UNode * headofUList;
extern char loggedUserNameInChar[NAMEMAX];
extern QString TraceFilepath;
extern QString playbackfilepath;
extern int playstep;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::newGame();



    QObject::connect(this,SIGNAL(gameOverandWin()),this,SLOT(gameWin()));
    QObject::connect(this,SIGNAL(gameOverandFail()),this,SLOT(gameFail()));
    QObject::connect(this,SIGNAL(gameContinue()),this,SLOT(gameGoon()));
    QObject::connect(this->ui->action_New_Game,SIGNAL(triggered()),this,SLOT(newGame()));
    QObject::connect(this->ui->action_Login,SIGNAL(triggered()),this,SLOT(popLoginWindow()));
    QObject::connect(this->ui->actionFail_this_Game,SIGNAL(triggered()),this,SLOT(gameFail()));
    QObject::connect(this->ui->actionLeader_Board,SIGNAL(triggered()),this,SLOT(popLeaderBoard()));
    QObject::connect(this->ui->action_Record,SIGNAL(triggered()),this,SLOT(popTCFchoose()));
    QObject::connect(this->ui->action_Play_Back,SIGNAL(triggered()),this,SLOT(setplaybackwids()));

   if(readUserFile()) ui->statusBar->showMessage("UserFile Loaded Successfully");
   else ui->statusBar->showMessage("UserFile Loaded unsuccessfully");
    popLoginWindow();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rePrintBoard()
{
    /*ui->G11->display(board[0][0]);
    ui->G12->display(board[0][1]);
    ui->G13->display(board[0][2]);
    ui->G14->display(board[0][3]);
    ui->G21->display(board[1][0]);
    ui->G22->display(board[1][1]);
    ui->G23->display(board[1][2]);
    ui->G24->display(board[1][3]);
    ui->G31->display(board[2][0]);
    ui->G32->display(board[2][1]);
    ui->G33->display(board[2][2]);
    ui->G34->display(board[2][3]);
    ui->G41->display(board[3][0]);
    ui->G42->display(board[3][1]);
    ui->G43->display(board[3][2]);
    ui->G44->display(board[3][3]);*/

    ui->L11->setText(QString::number(board[0][0]));
    if(!board[0][0]) ui->L11->setText("");
    ui->L12->setText(QString::number(board[0][1]));
    if(!board[0][1]) ui->L12->setText("");
    ui->L13->setText(QString::number(board[0][2]));
    if(!board[0][2]) ui->L13->setText("");
    ui->L14->setText(QString::number(board[0][3]));
    if(!board[0][3]) ui->L14->setText("");
    ui->L21->setText(QString::number(board[1][0]));
    if(!board[1][0]) ui->L21->setText("");
    ui->L22->setText(QString::number(board[1][1]));
    if(!board[1][1]) ui->L22->setText("");
    ui->L23->setText(QString::number(board[1][2]));
    if(!board[1][2]) ui->L23->setText("");
    ui->L24->setText(QString::number(board[1][3]));
    if(!board[1][3]) ui->L24->setText("");
    ui->L31->setText(QString::number(board[2][0]));
    if(!board[2][0]) ui->L31->setText("");
    ui->L32->setText(QString::number(board[2][1]));
    if(!board[2][1]) ui->L32->setText("");
    ui->L33->setText(QString::number(board[2][2]));
    if(!board[2][2]) ui->L33->setText("");
    ui->L34->setText(QString::number(board[2][3]));
    if(!board[2][3]) ui->L34->setText("");
    ui->L41->setText(QString::number(board[3][0]));
    if(!board[3][0]) ui->L41->setText("");
    ui->L42->setText(QString::number(board[3][1]));
    if(!board[3][1]) ui->L42->setText("");
    ui->L43->setText(QString::number(board[3][2]));
    if(!board[3][2]) ui->L43->setText("");
    ui->L44->setText(QString::number(board[3][3]));
    if(!board[3][3]) ui->L44->setText("");


    return;
}

void MainWindow::rePrintScore()
{
    ui->scoreLabel->setText("Score:"+QString::number(scores, 10));
    return;
}

void MainWindow::checkGameStatue()
{
    if(gameStatue()==1) emit gameContinue();
    else if(gameStatue()==0) emit gameOverandFail();
    else if(gameStatue()==2) emit gameOverandWin();

}

void MainWindow::popLeaderBoard()
{
    leaderboard lb;
    lb.setlabeltexts();
    lb.exec();
}

void MainWindow::popTCFchoose()
{



     TraceFilepath=QFileDialog::getSaveFileName(this,
          tr("Choose trace file to record:"),".",tr("tracefile (*.tcf)"),
                                                QFileDialog::AnyFile|QFileDialog::Detail);

    qDebug()<<"Trace file path is ---"+TraceFilepath;

}

void MainWindow::setplaybackwids()
{
  playbackfilepath=QFileDialog::getOpenFileName(this,
         tr("Choose trace file to play:"),".",tr("tracefile (*.tcf)"),
                                               QFileDialog::AnyFile|QFileDialog::Detail);
    if(playbackfilepath.isEmpty()) playbackfilepath="tracefile.tcf";
    ui->playBackProgressBar->setVisible(true);
    ui->nextButton->setVisible(true);
    ui->nextButton->setEnabled(true);
    ui->statusBar->showMessage("Loaded Trace File: "+playbackfilepath);

    QFile playfile(playbackfilepath);
    if(!playfile.open(QFile::ReadOnly))
       {
           qDebug() << " Could not open the file for reading";
           return;
       }

   playfile.close();

}




void MainWindow::on_pushButton_3_clicked()
{
   // readUserFile();
    rePrintBoard();
    rePrintScore();
    emit gameOverandFail();


}

void MainWindow::userLogin(QString name)
{
    loggedUsername=name;
    std::string dome2=loggedUsername.toStdString();
    int i=0;
    const char * temp2= dome2.c_str();
       for(;i<=NAMEMAX -2;i++)
       {
           loggedUserNameInChar[i]=temp2[i];
       }
       loggedUserNameInChar[i]=0;
    qDebug()<<"loggedusernameinchar is transformed as "<<loggedUserNameInChar;
    //for test
    ui->scoreLabel->setText("Welcome to 2048");
    ui->statusBar->showMessage("User "+loggedUsername.left(NAMEMAX)+" logged in successfully.",15000);

}


void MainWindow::gameFail()
{
    rePrintBoard();
    QMessageBox::information(NULL,"You Lose !","<font face='Cabin Sketch' size=28 color='#aa5500'>Game is over and you lose with score of "+QString::number(scores)+" </font>",QMessageBox::Yes,QMessageBox::NoButton);

    setButtonsDisabled();
     //检查链表刷新分数
    refreshHigestScore();
    //保存用户文件
     writeUserFile();
      ui->statusBar->showMessage("Your score is recorded successfully");
     ui->action_Play_Back->setEnabled(true);

}

void MainWindow::gameWin()
{
    rePrintBoard();
    //显示获胜信息
    QMessageBox::information(NULL,"You Win !","<font face='Cabin Sketch' size=28 color='#aa5500'>Game is over and you win with score of "+QString::number(scores)+ " </font>",QMessageBox::Yes,QMessageBox::NoButton);

    //保存分数
    //按钮无效
    setButtonsDisabled();
    //检查链表刷新分数
    refreshHigestScore();
      //保存用户文件
    writeUserFile();
    ui->statusBar->showMessage("Your score is recorded successfully");
    ui->action_Play_Back->setEnabled(true);

}

void MainWindow::gameGoon()
{
    rePrintBoard();
    rePrintScore();
}

void MainWindow::newGame()
{
    //重置分数
    scores=0;
    //重置步数
    steps=0;
    playstep=0;


    //清空棋盘
    clearBaord();
    //生成随机数
    generateNumber();
    generateNumber();
    pushBoard();
    //刷新显示
    rePrintBoard();
    rePrintScore();
    //恢复按钮
    setButtonsAbled();


    ui->playBackProgressBar->setVisible(false);
    ui->playBackProgressBar->setValue(0);
    ui->nextButton->setVisible(false);
    ui->action_Play_Back->setEnabled(false);

    QFile tracefile(TraceFilepath);
    if(!tracefile.open(QFile::WriteOnly))
       {
           qDebug() << " Could not open the file for reading";
           return;
       }

    tracefile.close();

}

void MainWindow::on_upButton_clicked()
{
   if(swipeUp()) stepSettle();

   checkGameStatue();
}

void MainWindow::on_downButton_clicked()
{
    if(swipeDown()) stepSettle();

    checkGameStatue();
}



void MainWindow::on_leftButton_clicked()
{
    if(swipeLeft()) stepSettle();

    checkGameStatue();
}



void MainWindow::on_rightButton_clicked()
{
    if(swipeRight()) stepSettle();

    checkGameStatue();
}

void MainWindow::setButtonsDisabled()
{
    ui->leftButton->setEnabled(false);
    ui->rightButton->setEnabled(false);
    ui->upButton->setEnabled(false);
    ui->downButton->setEnabled(false);
    ui->redoButton->setEnabled(false);
    ui->undoButton->setEnabled(false);
}

void MainWindow::setButtonsAbled()
{
    ui->leftButton->setEnabled(true);
    ui->rightButton->setEnabled(true);
    ui->upButton->setEnabled(true);
    ui->downButton->setEnabled(true);
    ui->redoButton->setEnabled(true);
    ui->undoButton->setEnabled(true);
}


void MainWindow::on_NewGameButton_clicked()
{
    newGame();
}

void MainWindow::popLoginWindow()
{
    loginDialog ld;
    QObject::connect(&ld,SIGNAL(nameTypedDone(QString)),this,SLOT(userLogin(QString)));
    ld.exec();
}


void MainWindow::on_undoButton_clicked()
{
    undo();
    rePrintBoard();

}

void MainWindow::on_redoButton_clicked()
{
    redo();
     rePrintBoard();
}

void MainWindow::on_nextButton_clicked()
{

    if(playstep<steps)
    {
        QFile playfile(playbackfilepath);
        if(!playfile.open(QFile::ReadOnly))
           {
               qDebug() << " Could not open the file for reading";
               return;
           }
        playfile.seek(playstep*16*sizeof(int));
        QDataStream playread(&playfile);

       quint32 temp;
        for(int i=0;i<=3;i++)
            for(int j=0;j<=3;j++)
            {
                 playread >> temp;
                 qDebug()<<temp;
                 board[i][j]=int(temp);
                // qDebug()<<temp->save[i][j];
            }

        rePrintBoard();
        playstep++;
        ui->playBackProgressBar->setValue(int(100*playstep/steps));
        playfile.close();
    }
    else ui->nextButton->setEnabled(false);

}
