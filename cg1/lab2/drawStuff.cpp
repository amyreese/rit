/**
 * Basic 2D drawing routines.
 *
 * @author John Reese
 */
#include <stdio.h>
#include <math.h>
#include <list>

using namespace std;

void setPixel (int x, int y);

#define MAX_VERTS 50

/* 
 * Draw line from x1, y1 to x2, y2 
 */
void drawLine( int x1, int y1, int x2, int y2) 
{
	// length of bounding rectangle sides
	int dx = abs( x2 - x1 );
	int dy = abs( y2 - y1 );

	// increment direction
	int sx = x2 - x1 > 0 ? 1 : -1;
	int sy = y2 - y1 > 0 ? 1 : -1;

	// watch for slope > 1
	int steep = dy > dx ? 1 : 0;

	// initial starting parameter
	int p = steep ? (2 * dx) - dy : (2 * dy) - dx;

	setPixel( x1, y1 );

	//printf( "\n\ndx: %d, dy: %d, sx: %d, sy: %d, steep: %d\n\n", dx, dy, sx, sy, steep );

	int i, x = x1, y = y1;
	if ( steep )
		// major axis y
		for ( i = 0; i <= dy; i++ ) {
			y += sy;

			//printf( "x: %d, y: %d, p: %d - ", x, y, p );

			if ( p > 0 ) {
				p -= 2 * dy;
				x++;
			}
			p += 2 * dx;
			setPixel( x, y );
		}
	else
		// major axis x
		for ( i = 0; i <= dx; i++ ) {
			x += sx;

			//printf( "x: %d, y: %d, p: %d - ", x, y, p );

			if ( p > 0 ) {
				p -= 2 * dx;
				y++;
			}
			p += 2 * dy;
			setPixel( x, y );
		}
}

// Info about an edge
struct edge {
	int xmin;
	int xmax;
	int ymin;
	int ymax;
	double xval;
	double slope;
	bool crc;
};

typedef list<edge> etable;

/*
 * Create an edge struct for a pair of coordinates
 */
edge newEdge( int x1, int y1, int x2, int y2 )
{
	edge e;
	e.xmin = x1 < x2 ? x1 : x2;
	e.xmax = x1 > x2 ? x1 : x2;
	e.ymin = y1 < y2 ? y1 : y2;
	e.ymax = y1 > y2 ? y1 : y2;
	e.xval = y1 > y2 ? x1 : x2;
	e.slope = y1 - y2 != 0 ? ( x2 - x1 ) / ( y2 - y1 ) : 0;
	e.crc = y1 - y2 != 0;
	return e;
}

void processEdge( etable *a, etable *g, int x1, int y1, int x2, int y2, int &xmin, int &xmax, int &ymin, int &ymax ) 
{
	edge e = newEdge( x1, y1, x2, y2 );
	if ( e.crc ) {
		g->push_back( e );
	}
	a->push_back( e );
	xmin = e.xmin < xmin ? e.xmin : xmin;
	xmax = e.xmax > xmax ? e.xmax : xmax;
	ymin = e.ymin < ymin ? e.ymin : ymin;
	ymax = e.ymax > ymax ? e.ymax : ymax;
}

/* 
 * Draw filled polygon 
 */
void drawPolygon( int n, int x[], int y[] ) 
{
	int i, p = 0;
	int xmin, xmax, ymin, ymax;
	etable all, global, active, inactive;

	xmin = xmax = x[0];
	ymin = ymax = y[0];

	// fill all & global edge tables
	for ( i = 0; i < n-1; i++ ) {
		processEdge( &all, &global, x[i], y[i], x[i+1], y[i+1], xmin, xmax, ymin, ymax );
	}
	processEdge( &all, &global, x[i], y[i], x[0], y[0], xmin, xmax, ymin, ymax );

	//printf( "all: %d, global: %d, ymin: %d, ymax: %d\n", all.size(), global.size(), ymin, ymax );
	
	etable::iterator iter;
	etable::iterator end = global.end();
	
	int py, px;

	// scanline
	for ( py = ymin; py <= ymax; py++ ) { 
		p = 0;

		// get the currently active edges
		end = global.end();
		for ( iter = global.begin(); iter != end; iter++ ) {
			if ( iter->ymin <= py && iter->ymax >= py ) { // intersects current scanline
				if ( active.size() == 0 ) { // first edge
					active.push_back( *iter );
				} else { // insert edge in xval order
					etable::iterator e = active.end();
					etable::iterator n = active.begin();
					while ( n != e ) {
						if ( n->xval > iter->xval ) {
							active.insert( n, *iter );
							break;
						}
						n++;
					}
				}
			} else {
				inactive.push_back(*iter);
			}
		}
		global = inactive;

		//printf( "active: %d, global: %d\n", active.size(), global.size() );

		// pixel column
		for ( px = xmin; px <= xmax; px++ ) {
			// check for intersecting edges
			end = active.end();
			for ( iter = active.begin(); iter != end; iter++ ) {
				if ( round(iter->xval) == px ) { // intersection
					p = p ? 0 : 1; // toggle parity
				}
			}
			if ( p ) setPixel( px, py ); // draw pixel if parity odd  (inside polygon)
		}

		// update edge xval & return to global edge table
		end = active.end();
		for ( iter = active.begin(); iter != end; iter++ ) {
			iter->xval += iter->slope;
			global.push_back( *iter );
		}

		// clear per scanline edge tables
		active.clear();
		inactive.clear();

	}
}

/**
 * Clip the polygon with vertex count in and verticies inx and iny against
 * the rectangular clipping region specified by lower left corner (x0, y0) 
 * and upper right corner (x1, y1).  The resulting vertices are places in
 * outx, and outy with the vertex count places in out.
 */
void clipPolygon (int in, int inx[], int iny[], int *out, int outx[],
                  int outy[], int x0, int y0, int xq, int y1)
{
}
