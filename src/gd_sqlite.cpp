/* MIT License
 *
 * Copyright (c) 2017 maxmurder
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
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

int GDSqlite::close()
{
   return sqlite3_close(db);
}

int GDSqlite::create_table(Variant _name, Variant _columns)
{
    String name = _name;
    Array columns = _columns;
    int ret = -1;
    // generate query
    char query[128];
    sprintf(query, "CREATE TABLE IF NOT EXISTS `%s` (", name.c_string());
    for(int itr=0; itr<columns.size(); itr++)
    {
        String column = columns[itr];
        sprintf(query, "%s%s%s", query, (itr != 0 ? "," : ""), column.c_string());
    }
    sprintf(query, "%s);", query);
    // compile & execute statement
    if(prepare(query) == SQLITE_OK)
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
    if( prepare(query.c_string()) == SQLITE_OK )
    {
        ret = step();
        finalize();
    }
    return ret;
}

Array GDSqlite::query_array( Variant _query )
{
    Array out;
    String query = _query;
    // construct output array from the query 
    if( prepare(query.c_string()) == SQLITE_OK)
    {
        int ret = step();
        while (ret == SQLITE_ROW) {
            Dictionary row;
            // add all columns to each row
            for(int col = 0; col < sqlite3_column_count(stmt); col++)
            {
               // handle diffrent column types
               switch(sqlite3_column_type(stmt, col))
               {
                    case SQLITE_INTEGER: 
                        row[sqlite3_column_name(stmt, col)] = sqlite3_column_int(stmt, col);
                        break;
                    case SQLITE_FLOAT:
                        row[sqlite3_column_name(stmt, col)] = sqlite3_column_double(stmt, col);
                        break;
                    case SQLITE_TEXT:
                        row[sqlite3_column_name(stmt, col)] = String((char *)sqlite3_column_text(stmt, col));
                        break;
               }
            }
            // store result and iterate
            out.push_back(row);
            ret = step();
        }
    }
    finalize();
    return out;
}

String GDSqlite::get_path()
{
    return path;
}

int GDSqlite::prepare(const char* query)
{
    return sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
}

int GDSqlite::step()
{
    return sqlite3_step(stmt);
}

int GDSqlite::finalize()
{
    return sqlite3_finalize(stmt);
}

