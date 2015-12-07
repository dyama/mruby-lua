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

void class_lua_final(mrb_state* mrb, void* p)
{
  lua_State* L = p;
  lua_close(L);
  // mrb_free(mrb, p);
}

static struct mrb_data_type class_lua_type
  = { "Lua", class_lua_final };

mrb_value class_lua_init(mrb_state* mrb, mrb_value self)
{
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);
  DATA_PTR(self) = L;
  DATA_TYPE(self) = &class_lua_type;
  return self;
}

mrb_value class_lua_dostring(mrb_state* mrb, mrb_value self)
{
  mrb_value str;
  int argc = mrb_get_args(mrb, "S", &str);
  lua_State* L = DATA_PTR(self);
  if (luaL_dostring(L, RSTRING_PTR(str))) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to execute Lua.");
  }
  return mrb_nil_value();
}

void mrb_mruby_lua_gem_init(mrb_state* mrb)
{
  struct RClass* rclass = mrb_define_class(mrb, "Lua", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", class_lua_init, MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "dostring",  class_lua_dostring,MRB_ARGS_REQ(1));
  return;
}

void mrb_mruby_lua_gem_final(mrb_state* mrb)
{
  return;
}

