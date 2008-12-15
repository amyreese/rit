/**
 * Lua Bindings
 */

#include <QtGui>
#include "Unicalc.h"
#include "Unilua.h"

extern "C" {
#include <lua.h>
}

int Unilua::delay = 0;
int Unilua::count = 1;

void Unilua::init (lua_State *l)
{
	lua_register(l, "ul_press", Unilua::press);
	lua_register(l, "ul_setcount", Unilua::setcount);
	lua_register(l, "ul_setdelay", Unilua::setdelay);
	
	//Unilua::delay = 0;
	//Unilua::count = 1;
}

int Unilua::setdelay (lua_State *l)
{
	int d = lua_tonumber(l, -1);
	Unilua::delay = (d >= 0 ? d : 0);
	return 0;
}

int Unilua::setcount (lua_State *l)
{
	int c = lua_tonumber(l, -1);
	Unilua::count = (c >= 0 ? c : 0);
	return 0;
}

int Unilua::press (lua_State *l)
{
	const char* str = lua_tolstring(l, -1, NULL);
	if (str != NULL) {
		QString button(str);
		
		int d = Unilua::count * Unilua::delay;
		Unilua::count++;

		Unilua::parent -> click(button, d);
	}
	return 0;
}

//EOF

