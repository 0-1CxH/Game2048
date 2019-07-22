#include <board.h>
#include <mainwindow.h>
int board[4][4]={
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }
};
int flagBoard[4][4]=
{
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }
};
int * blankList[16] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
//维护一个空棋盘格指针表
extern int steps;
extern int scores;

//extern MainWindow w;

int refreshBlankList()
{
    int ind_x, ind_y, s = 0;
    for(int temp=0;temp<=15;temp++)//清空指针表
        blankList[temp]=NULL;
    for (ind_x = 0; ind_x <= 3; ind_x++)//扫描当前空缺位置，存入指针数组中
        {
            for (ind_y = 0; ind_y <= 3; ind_y++)
            {
                if (board[ind_x][ind_y] == 0)
                {
                    blankList[s] = &(board[ind_x][ind_y]);
                    s++;
                }
            }
        }
        return s;
}




void generateNumber()
{
    int s=refreshBlankList();
    srand((unsigned)time(NULL));
        int position=rand() % s;
        *(blankList[position]) = (((rand()*rand()) % 2) + 1) * 2;

        return;
}

void stepSettle()
{
    //算分

    //压栈
    steps++;

    pushBoard();



    //刷新显示
    //w.rePrintBoard();

    //产生新数
    generateNumber();
}


void clearFlagBoard()
{
    for(int tempx=0;tempx<=3;tempx++)
        for(int tempy=0;tempy<=3;tempy++)
        {
            flagBoard[tempx][tempy]=0;
        }


}

bool swipeUp()
{
    int validmoves=0;
    int con_x = 1, con_y = 0,timesForMove=3;
    clearFlagBoard();
    for (; timesForMove >= 0; timesForMove--)
        {
            for (con_x = 1; con_x <= 3; con_x++)
            {
                for (con_y = 0; con_y <= 3; con_y++)
                {
                        if (board[con_x][con_y] != 0&&board[con_x - 1][con_y] == 0)//若上一位是0，而且此位不为0，则向上移动
                        {
                            board[con_x - 1][con_y] = board[con_x][con_y];
                            board[con_x][con_y] = 0;
                            validmoves++;//变成有效步骤
                        }
                        else if ((board[con_x][con_y] != 0) && (board[con_x][con_y] == board[con_x - 1][con_y])&&(flagBoard[con_x-1][con_y]!=1))
                        {//上下两位均非0，而且相同，并且可加，才相加

                            board[con_x - 1][con_y] = board[con_x - 1][con_y] + board[con_x][con_y];
                            scores += board[con_x - 1][con_y];
                            board[con_x][con_y] = 0;
                            for (int m = 0; m <= con_x - 1;m++) flagBoard[m][con_y] = 1;//该处以上不再可加
                            validmoves++;
                        }
                    }
                }
        }
    if(validmoves>0) return true;
    else return false;
}

bool swipeDown()
{
    int validmoves=0;
    int con_x = 1, con_y = 0,timesForMove=3;
    clearFlagBoard();
    for (; timesForMove >= 0; timesForMove--)
        {
            for (con_x = 2; con_x >= 0; con_x--)
            {
                for (con_y = 0; con_y <= 3; con_y++)
                {
                    if (board[con_x][con_y] != 0 && board[con_x + 1][con_y] == 0)//若下一位是0，而且此位不为0，则向下移动
                    {
                        board[con_x + 1][con_y] = board[con_x][con_y];
                        board[con_x][con_y] = 0;
                        validmoves++;//变成有效步骤
                    }
                    else if ((board[con_x][con_y] != 0) && (board[con_x][con_y] == board[con_x + 1][con_y]) && (flagBoard[con_x + 1][con_y] != 1))
                                    {//上下两位均非0，而且相同，并且可加，才相加
                                        board[con_x + 1][con_y] = board[con_x + 1][con_y] + board[con_x][con_y];
                                        scores += board[con_x + 1][con_y];
                                        board[con_x][con_y] = 0;
                                        for (int m = 3; m >= con_x + 1;m--) flagBoard[m][con_y] = 1;//该处下不再可加
                                        validmoves++;
                                    }

                }
            }
        }
    if(validmoves>0) return true;
    else return false;
}

bool swipeLeft()
{
    int validmoves=0;
    int con_x = 1, con_y = 0,timesForMove=3;
    clearFlagBoard();
    for (; timesForMove >= 0; timesForMove--)
        {
            for (con_x = 0; con_x <= 3; con_x++)
            {
                for (con_y = 1; con_y <=3 ; con_y++)
                {
                    if (board[con_x][con_y] != 0 && board[con_x][con_y - 1] == 0)//若左一位是0
                    {
                        board[con_x][con_y - 1] = board[con_x][con_y];
                        board[con_x][con_y] = 0;
                        validmoves++;
                    }
                    else if ((board[con_x][con_y] != 0) && (board[con_x][con_y - 1] == board[con_x][con_y]) && (flagBoard[con_x][con_y - 1]!=1))
                    {


                        board[con_x][con_y - 1] = board[con_x][con_y - 1] + board[con_x][con_y];
                        scores += board[con_x][con_y - 1];
                        board[con_x][con_y] = 0;
                        for (int m = 0; m <= con_y - 1;m++)flagBoard[con_x][m] = 1;//该处不再可加
                        validmoves++;
                    }
                }
            }
        }
    if(validmoves>0) return true;
    else return false;
}

bool swipeRight()
{
    int validmoves=0;
    int con_x = 1, con_y = 0,timesForMove=3;
    clearFlagBoard();
    for (; timesForMove >= 0; timesForMove--)
        {
            for (con_y = 2; con_y >= 0; con_y--)

            {
                for (con_x = 0; con_x <= 3; con_x++)
                {
                    if (board[con_x][con_y] != 0 && board[con_x][con_y + 1] == 0)//若上一位是0
                    {
                        board[con_x][con_y + 1] = board[con_x][con_y];
                        board[con_x][con_y] = 0;
                        validmoves++;
                    }
                    else if ((board[con_x][con_y] != 0) && (board[con_x][con_y + 1] == board[con_x][con_y])&&(flagBoard[con_x][con_y + 1]!=1))
                    {
                        board[con_x][con_y + 1] = board[con_x][con_y + 1] + board[con_x][con_y];
                        scores += board[con_x][con_y + 1];
                        board[con_x][con_y] = 0;
                        for (int m = 3; m >= con_y + 1;m--)flagBoard[con_x][m] = 1;//该处不再可加
                        validmoves++;
                    }
                }
            }
        }
    if(validmoves>0) return true;
    else return false;
}


int gameStatue()
{
    if(appear2048()==true) return 2;
    else if(refreshBlankList()==0&&checkAdjacent()==false) return 0;
    else return 1;
}

bool checkAdjacent()
{
    bool res= false;
    int tempx=0;
    int tempy=0;
    for(;tempx<=3;tempx++)
    {
        for(int ty=0;ty<=2;ty++)
        if(board[tempx][ty]==board[tempx][ty+1]) res=true;

    }
    for(;tempy<=3;tempy++)
    {
        for(int tx=0;tx<=2;tx++)
            if(board[tx][tempy]==board[tx+1][tempy]) res=true;
    }
    return res;
}

bool appear2048()
{
    for(int tempx=0;tempx<=3;tempx++)
        for(int tempy=0;tempy<=3;tempy++)
        {
            if(board[tempx][tempy]==2048) return true;
        }
    return false;
}


void clearBaord()
{
    for(int tempx=0;tempx<=3;tempx++)
        for(int tempy=0;tempy<=3;tempy++)
        {
            board[tempx][tempy]=0;
        }
}
