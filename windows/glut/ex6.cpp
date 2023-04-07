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
#define MODE_SOLID 1
#define MODE_LINE 2
#define MODE_POINTS 3
GLint iMode=MODE_SOLID;// ����ε���䷽ʽ
GLboolean bEdgeFlag=GL_TRUE;//���Ʊߵ���ʾ���
//��֧�ֵĵ��С��Χ
GLfloat sizes[2];
//��֧�ֵĵ��С����
GLfloat step;
//�˵��ص�����
void processMenu(int value){
	switch(value){
		case 1:
			iMode=MODE_SOLID;
			break;
		case 2:
			iMode=MODE_LINE;
			break;
		case 3:
			iMode=MODE_POINTS;
			break;
		case 4:
			bEdgeFlag=GL_TRUE;
			break;
		case 5:
			bEdgeFlag=GL_FALSE;
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
	int i;
    //��������������Ϊ��ǰ������ɫ����ɫ
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //����ǰMatrix״̬��ջ
    glPushMatrix();
    //����ϵ��x����תxRotAngle
    glRotatef(xRotAngle,1.0f,0.0f,0.0f);
    //����ϵ��y����תyRotAngle
    glRotatef(yRotAngle,0.0f,1.0f,0.0f);
	//���ö��������ͱ�������ģʽ
	if(MODE_SOLID==iMode)
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	if(MODE_LINE==iMode)
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	if(MODE_POINTS==iMode)
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	x=0.0f;
	y=0.0f;
    z=0.0f;
	//����ƽ������
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH,GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH,GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH,GL_NICEST);
	//��������ϵ
	if(MODE_POINTS!=iMode){
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
	}
	glColor3f(0.0f,1.0f,0.0f);
	glBegin(GL_TRIANGLES);
		//glPointSize(sizes[1]);
		glEdgeFlag(bEdgeFlag);
		glVertex2f(-20.0f, 20.0f);
		glEdgeFlag(GL_TRUE);
		glVertex2f(20.0f, 20.0f);
		glVertex2f(0.0f, 60.0f);

		glVertex2f(-20.0f,20.0f);
		glVertex2f(-60.0f,0.0f);
		glEdgeFlag(bEdgeFlag);
		glVertex2f(-20.0f,-20.0f);
		glEdgeFlag(GL_TRUE);

		glVertex2f(-20.0f,-20.0f);
		glVertex2f(0.0f, -60.0f);
		glEdgeFlag(bEdgeFlag);
		glVertex2f(20.0f, -20.0f);
		glEdgeFlag(GL_TRUE);

		glVertex2f(20.0f, -20.0f);
		glVertex2f(60.0f, 0.0f);
		glEdgeFlag(bEdgeFlag);
		glVertex2f(20.0f, 20.0f);
		glEdgeFlag(GL_TRUE);

		// Center square as two triangles
		glEdgeFlag(bEdgeFlag);
		glVertex2f(-20.0f, 20.0f);
		glVertex2f(-20.0f,-20.0f);
		glVertex2f(20.0f, 20.0f);

		glVertex2f(-20.0f,-20.0f);
		glVertex2f(20.0f, -20.0f);
		glVertex2f(20.0f, 20.0f);
		glEdgeFlag(GL_TRUE);
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
	//ʹ����Ȳ���
	glEnable(GL_DEPTH_TEST);
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
    int nModeMenu;
	int nEdgeMenu;
	int nMainMenu;
	//��ʼ��glut
    glutInit(&argc,argv);
    //ʹ��˫������ģʽ
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    //��ȡϵͳ�Ŀ�����
    SCREEN_WIDTH=glutGet(GLUT_SCREEN_WIDTH);
    //��ȡϵͳ�ĸ�����
    SCREEN_HEIGHT=glutGet(GLUT_SCREEN_HEIGHT);
	//�������ڣ���������ΪOpenGL Star Demo
    glutCreateWindow("OpenGL Star Demo");
	//���������˵�
	nModeMenu=glutCreateMenu(processMenu);
	glutAddMenuEntry("Solid",1);
	glutAddMenuEntry("Outline",2);
	glutAddMenuEntry("Points",3);
	nEdgeMenu=glutCreateMenu(processMenu);
	glutAddMenuEntry("On",4);
	glutAddMenuEntry("Off",5);
	nMainMenu=glutCreateMenu(processMenu);
	glutAddSubMenu("Mode",nModeMenu);
	glutAddSubMenu("Edge",nEdgeMenu);
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
