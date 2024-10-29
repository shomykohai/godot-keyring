#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")
env.PrependENVPath("PATH", os.getenv("PATH"))
env.PrependENVPath("PKG_CONFIG_PATH", os.getenv("PKG_CONFIG_PATH"))
env.Append(CPPPATH=["src/"])
sources = [Glob("src/*.cpp")]


if env["platform"] == "linux":
    env.Append(LINKFLAGS=['-static-libstdc++'])
    # Add libsecret headers to the compilation flow
    env.ParseConfig("pkg-config libsecret-1 --cflags --libs")
    sources.append(Glob("src/keychain/keychain_linux.cpp"))
elif env["platform"] == "windows":
    sources.append(Glob("src/keychain/keychain_win.cpp"))
# Have to be tested, so for now commenting it out
# elif env["platform"] == "macos":
#     sources.append(Glob("src/keychain/keychain_mac.cpp"))

libpath = "demo/bin/keyring{}{}".format(env["suffix"], env["SHLIBSUFFIX"])
library = env.SharedLibrary(libpath, source=sources)
Default(library)
