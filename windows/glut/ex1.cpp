/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include "lib/glut.h"

/**************************
 * Function Declarations
 *
 **************************/

void display()
{
    glClear (GL_COLOR_BUFFER_BIT);/* clear all pixels   */
    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);/* draw white polygon with corners at(0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)*/
       glVertex3f (0.25, 0.25, 0.0);
       glVertex3f (0.75, 0.25, 0.0);
       glVertex3f (0.75, 0.75, 0.0);
       glVertex3f (0.25, 0.75, 0.0);
    glEnd();
    glFlush ();/* start processing buffered OpenGL routines   */
}

void init ()
{
    glClearColor (0.0, 0.0, 0.0, 0.0);/* select clearing color   */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);/* initialize viewing values   */
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);/*Declare initial display mode(single buffer and RGBA).*/
    glutInitWindowSize (250, 250); /*Declare initial window size.*/
    glutInitWindowPosition (100, 100);/*Declare initial window position.*/
    glutCreateWindow ("hello");/*Open window with "hello"in its title bar.*/
    init ();/*Call initialization routines.*/
    glutDisplayFunc(display); /*Register callback function to display graphics.*/
    glutMainLoop();/*Enter main loop and process events.*/
    return 0;    /* ANSI C requires main to return int. */
}
