# gd-sqlite

A GDNative SQLite wrapper module for Godot 3.0

### Compiling
1. <a href="https://godot.readthedocs.io/en/stable/development/compiling/compiling_for_x11.html#">Compile Godot 3.0 </a>
2. Get the GodotNativeTools sources:
```bash
$ cd gd-sqlite/
$ git clone https://github.com/GodotNativeTools/godot_headers.git
$ git clone https://github.com/GodotNativeTools/godot-cpp.git
```
3. Link godot source
```bash
$ ln -s [/path/to/godot/] godot_fork
```
```
[gd-sqlite]
    ├──godot_fork -> [/path/to/godot/]
    ├──cpp_bindings/
    ├──godot_headers/
    └──src/
    
```
4. <a href="https://github.com/GodotNativeTools/godot-cpp">Generate bindings:</a>
```bash
$ cd cpp_bindings
$ scons godotbinpath="../godot_fork/bin/" headers="../godot_headers/" p=linux generate_bindings=yes
```
5. Copy libraries into libs dir
```bash
$ cd ..
$ mkdir lib
$ cp cpp_bindings/bin/libgodot_cpp_bindings.a lib/
```
Final Directory Structure:
```
[gd-sqlite]
    ├──godot_fork -> [/path/to/godot/]
    ├──cpp_bindings/
    ├──godot_headers/
    ├──lib/
    |   └──libgodot_cpp_bindings.a
    └──src/
```
6. Compile Library
```bash
$ scons
```
### Import GDNative library
1. Copy contents of `gd-sqlite/lib/` dircetory into `lib/` directory in your 
   godot project.
2. Open your project in Godot.
3. In Godot create GDNativeScript resource: `Create New Resource > GDNativeScript`
4. Configure Class Name: `GDNativeScript Properties > Class Name` `GDSqlite`
5. Configure library: `GDNativeScript Propeties > Library > New GDNativeLibrary`
6. Set X11 resource: `GDNativeLibrary Properties > Platform > X11 64bit` `res://lib/libgd_sqlite.so`

### Usage
You can now load the GDNativeScript resoure and call library functions from gdscript.
``` test.gd
extends Node
 
# load the GDNativeScript resource
var GDSqlite = load("res://lib/gd_sqlite.gdns");

# instantiate class
var db = GDSqlite.new();

func _ready():
        # open database
        db.open("test.sql");
        
        # create table 
        db.create_table("test", ["id INTEGER PRIMARY KEY AUTOINCREMENT", "name TEXT", "test INTEGER"]);
        
        # insert row
        db.query("INSERT INTO test (name, test) VALUES ('test', '999');");
        
        # fetch query 
        var data = db.query_array("SELECT * FROM test;");
        print(data.size());
        for item in data:
                for key in item.keys():
                        print(item[key]);
        
        # close database
        db.close();
        pass
```
