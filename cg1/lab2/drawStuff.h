#ifndef _drawstuff
#define _drawstuff

void drawLine( int x1, int y1, int x2, int y2);
void drawPolygon( int n, int x[], int y[] ); 
void clipPolygon (int in, int inx[], int iny[], int *out, int outx[],
                  int outy[], int x0, int y0, int xq, int y1);

#endif
