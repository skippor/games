#include<iostream>
#include<string>
#include<iomanip>
#include<ctime>
#include<cmath>
#include<cstdlib>
using namespace std;
struct MnSwp
{
public:
	char MineNum;
	char Flag;
	char Logo;
    MnSwp();
};
MnSwp::MnSwp()
{
	MineNum='0';
	Flag='N';
	Logo='#';
}
const int N=9;
int X,Y;
MnSwp Sweeping[N][N];
int ExceptMine(int S,int T);
void AddMineNum(int XX,int YY);
void IfNotW(int XXX,int YYY);
int Iter=0;
int main()
{
/////////////////////Initialization And Print///////////////////////
	for(int i=0;i!=N;++i)
	{
		for(int j=0;j!=N;++j)
		{
			cout<<setw(2)<<Sweeping[i][j].Logo;
		}
		cout<<endl;
	}
////////////////////Random Creat the Mines And Put num around Mines///////////////////////
	int Random=0,m=0,n=0;
	srand((unsigned) time(NULL));
	for(int k=0;k!=10;++k)
	{
		Random=rand()%(N*N);
		m=Random/N;
		n=Random%N;
		if(Sweeping[m][n].Flag!='Y')
		{
			Sweeping[m][n].Flag='Y';
			AddMineNum(m-1,n-1);
			AddMineNum(m-1,n);
			AddMineNum(m-1,n+1);
			AddMineNum(m,n-1);
			AddMineNum(m,n+1);
			AddMineNum(m+1,n-1);
			AddMineNum(m+1,n);
			AddMineNum(m+1,n+1);
		}
		else --k;
	}


//////////////////Let user Enter Coordinates//////////////////
	while(N==N)
	{
		if(Iter==(N*N-10))
		{
			cout<<"Congratulations!You succeed to debar all the Mines!"<<endl;
			return 0;
		}
		else
		{
			cout<<"Please enter the Row Number(1~"<<N<<"):";
			cin>>X;
			cout<<"Please enter the Arrange Number(1~"<<N<<"):";
			cin>>Y;

			--X;
			--Y;
//////////////////When user Stamp on a Mine////////////////////
			if(Sweeping[X][Y].Flag=='Y')
			{
				system("cls");
				for(int i=0;i!=N;++i)
				{
					for(int j=0;j!=N;++j)
					{
						if(Sweeping[i][j].Flag!='Y')
							cout<<setw(2)<<Sweeping[i][j].MineNum;
						else
							cout<<setw(2)<<'X';
					}
					cout<<endl;
				}
				cout<<"Your cess is Bad!!!You Stamped on a Mine!"<<endl;
				return 0;
			}
/////////////////Not Stamp on a Mine//////////////////////
			else
			{
				system("cls");
				ExceptMine(X,Y);
				for(int a=0;a!=N;++a)
				{
					for(int b=0;b!=N;++b)
					{
						cout<<setw(2)<<Sweeping[a][b].Logo;
					}
					cout<<endl;
				}
			}
		}
	}
	return 0;
}

int ExceptMine(int S,int T)
{
	if(Sweeping[S][T].MineNum=='0')
	{
		Sweeping[S][T].Logo=Sweeping[S][T].MineNum;
		Sweeping[S][T].Flag='W';
		++Iter;
		IfNotW(S-1,T-1);
		IfNotW(S-1,T);
		IfNotW(S-1,T+1);
		IfNotW(S,T-1);
		IfNotW(S,T+1);
		IfNotW(S+1,T-1);
		IfNotW(S+1,T);
		IfNotW(S+1,T+1);
	}
	else
	{
		Sweeping[S][T].Logo=Sweeping[S][T].MineNum;
		Sweeping[S][T].Flag='W';
		++Iter;
	}
	return 0;
}
void AddMineNum(int XX,int YY)
{
	if(XX>=0&&XX<N&&YY>=0&&YY<N)
		++Sweeping[XX][YY].MineNum;
}
void IfNotW(int XXX,int YYY)
{
	if((XXX>=0&&XXX<N&&YYY>=0&&YYY<N)&&Sweeping[XXX][YYY].Flag!='W')
		ExceptMine(XXX,YYY);
}

