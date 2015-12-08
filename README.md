# mruby-lua

**mruby-lua** calls Lua script engine from mruby.
It provide to use many Lua scripts written for embedded host on mruby environment.

## Classes

### Lua

#### Singleton methods

* `new -> self`
  - Create instance of Lua script engine.

#### Instance methods

* `dostring(script_string) -> nil`
  - Run Lua script from string object.

* `dostring(script_file_path) -> nil`
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

Set global variable from Lua.

    lua = Lua.new

    lua["a"] = 123
    lua["b"] = 23.45
    lua["c"] = true
    lua["d"] = nil

    lua.dostring "print(a)" # => 123
    lua.dostring "print(b)" # => 23.45
    lua.dostring "print(c)" # => true
    lua.dostring "print(d)" # => nil

