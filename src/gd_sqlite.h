#ifndef GDSQLITE_H
#define GDSQLITE_H

#include <core/Godot.hpp>
#include <Reference.hpp>

using namespace godot;

class GDSqlite : public GodotScript<Reference> { 
    GODOT_CLASS(GDSqlite)
public:
    static void _register_methods();
    
    int open(Variant filename, bool bInMemory = false);
    void close();
private: 
    class sqlite3 *db;
};

#endif