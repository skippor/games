#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <iostream>

using namespace std;

// 获取控制台窗口句柄 微软官方网站的程序 直接拿来用了
HWND GetConsoleHwnd(void)
{
    #define MY_BUFSIZE 1024 // Buffer size for console window titles.
    HWND hwndFound;         // This is what is returned to the caller.
    char pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
    char pszOldWindowTitle[MY_BUFSIZE]; // Contains original
    GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);
    wsprintf(pszNewWindowTitle,"%d/%d",
        GetTickCount(),
        GetCurrentProcessId());
    SetConsoleTitle(pszNewWindowTitle);
    Sleep(40);
    hwndFound=FindWindow(NULL, pszNewWindowTitle);
    SetConsoleTitle(pszOldWindowTitle);
    return(hwndFound);
}

int main (void)
{
	float center1X = 200;
	float center1Y = 100;
	float center2X = 350;
	float center2Y = 250;
	float center0X = (center1X + center2X)/2;
	float center0Y = (center1Y + center2Y)/2;
	float centerRradius = (center2X - center1X)/2;

	float around1X = 0;
	float around1Y = 0;
	float around2X = 0;
	float around2Y = 0;
	float around0X = 0;
	float around0Y = 0;
	float aroundRradius = 20;
	int angle = 0;
    HWND hConsole = GetConsoleHwnd();    // 获得控制台窗口句柄
    HDC hDC = GetDC(hConsole);    // 获得控制台窗口绘图DC

    HPEN hPen = CreatePen(0, 5, RGB(200, 256,256));
	HBRUSH hBrush1 = CreateSolidBrush(RGB(81, 24,214));
	HBRUSH hBrush2 = CreateSolidBrush(RGB(169, 138,0));
	HBRUSH hBrush3 = CreateSolidBrush(RGB(0,0,0));

    HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);    // 让DC选择此画笔
	HDC pdc=GetDC(hConsole);

	hOldPen = (HPEN)SelectObject(pdc,hBrush1);
	Ellipse(pdc,center1X,center1Y,center2X,center2Y);//用笔刷画实心圆 ;
	while(1)
	{
		hOldPen = (HPEN)SelectObject(pdc,hBrush2);
		around0X = center0X - (centerRradius+40)*sin((angle%360)/180.0 * 3.14159265358979);
		around0Y = center0Y + (centerRradius+40)*cos((angle%360)/180.0 * 3.14159265358979);
		Ellipse(pdc,around0X - aroundRradius,around0Y + aroundRradius,around0X + aroundRradius,around0Y - aroundRradius);
		_sleep(10);
		hOldPen = (HPEN)SelectObject(pdc,hBrush3);
		Ellipse(pdc,around0X - aroundRradius,around0Y + aroundRradius,around0X + aroundRradius,around0Y - aroundRradius);
		angle ++;
	}


	//Ellipse(pdc,5,5,45,45);//用笔刷画实心圆 ;
	//MoveToEx(hDC,0, 250, NULL);
	//Arc(hDC,100,100,300,300,350,500,350,500);//用画笔画空心圆 ;
    //for(int i=0;i<500;i++)
     //   LineTo(hDC,10*i,150+100*sin(i*6));
    //InvalidateRect(hConsole, NULL, TRUE); // 刷新窗口

    ReleaseDC(hConsole, hDC);// 释放DC
	while(1);
    return 0;
}

