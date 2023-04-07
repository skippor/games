#include <windows.h>
#include <cstdio>
#include <cmath>

#include "lib/glut.h"


//Բ���ʺ�
#define GL_PI 3.1415f
//��ȡ��Ļ�Ŀ��
GLint SCREEN_WIDTH=0;
GLint SCREEN_HEIGHT=0;
//���ó���Ĵ��ڴ�С
GLint windowWidth=400;
GLint windowHeight=300;
//��x����ת�Ƕ�
GLfloat xRotAngle=0.0f;
//��y����ת�Ƕ�
GLfloat yRotAngle=0.0f;
//��ʾ�ص�����
//��֧�ֵĵ��С��Χ
GLfloat sizes[2];
//��֧�ֵĵ��С����
GLfloat step;
void renderScreen(void){
	GLfloat x,y,z,angle;
	//��ǰ��Ĵ�С
	GLfloat curSize=0.0f;
	//��������������Ϊ��ǰ������ɫ����ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	//����ǰMatrix״̬��ջ
	glPushMatrix();
	//����ϵ��x����תxRotAngle
	glRotatef(xRotAngle,1.0f,0.0f,0.0f);
	//����ϵ��y����תyRotAngle
	glRotatef(yRotAngle,0.0f,1.0f,0.0f);
	//��ǰ��Ĵ�С
	curSize = sizes[0];
	z=-50.0f;
	//�����ĸ�����
	for(angle=0.0f;angle<=((2.0f*GL_PI)*4.0f);angle+=0.1f){
		x=50.0f*cos(angle);
		y=50.0f*sin(angle);
		//���õ�Ĵ�С
		glPointSize(curSize);
		//����ƽ������
		glEnable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH,GL_NICEST);
		//��ʼ���
		glBegin(GL_POINTS);
		glVertex3f(x,y,z);
		//�������
		glEnd();
		z+=0.4f;
		//����
		curSize+=step;
	}
	//�ָ�ѹ��ջ��Matrix
	glPopMatrix();
	//����������������ָ��
	glutSwapBuffers();
}
//����Redering State
void setupRederingState(void){
	//����������ɫΪ��ɫ
	glClearColor(0.0f,0.0,0.0,1.0f);
	//���û滭��ɫΪ��ɫ
	glColor3f(0.0f,1.0f,0.0f);
	//��ȡ��֧�ֵĵ��С��Χ
	glGetFloatv(GL_POINT_SIZE_RANGE,sizes);
	//��ȡ��֧�ֵĵ��С����
	glGetFloatv(GL_POINT_SIZE_GRANULARITY,&step);
	printf("point size range:%f-%f\n",sizes[0],sizes[1]);
	printf("point step:%f\n",step);
}
//���ڴ�С�仯�ص�����
void changSize(GLint w,GLint h){
	//������
	GLfloat ratio;
	//��������ϵΪx(-100.0f,100.0f)��y(-100.0f,100.0f)��z(-100.0f,100.0f)
	GLfloat coordinatesize=100.0f;
	//���ڿ��Ϊ��ֱ�ӷ���
	if((w==0)||(h==0))
		return;
	//�����ӿںʹ��ڴ�Сһ��
	glViewport(0,0,w,h);
	//��ͶӰ����Ӧ�����ľ������
	glMatrixMode(GL_PROJECTION);
	//���õ�ǰָ���ľ���Ϊ��λ����
	glLoadIdentity();
	ratio=(GLfloat)w/(GLfloat)h;
	//����ͶӰ
	if(w<h)
		glOrtho(-coordinatesize,coordinatesize,-coordinatesize/ratio,coordinatesize/ratio,-coordinatesize,coordinatesize);
	else
		glOrtho(-coordinatesize*ratio,coordinatesize*ratio,-coordinatesize,coordinatesize,-coordinatesize,coordinatesize);
	//��ģ����ͼ�����ջӦ�����ľ������
	glMatrixMode(GL_MODELVIEW);
	//���õ�ǰָ���ľ���Ϊ��λ����
	glLoadIdentity();
}

//�������봦����
void sPecialkeyFuc(int key,int x,int y){
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
	//���»���
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc,argv);
	//ʹ��˫������ģʽ
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	//��ȡϵͳ�Ŀ�����
	SCREEN_WIDTH=glutGet(GLUT_SCREEN_WIDTH);
	//��ȡϵͳ�ĸ�����
	SCREEN_HEIGHT=glutGet(GLUT_SCREEN_HEIGHT);
	//�������ڣ���������ΪPointsDemo
	glutCreateWindow("PointsDemo");
	//���ô��ڴ�С
	glutReshapeWindow(windowWidth,windowHeight);
	//���ھ�����ʾ
	glutPositionWindow((SCREEN_WIDTH-windowWidth)/2,(SCREEN_HEIGHT-windowHeight)/2);
	//���ô��ڴ�С�仯ʱ�Ļص�����
	glutReshapeFunc(changSize);
	//������ʾ�ص�����
	glutDisplayFunc(renderScreen);
	//���ð������봦��ص�����
	glutSpecialFunc(sPecialkeyFuc);
	//����ȫ����Ⱦ����
	setupRederingState();
	glutMainLoop();
	return 0;
}
