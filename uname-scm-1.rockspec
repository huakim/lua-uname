package = "uname"
version = "scm-1"
source = {
  url = "git://github.com/huakim/lua-uname.git"
}
description = {
  summary = "A hello-world C module for Lua",
  detailed = [[
    This is simple Lua module written in C, intended
    to help you learn how to write C modules.
  ]],
  license = "MIT/X11",
  homepage = "http://norman.github.com/hello-lua"
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
