# mruby-lua

**mruby-lua** calls Lua script engine from mruby.
It provides to use many Lua scripts written for embedded host on mruby environment.

## Dependency

* liblua5.2 libraries and headers.

I checked to build on Debian GNU/Linux x86, LMDE2 x64 and MinGW32 on MS-Windows7.

## Classes

### class Lua

Class Lua provides Lua script engine. It has a pointer to lua\_State structure.

#### Singleton methods

* `new -> self`
  - Create instance of Lua script engine.

#### Instance methods

* `dostring(script_string) -> nil`
  - Run Lua script from string object.

* `dofile(script_file_path) -> nil`
  - Run Lua script from file.

* `[key] -> object, [key] = object`
  - Set or Get global variable from Lua.

## Examples

### Lua#dostring method

    lua = Lua.new
    
    script =<<"EOF"
      function twice(x)
        return x * 2
      end
      a = 10
      b = 20
      print(a * twice(b))
    EOF
    
    lua.dostring script
      => 400

### Lua#dofile method

    lua = Lua.new
    lua.dofile "test/fib.lua"

### Lua#[] method

Get global variable from Lua.

    lua = Lua.new

    lua.dostring "a = 10; b = 20; c = a * b"

    p lua["a"] # => 10
    p lua["b"] # => 20
    p lua["c"] # => 200

    lua.dostring "vec1 = { x = 0.0, y = 1.0, z = 3.0 }"
    p lua["vec1"]
    # => {"x"=>0, "y"=>1, "z"=>3}

### Lua#[]= method

Set global variable to Lua.

    lua = Lua.new

    lua["a"] = 123
    lua["b"] = 23.45
    lua["c"] = true
    lua["d"] = nil

    lua.dostring "print(a)" # => 123
    lua.dostring "print(b)" # => 23.45
    lua.dostring "print(c)" # => true
    lua.dostring "print(d)" # => nil

## Supported data convertion

|MRuby type|To Lua|From Lua|Lua type     |
|:--------:|:----:|:------:|:-----------:|
|Nil       | o    | o      |NIL          |
|Fixnum    | o    | o      |NUMBER       |
|Float     | o    | o      |NUMBER       |
|String    | o    | o      |STRING       |
|array     |      |        |TABLE        |
|hash      |      | o      |TABLE        |
|C pointer |      | o      |FUNCTION(c)  |
| -        |      |        |FUNCTION     |
|Exception |      |        | -           |
|Bool      | o    | o      |BOOLEAN      |
| -        |      |        |USERDATA     |
| -        |      |        |LIGHTUSERDATA|
| -        |      |        |THREAD       |

