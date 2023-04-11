#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

//#include "data.h"　　//声明了名为point的二维数组，以及记录数组元素个数的NUMBER常量
#define NUMBER 10
#define pow2(x) pow(x,2)
//struct POINT
//{
//	int x;
//	int y;
//};

POINT point[NUMBER];

//
//下列X-Y坐标平面的值取决于控制台的尺寸，需要根据实际情况进行调整
//

//起始X坐标
#define X_START    10
//结束X坐标
#define X_END    650
//每个值的X坐标增量，相当于512uS
#define X_INC    10
//Y坐标
#define Y    250

void circle(POINT *center,int radius)
{
    HWND    hwnd;
    HDC    hdc;
    int    xmin = center->x - radius;
    int    xmax = center->x + radius;
    int    ymin = center->y - radius;
    int    ymax = center->y + radius;
    POINT    point;

    hwnd = GetConsoleWindow();
    hdc = GetDC(hwnd);

    point.x = xmin;
    point.y = ymin;
    MoveToEx(hdc,center->x,center->y - radius,NULL);
    while (TRUE)
    {
        if (fabs(sqrt(pow2(point.x - center->x) + pow2(point.y - center->y)) - radius) <= 1)
        {
            //DrawPoint(hdc,&point);
        }
       //是否到达行末
        if (point.x == xmax)
        {
            if (point.y == ymax)
            {
                break;
            }
            else
            {
                point.x = xmin;
                point.y++;
                continue;
            }
        }
        point.x++;
    }
}


int main()
{
	for(int i=0;i<NUMBER;i++)
	{
		point[i].x=i;
		point[i].y=i*i;
	}
	
    HWND    hwnd;
    HDC    hdc;
    int    i;

    //获取console的设备上下文句柄
    hwnd = GetConsoleWindow();
    hdc = GetDC(hwnd);

    //调整一下console背景颜色，否则看不清线条
    system("color 3D");

    //起始位置，Windows中窗口的坐标系相当于直角坐标系第一象限翻转到第四象限
    MoveToEx(hdc,X_START,Y,NULL);

    //画基准坐标线
    LineTo(hdc,X_END,Y);

    //开始绘图
    MoveToEx(hdc,X_START,Y,NULL);
    for (i = 0; i < NUMBER; i++)
    {
        LineTo(hdc,point[i].x,point[i].y);
    }
    _getch();
    return 0;
}
