# mruby-lua

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

    lua["a"] # => 10
    lua["c"] # => 20
    lua["c"] # => 200

