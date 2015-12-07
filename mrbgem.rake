MRuby::Gem::Specification.new('mruby-lua') do |spec|
  spec.license = 'MIT'
  spec.author  = 'dyama'
  spec.summary = 'Lua interpretor engine'

  spec.linker.library_paths << "/usr/lib/i386-linux-gnu"
  spec.linker.libraries << "lua5.2"
  # spec.cxx.flags << "-I/usr/include"
end
