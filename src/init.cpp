#include <Godot.hpp>
#include "gd_sqlite.h"

using namespace godot;

GDNATIVE_INIT(godot_gdnative_init_options *options) {
}

GDNATIVE_TERMINATE(godot_gdnative_terminate_options *options) {
}


NATIVESCRIPT_INIT() {
    register_class<GDSqlite>();
}