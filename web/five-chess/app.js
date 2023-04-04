// app.js

//----------------------- 常量部分 ---------------------------//
var UNIT_WIDTH = 25;  //单元格宽度
var LEFT_POS = 50;    //游戏区左上角x坐标
var TOP_POS = 50;     //游戏区左上角y坐标
var EMPTY = 0;        //当前位置为空
var WHITE = 1;        //当前位置为白棋
var BLACK = 2;        //当前位置为黑棋
var ALL_COUNT = 21*21;//总棋子数

var SCORE = [0,1,10,100,1000];
//----------------------- 常量部分 ---------------------------//

//----------------------- 游戏变量部分 ---------------------------//
var chess=new Array();//存储棋子状态
var g_count = 0;      //已下棋子数
var x=0,y=0;          //鼠标按下坐标
//var flag=false;       //测试用，待删
var result="ING";
//----------------------- 游戏变量部分 ---------------------------//

//----------------------- 游戏部分 ---------------------------//
function InitChessArray(){
	for(var i=0;i<21;i++){
		chess[i]=new Array();
		for(var j=0;j<21;j++){
			chess[i][j]=EMPTY;
		}
	}
}

function GetChessCount(Fix,x,y,dx,dy){
	var count=0;
	var xTmp=x+dx;
	var yTmp=y+dy;
	while(xTmp>=0&&xTmp<21&&yTmp>=0&&yTmp<21){
		if(chess[xTmp][yTmp]!=EMPTY&&chess[xTmp][yTmp]==Fix){
			count++;
			xTmp=xTmp+dx;
			yTmp=yTmp+dy;
		}else{
			break;
		}
	}
	return count;
}

function CheckFive(x,y){
	//水平方向
	if(GetChessCount(chess[x][y],x,y,-1,0)+GetChessCount(chess[x][y],x,y,1,0)+1>=5) return true;
	//竖直方向
	if(GetChessCount(chess[x][y],x,y,0,-1)+GetChessCount(chess[x][y],x,y,0,1)+1>=5) return true;
	//正斜方向
	if(GetChessCount(chess[x][y],x,y,-1,-1)+GetChessCount(chess[x][y],x,y,1,1)+1>=5) return true;
	//反斜方向
	if(GetChessCount(chess[x][y],x,y,-1,1)+GetChessCount(chess[x][y],x,y,1,-1)+1>=5) return true;
	
	return false;
}

function CheckEnd(x,y){
	if(CheckFive(x,y)){
		result = chess[x][y]==BLACK?"你赢了!":"你输了!";
		DrawChess(context,x,y,"red")
		alert(result);
		//InitGame(context);
	}else if(g_count>=ALL_COUNT){
		alert("平局!!");
		//InitGame(context);
		//alert(g_count+","+chess);
	}
}

function ComputeWeight(Fix,x,y){
	var weight = 0;
	var count=0,cnt=0,stock=0;
	var dx=[-1,1,0,0,-1,1,-1,1];
	var dy=[0,0,-1,1,-1,1,1,-1];
	
	for(var i=0;i<8;i++){
		cnt=GetChessCount(Fix,x,y,dx[i],dy[i]);
		count+=cnt;
		cx = x+(cnt+1)*dx[i];
		cy = y+(cnt+1)*dy[i];
		
		if(cnt>0&&cx>=0&&cx<21&&cy>=0&&cy<21){
			if(chess[cx][cy]!=EMPTY) stock++;
		}
		
		
		if(i%2==1){
			if(count==2||count==3) count -= stock;
			weight+=SCORE[count];
			count=0;
			stock=0;
		}
	}
	
	/* //水平方向
	count=GetChessCount(Fix,x,y,-1,0)+GetChessCount(Fix,x,y,1,0);
	weight+=SCORE[count];
	//竖直方向
	count=GetChessCount(Fix,x,y,0,-1)+GetChessCount(Fix,x,y,0,1);
	weight+=SCORE[count];
	//正斜方向
	count=GetChessCount(Fix,x,y,-1,-1)+GetChessCount(Fix,x,y,1,1);
	weight+=SCORE[count];
	//反斜方向
	count=GetChessCount(Fix,x,y,-1,1)+GetChessCount(Fix,x,y,1,-1);
	weight+=SCORE[count]; */
	
	return weight;
}

function InitGame(ctx){
	context.clearRect(0,0,600,600); 
	g_count = 0;
	result="ING";
	InitChessArray();
	DrawChessBoard(ctx);
}

function TurnsToWhite(){
	if(g_count>=ALL_COUNT){
		alert("平局!");
		//alert(g_count+","+chess);
	}else{
		//DrawChess(context,x,y,"white");
		//chess[y][x]=WHITE;
		var a,b;
		var maxb=0,ab,bb;
		var maxw=0,aw,bw;
		
		for(var i=0;i<21;i++){
			for(var j=0;j<21;j++){
				if(chess[i][j]==EMPTY){
					var wblack = ComputeWeight(BLACK,i,j);
					var wwhite = ComputeWeight(WHITE,i,j);
					if(maxb<wblack){
						maxb=wblack;
						ab=i;
						bb=j;
					}
					if(maxw<wwhite){
						maxw=wwhite;
						aw=i;
						bw=j;
					}
				}
			}
		}
		
		if(maxb>maxw){
			a=ab;
			b=bb;
		}else{
			a=aw;
			b=bw;
		}
		
		/* var a=Math.floor(21*Math.random());
		var b=Math.floor(21*Math.random());
		while(chess[a][b]!=EMPTY){
			a=Math.floor(21*Math.random());
			b=Math.floor(21*Math.random());
		} */
		
		DrawChess(context,a,b,"white");
		chess[a][b]=WHITE;
		g_count++;
		CheckEnd(a,b);
	}
}


//----------------------- 游戏部分 ---------------------------//

//----------------------- 绘制部分 ---------------------------//
function $(id){
	return document.getElementById(id);
}

//绘制棋盘
function DrawChessBoard(ctx){
	ctx.strokeRect(50,50,500,500); 
	for(var i=25;i<500;i+=25)
	{
		ctx.beginPath();    // 开始路径绘制
		//横向画线
		ctx.moveTo(50, i+50);  // 设置路径起点，
		ctx.lineTo(550, i+50); // 绘制一条直线
		//纵向画线
		ctx.moveTo(i+50, 50);
		ctx.lineTo(i+50, 550);
		ctx.stroke(); // 进行线的着色，这时整条线才变得可见
	}
	
	//几个实心点
	ctx.beginPath(); 
	ctx.fillStyle = "#ff0000";
	ctx.arc(5*UNIT_WIDTH+50,  5*UNIT_WIDTH+50,  3, 0, Math.PI*2, true);   //6*6
	ctx.fill();
	ctx.beginPath(); 
	ctx.arc(5*UNIT_WIDTH+50, 15*UNIT_WIDTH+50,  3, 0, Math.PI*2, true);   //6*17
	ctx.fill();
	ctx.beginPath(); 
	ctx.arc(10*UNIT_WIDTH+50,10*UNIT_WIDTH+50,  3, 0, Math.PI*2, true);   //11*11
	ctx.fill();
	ctx.beginPath(); 
	ctx.arc(15*UNIT_WIDTH+50, 5*UNIT_WIDTH+50,  3, 0, Math.PI*2, true);   //17*6
	ctx.fill();
	ctx.beginPath(); 
	ctx.arc(15*UNIT_WIDTH+50,15*UNIT_WIDTH+50,  3, 0, Math.PI*2, true);   //17*17
	ctx.fill();
}

//绘制棋子
function DrawChess(ctx,x,y,color){
	ctx.beginPath(); 
	ctx.arc(x*UNIT_WIDTH+50,y*UNIT_WIDTH+50,  11, 0, Math.PI*2, true);
	ctx.fillStyle = color;
	ctx.fill();
}
//----------------------- 绘制部分 ---------------------------//
//----------------------- 鼠标事件部分 ---------------------------//
document.onmousedown = function(e){
	x=Math.round((e.clientX-canvas.offsetLeft-50)/25);
	y=Math.round((e.clientY-canvas.offsetTop-50)/25); 
}; 
document.onmouseup = function(){  
	if(x>=0&&x<=20&&y>=0&&y<=20&&chess[x][y]==EMPTY){
		DrawChess(context,x,y,"black");
		chess[x][y]=BLACK;
		g_count++;
		CheckEnd(x,y);
		if(result!="ING") return;
		
		TurnsToWhite();
	}
	
	//alert(chess[0]);
};
//----------------------- 鼠标事件部分 ---------------------------//