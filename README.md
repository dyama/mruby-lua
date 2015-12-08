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

    p lua["a"] # => 10
    p lua["c"] # => 20
    p lua["c"] # => 200

    lua.dostring "vec1 = { x = 0.0, y = 1.0, z = 3.0 }"
    p lua["vec1"]
    # => {"x"=>0, "y"=>1, "z"=>3}

