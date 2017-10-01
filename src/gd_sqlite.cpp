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

int GDSqlite::create_table(Variant _name, Variant _columns)
{
    String name = _name;
    Array columns = _columns;
    // Generate query
    char query[128];
    sprintf(query, "CREATE TABLE IF NOT EXISTS `%s` (", name.c_string());
    for(int itr=0; itr<columns.size(); itr++)
    {
        String column = columns[itr];
        sprintf(query, "%s%s%s", query, (itr != 0 ? "," : ""), column.c_string());
    }
    sprintf(query, "%s);", query);
    // compile & execute statement
    int ret = -1;
    if(prepare_stmt(query) == SQLITE_OK)
    {
        ret = step();
        finalize();
    }
    return ret;
}

int GDSqlite::query(Variant _query)
{ 
    int ret = -1;
    String query = _query;
    if( prepare_stmt(query.c_string()) == SQLITE_OK )
    {
        ret = step();
        finalize();
    }
    return ret;
}

String GDSqlite::get_path()
{
    return path;
}

int GDSqlite::prepare_stmt(const char* query)
{
    return sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
}

int GDSqlite::step()
{
    return sqlite3_step(stmt);
}

void GDSqlite::finalize()
{
    sqlite3_finalize(stmt);
}

