#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void rePrintBoard();
    void rePrintScore();
    void checkGameStatue();


private slots:
    void on_pushButton_3_clicked();
    void userLogin(QString);
    void newGame();
    void gameFail();
    void gameWin();
    void gameGoon();
    void on_upButton_clicked();

    void on_downButton_clicked();

    void on_leftButton_clicked();

    void on_rightButton_clicked();

    void on_NewGameButton_clicked();
   void popLoginWindow();
   void popLeaderBoard();
   void popTCFchoose();
   void setplaybackwids();


   void on_undoButton_clicked();

   void on_redoButton_clicked();

   void on_nextButton_clicked();

signals:
    void gameOverandWin();
    void gameOverandFail();
    void gameContinue();

private:
    Ui::MainWindow *ui;
    void setButtonsDisabled();
    void setButtonsAbled();
};

#endif // MAINWINDOW_H

