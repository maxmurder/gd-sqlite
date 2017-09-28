#include "gd_sqlite.h"
#include "sqlite/sqlite3.h"
#include <OS.hpp>

int GDSqlite::open(Variant filename, bool bInMemory)
{
    String path = bInMemory ? String("file::memory:") : OS::get_data_dir() + String("/") + filename;
    int ret = sqlite3_open(path.c_string(), &db);
    if (ret != SQLITE_OK)
    {
        printf("[GDSqlite] Error opening database: %s\n", sqlite3_errmsg(db));
    }
    return ret;
}

void GDSqlite::close()
{
    sqlite3_close(db);
}

void GDSqlite::_register_methods() 
{
    register_method((char *)"Open", &GDSqlite::open);
    register_method((char *)"Close", &GDSqlite::close);
}