/**
 * UnicalcLua.cpp
 *
 * @author John Reese
 */

#include <QtGui>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include "Unicalc.h"
#include "UnicalcLua.h"
#include "UnicalcMath.h"
#include "Unilua.h"

Unicalc *Unilua::parent;

UnicalcLua::UnicalcLua(Unicalc *parentLink)
{
	parent = parentLink;
	Unilua::parent = parentLink;
	
	lua = luaInit();
}

UnicalcLua::~UnicalcLua()
{
	lua_close(lua); 
}

void UnicalcLua::exec() 
{ 
	luaCommand(buffer);
}

void UnicalcLua::load() 
{
	QString fname = QFileDialog::getOpenFileName(parent, tr("Open Script"), "lua/", tr("Lua (*.lua);;All Files (*.*)"));
	
	QFile f(fname);
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	buffer.clear();
	while (!f.atEnd()) {
		buffer.append(f.readLine());
	}
}

void UnicalcLua::reset() 
{ 
	lua_close(lua);
	lua = luaInit();
}

lua_State* UnicalcLua::luaInit()
{
	lua_State *l = lua_open();
	
	luaopen_base(l);
	luaopen_math(l);
	luaopen_table(l);
	luaopen_string(l);

	Unilua::init(l);

	return l;
}

void UnicalcLua::luaCommand (QByteArray chunk)
{
	if (chunk.count() > 0) {
		int error = luaL_loadbuffer(lua, chunk.data(), chunk.count(), "unicalc")
			|| lua_pcall(lua, 0, 0, 0);

		if (error) {
			fprintf(stderr, "%s", lua_tostring(lua, -1));
			lua_pop(lua, 1);
		}
	}
}


// EOF

