Gem::Specification.new do |s|
  s.name = 'bktree'
  s.version = '0.0.1'
  s.authors = ["Tyler McMullen"]
  s.date = '2010-02-13'
  s.description = 'bktree in c with ruby bindings'
  s.email = 'tbmcmullen@gmail.com'
  s.extensions = ["ext/extconf.rb"]
  s.extra_rdoc_files = ["README"]
  s.files = Dir['*'] + Dir['ext/*.{c,h,rb}']
  s.homepage = 'http://github.com/tyler/BkTree'
  s.require_paths = ["ext"]
  s.rubygems_version = '1.3.5'
  s.summary = 'bktree in c with ruby bindings'
end
