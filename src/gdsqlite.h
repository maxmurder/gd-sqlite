#ifndef GDSQLITE_H
#define GDSQLITE_H

#include "sqlite/sqlite3.h"

#include <core/Godot.hpp>
#include <Reference.hpp>
#include <OS.hpp>

using namespace godot;

class GDsqlite : public GodotScript<Reference> { 
    GODOT_CLASS(GDSqlite)
public:
    static void _register_methods();
};

#endif