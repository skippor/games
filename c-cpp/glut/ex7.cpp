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

//�Ƿ�򿪲���ʾ���湦��
GLint cullFace=0;
//�Ƿ����Ȳ��Թ���
GLint depthTest=0;
//�����ǲ��������������ʹ�õ�ɫ��䡡
GLint outLine=0;
//�˵��ص�����
void processMenu(int value){
	switch(value){
		case 1:
			depthTest=!depthTest;
			break;
		case 2:
			cullFace=!cullFace;
		case 3:
			outLine=!outLine;
			break;
			break;
		default:
			break;
	}
	//���»���
	glutPostRedisplay();
}
//��ʾ�ص�����
void renderScreen(void){
    GLfloat x,y,z,angle;
	GLfloat i;
    //��������������Ϊ��ǰ������ɫ����ɫ
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //����ǰMatrix״̬��ջ
    glPushMatrix();
    //����ϵ��x����תxRotAngle
    glRotatef(xRotAngle,1.0f,0.0f,0.0f);
    //����ϵ��y����תyRotAngle
    glRotatef(yRotAngle,0.0f,1.0f,0.0f);
	if(depthTest)
		glEnable(GL_DEPTH_TEST);//����Ȳ��Թ���
	else
		glDisable(GL_DEPTH_TEST);//�ر���Ȳ��Թ���
	if(cullFace)
		glEnable(GL_CULL_FACE);//�򿪲���ʾ���湦��
	else
		glDisable(GL_CULL_FACE);//�رղ���ʾ���湦��
	if(outLine)
		glPolygonMode(GL_BACK,GL_LINE);//����α���ʹ���������
	else
		glPolygonMode(GL_BACK,GL_FILL);//����α���ʹ�õ�ɫ���
	x=0.0f;
	y=0.0f;
    z=0.0f;
	//����ƽ������
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH,GL_NICEST);
	//��������ϵ
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_LINES);
		glVertex3f(-80.0f,0.0f,0.0f);
		glVertex3f(80.0f,0.0f,0.0f);
		glVertex3f(0.0f,-80.0f,0.0f);
		glVertex3f(0.0f,80.0f,0.0f);
		glVertex3f(0.0f,0.0f,-80.0f);
		glVertex3f(0.0f,0.0f,80.0f);
	glEnd();

	glPushMatrix();
	glTranslatef(80.0f,0.0f,0.0f);
	glRotatef(90.0f,0.0f,1.0f,0.0f);
	glutWireCone(3,6,10,10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,80.0f,0.0f);
	glRotatef(-90.0f,1.0f,0.0f,0.0f);
	glutWireCone(3,6,10,10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,0.0f,80.0f);
	glRotatef(90.0f,0.0f,0.0f,1.0f);
	glutWireCone(3,6,10,10);
	glPopMatrix();

	//��ʼ����GL_QUAD_STRIP
	glBegin(GL_QUAD_STRIP);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,25.0f,0.0f);
		glVertex3f(25.0f,0.0f,0.0f);
		glVertex3f(25.0f,25.0f,0.0f);

		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(50.0f,0.0f,0.0f);
		glVertex3f(50.0f,25.0f,0.0f);
    //������GL_QUAD_STRIP
    glEnd();

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
	//
	glShadeModel(GL_FLAT);
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

//�������봦��ص�����
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
    //���»���
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    //��ʼ��glut
    glutInit(&argc,argv);
    //ʹ��˫������ģʽ
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    //��ȡϵͳ�Ŀ�����
    SCREEN_WIDTH=glutGet(GLUT_SCREEN_WIDTH);
    //��ȡϵͳ�ĸ�����
    SCREEN_HEIGHT=glutGet(GLUT_SCREEN_HEIGHT);
	//�������ڣ���������ΪOpenGL TriAngle Demo
    glutCreateWindow("OpenGL QuadStrip Demo");
	//�˵��ص�����
	glutCreateMenu(processMenu);
	//��Ӳ˵�
	glutAddMenuEntry("Toggle depth test",1);
	glutAddMenuEntry("Toggle cull face",2);
	glutAddMenuEntry("Toggle back outline",3);
	//���˵��񶨵�����Ҽ���
	glutAttachMenu(GLUT_RIGHT_BUTTON);
    //���ô��ڴ�С
    glutReshapeWindow(windowWidth,windowHeight);
    //���ھ�����ʾ
    glutPositionWindow((SCREEN_WIDTH-windowWidth)/2,(SCREEN_HEIGHT-windowHeight)/2);
    //���ڴ�С�仯ʱ�Ĵ�����
    glutReshapeFunc(changSize);
    //������ʾ�ص�����
    glutDisplayFunc(renderScreen);
    //���ð������봦��ص�����
    glutSpecialFunc(specialKey);
    //����ȫ����Ⱦ����
    setupRederingState();
    glutMainLoop();
    return 0;
}
