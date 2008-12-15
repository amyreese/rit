/**
 * Unilua.h
 * Embedded lua library
 */

#ifndef UNICALC_UNILUA_H
#define UNICALC_UNILUA_H

extern "C" {
#include <lua.h>
}

class Unicalc;

class Unilua
{

public:
	static void init (lua_State *l);

	static int setdelay (lua_State *l);
	static int setcount (lua_State *l);
	static int press (lua_State *l);

	static Unicalc *parent;

private:
	static int delay;
	static int count;
};

#endif // UNICALC_UNILUA_H

//EOF

