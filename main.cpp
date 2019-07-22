#include "mainwindow.h"
#include "board.h"
#include "logindialog.h"
#include "players.h"
#include <QApplication>
int steps=0;
int scores=0;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("2048 by HQC");
    w.show();
    w.rePrintBoard();



    return a.exec();
}
