#ifndef GDSQLITE_H
#define GDSQLITE_H

#include <core/Godot.hpp>
#include <Reference.hpp>

using namespace godot;

class GDSqlite : public GodotScript<Reference> { 
    GODOT_CLASS(GDSqlite)
public:
    int open(Variant filename, bool bInMemory = false);
    void close();
    String create_table(Variant name, Variant columns);
    
    String get_path();
private: 
    class sqlite3 *db;
    bool bInMemory;
    String path;
public:
    static void _register_methods();
    ~GDSqlite()
    {
        close();
    }
};

#endif