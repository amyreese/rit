#ifndef UNICALC_LUA_H
#define UNICALC_LUA_H

/**
 * UnicalcLua.h
 * Object containing the Lua interpreter
 *
 * @author John Reese
 */

#include <QtGui>

extern "C" {
#include <lua.h>
}

class Unicalc;

class UnicalcLua : public QObject
{
	Q_OBJECT

public:
	UnicalcLua(Unicalc *parentLink);
	~UnicalcLua();

public slots:
	void exec();
	void load();
	void reset();

private:
	Unicalc *parent;

	lua_State *luaInit();
	void luaCommand (QByteArray chunk);
	
	lua_State *lua;

	QByteArray buffer;

};

#endif //UNICALC_LUA_H

//EOF

