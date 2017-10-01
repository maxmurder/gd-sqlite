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
    int create_table(Variant name, Variant columns);
    int query(Variant query);
    
    String get_path();
private: 
    class sqlite3 *db;
    class sqlite3_stmt *stmt;
    bool bInMemory;
    String path;
    
    int prepare_stmt(const char* query);
    int step();
    void finalize();
public:
    static void _register_methods()
    {
        register_method((char *)"open", &GDSqlite::open);
        register_method((char *)"close", &GDSqlite::close);
        register_method((char *)"create_table", &GDSqlite::create_table);
        register_method((char *)"query", &GDSqlite::query);
        register_method((char *)"get_path", &GDSqlite::get_path);
    }
    ~GDSqlite()
    {
        close();
    }
};

#endif