#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

extern "C"
{
	WINBASEAPI HWND WINAPI GetConsoleWindow();
}

int main()
{
	HWND hwnd;
	HDC hdc;
	system("color 3D");
	hwnd = GetConsoleWindow();
	hdc = GetDC(hwnd);
	LineTo(hdc, 200, 300);
	Rectangle(hdc, 10, 30, 300, 50);
	ReleaseDC(hwnd, hdc);
	
	while(1);
	return 0;
}

