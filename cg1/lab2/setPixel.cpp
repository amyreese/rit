/**
 * setPixel -- openGL routine for setting a pixel
 *
 */

#include <GL/gl.h>

void setPixel (int x, int y)
{
  glRecti( x, y, x+1, y+1 );
}
