#include <windows.h>
#include <cstdio>
#include <cmath>

#include "lib/glut.h"


//圆周率宏
#define GL_PI 3.1415f
//获取屏幕的宽度
GLint SCREEN_WIDTH=0;
GLint SCREEN_HEIGHT=0;
//设置程序的窗口大小
GLint windowWidth=400;
GLint windowHeight=300;
//绕x轴旋转角度
GLfloat xRotAngle=0.0f;
//绕y轴旋转角度
GLfloat yRotAngle=0.0f;
//受支持的点大小范围
GLfloat sizes[2];
//受支持的点大小增量
GLfloat step;
GLint iMode=0;
//菜单回调函数
void processMenu(int value){
	switch(value){
		case 1:
			iMode=0;
			break;
		case 2:
			iMode=1;
			break;
	}
	//重新绘制
	glutPostRedisplay();
}
//显示回调函数
void renderScreen(void){
	//将窗口颜色清理为黑色
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//将模板缓冲区值全部清理为1
	glClearStencil(1);
	//使能模板缓冲区
	glEnable(GL_STENCIL_TEST);
    //把整个窗口清理为当前清理颜色：黑色。清除深度缓冲区、模板缓冲区
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    //将当前Matrix状态入栈
    glPushMatrix();
    //坐标系绕x轴旋转xRotAngle
    glRotatef(xRotAngle,1.0f,0.0f,0.0f);
    //坐标系绕y轴旋转yRotAngle
    glRotatef(yRotAngle,0.0f,1.0f,0.0f);
	//进行平滑处理　
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH,GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH,GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH,GL_NICEST);

	//第一次模板不绘制图形，没有通过模板测试的像素对应模板缓冲区的模板值加1，这样绘制螺旋线的地方模板缓冲区值变为了0x2，没有绘制螺旋线的地方模板缓冲区值还为原来的值0x1
    glStencilFunc(GL_NEVER, 0x0, 0x0);
    glStencilOp(GL_INCR, GL_INCR, GL_INCR);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
		GLdouble dAngle = 0;
		GLdouble dRadius = 0.1;
		//绘制螺旋线，但是不显示出来，仅用来修改模板缓冲区的模板值
        for(dAngle = 0; dAngle < 400.0; dAngle += 0.1)
        {
            glVertex2d(dRadius * cos(dAngle), dRadius * sin(dAngle));
            dRadius *= 1.002;
        }
    glEnd();

    if(1==iMode)
		glStencilFunc(GL_EQUAL, 0x1, 0x3);//参考值0x1==(模板值&0x3)则绘制，即绘制的是第一次使用模板没有绘图的部分．
	else
		glStencilFunc(GL_EQUAL, 0x2, 0x3);//参考值0x2==(模板值&0x3)则绘制，即绘制的是第一次使用模板绘图的部分．
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glColor3f(0.0f, 1.0f, 1.0f);
    glRectf(-40.0f, -40.0f, 40.0f, 40.0f);//使用模板绘制矩形

    //恢复压入栈的Matrix
    glPopMatrix();
    //交换两个缓冲区的指针
    glutSwapBuffers();
}
//设置Redering State
void setupRederingState(void){
    //设置清理颜色为黑色
    glClearColor(0.0f,0.0,0.0,1.0f);
    //设置绘画颜色为绿色
    glColor3f(0.0f,1.0f,0.0f);
	//使能深度测试
	glEnable(GL_DEPTH_TEST);
	//获取受支持的点大小范围
	glGetFloatv(GL_POINT_SIZE_RANGE,sizes);
	//获取受支持的点大小增量
	glGetFloatv(GL_POINT_SIZE_GRANULARITY,&step);
	printf("point size range:%f-%f\n",sizes[0],sizes[1]);
	printf("point step:%f\n",step);
}
//窗口大小变化回调函数
void changSize(GLint w,GLint h){
    //横宽比率
    GLfloat ratio;
    //设置坐标系为x(-100.0f,100.0f)、y(-100.0f,100.0f)、z(-100.0f,100.0f)
    GLfloat coordinatesize=100.0f;
    //窗口宽高为零直接返回
    if((w==0)||(h==0))
        return;
    //设置视口和窗口大小一致
    glViewport(0,0,w,h);
    //对投影矩阵应用随后的矩阵操作
    glMatrixMode(GL_PROJECTION);
    //重置当前指定的矩阵为单位矩阵　
    glLoadIdentity();
    ratio=(GLfloat)w/(GLfloat)h;
    //正交投影
    if(w<h)
        glOrtho(-coordinatesize,coordinatesize,-coordinatesize/ratio,coordinatesize/ratio,-coordinatesize,coordinatesize);
    else
        glOrtho(-coordinatesize*ratio,coordinatesize*ratio,-coordinatesize,coordinatesize,-coordinatesize,coordinatesize);
    //对模型视图矩阵堆栈应用随后的矩阵操作
    glMatrixMode(GL_MODELVIEW);
    //重置当前指定的矩阵为单位矩阵　
    glLoadIdentity();
}

//按键输入处理回调函数
void specialKey(int key,int x,int y){

    if(key==GLUT_KEY_UP){
        xRotAngle-=5.0f;
    }
    else if(key==GLUT_KEY_DOWN){
        xRotAngle+=5.0f;
    }
    else if(key==GLUT_KEY_LEFT){
        yRotAngle-=5.0f;
    }
    else if(key==GLUT_KEY_RIGHT){
        yRotAngle+=5.0f;
    }
    //重新绘制
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	//初始化glut
    glutInit(&argc,argv);
    //使用双缓冲区、深度缓冲区、模板缓冲区
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
    //获取系统的宽像素
    SCREEN_WIDTH=glutGet(GLUT_SCREEN_WIDTH);
    //获取系统的高像素
    SCREEN_HEIGHT=glutGet(GLUT_SCREEN_HEIGHT);
	//创建窗口，窗口名字为OpenGL Stencil Demo
    glutCreateWindow("OpenGL Stencil Demo");
    //设置窗口大小
    glutReshapeWindow(windowWidth,windowHeight);
    //窗口居中显示
    glutPositionWindow((SCREEN_WIDTH-windowWidth)/2,(SCREEN_HEIGHT-windowHeight)/2);
	//创建菜单
	glutCreateMenu(processMenu);
	glutAddMenuEntry("Display Stencil",1);
	glutAddMenuEntry("Don't dsplay Stencil",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
    //窗口大小变化时的处理函数
    glutReshapeFunc(changSize);
    //设置显示回调函数
    glutDisplayFunc(renderScreen);
    //设置按键输入处理回调函数
    glutSpecialFunc(specialKey);
    //设置全局渲染参数
    setupRederingState();
    glutMainLoop();
    return 0;
}
