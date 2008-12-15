/**
 * Assignment 3
 *
 * @author John Reese
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include <list>

using namespace std;

int screenWidth = 800;
int screenHeight = 600;

bool enabled = false;
double angle = 0;
int camera = 1;
int step = 0;

GLUquadricObj  *cylinder;
GLUquadricObj  *sphere;

int timer = 30;

struct glob
{
	double m;
	double x;
	double y;
	double z;
	double v;
	double r;
	double rx;
	double ry;
	double rz;
};

typedef list<glob> gvector;
gvector globs;

void scene()
{
	glPushMatrix();
	glColor3f( 1, 0, 0 );
	gluCylinder( cylinder, 1, 1, 50, 5, 5 );
	glPopMatrix();

	glPushMatrix();
	glColor3f( 0, 1, 0 );
	glRotated( 90, -1, 0, 0 );
	gluCylinder( cylinder, 1, 1, 50, 5, 5 );
	glPopMatrix();

	glPushMatrix();
	glColor3f( 0, 0, 1 );
	glRotated( 90, 0, 1, 0 );
	gluCylinder( cylinder, 1, 1, 50, 5, 5 );
	glPopMatrix();

	gvector::iterator i = globs.begin();
	glob* g = &(*i);
	
	glColor3f( 1.0, 1.0, 0.0 );
	glRotated( g->r, g->rx, g->ry, g->rz );
	glTranslated( g->x, g->y, g->z );
	gluSphere( sphere, g->m, 16, 16 );

	glPushMatrix();
	glColor3f( 0.7, 0, 0 );
	gluCylinder( cylinder, 1, 1, 50, 5, 5 );
	glPopMatrix();

	glPushMatrix();
	glColor3f( 0, 0.7, 0 );
	glRotated( 90, -1, 0, 0 );
	gluCylinder( cylinder, 1, 1, 50, 5, 5 );
	glPopMatrix();

	glPushMatrix();
	glColor3f( 0, 0, 0.7 );
	glRotated( 90, 0, 1, 0 );
	gluCylinder( cylinder, 1, 1, 50, 5, 5 );
	glPopMatrix();

	glColor3f( 1.0, 0.4, 0.1 );
	for ( ++i; i != globs.end(); i++ ) {
		g = &(*i);

		glPushMatrix();

		glRotated( g->r, g->rx, g->ry, g->rz );
		glTranslated( g->x, g->y, g->z );
		gluSphere( sphere, g->m, 16, 16 );

		glPopMatrix();
	}
}

void animate( int n )
{
	if ( enabled ) {
		for ( gvector::iterator i = globs.begin(); i != globs.end(); i++ ) {
			glob* g = &(*i);

			g->r += g->v;
		}
	}
	glutTimerFunc( timer, animate, 1 );
	//angle+=1;

	glutPostRedisplay();
}

void display( void ) 
{
	glClear( GL_COLOR_BUFFER_BIT );
	glMatrixMode( GL_MODELVIEW );

	glLoadIdentity();
	glRotated( angle, 0.0, 0.0, 1.0 );

	switch( camera ) {
		case 1:
			gluLookAt( 400.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );
			break;
		case 2:
			gluLookAt( 0.0, 400.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );
			break;
		case 3:
			gluLookAt( 1.0, 0.0, 400.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );
			break;

	}

	glPushMatrix();
	glColor3f( 1.0, 0.0, 0.0 );
	scene();
	glPopMatrix();
	
	glutSwapBuffers();
}


void resize( int width, int height ) 
{
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	gluPerspective( 50.0, ((double)width / (double)height), 1.0, 5000.0 );
}

void keyboard( unsigned char key, int x, int y )
{
	switch ( key ) {
		case 49: //view 1
			camera = 1;
			break;
		case 50: //view 2
			camera = 2;
			break;
		case 51: //view 3
			camera = 3;
			break;
		case 97: //animate
			enabled = true;
			break;
		case 27: // quit
		case 113:
			exit(0);
	}
}

void mouse( int button, int state, int x, int y ) 
{
}

void loadGlobs() {
	glob g;
	g.m = 20;
	g.x = 0;
	g.y = 0;
	g.z = 0;
	g.v = 0.15;
	g.r = 0;
	g.rx = 1;
	g.ry = 1;
	g.rz = 1;
	globs.push_back( g );
	for ( int i = 0; i < 10; i++ ) {
		g.m = rand() % 8 + 1;
		g.x = 0;
		g.y = 0;
		g.z = 0;
		g.r = rand() % 360 + 1;
		g.rx = 0;
		g.ry = 0;
		g.rz = 0;
		int rp = rand() % 3 + 1;
		switch( rp ) {
			case 1:
				g.rx = 1;
		g.y = rand() % 300 - 150;
		g.z = rand() % 300 - 150;
				break;
			case 2:
				g.ry = 1;
		g.x = rand() % 300 - 150;
		g.z = rand() % 300 - 150;
				break;
			case 3:
				g.rz = 1;
		g.x = rand() % 300 - 150;
		g.y = rand() % 300 - 150;
				break;
		}

		g.v = ( g.m * g.r / 10 ) / (g.x + g.y + g.z);
		globs.push_back( g );
	}
}

int main( int argc, char* argv[] ) 
{
	srand( time(NULL) );

	glutInit( &argc, argv ); 
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );

	glutInitWindowSize( screenWidth, screenHeight );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "Uber" ); 

	cylinder = gluNewQuadric();
	gluQuadricDrawStyle( cylinder, GLU_LINE );
	sphere = gluNewQuadric();
	gluQuadricDrawStyle( sphere, GLU_LINE );

	loadGlobs();

	glutDisplayFunc( display );
	glutTimerFunc( timer, animate, 0 );

	glutMouseFunc( mouse );
	glutKeyboardFunc( keyboard );
	glutReshapeFunc( resize );

	glutMainLoop();

	return 0;
}

//EOF

