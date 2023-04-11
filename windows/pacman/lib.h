#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

//标识用户按下的方向键
#define KEY_UP				WM_USER + 1
#define KEY_DOWN			WM_USER + 2
#define KEY_LEFT			WM_USER + 3
#define KEY_RIGHT			WM_USER + 4

//标识用户当前运动方向
#define DIRECTION_UP		WM_USER + 5
#define DIRECTION_DOWN		WM_USER + 6
#define DIRECTION_LEFT		WM_USER + 7
#define DIRECTION_RIGHT		WM_USER + 8

//标识要打印的元素类型
#define PRINT_WALL			WM_USER + 9
#define PRINT_FOOD			WM_USER + 10
#define PRINT_BODY			WM_USER + 11
#define PRINT_CLEAN			WM_USER + 12

#define KNOCK_WALL			WM_USER + 13
#define KNOCK_FOOD			WM_USER + 14



struct POS
{
	int x;
	int y;
};
struct WALL
{
	POS pos[9999];
	int len;
};
struct FOOD
{
	POS pos[8];
	int len;
	int IsHidden;
};
struct BODY
{
	POS pos;
	int Direction;
};
struct HALL{
	POS pos[200];
	int len;
};

void Init(FOOD *pFood,WALL *pWall,BODY *pBody,HALL *pHall); //进行一些初始化操作
void Print(POS *pos,int TYPE,int ix = 0); //完成打印功能
void MakeWall(WALL *pWall); //生成墙
void MakeFood(HALL *pHall,FOOD *pFood); //生成食物
int Move(FOOD *pFood,WALL *pWall,BODY *pBody); //用户移动
void ShowScore(BODY *pBody,FOOD *pFood); //显示等级 和剩余豆子数
int IsOver(POS pos1,POS pos2,int TYPE); //判断2点是否重合
int IsKnock(WALL *pWall,BODY *pBody,FOOD *pFood,int TYPE); //判断是否撞墙、吃到豆子
int GetKey(); //得到用户按键
