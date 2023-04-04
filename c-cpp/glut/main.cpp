#include <windows.h>
#include <cstdio>
#include <cmath>

#include "lib/glut.h"

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutWireTeapot(0.5);
	glFlush();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("OpenGL Window");
	
	
	glutDisplayFunc(&display); 
	glutMainLoop();

    return 0;
}
