#include <trace.h>
extern int board[4][4];
extern int steps;
QString TraceFilepath="tracefile.tcf";
QString playbackfilepath="tracefile.tcf";

typedef struct traceStackNode{
    int save[4][4]={
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    };
    struct traceStackNode * next=NULL;
    struct traceStackNode * prev=NULL;

}TSNode;

TSNode eButtom;
TSNode * buttom= &eButtom;
TSNode * top = buttom;
TSNode * third =NULL;

int playstep=0;


void pushBoard()
{

    TSNode * temp=(TSNode *)malloc(sizeof(TSNode));
    temp->next=top;
    top->prev=temp;
    top=temp;
    for(int i=0;i<=3;i++)
        for(int j=0;j<=3;j++)
        {
            temp->save[i][j]=board[i][j];
            // qDebug()<<temp->save[i][j];
        }
    third=top;

 qDebug()<<temp->save;

    QFile tracfile(TraceFilepath);
    if(!tracfile.open(QFile::ReadWrite))
       {
           qDebug() << " Could not open the file for reading";
           return;
       }
    tracfile.seek(steps*16*sizeof(int));

    QDataStream tracewrite(&tracfile);

    for(int i=0;i<=3;i++)
        for(int j=0;j<=3;j++)
        {
            tracewrite << board[i][j];
            // qDebug()<<temp->save[i][j];
        }
    tracfile.close();



}


bool undo()
{
    if(third->next!=buttom)
    {
        third=third->next;
        for(int i=0;i<=3;i++)
            for(int j=0;j<=3;j++)
            {
                board[i][j]=third->save[i][j];
                // qDebug()<<temp->save[i][j];
            }
        top=third;

    return true;
    }
    return false;

}

bool redo()
{
    if(third->prev!=NULL)
    {
        third=third->prev;
        for(int i=0;i<=3;i++)
            for(int j=0;j<=3;j++)
            {
                board[i][j]=third->save[i][j];
                // qDebug()<<temp->save[i][j];
            }
        top=third;
        return true;
    }
    return false;

}




