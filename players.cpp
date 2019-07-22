#include "players.h"
#include <QDebug>
QString loggedUsername;
char loggedUserNameInChar[NAMEMAX];
FILE * userFile =NULL;

UNode * headofUList=(UNode *)malloc(sizeof(UNode));
extern int scores;



bool readUserFile()
{
    UNode * cur = headofUList;
    if(!(userFile=fopen("userfile.dat","r+b"))) return false;
    UNode * temp = (UNode *)malloc(sizeof(UNode));

    while( fread(temp,sizeof(UNode),1,userFile))
    {
        temp->name[NAMEMAX-1]=0;




        //test
          qDebug()<<sizeof(UNode);
          qDebug()<<temp->name;
          qDebug()<<sizeof(temp->name);
          qDebug()<<temp->highestScore;
          qDebug()<<sizeof(temp->highestScore);
          qDebug()<<temp->next;
          qDebug()<<sizeof(temp->next);


       temp->next= (UNode *)malloc(sizeof(UNode));
       cur->next=temp;
       cur=temp;
       temp=temp->next;
    }
    temp->next=NULL;
    cur->next=NULL;
    fclose(userFile);
    if(cur==headofUList) return false;
    else return true;
}


bool writeUserFile()
{
    UNode * cur = headofUList->next;
    if(!(userFile=fopen("userfile.dat","wb"))) return false;

    while(cur!=NULL)
        {

            fwrite(cur,sizeof(UNode),1,userFile);
            cur=cur->next;
        }
    fclose(userFile);
        if(cur==headofUList->next) return false;
        else return true;
}


bool refreshHigestScore()
{
    //check New Or Old
    UNode * temp=locateUser();
    qDebug()<<"temp = "<<temp<<"is located";
    if(temp!=NULL)
    {


    //test
      qDebug()<<temp->name;
      qDebug()<<temp->highestScore;
      qDebug()<<temp->next;


      if(scores>=temp->highestScore)
      {
          temp->highestScore=scores;
          sortUser();
          return true;
      }

      else return false;
    }
    else if(temp==NULL)
    {

        temp=(UNode *)malloc(sizeof(UNode));
        strcpy(temp->name,loggedUserNameInChar);
        temp->highestScore=scores;
        findTail()->next=temp;
        temp->next = NULL;
        sortUser();
        return true;
    }


}

UNode * locateUser()
{

    for(UNode * temp=headofUList->next;temp!=NULL;temp=temp->next)
    if(!(strcmp(loggedUserNameInChar,temp->name))) return temp;


    return NULL;
}


void sortUser()
{
    //Bubble Sort
    int timescyc=getLength();

    for(;timescyc!=0;timescyc--)
    {

        for( UNode * temp = headofUList->next;temp->next!=NULL;temp=temp->next)
        {
            if(temp->highestScore<temp->next->highestScore)
                swapUNode(temp);
        }

    }


}


UNode *findTail()
{
    UNode * temp = headofUList;
    for(;temp->next!=NULL;temp=temp->next)
    {}
    return temp;
}

int getLength()
{
    int res=0;
    UNode * temp = headofUList;
    for(;temp->next!=NULL;temp=temp->next)
    {
       res++;
    }
    return res;
}

void swapUNode(UNode * pre)
{
    UNode * piv = (UNode *)malloc(sizeof(UNode));
    strcpy(piv->name,pre->next->name);
    strcpy(pre->next->name,pre->name);
    strcpy(pre->name,piv->name);

    piv->highestScore=pre->next->highestScore;
    pre->next->highestScore=pre->highestScore;
    pre->highestScore=piv->highestScore;


}

