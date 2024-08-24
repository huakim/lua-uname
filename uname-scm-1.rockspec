package = "uname"
version = "scm-1"
source = {
  url = "git://github.com/huakim/lua-uname.git"
}
description = {
  summary = "C module for Lua for getting distribution information",
  detailed = [[
    Lua module written in C, which gets distribution information.
  ]],
  license = "MIT/X11",
  homepage = "http://github.com/huakim/lua-uname"
}
dependencies = {
  "lua >= 5.1"
}
build = {
  type = "builtin",
  modules = {
    uname = {
      sources = {"uname.c"}
    }
  }
}
