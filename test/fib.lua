-- 
-- fib.lua
-- test script for mruby-lua.
--

function fib(k)
  if k == 0 then
    return 0
  elseif k == 1 then
    return 1
  end
  return fib(k - 2) + fib(k - 1)
end

for i=1, 10, 1 do
  print(fib(i))
end

