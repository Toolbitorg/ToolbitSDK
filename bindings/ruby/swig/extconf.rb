require 'mkmf'

if RUBY_PLATFORM.downcase =~ /mswin(?!ce)|mingw|cygwin|bccwin/
  puts "Windows"#
  $libs += "-lsetupapi"
# The following options might be useful to distribute it for non MinGW users
# $libs += "-lsetupapi -static-libstdc++ -static-libgcc"

else
  puts "Linux"
  $libs += " -lstdc++ -lusb-1.0 -lpthread"
end

create_makefile("tbi")