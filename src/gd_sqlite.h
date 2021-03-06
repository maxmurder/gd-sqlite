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
#ifndef GDSQLITE_H
#define GDSQLITE_H

#include <core/Godot.hpp>
#include <Reference.hpp>

using namespace godot;

class GDSqlite : public GodotScript<Reference> { 
    GODOT_CLASS(GDSqlite)
public:
    /* Opens a database file for read/write.
     * @param filename  Variant<String> 
     *                  Name of slqite database file to be opened. Files are 
     *                  saved to the godot app_userdata folder.
     * @param bInMemory bool
     *                  If true database is opened as an slqite3 in-memory
     *                  database.
     * @return int      sqlite3 return code.
     */                
    int open(Variant filename, bool bInMemory = false);
    
    /* Closes the currently open database. 
     * @return int      sqlite3 return code.
     */
    int close();
    
    /* Backup database to a file on disk.
     * @param filename  Variant<String>
     *                  Name of file to write to.
     * @return int      sqlite3 return code. 
     */
    int backup(Variant filename);
    
    /* Saves an in memory database to disk 
     * @return int      sqlite3 return code.
     */
    int save();
    
    /* Simple query, best used for insertions, deletions etc.
     * @param query     Variant<String>
     *                  SQL query to be executed on database. Follows 
     *                  traditional SQL syntax.
     * @return int      sqlite3 return code.
     */
    int query(Variant query);
    
    /* Query which returns an array of the query results, best used for
     * selections etc.
     * @param query     Variant<String>
     *                  SQL query to be executed on the database Follows
     *                  Traditional SQL syntax.
     * @return Array<Dictionary> Array of rows returned by the query.
     */
    Array query_array(Variant query);
    
    /* Creates a new table in the database.
     * @param name      Variant<String>
     *                  Name of table to be created.
     * @param columns   Variant<Array<String>>
     *                  List of columns to be added to created table. Follows
     *                  traditional SQL syntax.
     *                  ["id INTEGER PRIMARY KEY AUTOINCREMENT", "name TEXT"]
     * @return int      sqlite3 return code.
     */
    int create_table(Variant name, Variant columns);
    
    /* Returns true if database is in memory */
    bool is_in_memory();
    
    /* Returns the path to the sqlite3 database file. */
    String get_path();
    
    /* Returns latest error message from the sqlite3 database */ 
    String get_error();
    
    
private: 
    class sqlite3 *db;
    class sqlite3_stmt *stmt;
    bool bInMemory;
    String path;
    
    int prepare(const char* query);
    int step();
    int finalize();
public:
    static void _register_methods()
    {
        register_method((char *)"open", &GDSqlite::open);
        register_method((char *)"close", &GDSqlite::close);
        register_method((char *)"backup", &GDSqlite::backup);
        register_method((char *)"save", &GDSqlite::save);
        register_method((char *)"query", &GDSqlite::query);
        register_method((char *)"query_array", &GDSqlite::query_array);
        register_method((char *)"create_table", &GDSqlite::create_table);
        register_method((char *)"is_in_memory", &GDSqlite::is_in_memory);
        register_method((char *)"get_path", &GDSqlite::get_path);
        register_method((char *)"get_error", &GDSqlite::get_error);
    }
    ~GDSqlite()
    {
        close();
    }
};

#endif