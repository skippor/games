#include "lib.cpp"

#pragma once

extern int level;

int main()
{
	FOOD food;
	WALL wall;
	BODY CurPos;
	HALL hall;

	int iExit = 0;
	while(1)
	{
		if(iExit)
			break;

		Init(&food,&wall,&CurPos,&hall);
		MakeWall(&wall);
		while(1)
		{
			Sleep(200);
			int res = Move(&food,&wall,&CurPos);
			if(1 == res) //重新开局
				break;
			else if(-1 == res) //用户退出
			{
				iExit = 1;
				break;
			}
			ShowScore(&CurPos,&food);
		}
	}
	return 0;
}

