/*
 *  lineTest.c
 *
 *  This program is designed to test "drawLine".
 */

#include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/


void display( void ) {

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
    * Use drawLine from Student's to draw 
    */
   drawLine( 100, 100, 100, 150 );  /* Vertical */
   drawLine( 100, 100, 100, 50 );   /* Vertical */

   drawLine( 100, 100, 50, 100 );   /* Horizontal */
   drawLine( 100, 100, 150, 100 );  /* Horizontal */

   drawLine( 100, 100, 150, 150 );  /* + diagonal */
   drawLine( 100, 100, 50, 50 );    /* + diagonal */

   drawLine( 100, 100, 50, 150 );   /* - diagonal */
   drawLine( 100, 100, 150, 50 );   /* - diagonal */

   drawLine( 100, 100, 150, 125 );  /* shallow + slope */
   drawLine( 100, 100, 50, 75 );    /* shallow + slope */

   drawLine( 100, 100, 150, 75 );   /* shallow - slope */
   drawLine( 100, 100, 50, 125 );   /* shallow - slope */

   drawLine( 100, 100, 125, 150 );  /* steep + slope */
   drawLine( 100, 100, 75, 50 );    /* steep + slope */

   drawLine( 100, 100, 125, 50 );   /* steep - slope */
   drawLine( 100, 100, 75, 150 );   /* steep - slope */

   /* Forces OpenGL commands to be displayed */
   glFlush( );

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
   glutCreateWindow( "Line Test" );

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
