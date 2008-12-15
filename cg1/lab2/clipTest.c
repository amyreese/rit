/*
 *  clipPolygonTest.c
 *
 *  This program is designed to test polygon clipping
 */

#include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/

void clipPolygon (int in, int inx[], int iny[], int *out, int outx[],
                  int outy[], int x0, int y0, int xq, int y1);

int quad1x[4] = { 20, 20, 40, 40 };
int quad1y[4] = { 20, 40, 40, 20 };
int quad2x[4] = { 80, 80, 60, 60 };
int quad2y[4] = { 60, 100, 100, 60 };
int quad3x[4] = { 20, 50, 50, 20 };
int quad3y[4] = { 60, 60, 50, 50 };
int quad4x[4] = { 44, 60, 60, 44 };
int quad4y[4] = { 22, 22, 46, 46 };

int pent1x[5] = {80, 90, 110, 100, 80 };
int pent1y[5] = {20, 10, 20, 50, 40 };

int hept1x[7] = {120, 140, 160, 160, 140, 120, 110 };
int hept1y[7] = { 70,  70,  80, 100, 110, 100,  90 };

int wx[50];
int wy[50];
int wl;

void print_loop( int n, int x[], int y[] ) {
   int i;

   glBegin( GL_LINE_LOOP );
      for( i = 0; i < n; ++i ) {
         glVertex2i( x[i], y[i] );
      }
   glEnd();

}

void print_poly( int n, int x[], int y[] ) {
   int i;

   glBegin( GL_POLYGON );
      for( i = 0; i < n; ++i ) {
         glVertex2i( x[i], y[i] );
      }
   glEnd();

}

void display( void ) {
    int i;

   /*
    * Clear window
    */
   glClearColor( 1.0, 1.0, 1.0, 1.0 );
   glClear( GL_COLOR_BUFFER_BIT );

   /*
    * Set the viewWindow
    */
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity( );
   gluOrtho2D( 0, 300, 0, 300 );

   /*
    * Set the viewport to match the viewWindow
    */
   glViewport( 0, 0, 299, 299 );

   /* 
    * first polygon:  entirely within region
    */

   wl = 0;
   clipPolygon( 4, quad1x, quad1y, &wl, wx, wy, 10, 10, 50, 50 );
   glColor3f( 1.0, 0.0, 0.0 );		/* red */
   print_loop( 4, quad1x, quad1y );
   print_poly( wl, wx, wy );

   /*
    * second polygon:  entirely outside region
    */

   wl = 0;
   clipPolygon( 4, quad2x, quad2y, &wl, wx, wy, 10, 10, 50, 50 );
   /* shouldn't draw anything! */
   if( wl > 0 ) {
      glColor3f( 0.0, 1.0, 0.0 );		/* green */
      print_loop( 4, quad2x, quad2y );
      print_poly( wl, wx, wy );
   }

   /*
    * third polygon:  halfway outside on left
    */

   wl = 0;
   clipPolygon( 4, quad3x, quad3y, &wl, wx, wy, 30, 10, 70, 80 );
   glColor3f( 0.0, 0.0, 1.0 );		/* blue */
   print_loop( 4, quad3x, quad3y );
   print_poly( wl, wx, wy );

   /*
    * fourth polygon:  part outside on right
    */

   wl = 0;
   clipPolygon( 4, quad4x, quad4y, &wl, wx, wy, 10, 10, 50, 50 );
   glColor3f( 1.0, 0.0, 1.0 );		/* magenta */
   print_loop( 4, quad4x, quad4y );
   print_poly( wl, wx, wy );

   /*
    * fifth polygon:  enclosing
    */

   wl = 0;
   clipPolygon( 5, pent1x, pent1y, &wl, wx, wy, 90, 20, 100, 30 );
   glColor3f( 0.5, 0.5, 1.0 );		/* reddish-greenish-blue ? */
   print_loop( 5, pent1x, pent1y );
   print_poly( wl, wx, wy );

   /*
    * sixth polygon:  outside on left and bottom
    */

   wl = 0;
   clipPolygon( 5, pent1x, pent1y, &wl, wx, wy, 90, 34, 120, 60 );
   glColor3f( 1.0, 0.5, 1.0 );		/* red-greenish-blue ? */
   print_loop( 5, pent1x, pent1y );
   print_poly( wl, wx, wy );

   /*
    * seventh polygon:  outside on top, right, and bottom
    */

   wl = 0;
   clipPolygon( 7, hept1x, hept1y, &wl, wx, wy, 90, 80, 130, 110 );
   glColor3f( 0.0, 0.0, 0.0 );		/* black */
   print_loop( 7, hept1x, hept1y );
   print_poly( wl, wx, wy );

   /* 
    * Flushs OpenGL commands to display 
    */
   glFlush();

}


/*
 * Main routine - GLUT setup and initialization
 */

int main( int argc, char** argv ) {

   /*
    * Initializes GLUT and should be used before any OpenGL functions
    */
   glutInit( &argc, argv );

   /*
    * Creates window on screen with title in argument
    */
   glutCreateWindow( "Filled Polygon Test" );

   /*
    * Callback function; causes "display()" to be called each time there
    * is a display callback.
    */
   glutDisplayFunc( display );

   /*
    * Causes program to enter an event-processing loop; should be last
    * statement in main()
    */
   glutMainLoop( );

   return 0;

}
