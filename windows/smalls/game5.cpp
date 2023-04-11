/*
推箱子
作者：MasterRay
时间：2007-10-18
使用Win32 API
请用Visual C++编译
这些仅是源代码，附件里有程序和地图信息
*/
#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define ENTER 13
#define ESC 27
#define SPACE 32
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ARROW 224

HANDLE hOut;
COORD TopLeft={0, 0}, MainPos={0, 5};
FILE *f;
char map[720], FileName[256]={"box\\"};
short x, y, //推箱者的坐标
    DirectionX[20], DirectionY[20], //目标的坐标
    maxx, maxy, level=1;

char *DecToStr(char *str, short dec)
{
    char ch, *left=str, *right=str, *p;
    do
    {
        *right++=dec%10|'0';
    }while (dec/=10);
    p=right--;
    while (left<right)
    {
        ch=*left;
        *left++=*right;
        *right--=ch;
    }
    *p++='.';
    *p++='t';
    *p++='x';
    *p++='t';
    *p='\0';
    return str;
}

//清除地图
void ClearMap()
{
    FillConsoleOutputCharacter(hOut, ' ', 1600, MainPos, 0);
}

//画地图
void DrawMap()
{
    COORD pos={0, 7};
    short i=0, j, p=0;
    char ch;
    ClearMap();
    SetConsoleCursorPosition(hOut, pos);
    for (; i<maxy; i++)
    {
        for (j=0; j<maxx; j++)
        {
            switch (map[i*maxx+j])
            {
            case 'B': //箱子
                SetConsoleTextAttribute(hOut, FOREGROUND_BLUE|FOREGROUND_INTENSITY); //蓝色
                WriteConsoleA(hOut, "■", 2, 0, 0);
                break;
            case 'D': //目标
                DirectionX[p]=j;
                DirectionY[p++]=i;
                SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); //黄色
                WriteConsoleA(hOut, "◆", 2, 0, 0);
                break;
            case 'F': //目标+箱子
                map[i*maxx+j]='B';
                DirectionX[p]=j;
                DirectionY[p++]=i;
                SetConsoleTextAttribute(hOut, FOREGROUND_BLUE|FOREGROUND_INTENSITY); //蓝色
                WriteConsoleA(hOut, "■", 2, 0, 0);
                break;
            case 'P': //推箱者
                x=j;
                y=i;
                SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_INTENSITY); //红色
                WriteConsoleA(hOut, "★", 2, 0, 0);
                break;
            case 'W': //墙
                SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); //白色
                WriteConsoleA(hOut, "■", 2, 0, 0);
                break;
            default:
                SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); //白色
                WriteConsoleA(hOut, "　", 2, 0, 0);
            }
        }
        pos.Y++;
        SetConsoleCursorPosition(hOut, pos);
    }
    DirectionX[p]=DirectionY[p]=0;
    SetConsoleCursorPosition(hOut, MainPos);
    SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); //白色
}

//新地图
void NewMap()
{
    int ch;
    char *p=map, flag=1;
    DecToStr(FileName+4, level);
    if ((f=fopen(FileName, "r"))==0) TerminateProcess(GetCurrentProcess(), 0);
    maxy=1;
    while ((ch=fgetc(f))!=EOF)
    {
        if (ch!='\r' && ch!='\n') *p++=ch;
        else {maxx=p-map; break;}
    }
    while ((ch=fgetc(f))!=EOF)
    {
        if (ch!='\r' && ch!='\n')
        {
            if (flag)
            {
                maxy++;
                flag=0;
            }
            *p++=ch;
        }
        else if (ch=='\n') flag=1;
    }
    DrawMap();
}

//胜利
void NextMap()
{
    SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); //黄色
    SetConsoleCursorPosition(hOut, MainPos);
    WriteConsoleA(hOut, "你赢了！\n", 8, 0, 0);
    level++;
    getch();
    NewMap();
}

//判断是否胜利
void JudgeMap()
{
    char win=1;
    short p=0;
    COORD pos;
    SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); //黄色
    while (DirectionX[p])
    {
        if (map[DirectionY[p]*maxx+DirectionX[p]]!='B')
        {
            win=0;
            if (DirectionX[p]!=x || DirectionY[p]!=y)
            {
                pos.X=DirectionX[p]<<1;
                pos.Y=DirectionY[p]+7;
                SetConsoleCursorPosition(hOut, pos);
                WriteConsoleA(hOut, "◆", 2, 0, 0);
            }
        }
        p++;
    }
    SetConsoleCursorPosition(hOut, MainPos);
    if (win) NextMap();
    SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
}

//选择地图
void SelectMap()
{
    int i, n=3;
    char szLevel[1];
    SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); //黄色
    SetConsoleCursorPosition(hOut, MainPos);
    WriteConsoleA(hOut, "关卡　\n", 6, 0, 0);
    level=0;
    while ((i=getch())!='\r')
    {
        if (i>='0' && i<='9')
        {
            level*=10;
            level+=i&15;
            szLevel[0]=i;
            WriteConsoleA(hOut, szLevel, 1, 0, 0);
            if (n--==0) break;
        }
    }
    NewMap();
}

//开始游戏
void StartGame()
{
    SetConsoleTextAttribute(hOut, BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_INTENSITY);
    SetConsoleCursorPosition(hOut, TopLeft);
    WriteConsoleA(hOut, "推箱子 　　　　　\n", 18, 0, 0);
    SetConsoleTextAttribute(hOut, BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
    WriteConsoleA(hOut, "ENTER——选关　　\nSPACE——重新开始\nESC———退出　　　", 53, 0, 0);
}

//控制推箱者移动
void move(short heading)
{
    COORD pos={x<<1 ,y+7};
    SMALL_RECT rc={x<<1, y+7, x<<1|1, y+7};
    CHAR_INFO chFill;
    chFill.Attributes=FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE;
    chFill.Char.AsciiChar=' ';
    switch (heading)
    {
    case UP:
        if (y<=0) return;
        if (map[(y-1)*maxx+x]!='B' && map[(y-1)*maxx+x]!='W')
        {
            y--;
            pos.Y--;
        }
        else if (y>1 && map[(y-1)*maxx+x]=='B' && map[(y-2)*maxx+x]!='B' && map[(y-2)*maxx+x]!='W')
        {
            map[(y-1)*maxx+x]='P';
            map[(y-2)*maxx+x]='B';
            y--;
            pos.Y-=2;
            rc.Top--;
        }
        break;
    case LEFT:
        if (x<=0) return;
        if (map[y*maxx+x-1]!='B' && map[y*maxx+x-1]!='W')
        {
            x--;
            pos.X-=2;
        }
        else if (x>1 && map[y*maxx+x-1]=='B' && map[y*maxx+x-2]!='B' && map[y*maxx+x-2]!='W')
        {
            map[y*maxx+x-1]='P';
            map[y*maxx+x-2]='B';
            x--;
            pos.X-=4;
            rc.Left-=2;
        }
        break;
    case RIGHT:
        if (x+1>=maxx) return;
        if (map[y*maxx+x+1]!='B' && map[y*maxx+x+1]!='W')
        {
            x++;
            pos.X+=2;
        }
        else if (x<maxx-2 && map[y*maxx+x+1]=='B' && map[y*maxx+x+2]!='B' && map[y*maxx+x+2]!='W')
        {
            map[y*maxx+x+1]='P';
            map[y*maxx+x+2]='B';
            x++;
            pos.X+=2;
            rc.Right+=2;
        }
        break;
    case DOWN:
        if (y+1>=maxy) return;
        if (y<maxy-1 && map[(y+1)*maxx+x]!='B' && map[(y+1)*maxx+x]!='W')
        {
            y++;
            pos.Y++;
        }
        else if (y<maxy-2 && map[(y+1)*maxx+x]=='B' && map[(y+2)*maxx+x]!='B' && map[(y+2)*maxx+x]!='W')
        {
            map[(y+1)*maxx+x]='P';
            map[(y+2)*maxx+x]='B';
            y++;
            pos.Y++;
            rc.Bottom++;
        }
        break;
    }
    ScrollConsoleScreenBuffer(hOut, &rc, 0, pos, &chFill);
    JudgeMap();
}

//获取按键
void GetKey()
{
    switch (getch())
    {
    case ENTER: SelectMap(); break;
    case ESC: CloseHandle(hOut); exit(0); break;
    case SPACE:    NewMap(); break;
    case ARROW:
        switch (getch())
        {
        case UP: move(UP); break;
        case LEFT: move(LEFT); break;
        case RIGHT: move(RIGHT); break;
        case DOWN: move(DOWN);
        }
    }
}

int main()
{
    COORD size={80, 25};
    hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(936);
    SetConsoleTitleA("推箱子——MasterRay");
    SetConsoleScreenBufferSize(hOut, size);
    StartGame();
    NewMap();
    while (1) GetKey();
    
    return 0;
}
