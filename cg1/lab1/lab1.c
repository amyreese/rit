/**
 * Assignment 1
 *
 * @author John Reese
 */

#include <stdio.h>
#include <GL/glut.h>

int screenHeight = 500;
int screenWidth = 500;

int screen = 1;
int zaps = 0;

void screen1() {
	glLoadIdentity();
	glTranslatef( -1.0f, -1.5f, -5.0f );
	glRotatef( 25, 0.4f, 0.0f, -1.0f );
	glScalef( 2.0f, 2.0f, 2.0f );
	glColor4f( 1.0f, 0.6f, 0.1f, 1.0f );

	glBegin( GL_POLYGON );
	glVertex3f( -1.0f, -1.0f, -10.0f );
	glVertex3f( -1.5f,  0.0f, -10.0f );
	glVertex3f( -1.0f,  1.0f, -10.0f );
	glVertex3f(  1.0f,  1.0f, -10.0f );
	glVertex3f(  1.5f,  0.0f, -10.0f );
	glVertex3f(  1.0f, -1.0f, -10.0f );
	glEnd();

	glLoadIdentity();
	glTranslatef( -1.0f, 0.0f, 0.0f );
	glRotatef( 70, 0.0f, 0.0f, 1.0f );
	glScalef( 1.5f, 1.5f, 1.5f );
	glColor4f( 0.3f, 0.7f, 0.9f, 1.0f );

	glLineWidth( 5.0f );
	glLineStipple( 3, 0xC5DC );
	glEnable( GL_LINE_STIPPLE );

	glBegin( GL_LINE_LOOP );
	glVertex3f( 1.0f, 1.0f, -5.0f );
	glVertex3f( 0.0f, -1.5f, -5.0f );
	glVertex3f( -1.0f, 0.0f, -5.0f );
	glEnd();

	glDisable( GL_LINE_STIPPLE );

	glLoadIdentity();
	glRotatef( 45, 0.0f, 0.0f, 1.0f );
	glColor4f( 1.0f, 1.0f, 1.0f, 0.5f );

	glBegin( GL_POLYGON );
	glVertex3f( (float)zaps * -0.02f, (float)zaps * -0.02f, -1.0f );
	glVertex3f( (float)zaps * -0.02f, (float)zaps *  0.02f, -1.0f );
	glVertex3f( (float)zaps *  0.02f, (float)zaps *  0.02f, -1.0f );
	glVertex3f( (float)zaps *  0.02f, (float)zaps * -0.02f, -1.0f );
	glEnd();

}

void screen2() {
	glLoadIdentity();
	glRotatef( 30, 0.0f, 0.0f, -1.0f );
	glColor4f( 0.9f, 0.2f, 0.9f, 0.2f );

	glBegin( GL_LINE_LOOP );
	glVertex3f( 0.0f, 5.0f, -15.0f );
	glVertex3f( 2.0f,  -5.0f, -15.0f );
	glVertex3f( -5.0f,  2.0f, -15.0f );
	glVertex3f(  5.0f,  2.0f, -15.0f );
	glVertex3f(  -2.0f, -5.0f, -15.0f );
	glEnd();

	glLoadIdentity();
	glRotatef( 20, 0.0f, 1.0f, 1.0f );
	glColor4f( 0.5f, 0.5f, 0.5f, 0.2f );

	glBegin( GL_POLYGON );
	glVertex3f( -4.0f, -4.0f, -25.0f );
	glVertex3f( -4.0f,  4.0f, -25.0f );
	glVertex3f(  4.0f,  4.0f, -25.0f );
	glVertex3f(  4.0f, -4.0f, -25.0f );
	glEnd();
	
	glLoadIdentity();
	glTranslatef( -1.0f + (float)zaps * 0.01f, -0.5f + (float)zaps * 0.01f, 0.0f );
	glRotatef( 45, 0.0f, 0.0f, 1.0f );
	glScalef( 0.0f + (float)zaps * 0.02f, 0.0f + (float)zaps * 0.025f, 1.0f );
	glColor4f( 1.0f, 1.0f, 1.0f, 0.5f );

	glBegin( GL_POLYGON );
	glVertex3f( -1.0f, -1.0f, -2.0f );
	glVertex3f( -1.0f,  1.0f, -2.0f );
	glVertex3f(  1.0f,  1.0f, -2.0f );
	glVertex3f(  1.0f, -1.0f, -2.0f );
	glEnd();
}

void zap( int index ) {
	if ( zaps < 100 ) {
		zaps++;
		glutTimerFunc( 5, zap, 0 );
	} else {
		screen = screen < 2 ? screen+1 : 1;
		zaps = 0;
	}
	glutPostRedisplay();
}

void display( void ) 
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode( GL_MODELVIEW );

	switch ( screen ) {
		case 1:
			screen1(); break;
		case 2:
			screen2(); break;
		default:
			screen1();
	}

	glutSwapBuffers();
}

void resize( int width, int height ) {
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION );
	
	glLoadIdentity();
	gluPerspective( 45.0, (double) width / (double) height, 1.0, 200.0);
}

void keyboard( unsigned char key, int x, int y )
{
	switch ( key ) {
		case 27:
			exit(0);
	}
}

void mouse( int button, int state, int x, int y ) 
{
	if ( state == GLUT_DOWN && zaps == 0 ) {
		glutTimerFunc( 5, zap, 0 );
	}
	glutPostRedisplay();
}

int main( int argc, char* argv[] ) 
{
	glutInit( &argc, argv ); 
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

	glutInitWindowSize( screenWidth, screenHeight );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "Uber" ); 

	glEnable( GL_DEPTH_TEST );

	glutDisplayFunc( display );
	glutReshapeFunc( resize );

	glutMouseFunc( mouse );
	glutKeyboardFunc( keyboard );

	glutMainLoop();

	return 0;
}

//EOF

