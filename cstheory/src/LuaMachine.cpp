/*
** Lua binding: machine
** Generated automatically by tolua++-1.0.92 on Wed Aug  1 22:27:57 2007.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_machine_open (lua_State* tolua_S);

#include "Machine.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_Machine (lua_State* tolua_S)
{
 Machine* self = (Machine*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"State");
 tolua_usertype(tolua_S,"Transition");
 tolua_usertype(tolua_S,"Machine");
 tolua_usertype(tolua_S,"vector<Transition*>");
}

/* get function: symbol of class  Transition */
#ifndef TOLUA_DISABLE_tolua_get_Transition_symbol
static int tolua_get_Transition_symbol(lua_State* tolua_S)
{
  Transition* self = (Transition*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'symbol'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->symbol);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: symbol of class  Transition */
#ifndef TOLUA_DISABLE_tolua_set_Transition_symbol
static int tolua_set_Transition_symbol(lua_State* tolua_S)
{
  Transition* self = (Transition*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'symbol'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->symbol = ((char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: destination of class  Transition */
#ifndef TOLUA_DISABLE_tolua_get_Transition_destination
static int tolua_get_Transition_destination(lua_State* tolua_S)
{
  Transition* self = (Transition*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'destination'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->destination);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: destination of class  Transition */
#ifndef TOLUA_DISABLE_tolua_set_Transition_destination
static int tolua_set_Transition_destination(lua_State* tolua_S)
{
  Transition* self = (Transition*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'destination'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->destination = ((string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: name of class  State */
#ifndef TOLUA_DISABLE_tolua_get_State_name
static int tolua_get_State_name(lua_State* tolua_S)
{
  State* self = (State*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: name of class  State */
#ifndef TOLUA_DISABLE_tolua_set_State_name
static int tolua_set_State_name(lua_State* tolua_S)
{
  State* self = (State*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->name = ((string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: accepting of class  State */
#ifndef TOLUA_DISABLE_tolua_get_State_accepting
static int tolua_get_State_accepting(lua_State* tolua_S)
{
  State* self = (State*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'accepting'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->accepting);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: accepting of class  State */
#ifndef TOLUA_DISABLE_tolua_set_State_accepting
static int tolua_set_State_accepting(lua_State* tolua_S)
{
  State* self = (State*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'accepting'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->accepting = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: transits of class  State */
#ifndef TOLUA_DISABLE_tolua_get_State_transits
static int tolua_get_State_transits(lua_State* tolua_S)
{
  State* self = (State*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'transits'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->transits,"vector<Transition*>");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: transits of class  State */
#ifndef TOLUA_DISABLE_tolua_set_State_transits
static int tolua_set_State_transits(lua_State* tolua_S)
{
  State* self = (State*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'transits'",NULL);
  if (!tolua_isusertype(tolua_S,2,"vector<Transition*>",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->transits = *((vector<Transition*>*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Machine */
#ifndef TOLUA_DISABLE_tolua_machine_Machine_new00
static int tolua_machine_Machine_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Machine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Machine* tolua_ret = (Machine*)  new Machine();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Machine");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Machine */
#ifndef TOLUA_DISABLE_tolua_machine_Machine_new00_local
static int tolua_machine_Machine_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Machine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Machine* tolua_ret = (Machine*)  new Machine();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"Machine");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Machine */
#ifndef TOLUA_DISABLE_tolua_machine_Machine_delete00
static int tolua_machine_Machine_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Machine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Machine* self = (Machine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDebug of class  Machine */
#ifndef TOLUA_DISABLE_tolua_machine_Machine_setDebug00
static int tolua_machine_Machine_setDebug00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Machine",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Machine* self = (Machine*)  tolua_tousertype(tolua_S,1,0);
  int level = ((int)  tolua_tonumber(tolua_S,2,MACHINE_DEBUG));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDebug'",NULL);
#endif
  {
   self->setDebug(level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDebug'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addSymbol of class  Machine */
#ifndef TOLUA_DISABLE_tolua_machine_Machine_addSymbol00
static int tolua_machine_Machine_addSymbol00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Machine",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Machine* self = (Machine*)  tolua_tousertype(tolua_S,1,0);
  string symbol = ((string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addSymbol'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->addSymbol(symbol);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addSymbol'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addState of class  Machine */
#ifndef TOLUA_DISABLE_tolua_machine_Machine_addState00
static int tolua_machine_Machine_addState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Machine",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Machine* self = (Machine*)  tolua_tousertype(tolua_S,1,0);
  string name = ((string)  tolua_tocppstring(tolua_S,2,0));
  bool accepting = ((bool)  tolua_toboolean(tolua_S,3,false));
  bool starting = ((bool)  tolua_toboolean(tolua_S,4,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addState'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->addState(name,accepting,starting);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addTransition of class  Machine */
#ifndef TOLUA_DISABLE_tolua_machine_Machine_addTransition00
static int tolua_machine_Machine_addTransition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Machine",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,1,&tolua_err) ||
     !tolua_iscppstring(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Machine* self = (Machine*)  tolua_tousertype(tolua_S,1,0);
  string state = ((string)  tolua_tocppstring(tolua_S,2,0));
  string destination = ((string)  tolua_tocppstring(tolua_S,3,0));
  string symbol = ((string)  tolua_tocppstring(tolua_S,4,0));
  string read = ((string)  tolua_tocppstring(tolua_S,5,""));
  string write = ((string)  tolua_tocppstring(tolua_S,6,""));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addTransition'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->addTransition(state,destination,symbol,read,write);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addTransition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStarting of class  Machine */
#ifndef TOLUA_DISABLE_tolua_machine_Machine_setStarting00
static int tolua_machine_Machine_setStarting00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Machine",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Machine* self = (Machine*)  tolua_tousertype(tolua_S,1,0);
  string name = ((string)  tolua_tocppstring(tolua_S,2,0));
  bool starting = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStarting'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setStarting(name,starting);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setStarting'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAccepting of class  Machine */
#ifndef TOLUA_DISABLE_tolua_machine_Machine_setAccepting00
static int tolua_machine_Machine_setAccepting00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Machine",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Machine* self = (Machine*)  tolua_tousertype(tolua_S,1,0);
  string name = ((string)  tolua_tocppstring(tolua_S,2,0));
  bool accepting = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAccepting'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setAccepting(name,accepting);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAccepting'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: accepts of class  Machine */
#ifndef TOLUA_DISABLE_tolua_machine_Machine_accepts00
static int tolua_machine_Machine_accepts00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Machine",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Machine* self = (Machine*)  tolua_tousertype(tolua_S,1,0);
  string test = ((string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'accepts'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->accepts(test);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'accepts'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dumpMachine of class  Machine */
#ifndef TOLUA_DISABLE_tolua_machine_Machine_dumpMachine00
static int tolua_machine_Machine_dumpMachine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Machine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Machine* self = (Machine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dumpMachine'",NULL);
#endif
  {
   self->dumpMachine();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dumpMachine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: error of class  Machine */
#ifndef TOLUA_DISABLE_tolua_machine_Machine_error00
static int tolua_machine_Machine_error00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Machine",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  string message = ((string)  tolua_tocppstring(tolua_S,2,0));
  bool ignore = ((bool)  tolua_toboolean(tolua_S,3,false));
  {
   Machine::error(message,ignore);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'error'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_machine_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"Transition","Transition","",NULL);
  tolua_beginmodule(tolua_S,"Transition");
   tolua_variable(tolua_S,"symbol",tolua_get_Transition_symbol,tolua_set_Transition_symbol);
   tolua_variable(tolua_S,"destination",tolua_get_Transition_destination,tolua_set_Transition_destination);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"State","State","",NULL);
  tolua_beginmodule(tolua_S,"State");
   tolua_variable(tolua_S,"name",tolua_get_State_name,tolua_set_State_name);
   tolua_variable(tolua_S,"accepting",tolua_get_State_accepting,tolua_set_State_accepting);
   tolua_variable(tolua_S,"transits",tolua_get_State_transits,tolua_set_State_transits);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Machine","Machine","",tolua_collect_Machine);
  #else
  tolua_cclass(tolua_S,"Machine","Machine","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Machine");
   tolua_function(tolua_S,"new",tolua_machine_Machine_new00);
   tolua_function(tolua_S,"new_local",tolua_machine_Machine_new00_local);
   tolua_function(tolua_S,".call",tolua_machine_Machine_new00_local);
   tolua_function(tolua_S,"delete",tolua_machine_Machine_delete00);
   tolua_function(tolua_S,"setDebug",tolua_machine_Machine_setDebug00);
   tolua_function(tolua_S,"addSymbol",tolua_machine_Machine_addSymbol00);
   tolua_function(tolua_S,"addState",tolua_machine_Machine_addState00);
   tolua_function(tolua_S,"addTransition",tolua_machine_Machine_addTransition00);
   tolua_function(tolua_S,"setStarting",tolua_machine_Machine_setStarting00);
   tolua_function(tolua_S,"setAccepting",tolua_machine_Machine_setAccepting00);
   tolua_function(tolua_S,"accepts",tolua_machine_Machine_accepts00);
   tolua_function(tolua_S,"dumpMachine",tolua_machine_Machine_dumpMachine00);
   tolua_function(tolua_S,"error",tolua_machine_Machine_error00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_machine (lua_State* tolua_S) {
 return tolua_machine_open(tolua_S);
};
#endif

