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
//��֧�ֵĵ��С��Χ
GLfloat sizes[2];
//��֧�ֵĵ��С����
GLfloat step;
GLint iMode=0;
//�˵��ص�����
void processMenu(int value){
	switch(value){
		case 1:
			iMode=0;
			break;
		case 2:
			iMode=1;
			break;
	}
	//���»���
	glutPostRedisplay();
}
//��ʾ�ص�����
void renderScreen(void){
	//��������ɫ����Ϊ��ɫ
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//��ģ�建����ֵȫ������Ϊ1
	glClearStencil(1);
	//ʹ��ģ�建����
	glEnable(GL_STENCIL_TEST);
    //��������������Ϊ��ǰ������ɫ����ɫ�������Ȼ�������ģ�建����
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    //����ǰMatrix״̬��ջ
    glPushMatrix();
    //����ϵ��x����תxRotAngle
    glRotatef(xRotAngle,1.0f,0.0f,0.0f);
    //����ϵ��y����תyRotAngle
    glRotatef(yRotAngle,0.0f,1.0f,0.0f);
	//����ƽ������
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH,GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH,GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH,GL_NICEST);

	//��һ��ģ�岻����ͼ�Σ�û��ͨ��ģ����Ե����ض�Ӧģ�建������ģ��ֵ��1���������������ߵĵط�ģ�建����ֵ��Ϊ��0x2��û�л��������ߵĵط�ģ�建����ֵ��Ϊԭ����ֵ0x1
    glStencilFunc(GL_NEVER, 0x0, 0x0);
    glStencilOp(GL_INCR, GL_INCR, GL_INCR);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
		GLdouble dAngle = 0;
		GLdouble dRadius = 0.1;
		//���������ߣ����ǲ���ʾ�������������޸�ģ�建������ģ��ֵ
        for(dAngle = 0; dAngle < 400.0; dAngle += 0.1)
        {
            glVertex2d(dRadius * cos(dAngle), dRadius * sin(dAngle));
            dRadius *= 1.002;
        }
    glEnd();

    if(1==iMode)
		glStencilFunc(GL_EQUAL, 0x1, 0x3);//�ο�ֵ0x1==(ģ��ֵ&0x3)����ƣ������Ƶ��ǵ�һ��ʹ��ģ��û�л�ͼ�Ĳ��֣�
	else
		glStencilFunc(GL_EQUAL, 0x2, 0x3);//�ο�ֵ0x2==(ģ��ֵ&0x3)����ƣ������Ƶ��ǵ�һ��ʹ��ģ���ͼ�Ĳ��֣�
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glColor3f(0.0f, 1.0f, 1.0f);
    glRectf(-40.0f, -40.0f, 40.0f, 40.0f);//ʹ��ģ����ƾ���

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
	//��ʼ��glut
    glutInit(&argc,argv);
    //ʹ��˫����������Ȼ�������ģ�建����
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
    //��ȡϵͳ�Ŀ�����
    SCREEN_WIDTH=glutGet(GLUT_SCREEN_WIDTH);
    //��ȡϵͳ�ĸ�����
    SCREEN_HEIGHT=glutGet(GLUT_SCREEN_HEIGHT);
	//�������ڣ���������ΪOpenGL Stencil Demo
    glutCreateWindow("OpenGL Stencil Demo");
    //���ô��ڴ�С
    glutReshapeWindow(windowWidth,windowHeight);
    //���ھ�����ʾ
    glutPositionWindow((SCREEN_WIDTH-windowWidth)/2,(SCREEN_HEIGHT-windowHeight)/2);
	//�����˵�
	glutCreateMenu(processMenu);
	glutAddMenuEntry("Display Stencil",1);
	glutAddMenuEntry("Don't dsplay Stencil",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
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
