#ifndef BOARD_H
#define BOARD_H


#include<cstdio>
#include<conio.h>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include "trace.h"




    int gameStatue();//如果游戏继续则为1，游戏结束且胜利则为2，游戏结束且失败则为0
    bool checkAdjacent();//检查棋盘中每一个格子的四周是否有相同的
    bool appear2048();//是否出现2048

    bool swipeUp();//执行向上移动并且返回是否为有效移动
    bool swipeDown();//执行向下移动并且返回是否为有效移动
    bool swipeLeft();//执行向左移动并且返回是否为有效移动
    bool swipeRight();//执行向右移动并且返回是否为有效移动

    void stepSettle();//单步结算
    void generateNumber();//在空格处生成随机数

    void clearBaord();//清空棋盘
    void clearFlagBoard();//清空标志盘
    int refreshBlankList();//刷新空格表并返回空格的个数






#endif // BOARD_H
