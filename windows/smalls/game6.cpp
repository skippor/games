/*扫雷游戏
尚未完成功能：
存储和导入个人记录；
残局和继续；
中途结束和重新开始；
等等。。。。。
*/

//符号○●⊙①②③④⑤⑥⑦⑧⑨◎¤★□
//○代表无，●代表有


#include <iostream>
#include<time.h>
#include<stdlib.h>
#define MINE 30
using namespace std;
bool mine[10][10];//储存雷的状况
int minenum[10][10];//存储周围雷数
int state[10][10];//标记是否显示过,0表示没显示过，1表示显示过数字，2表示显示过★
bool vacant[10][10];//保存是否要显示的空位置
int counter,num,COUNT;
char onceagain;
void statistics();//统计周围雷数
void Output(int number);
void fun1(int r,int l);
void fun2(int r,int l);
void fun3(int r,int l);
void fun4(int r,int l);
//布雷函数
void laymine()
{
 COUNT=0;
 for (int m=0;m<10;m++)
 {
  for (int n=0;n<10;n++)
  {
   cout<<"□";
  }
  cout<<endl;
 }
 srand((unsigned)time(0));
 for (int m=0;m<10;m++)
 {
  for (int n=0;n<10;n++)
  {
   mine[m][n]=false;
   state[m][n]=0;
   vacant[m][n]=false;
  }
 }
 counter=0;
 do
 {
  int x=rand()%10;
  int y=rand()%10;
  if(mine[x][y]==false)
  {
   mine[x][y]=true;
   counter++;
   if(counter==MINE) {break;}
  }
 } while (counter<MINE);

 num=0;
 statistics();
}
void statistics()
{
 //统计非边界区域周围雷数
 for (int i=1;i<9;i++)
 {
  for (int j=1;j<9;j++)
  {
   if (mine[i][j]==false)
   {
    for (int k=i-1;k<=i+1;k++)
    {
     for (int t=j-1;t<=j+1;t++)
     {
      if (mine[k][t]==true)
      {
       num++;
      }
     }
    }
    minenum[i][j]=num;
    num=0;
   }
  }
 }
 /*边界区域雷数*/
 //最上一行
 for (int top=1;top<9;top++)
 {
  if (mine[0][top]==false)
  {
   for(int r=0;r<=1;r++)
   {
    for (int t1=top-1;t1<=top+1;t1++)
    {
     if (mine[r][t1]==true)
     {
      num++;
     }
    }
   }
   minenum[0][top]=num;
   num=0;
  }
 }
 //最下一行
 for (int buttom=1;buttom<9;buttom++)
 {
  if (mine[9][buttom]==false)
  {
   for(int r=8;r<=9;r++)
   {
    for (int t2=buttom-1;t2<=buttom+1;t2++)
    {
     if (mine[r][t2]==true)
     {
      num++;
     }
    }
   }
   minenum[9][buttom]=num;
   num=0;
  }
 }
 //最左一列
 for (int left=1;left<9;left++)
 {
  if (mine[left][0]==false)
  {
   for(int l=0;l<=1;l++)
   {
    for (int t3=left-1;t3<=left+1;t3++)
    {
     if (mine[t3][l]==true)
     {
      num++;
     }
    }
   }
   minenum[left][0]=num;
   num=0;
  }
 }
 //最右一列
 for (int right=1;right<9;right++)
 {
  if (mine[right][9]==false)
  {
   for(int l=8;l<=9;l++)
   {
    for (int t4=right-1;t4<=right+1;t4++)
    {
     if (mine[t4][l]==true)
     {
      num++;
     }
    }
   }
   minenum[right][9]=num;
   num=0;
  }
 }
 //四个顶点
 if (mine[0][0]==false)
 {
  minenum[0][0]=mine[0][1]+mine[1][0]+mine[1][1];
 }
 if (mine[9][9]==false)
 {
  minenum[9][9]=mine[8][9]+mine[8][8]+mine[9][8];
 }
 if (mine[0][9]==false)
 {
  minenum[0][9]=mine[0][8]+mine[1][8]+mine[1][9];
 }
 if (mine[0][0]==false)
 {
  minenum[9][0]=mine[8][2]+mine[8][0]+mine[9][1];
 }

}
//清屏刷新显示
void refresh()
{
 system("cls");
 for (int m=0;m<10;m++)
 {
  for (int n=0;n<10;n++)
  {
   if (state[m][n]==1)
   {
    Output(minenum[m][n]);//显示过的无雷的
   }
   else if(mine[m][n]==true)
   {
    cout<<"●";//有雷
   }
   else
   {
    cout<<"□";
   }
  }
  cout<<endl;
 }
}
//输出符号
void Output(int number)
{
 switch (number)
 {
 case 0:cout<<"◎";break;
 case 1:cout<<"①";break;
 case 2:cout<<"②";break;
 case 3:cout<<"③";break;
 case 4:cout<<"④";break;
 case 5:cout<<"⑤";break;
 case 6:cout<<"⑥";break;
 case 7:cout<<"⑦";break;
 case 8:cout<<"⑧";break;
 }
}

void explosion()
{
 cout<<"¤ "<<endl;
 system("cls");
 cout<<"¤A "<<endl;
 system("cls");
 cout<<"¤A  "<<endl;
 system("cls");
 cout<<"¤A W "<<endl;
 system("cls");
 cout<<"¤A Wi "<<endl;
 system("cls");
 cout<<"¤A Win "<<endl;
 system("cls");
 cout<<"¤A Winm "<<endl;
 system("cls");
 cout<<"¤A Winmi "<<endl;
 system("cls");
 cout<<"¤A Winmin "<<endl;
 system("cls");
 cout<<"¤A Winmine "<<endl;
 system("cls");
 cout<<"¤A Winmine G "<<endl;
 system("cls");
 cout<<"¤A Winmine Ga "<<endl;
 system("cls");
 cout<<"¤A Winmine Gam "<<endl;
 system("cls");
 cout<<"¤A Winmine Game  "<<endl;
 system("cls");
 cout<<"¤A Winmine Game P "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Pr "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Pro "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Prog "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Progr "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Progra "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Program "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Programm "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Programme "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Programmed  "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Programmed B "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Programmed By  "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Programmed By D "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Programmed By Du "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Programmed By Dua "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Programmed By Duan "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Programmed By Duan C "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Programmed By Duan Co "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Programmed By Duan Con "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Programmed By Duan Cong "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Programmed By Duan Cong!Enjoy "<<endl;
 system("cls");
 cout<<"¤A Winmine Game Programmed By Duan Cong!Enjoy Yourself!"<<endl;
 system("cls");
 cout<<"¤A Winmine Game Programmed By Duan Cong!Enjoy Yourself!¤"<<endl;
 system("cls");
}

void fun1(int r,int l)
{
 if((mine[r-1][l-2]==false)&&l>1&&r>1)
 {
  //state[r-1][l-2]=1;
  vacant[r-1][l-2]=true;
  fun1(r-1,l);
  fun2(r-1,l);
  fun3(r-1,l);
  fun4(r-1,l);
 }
}
void fun2(int r,int l)
{
 if((mine[r-2][l-1]==false)&&(r>1)&&l>0)
 {
  //state[r-2][l-1]=1;
  vacant[r-2][l-1]=true;
  fun2(r,l-1);
 }
}
void fun3(int r,int l)
{
 if(mine[r][l-1]==false)
 {
  //state[r][l-1]=1;
  vacant[r][l-1]=true;
  fun2(r+1,l);
 }
}
void fun4(int r,int l)
{
 if(mine[r-1][l]==false)
 {
  //state[r-1][l]=1;
  vacant[r-1][l]=true;
  fun4(r,l+1);
 }
}
int main()
{
 //开始计时
 clock_t start, finish;
 double  duration;
 //cout<<"¤¤¤¤¤A Winmine Game Programmed By Duan Cong!Enjoy Yourself!¤¤¤¤¤¤"<<endl<<endl;
 explosion();
 cout<<"Game Rules:"<<endl;
 cout<<"○ means no mine"<<endl;
 cout<<"● stands for mine"<<endl;
 cout<<"★ is used to mark the known mines"<<endl;
 cout<<"□ shows the unsolved ones"<<endl;
 cout<<"◎①②③④⑤⑥⑦⑧⑨ represent numbers of mines around"<<endl;
 cout<<"Enter (0,0) to begin marking the mines"<<endl<<endl;
 int row,line;
 //laymine();
 onceagain='y';
 while(onceagain=='y')
 {
loop2: duration = 0.0;
  start = clock();
  laymine();
loop1: cout<<endl<<"Please putin the number of your line and row :"<<endl;
  cin>>row>>line;
  if (row==0&&line==0)
  {
   cout<<endl<<"Enter the row and line to mark the mine!"<<endl;
   cin>>row>>line;
   system("cls");
   for (int m=0;m<10;m++)
   {
    for (int n=0;n<10;n++)
    {
     if ((m==row-1)&&(n==line-1))
     {
      cout<<"★";
      state[m][n]=2;
      if (mine[m][n]==true)
      {
       COUNT++;
       if (COUNT==MINE)
       {
        cout<<"Congratulations! You have finished the mission! Once again?(Enter y/n)"<<endl;
        goto end;
       }
      }
     }
     else if (state[m][n]==1)
     {
      Output(minenum[m][n]);
     }
     else if (state[m][n]==0)
     {
      cout<<"□";
     }
     else if (state[m][n]==2)
     {
      cout<<"★";
     }
    }
    cout<<endl;
   }
   goto loop1;
  }
  else if(row>=0&&row<11&&line>=0&&line<11)
  {
   if (mine[row-1][line-1]==false)
   {
    state[row-1][line-1]=1;
    vacant[row-1][line-1]=true;
    system("cls");
    fun1(row,line);
    fun2(row,line);
    fun3(row,line);
    fun4(row,line);
    for (int m=0;m<10;m++)
    {
     for (int n=0;n<10;n++)
     {
      if (vacant[m][n]==true)
      {
       if(state[m][n]==1)
       {
        Output(minenum[m][n]);
       }
       else if (state[m][n]==2)
       {
        cout<<"★";
       }
       else
       {
        cout<<"○";
        state[m][n]=1;
       }
      }
      else if (state[m][n]==2)
      {
       cout<<"★";
      }
      else
      {
       cout<<"□";
      }
     }
     cout<<endl;
    }
    goto loop1;
   }
   else
   {
    refresh();
    cout<<endl<<"You have discovered "<<COUNT<<" mines";
    //计时
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    cout<<endl<<"The time you have spend is："<<duration<<" seconds"<<endl;
    //重新开始
    cout<<endl<<"Sorry! Game over! Once again? (Enter y/n)"<<endl;
end:   cin>>onceagain;
    if (onceagain=='y')
    {
     system("cls");
     goto loop2;
    }
    else
    {
     exit(0);
    }
   }
  }
  else
  {
   cout<<endl<<"Attention！Illegal iput!"<<endl;
   goto loop1;
  }
 }
 return 0;
}

