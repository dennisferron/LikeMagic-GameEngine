#include "LikeMagic/Utility/TraceDb.hpp"
#include "sqlite3.h"

#include "boost/variant.hpp"
#include "boost/variant/static_visitor.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <map>
#include <vector>
using namespace std;

namespace LM
{

struct DbNull {};

typedef boost::variant<DbNull, int, double, std::string const&, sqlite3_int64> sqlite_value_type;
typedef std::vector<std::pair<char const*, sqlite_value_type>> columns_and_values;

class BinderVisitor : public boost::static_visitor<>
{
private:
    sqlite3_stmt* stmt;
    int index;

    void handle(int rc) const
    {
        if (rc != SQLITE_OK)
            throw DbException();
    }

public:
    BinderVisitor(sqlite3_stmt* stmt_, int index_) : stmt(stmt_), index(index_) { }

    void operator()(DbNull) const
    {
        handle(sqlite3_bind_null(stmt, index));
    }

    void operator()(int value) const
    {
        handle(sqlite3_bind_int(stmt, index, value));
    }

    void operator()(double value) const
    {
        handle(sqlite3_bind_double(stmt, index, value));
    }

    void operator()(string const& value) const
    {
        handle(sqlite3_bind_text(stmt, index, value.c_str(), value.size(), SQLITE_TRANSIENT));
    }

    void operator()(sqlite3_int64 value) const
    {
        handle(sqlite3_bind_int64(stmt, index, value));
    }
};

class TraceDbImpl : public TraceDb
{
private:
    sqlite3* db;
    sqlite3_stmt* insert_session;
    sqlite3_stmt* insert_type_index;
    sqlite3_stmt* insert_expr;

    sqlite3_int64 session_id;
    vector<bool> saved_type_indices;

    sqlite3_stmt* prepare(char const* sql_str, std::size_t str_len);
    void bind(sqlite3_stmt* stmt, int index, sqlite_value_type value);
    void bind(sqlite3_stmt* stmt, columns_and_values values);
    void write_column_list(ostream& os, vector<string> columns, char const* prefix = nullptr);
    void write_column_equals_list(ostream& os, vector<string> columns, char const* separator);
    sqlite3_stmt* prepare_insert(string table_name, vector<string> columns);
    sqlite3_stmt* prepare_select(string table_name,
        vector<string> select_columns,
        vector<string> where_columns,
        vector<string> order_by_columns);
    void run_void(sqlite3_stmt* stmt, columns_and_values values);
    bool has_type_index(TypeIndex type);
    void set_has_type_index(TypeIndex type);

    void prepare_all_statements();

public:
    virtual void open(string program_name);
    virtual void close();
    virtual void test();
    virtual void register_type_index(TypeIndex type);
    virtual void new_Expr(void const* addr, TypeIndex type, void const* value_ptr);
    TraceDbImpl();
} instance;

LIKEMAGIC_API TraceDb* trace_db = &instance;

}

using namespace LM;

TraceDbImpl::TraceDbImpl()
    : db(nullptr)
{
}

void TraceDbImpl::open(std::string program_name)
{
    std::string path = "trace.db";
    int rc = sqlite3_open(path.c_str(), &db);

    if(rc)
    {
        stringstream ss;
        ss << "Can't open database: " << sqlite3_errmsg(db) << endl;
        cerr << ss.str();
        sqlite3_close(db);
        throw std::runtime_error(ss.str());
    }

    prepare_all_statements();

    run_void(insert_session, {{"Program", program_name}});
    session_id = sqlite3_last_insert_rowid(db);
}

void TraceDbImpl::prepare_all_statements()
{
    insert_session = prepare_insert("Session", { "Program" });
    insert_type_index = prepare_insert("TypeIndex",
    {
        "SessionId", "Id", "Description"
    });
    insert_expr = prepare_insert("Expr",
    {
        "SessionId", "Address", "TypeIndex", "ValuePtr"
    });
}

bool TraceDbImpl::has_type_index(TypeIndex type)
{
    size_t id = type.get_id();

    if (id >= saved_type_indices.size())
        return false;
    else
        return saved_type_indices[id];
}

void TraceDbImpl::set_has_type_index(TypeIndex type)
{
    size_t id = type.get_id();

    if (id >= saved_type_indices.size())
        saved_type_indices.resize(id+1);

    saved_type_indices[id] = true;
}

sqlite3_stmt* TraceDbImpl::prepare(char const* sql_str, std::size_t str_len)
{
    sqlite3_stmt* result;
    char const* tail;
    int rc = sqlite3_prepare_v2(db, sql_str, str_len, &result, &tail);

    if (rc != SQLITE_OK)
        throw DbException();

    if (tail != nullptr)
    {
        for (auto p=tail; p < (sql_str+str_len); ++p)
        {
            char c = *p;
            if (c == '\0')
                break;
            if (c != ' ' && c != '\r' && c != '\n' && c != '\t' && c != ';')
                throw DbException();  // multiple statements in sql string
        }
    }

    return result;
}

void TraceDbImpl::bind(sqlite3_stmt* stmt, int index, sqlite_value_type value)
{
    if (index < 1)
        throw DbException();

    BinderVisitor binder(stmt, index);
    boost::apply_visitor<BinderVisitor, sqlite_value_type>(binder, value);
}

void TraceDbImpl::bind(sqlite3_stmt* stmt, columns_and_values values)
{
    for (int i = 0; i < (int)values.size(); ++i)
    {
        bind(stmt, i+1, values[i].second);
    }
}

void TraceDbImpl::write_column_equals_list(ostream& os, vector<string> columns, char const* separator)
{
    for (int i = 0; i < (int)columns.size(); ++i)
    {
        if (i > 0)
            os << separator;

        os << columns[i] << " = @" << columns[i];
    }
}

void TraceDbImpl::write_column_list(ostream& os, vector<string> columns, char const* prefix)
{
    for (int i = 0; i < (int)columns.size(); ++i)
    {
        if (i > 0)
            os << ",";

        if (prefix != nullptr)
            os << prefix;

        os << columns[i];
    }
}

sqlite3_stmt* TraceDbImpl::prepare_insert(string table_name, vector<string> columns)
{
    stringstream ss;
    ss << "insert into ";
    ss << table_name;
    ss << "(";
    write_column_list(ss, columns);
    ss << ") values (";
    write_column_list(ss, columns, "@");
    ss << ")";

    string sql = ss.str();

    // debug print
    cout << sql << endl;

    return prepare(sql.c_str(), sql.length());
}

sqlite3_stmt* TraceDbImpl::prepare_select(
    string table_name,
    vector<string> select_columns,
    vector<string> where_columns,
    vector<string> order_by_columns)
{
    stringstream ss;
    ss << "select ";
    write_column_list(ss, select_columns);
    ss << " from " << table_name;

    if (where_columns.size() > 0)
    {
        ss << endl << "where ";
        write_column_equals_list(ss, where_columns, " and ");
    }

    if (order_by_columns.size() > 0)
    {
        ss << "order by ";
        write_column_list(ss, order_by_columns);
    }

    string sql = ss.str();

    // debug print
    cout << sql << endl;

    return prepare(sql.c_str(), sql.length());
}

void TraceDbImpl::run_void(sqlite3_stmt* stmt, columns_and_values values)
{
    sqlite3_reset(stmt);

    bind(stmt, values);

    int rc;
    while (true)
    {
        rc = sqlite3_step(stmt);
        switch (rc)
        {
        case SQLITE_DONE:
            return;
        case SQLITE_ROW:
            continue;
        default:
            throw DbException(); // Unexpected return code
        }
    }
}

void TraceDbImpl::close()
{
    sqlite3_close(db);
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for(i=0; i<argc; i++)
    {
        cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL");
    }
    cout << endl;
    return 0;
}

void TraceDbImpl::test()
{
    string sql_cmd = "select 1+2 columnA";
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql_cmd.c_str(), callback, 0, &zErrMsg);
    if( rc!=SQLITE_OK )
    {
        cerr << "SQL error: " << zErrMsg << endl;
        sqlite3_free(zErrMsg);
    }
}

void TraceDbImpl::register_type_index(TypeIndex type)
{
    if (!has_type_index(type))
    {
        run_void(insert_type_index,
        {
            {"SessionId", session_id},
            {"Id", (int)type.get_id()},
            {"Description", type.description()}
        });
        set_has_type_index(type);
    }
}

void TraceDbImpl::new_Expr(void const* addr, TypeIndex type, void const* value_ptr)
{
    register_type_index(type);

    stringstream addrSS;
    addrSS << addr;

    stringstream valueSS;
    valueSS << value_ptr;

    run_void(insert_expr,
    {
        {"SessionId", session_id},
        {"Address", addrSS.str()},
        {"TypeIndex", (int)type.get_id()},
        {"ValuePtr", valueSS.str()}
    });
}
