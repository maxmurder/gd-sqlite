#!python
import os

env = Environment()

platform = ARGUMENTS.get("p", "linux")
cpp_bindings = ARGUMENTS.get("cpp_bindings", "cpp_bindings/")
godot_headers = ARGUMENTS.get("headers", "godot_headers/")
godot_src = ARGUMENTS.get("godot", "godot_fork/")

godot_bin = "godot." + ("x11" if platform == "linux" else platform) + ".tools.64"

if ARGUMENTS.get("use_lvvm", "no") == "yes":
    env["CXX"] = "clang++"

if platform == "linux":
    env.Append(CCFLAGS = ['-fPIC', '-g', '-O3', '-std=c++14', '-Wwrite-strings'])
    env.Append(LINKFLAGS = ['-Wl,-R,\'$$ORIGIN\''])

env.Append(CPPPATH=[godot_headers, cpp_bindings + 'include/', cpp_bindings + 'include/core/', 'src' ])

env.Append(LIBS=['godot_cpp_bindings'])
env.Append(LIBPATH=[ cpp_bindings  + 'include/', 'lib' ])

def add_source(sources, name):
    sources.append(name);

def add_sources(sources, dir, extension):
    for f in os.listdir(dir):
        if f.endswith("." + extension):
            sources.append(dir + "/" + f)

sources = []
add_source(sources, "src/init.cpp")
add_source(sources, "src/gdsqlite.cpp")
add_sources(sources, "src/sqlite", "c")

library = env.SharedLibrary(target='lib/gdsqlite', source=sources)
Default(library)

