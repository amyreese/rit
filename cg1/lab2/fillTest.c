/*
 *  polygonTest.c
 *
 *  This program is designed to test filling triangles and rectangles
 */

#include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/

void display( void ) {

   int x[7], y[7];

   /*
    * Clear window  - glClear clears all buffers whose bits are set in mask
    * formed by logical OR of values defined in gl.h.  GL_COLOR_BUFFER_BIT
    * refers to color buffer.
    */
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
    * Use Student's drawPolygon 
    */
   x[0] = 10; y[0] = 10;
   x[1] = 20; y[1] = 10;
   x[2] = 20; y[2] = 20;
   x[3] = 10; y[3] = 20;

   /* 
    * LL => Lower Left Start, CCW => Vertices entered in 
    * counter clockwise progression 
    */
   drawPolygon( 4, x, y );	/* Square, LL, CCW */

   x[0] = 40; y[0] = 30;
   x[1] = 40; y[1] = 50;
   x[2] = 30; y[2] = 50;
   x[3] = 30; y[3] = 30;

   drawPolygon( 4, x, y );	/* Rectangle, LR, CCW */

   x[0] = 40; y[0] = 90;
   x[1] = 40; y[1] = 70;
   x[2] = 10; y[2] = 70;
   x[3] = 10; y[3] = 90;

   drawPolygon( 4, x, y );	/* Rectangle, UR, CW */

   x[0] = 10; y[0] = 230;
   x[1] = 40; y[1] = 230;
   x[2] = 40; y[2] = 210;
   x[3] = 10; y[3] = 210;

   drawPolygon( 4, x, y );	/* Rectangle, UL, CW */

   x[0] = 100; y[0] = 10;
   x[1] = 150; y[1] = 10;
   x[2] = 125; y[2] = 20;

   drawPolygon( 3, x, y );	/* Isosceles, flat bottom */

   x[0] = 100; y[0] = 30;
   x[1] = 140; y[1] = 50;
   x[2] = 175; y[2] = 50;

   drawPolygon( 3, x, y );	/* flat top - tail to left */

   x[0] = 120; y[0] = 40;
   x[1] = 80;  y[1] = 60;
   x[2] = 45;  y[2] = 60;

   drawPolygon( 3, x, y );	/* flat top - tail to right */

   x[0] = 10; y[0] = 100;
   x[1] = 10; y[1] = 120;
   x[2] = 25; y[2] = 100;

   drawPolygon( 3, x, y );	/* Right */

   x[0] = 10; y[0] = 130;
   x[1] = 20; y[1] = 130;
   x[2] = 20; y[2] = 140;

   drawPolygon( 3, x, y );	/* Right */

   x[0] = 10; y[0] = 170;
   x[1] = 20; y[1] = 170;
   x[2] = 10; y[2] = 150;

   drawPolygon( 3, x, y );	/* Right */

   x[0] = 100; y[0] = 70;
   x[1] = 150; y[1] = 70;
   x[2] = 75;  y[2] = 90;

   drawPolygon( 3, x, y );	/* flat bottom - top left */

   x[0] = 100; y[0] = 100;
   x[1] = 150; y[1] = 100;
   x[2] = 195; y[2] = 120;

   drawPolygon( 3, x, y );	/* flat bottom - top right */

   x[0] = 100; y[0] = 170;
   x[1] = 150; y[1] = 150;
   x[2] = 175; y[2] = 130;

   drawPolygon( 3, x, y );	/* scalene */

   x[0] = 200; y[0] =  50;
   x[1] = 225; y[1] =  90;
   x[2] = 250; y[2] =  50;
   x[3] = 225; y[3] =  10;

   drawPolygon ( 4, x, y );     /* diamond */

   x[0] = 200; y[0] = 125;
   x[1] = 210; y[1] = 150;
   x[2] = 260; y[2] = 145;
   x[3] = 275; y[3] = 120;
   x[4] = 250; y[4] = 100;
   x[5] = 225; y[5] = 100;

   drawPolygon ( 6, x, y );     /* hexagon */

   x[0] = 215; y[0] = 225;
   x[1] = 200; y[1] = 250;
   x[2] = 215; y[2] = 250;
   x[3] = 225; y[3] = 275;
   x[4] = 235; y[4] = 250;
   x[5] = 250; y[5] = 250;
   x[6] = 235; y[6] = 225;

   drawPolygon ( 7, x, y );     /* star top */

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
   glutCreateWindow( "Polygon Test" );

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
