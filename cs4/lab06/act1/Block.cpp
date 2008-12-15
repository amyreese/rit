// File: Block.cpp
// Author: John Reese
//
// Revisions:
//   $Log: Block.cpp,v $
//   Revision 1.2  2004/04/17 22:15:28  jmr8223
//   *** empty log message ***
//
//   Revision 1.1  2004/04/17 21:07:20  jmr8223
//    - initial commit
//

#include "Block.h"
#include <cassert>

using namespace std;

namespace RITCSFigures {

    Block::Block ( int r, int c, Display &d, int h, int w ) : 
    height (h), width (w), Figure (r, c, d) {
        assert( h >= 0 && w >= 0 );
    }
    
    string Block::what_am_i () const {
        return "Block";
    }
    
    void Block::display ( char ch ) {
        int r,c;
        
        for (r = get_row(); r < get_row() + height; r++) {
            for (c = get_column(); c < get_column() + width; c++) {
                get_canvas().set_cur_pos( r, c );
                get_canvas().put ( ch );
            }
        }
    }

}
