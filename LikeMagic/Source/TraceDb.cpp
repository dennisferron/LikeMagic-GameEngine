#include "LikeMagic/Utility/TraceDb.hpp"
#include "sqlite3.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;

namespace LM
{
class TraceDbImpl : public TraceDb
{
private:
    sqlite3* db;

public:
    virtual void open();
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

void TraceDbImpl::open()
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
