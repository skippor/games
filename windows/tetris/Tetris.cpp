#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include "colorConsole.cpp"

#define left	75
#define right	77
#define down	80
//游戏区域大小
#define width    12
#define height   20

int Lleft[4][4]  = {{1,0,0,0},
					{1,1,1,0},
					{0,0,0,0},
					{0,0,0,0}};	//左型L
int Lright[4][4] = {{0,0,1,0},
					{1,1,1,0},
					{0,0,0,0},
					{0,0,0,0}};	//右型L
int Zleft[4][4]  = {{1,1,0,0},
					{0,1,1,0},
					{0,0,0,0},
					{0,0,0,0}};	//左型Zigzag
int Zright[4][4] = {{0,1,1,0},
					{1,1,0,0},
					{0,0,0,0},
					{0,0,0,0}};	//右型Zigzag
int T[4][4]      = {{0,1,0,0},
					{1,1,1,0},
					{0,0,0,0},
					{0,0,0,0}};	//T型
int Stick[4][4]  = {{1,1,1,1},
					{0,0,0,0},
					{0,0,0,0},
					{0,0,0,0}};	//棒型
int Cube[4][4]   = {{1,1,0,0},
					{1,1,0,0},
					{0,0,0,0},
					{0,0,0,0}};	//正方形
int Diamond[4][4];				//用于表示不同方块的数组

int offset_x = 20;				//打印偏移量
int offset_y = 5;				//打印偏移量
int area[height][width];		//游戏区域的数组

void HomePage(HANDLE handle);							//首页
void Initialize();										//初始化界面
void PlayMusic();										//播放背景音乐
WORD CreateColors(WORD newColor[1]);					//产生随机方块颜色
int* Setup();											//创建
void Draw(int Dia[],int w,int h,int x,int y,WORD Colors[],int cColors);	//画方块
void TurnOver(int Dia[][4],int w,int h,int *x,int y);	//翻转方块*
BOOL PutDown(int Dia[],int x,int y,int w,int h);		//判断能否放下和移动*
void ClearIn(int *a,int w,int h,int x,int y);			//清除游戏区域内的方块
void ClearOut(int *b,int w,int h,int x,int y);			//清除游戏外围的方块
void DeleteRow(int m[][width],int row,int w,int h);		//消除一行*
void GAMEOVER();										//行数超过界限游戏结束
void FlashScreen();										//刷屏效果

int main()
{
	HANDLE handle;
	handle = initiate();
	HomePage(handle);	//游戏首页
	Initialize();		//进行初始化
	//创建新的方块
	int *advance = NULL;
	advance = Setup();
	int blank,x,y;
	bool flag;
	while(1)
	{
		//复制已创建的方块
		for(int i=0;i<4;i++)          
			for(int j=0;j<4;j++)
				if(Diamond[i][j]=*(advance+i*4+j)) 
					blank = i;
		y=1-blank;x=4;
		ClearOut(&Diamond[0][0],4,4,13,13);//清除上一个方块
		advance=Setup();
		WORD Colors[1];
		Colors[0] = FOREGROUND_RED|FOREGROUND_INTENSITY;//游戏区域外围即将出现的下一个方块的颜色
		Draw(advance,4,4,13,13,Colors,1);//游戏区域外围即将出现的下一个方块
		WORD newColor[1];
		Colors[0] = CreateColors(newColor);//游戏区域中出现的方块的颜色
		Draw(&Diamond[0][0],4,4,x,y,Colors,1);//游戏区域中出现方块
		while(_kbhit())//清除键盘缓冲区
			_getch();
		flag = true;
		while(flag)
		{
			int putoff = 0,putoff_max = 50; //延迟量
			while(putoff<putoff_max)
			{
				if(_kbhit())  
				{
					int d=0;
					int key=_getch();
					switch (key)
					{
					case 224:
						switch(_getch())
						{
						case down:
							putoff=putoff_max;
							break;
						case left:
							if(PutDown(&Diamond[0][0],x-1,y,4,4))//能否左移
							{
								ClearIn(&Diamond[0][0],4,4,x,y);//若能 清除当前方块
								x--;//左移x值减1
								d=1;
							}	
							break;
						case right:
							if(PutDown(&Diamond[0][0],x+1,y,4,4))//能否右移
							{
								ClearIn(&Diamond[0][0],4,4,x,y);//若能 清除当前方块
								x++;//右移x值加1
								d=1;
							}
							break;
						}
						break;
					case 99://翻转方块
						ClearIn(&Diamond[0][0],4,4,x,y);
						TurnOver(Diamond,4,4,&x,y);
						d=1;
						break;
					}
					if(d)//有按键操作后
					{
						HANDLE handle;
						handle=initiate();
						WORD Colors[1]={CreateColors(newColor)};
						Draw(&Diamond[0][0],4,4,x,y,Colors,1);
						d=0;
					}
				}
				Sleep(10);
				putoff++;
			}
			if(PutDown(&Diamond[0][0],x,y+1,4,4)) //是否能下移
			{
				ClearIn(&Diamond[0][0],4,4,x,y);//若能 清除当前方块
				y++;//下移y值加1
				HANDLE handle;
				handle=initiate();
				WORD Colors[1]={CreateColors(newColor)};
				Draw(&Diamond[0][0],4,4,x,y,Colors,1);
			}
			else
			{
				flag = !flag;//跳出while(flag)循环，产生新方块
				if(y<=1) 
					GAMEOVER();	//结束游戏			 
				for(int i=0;i<4;i++)//放下方块
					for(int j=0;j<4;j++)
						if(Diamond[i][j]&&((i+y)<height-1)&&((j+x)<width-1)) //////////此条件还没懂//////////
							area[i+y][j+x]=Diamond[i][j];
				int full;
				for(int i=y;i<min(y+4,height-1);i++)
				{
					//如果第i行全是1：某行，第一个元素是1，则括号内为假，不执行full=0，
					//返回继续for循环，直到若全为1则结束for，full仍为1，则执行消行的函数
					//同理若有一个元素为0了，则括号内为真，full=0被执行，则不执行消行的函数
					full=1;
					for(int j=1;j<11;j++)
						if(!area[i][j]) 
							full=0;
					if(full)//消掉一行
						DeleteRow(area,i,width,height);
				}
			}
		}
	}
	return 0;
}

void HomePage(HANDLE handle)
{
	handle = initiate();
	WORD titleColor[1] = {FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY};
	textout(handle,10,3,titleColor,1,"　┓╭┓┓╮┏━┳━┳┓　┓┏┏━╮　　━━╮　　┓　┓　　");
	textout(handle,10,4,titleColor,1,"┏╯┛┃┃┛┃　┃　┃┃┏┣┣┫　　┏━┳━━┛┏┣┏┣━┓");
	textout(handle,10,5,titleColor,1,"┃┃━┣┣┛┗━┻━┻╯　┣┫┃　　　　┣━━┓　┃　┃　┃");
	textout(handle,10,6,titleColor,1,"┃┃╭┣┃┃┣━━━━┓　┣┫┣┳┛╭　┃　　┃　┃━┣━┻");
	textout(handle,10,7,titleColor,1,"　┃┛┃┣╯╯┗━━╮┃┗┻┻┫┃　┃　┃　　┃　┃　┃　　");
	textout(handle,10,8,titleColor,1,"╰┛━╯╰┛┗━━━━╯┗╯┗┛┗╯┗━╯　━╯┗┻┗╯━╯");
	while(!_kbhit())
	{
		textout(handle,29,15,titleColor,1,"PRESS ANY KEY TO START");
		Sleep(60);
		textout(handle,29,15,titleColor,1,"                      ");
		Sleep(60);
	}
	int any_key = _getch();
	srand(any_key);//按任意键
	system("CLS");
}

void Initialize()
{
	HANDLE handle;
	handle=initiate();
	for(int i=1;i<20;i++)//游戏区域高20
	{
		area[i][0]=-1;//每行最后一个数组元素
		area[i][11]=-1;//每行第一个数组元素
	}
	for(int i=1;i<12;i++)//游戏区域宽12
		area[19][i]=-2;//最后一行
	
	WORD Colors[1]={FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY};
	textout(handle,offset_x+26,offset_y+2,Colors,1,"俄罗斯方块");
	textout(handle,offset_x+26,offset_y+4,Colors,1,"任意键开始");
	textout(handle,offset_x+26,offset_y+6,Colors,1,"c键翻转方块 方向键控制方向");
	textout(handle,offset_x+26,offset_y+10,Colors,1,"下一个方块:");
	Colors[0]=FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY;
    
	Draw(&area[0][0],12,20,0,0,Colors,1);//画游戏界面的边框
	
	Colors[0]=FOREGROUND_RED|FOREGROUND_BLUE;
	for(int net_y=offset_y+1;net_y<offset_y+height-1;net_y++)
		textout(handle,offset_x+2,net_y,Colors,1,"□□□□□□□□□□");
	
	int start=_getch();//有按键输入
	srand(start);	   //按键是任意的
}

void PlayMusic()
{
	sndPlaySound("Theme.wav",SND_LOOP|SND_ASYNC); 
}

WORD CreateColors(WORD newColor[1])
{
	WORD whiColor[1],yelColor[1],cyaColor[1];
	whiColor[0]=FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY;
	yelColor[0]=FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY;
	cyaColor[0]=FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY;
	srand(time(NULL));
	int seed=rand()%3;
	switch(seed)
	{
	case 0:
		newColor[0]=whiColor[0];
		break;
	case 1:
		newColor[0]=yelColor[0];
		break;
	case 2:
		newColor[0]=cyaColor[0];
		break;	
	}
	return newColor[0];
}

int* Setup()
{
	int* diamond=NULL;
	srand(time(NULL));
	int seed=rand()%7;		//七种方块
	switch(seed)
	{
	case 0:
		diamond=&Lleft[0][0];
		break;
	case 1:
		diamond=&Lright[0][0];
		break;
	case 2:
		diamond=&Zleft[0][0];
		break;
	case 3:
		diamond=&Zright[0][0];
		break;
	case 4:
		diamond=&T[0][0];
		break;
	case 5:
		diamond=&Stick[0][0];
		break;
	case 6:
		diamond=&Cube[0][0];
		break;
	}
	return diamond;
}

void Draw(int Dia[],int w,int h,int x,int y,WORD Colors[],int color)
{
	HANDLE handle;
	handle = initiate(); 
	int temp;
	for(int i=0;i<h;i++)
		for(int j=0;j<w;j++)//循环以访问到每个数组元素
			if((temp=Dia[i*w+j])&&y+i>0)//////////此条件还没太懂//////////
			{
				if(temp==1)
					textout(handle,2*(x+j)+offset_x,y+i+offset_y,Colors,color,"■");
				else if(temp==-1)//只用于画边框
					//Dia[]即边框处元素（考虑是二维数组）
					textout(handle,2*(x+j)+offset_x,y+i+offset_y,Colors,color,"∫");
				else if(temp==-2)//只用于画底框
					//Dia[]即边框处元素（考虑是二维数组）
					textout(handle,2*(x+j)+offset_x-1,y+i+offset_y,Colors,color,"∞");
			}
}

void TurnOver(int Dia[][4],int w,int h,int *x,int y)
{
	int change[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	int flag=0,l=0;
	for(int i=h-1;i>=0;i--)
	{
		for(int j=0;j<w;j++)
			if(Dia[i][j])
			{
				change[j][l]=Dia[i][j];
				flag=1;
			}
		if(flag) 
		{
			l++;
			flag=0;
		}
	}
	for(int i=0;i<4;i++)
		if(PutDown(&change[0][0],*x-i,y,w,h))
		{
			*x-=i;
			for(int k=0;k<h;k++)
				for(int j=0;j<w;j++)
				Dia[k][j]=change[k][j];
			break;
		}
}

BOOL PutDown(int a[],int x,int y,int w,int h)
{
	for(int i=max(y,1);i<y+h;i++)//max()--windef.h
		for(int j=x;j<x+w;j++)
			if(area[i][j]&&a[w*(i-y)+j-x])
				return 0;	//不能移动
	return 1;				//能移动
}

void ClearIn(int *a,int w,int h,int x,int y)
{
	HANDLE handle;
	handle=initiate();
	WORD Colors[1]={FOREGROUND_RED|FOREGROUND_BLUE};
	for(int i=0;i<h;i++)
		for(int j=0;j<w;j++)
			if(a[i*w+j]&&i+y>0)//和Draw函数的条件一样
				textout(handle,2*(x+j)+offset_x,y+i+offset_y,Colors,1,"□");
}

void ClearOut(int *b,int w,int h,int x,int y)
{
	HANDLE handle;
	handle=initiate();
	WORD Colors[1]={FOREGROUND_RED|FOREGROUND_BLUE};
	for(int i=0;i<h;i++)
		for(int j=0;j<w;j++)
			if(b[i*w+j]&&i+y>0)
				textout(handle,2*(x+j)+offset_x,y+i+offset_y,Colors,1,"  ");
}

void DeleteRow(int m[][width],int row,int w,int h)//消行
{
	HANDLE handle;
	handle=initiate();
	WORD newColor[1];
	WORD Colors[1]={CreateColors(newColor)};
	textout(handle,2+offset_x,row+offset_y,Colors,1,"□□□□□□□□□□");//满行写一行空白 10个
	Sleep(100);
	for(int i=row;i>1;i--)
	{
		ClearIn(&m[i][1],width-2,1,1,i);
		for(int j=1;j<width-1;j++)
			m[i][j]=m[i-1][j];
		Draw(&m[i][1],width-2,1,1,i,Colors,1);
	}
	for(int i=1;i<width-1;i++)
		m[1][i]=0;
}

void GAMEOVER()
{
	HANDLE handle;
	handle=initiate();
	WORD Colors[1]={FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY};
	FlashScreen();
	while(1)
	{
		textout(handle,offset_x+9,offset_y+8,Colors,1,"U LOST!");
		Sleep(300);
		textout(handle,offset_x+9,offset_y+8,Colors,1,"       ");
		Sleep(300);
	}
}

void FlashScreen()
{
	HANDLE handle;
	handle=initiate();
	WORD fsColor[1]={FOREGROUND_BLUE|FOREGROUND_INTENSITY};
	for(int yy=19;yy>0;yy--)
		for(int xx=0;xx<=11;xx++)
		{
			textout(handle,offset_x+xx*2,offset_y+yy,fsColor,1,"※");
			Sleep(10);
		}
}


							








