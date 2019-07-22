#ifndef PLAYERS_H
#define PLAYERS_H

#include <QFile>
#include <QIODevice>
#include <QString>
#include "logindialog.h"

#include<cstdio>
#include<conio.h>
#include<cstdlib>
#include<cstring>
#define NAMEMAX 12

    typedef struct userNode
    {
        char name[NAMEMAX];
        int highestScore=0;
        struct userNode * next;
    }UNode;

    bool readUserFile();//读取用户文件
    bool writeUserFile();//写用户文件




    bool refreshHigestScore();


    // qstringToCharstar(QString str);
    UNode * locateUser();
    void sortUser();
    int getLength();
    void swapUNode(UNode *);

    UNode * findTail();



#endif // PLAYERS_H
