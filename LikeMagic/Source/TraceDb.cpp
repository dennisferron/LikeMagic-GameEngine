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

typedef boost::variant<DbNull, int, double, std::string const&> sqlite_value_type;
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
};

class TraceDbImpl : public TraceDb
{
private:
    sqlite3* db;

    void bind(sqlite3_stmt* stmt, int index, sqlite_value_type value)
    {
        BinderVisitor binder(stmt, index);
        boost::apply_visitor<BinderVisitor, sqlite_value_type>(binder, value);
    }

    void bind(sqlite3_stmt* stmt, columns_and_values values)
    {
        for (int i = 0; i < (int)values.size(); ++i)
        {
            bind(stmt, i, values[i].second);
        }
    }

    void insert(string table_name, columns_and_values values)
    {
        stringstream ss;
        ss << "insert into ";
        ss << table_name;
        ss << "(";

    }

public:
    virtual void open(string program_name);
    virtual void close();
    virtual void test();
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
