#include <mruby.h>
#include <mruby/class.h>
#include <mruby/variable.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <lua5.2/lua.h>
#include <lua5.2/lauxlib.h>

void luaL_openlibs(lua_State*);

void lua_final(mrb_state* mrb, void* p)
{
  lua_State* L = p;
  lua_close(L);
  // mrb_free(mrb, p);
}

static struct mrb_data_type class_lua_type = { "Lua", lua_final };

mrb_value mrb_lua_init(mrb_state* mrb, mrb_value self)
{
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);
  DATA_PTR(self) = L;
  DATA_TYPE(self) = &class_lua_type;
  return self;
}

mrb_value lua_to_mrb(mrb_state* mrb, lua_State* L, int index)
{
  mrb_value result;
  switch (lua_type(L, index)) {
    case LUA_TNIL:
      result = mrb_nil_value();
      break;
    case LUA_TNUMBER:
      ;
      lua_Integer n = lua_tointeger(L, index);
      lua_Number  f = lua_tonumber(L, index);
      if (n != f) {
        result = mrb_float_value(mrb, f);
      }
      else {
        result = mrb_fixnum_value(n);
      }
      break;
    case LUA_TBOOLEAN:
      result = lua_toboolean(L, index) ? mrb_true_value() : mrb_false_value(); 
      break;
    case LUA_TSTRING:
      result = mrb_str_new_cstr(mrb, lua_tostring(L, index));
      break;
    case LUA_TFUNCTION:
      if (lua_iscfunction(L, index)) {
        lua_CFunction cf = lua_tocfunction(L, index);
        result = mrb_cptr_value(mrb, cf);
      }
      else if (lua_isfunction(L, index)) {
        // Not impremented.
        result = mrb_nil_value();
      }
      break;
    case LUA_TTABLE:
      result = mrb_str_new_cstr(mrb, "DEBUG");
      break;
    case LUA_TUSERDATA:
    case LUA_TLIGHTUSERDATA:
    case LUA_TTHREAD:
    default:
        // Not impremented.
      result = mrb_nil_value();
      break;
  }
  return result;
}

mrb_value mrb_lua_dostring(mrb_state* mrb, mrb_value self)
{
  mrb_value str;
  mrb_get_args(mrb, "S", &str);
  lua_State* L = DATA_PTR(self);
  if (luaL_dostring(L, RSTRING_PTR(str))) {
    mrb_raise(mrb, E_SCRIPT_ERROR, lua_tostring(L, -1));
  }
  return lua_to_mrb(mrb, L, -1);
}

mrb_value mrb_lua_dofile(mrb_state* mrb, mrb_value self)
{
  mrb_value path;
  mrb_get_args(mrb, "S", &path);
  lua_State* L = DATA_PTR(self);
  if (luaL_dofile(L, RSTRING_PTR(path))) {
    mrb_raise(mrb, E_SCRIPT_ERROR, lua_tostring(L, -1));
  }
  return lua_to_mrb(mrb, L, -1);
}

mrb_value mrb_lua_global(mrb_state* mrb, mrb_value self)
{
  mrb_value key;
  mrb_get_args(mrb, "S", &key);
  lua_State* L = DATA_PTR(self);
  lua_getglobal(L, RSTRING_PTR(key));
  return lua_to_mrb(mrb, L, -1);
}

void mrb_mruby_lua_gem_init(mrb_state* mrb)
{
  struct RClass* rclass = mrb_define_class(mrb, "Lua", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", mrb_lua_init,     MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "dostring",   mrb_lua_dostring, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "dofile",     mrb_lua_dofile,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "[]",         mrb_lua_global,   MRB_ARGS_REQ(1));
  return;
}

void mrb_mruby_lua_gem_final(mrb_state* mrb)
{
  return;
}

