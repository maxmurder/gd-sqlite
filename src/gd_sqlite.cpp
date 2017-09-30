#include "gd_sqlite.h"
#include "sqlite/sqlite3.h"
#include <OS.hpp>

int GDSqlite::open(Variant filename, bool _bInMemory)
{
    bInMemory = _bInMemory;
    path = _bInMemory ? String("file::memory:") : OS::get_data_dir() + String("/") + filename;
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

String GDSqlite::create_table(Variant _name, Variant _columns)
{
    String name = _name;
    Array columns = _columns;
    char query[128];
    sprintf(query, "CREATE TABLE IF NOT EXISTS `%s` (", name.c_string());
    for(int itr=0; itr<columns.size(); itr++)
    {
        String column = columns[itr];
        sprintf(query, "%s%s%s", query, (itr != 0 ? "," : ""), column.c_string());
    }
    sprintf(query, "%s);", query);
    return query;
}

String GDSqlite::get_path()
{
    return path;
}

void GDSqlite::_register_methods() 
{
    register_method((char *)"open", &GDSqlite::open);
    register_method((char *)"close", &GDSqlite::close);
    register_method((char *)"create_table", &GDSqlite::create_table);
    register_method((char *)"get_path", &GDSqlite::get_path);
}