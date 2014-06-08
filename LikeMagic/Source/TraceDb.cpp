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

typedef boost::variant<DbNull, int, double, std::string, sqlite3_int64> sqlite_value_type;
typedef std::vector<std::pair<char const*, sqlite_value_type>> names_and_values;
typedef std::vector<std::pair<char const*, char const*>> names_and_sql_code;

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

    void operator()(string value) const
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
    sqlite3_stmt* insert_io_tag;
    sqlite3_stmt* insert_io_object;
    sqlite3_stmt* update_io_object_data;
    sqlite3_stmt* insert_io_message;
    sqlite3_stmt* update_io_message_name;
    sqlite3_stmt* update_io_message_label;
    sqlite3_stmt* update_io_message_line;
    sqlite3_stmt* update_io_message_character;
    sqlite3_stmt* insert_io_call;
    sqlite3_stmt* update_io_call_message;
    sqlite3_stmt* insert_io_stack_object;
    sqlite3_stmt* insert_io_stack_mark;
    sqlite3_stmt* insert_io_stack_pop_mark;
    sqlite3_stmt* update_expr_when_freed;
    sqlite3_stmt* update_io_tag_when_freed;
    sqlite3_stmt* update_io_object_when_freed;
    sqlite3_stmt* update_io_message_when_freed;
    sqlite3_stmt* update_io_call_when_freed;

    sqlite3_int64 sequence;
    vector<bool> saved_type_indices;

    sqlite3_stmt* prepare(char const* sql_str, std::size_t str_len);
    void bind(sqlite3_stmt* stmt, int index, sqlite_value_type value);
    void bind(sqlite3_stmt* stmt, names_and_values values);
    void write_column_list(ostream& os, vector<string> columns, char const* prefix = nullptr);
    void write_column_list(ostream& os, names_and_sql_code columns);
    void write_value_list(ostream& os, names_and_sql_code values);
    void write_column_equals_list(ostream& os, vector<string> columns, char const* separator);
    sqlite3_stmt* prepare_insert(string table_name, vector<string> columns);
    sqlite3_stmt* prepare_custom_insert(string table_name, names_and_sql_code values);
    sqlite3_stmt* prepare_select(string table_name,
        vector<string> select_columns,
        vector<string> where_columns,
        vector<string> order_by_columns);
    sqlite3_stmt* prepare_update_last_address(string table_name,
        vector<string> columns);
    void run_void(sqlite3_stmt* stmt, names_and_values values);
    void open_transaction();
    void close_transaction();
    bool has_type_index(TypeIndex type);
    void set_has_type_index(TypeIndex type);
    void truncate(string table_name);

    void prepare_all_statements();
    void truncate_tables();

    std::string format_ptr(void const* ptr) const;
    char const* format_str(char const* ptr) const;

    void cycle_transaction();

public:
    virtual void open(string program_name);
    virtual void close();
    virtual void register_type_index(TypeIndex type);
    virtual void new_Expr(void const* addr, TypeIndex type, void const* value_ptr);
    virtual void new_IoTag(void const* addr, std::string name);
    virtual void new_IoObject(void const* addr, void const* proto, char const* proto_name, void const* io_tag);
    virtual void update_IoObject_data(void const* addr, void const* data);
    virtual void new_IoMessage(void const* addr);
    virtual void update_IoMessage_name(void const* addr, char const* name);
    virtual void update_IoMessage_label(void const* addr, char const* label);
    virtual void update_IoMessage_line(void const* addr, int line);
    virtual void update_IoMessage_character(void const* addr, int character);
    virtual void new_IoCall(void const* addr);
    virtual void update_IoCall_message(void const* addr, void const* message);
    virtual void IoStack_push_object(void const* object);
    virtual void IoStack_set_mark(size_t mark);
    virtual void IoStack_pop_mark(size_t mark);
    virtual void delete_Expr(void const* addr);
    virtual void delete_IoObject(void const* addr);
    virtual void delete_IoMessage(void const* addr);
    virtual void delete_IoCall(void const* addr);
    virtual void delete_IoTag(void const* addr);
    TraceDbImpl();
} instance;

LIKEMAGIC_API TraceDb* trace_db = &instance;

}

using namespace LM;

TraceDbImpl::TraceDbImpl()
    : db(nullptr), sequence(0)
{
}

void TraceDbImpl::cycle_transaction()
{
    int const ops_per_transaction = 500;
    if (sequence % ops_per_transaction == 0)
    {
        char * sErrMsg = 0;
        sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &sErrMsg);
        sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &sErrMsg);
    }
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

    sqlite3_extended_result_codes(db, 1);
    truncate_tables();
    prepare_all_statements();

    char * sErrMsg = 0;
    sqlite3_exec(db, "PRAGMA synchronous = OFF", NULL, NULL, &sErrMsg);

    run_void(insert_session, {{"Program", program_name}});
    ++sequence = sqlite3_last_insert_rowid(db);
}

void TraceDbImpl::truncate_tables()
{
    truncate("LMTypeIndex");
    truncate("LMExpr");
    truncate("IoObject");
    truncate("IoCall");
    truncate("IoMessage");
    truncate("IoStack");
    truncate("IoTag");
}

void TraceDbImpl::prepare_all_statements()
{
    insert_session = prepare_insert("Session", { "Program" });

    insert_type_index = prepare_insert("LMTypeIndex",
    {
        "Id", "Description"
    });

    insert_expr = prepare_insert("LMExpr",
    {
        "Sequence", "Address", "TypeIndex", "ValuePtr"
    });

    insert_io_tag = prepare_insert("IoTag",
    {
        "Sequence", "Address", "Name"
    });

    insert_io_object = prepare_insert("IoObject",
    {
        "Sequence", "Address", "IoTag", "Proto", "ProtoName"
    });

    update_io_object_data = prepare_update_last_address("IoObject",
    {
        "Data"
    });

    insert_io_message = prepare_insert("IoMessage",
    {
        "Sequence", "Address"
    });

    update_io_message_name = prepare_update_last_address("IoMessage",
    {
        "Name"
    });

    update_io_message_label = prepare_update_last_address("IoMessage",
    {
        "Label"
    });

    update_io_message_line = prepare_update_last_address("IoMessage",
    {
        "LineNumber"
    });

    update_io_message_character = prepare_update_last_address("IoMessage",
    {
        "CharacterNumber"
    });

    insert_io_call = prepare_insert("IoCall",
    {
        "Sequence", "Address"
    });

    update_io_call_message = prepare_update_last_address("IoCall",
    {
        "Message"
    });

    insert_io_stack_object = prepare_insert("IoStack",
    {
        "Sequence", "PushObject"
    });

    insert_io_stack_mark = prepare_insert("IoStack",
    {
        "Sequence", "SetMark"
    });

    insert_io_stack_pop_mark = prepare_insert("IoStack",
    {
        "Sequence", "PopMark"
    });

    update_expr_when_freed = prepare_update_last_address("LMExpr",
    {
        "WhenFreed"
    });

    update_io_object_when_freed = prepare_update_last_address("IoObject",
    {
        "WhenFreed"
    });

    update_io_message_when_freed = prepare_update_last_address("IoMessage",
    {
        "WhenFreed"
    });

    update_io_call_when_freed = prepare_update_last_address("IoCall",
    {
        "WhenFreed"
    });
}

string TraceDbImpl::format_ptr(void const* value) const
{
    stringstream valueSS;
    valueSS <<  value;
    return valueSS.str();
}

char const* TraceDbImpl::format_str(char const* value) const
{
    if (value == nullptr)
        return "NULL";
    else
        return value;
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

void TraceDbImpl::bind(sqlite3_stmt* stmt, names_and_values values)
{
    for (auto kv : values)
    {
        string name = string() + "@" + kv.first;
        int index = sqlite3_bind_parameter_index(stmt, name.c_str());
        bind(stmt, index, kv.second);
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


void TraceDbImpl::write_column_list(ostream& os, names_and_sql_code columns)
{
    for (int i = 0; i < (int)columns.size(); ++i)
    {
        if (i > 0)
            os << ",";

        os << columns[i].first;
    }
}


void TraceDbImpl::write_value_list(ostream& os, names_and_sql_code values)
{
    for (int i = 0; i < (int)values.size(); ++i)
    {
        if (i > 0)
            os << ",";

        os << values[i].second;
    }
}

void TraceDbImpl::truncate(string table_name)
{
    stringstream ss;
    ss << "delete from ";
    ss << table_name;

    string sql = ss.str();

    // debug print
    cout << sql << endl;

    sqlite3_stmt* stmt = prepare(sql.c_str(), sql.length());
    run_void(stmt, {});
    sqlite3_finalize(stmt);
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

sqlite3_stmt* TraceDbImpl::prepare_custom_insert(string table_name, names_and_sql_code columns)
{
    stringstream ss;
    ss << "insert into ";
    ss << table_name;
    ss << "(";
    write_column_list(ss, columns);
    ss << ") values (";
    write_value_list(ss, columns);
    ss << ")";

    string sql = ss.str();

    // debug print
    cout << sql << endl;

    return prepare(sql.c_str(), sql.length());
}

sqlite3_stmt* TraceDbImpl::prepare_update_last_address(string table_name,
    vector<string> columns)
{
    stringstream ss;
    ss << "update ";
    ss << table_name;
    ss << " set ";
    write_column_equals_list(ss, columns, ",");
    ss << " where Sequence = (select max(Sequence) from ";
    ss << table_name;
    ss << " where Address = @Address)";

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

void TraceDbImpl::run_void(sqlite3_stmt* stmt, names_and_values values)
{
    cycle_transaction();

    sqlite3_reset(stmt);

    bind(stmt, values);

    int busy_counter = 100000L;

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
        case SQLITE_BUSY:
            if (busy_counter--)
                continue;
            else
                throw DbException(); // Unexpected return code
        default:
            throw DbException(); // Unexpected return code
        }
    }
}

void TraceDbImpl::close()
{
    char * sErrMsg = 0;
    sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &sErrMsg);
    sqlite3_close(db);
}

void TraceDbImpl::register_type_index(TypeIndex type)
{
    if (!has_type_index(type))
    {
        run_void(insert_type_index,
        {
            {"Id", (int)type.get_id()},
            {"Description", type.description()}
        });
        set_has_type_index(type);
    }
}

void TraceDbImpl::new_Expr(void const* addr, TypeIndex type, void const* value_ptr)
{
    register_type_index(type);

    run_void(insert_expr,
    {
        {"Sequence", ++sequence},
        {"Address", format_ptr(addr)},
        {"TypeIndex", (int)type.get_id()},
        {"ValuePtr", format_ptr(value_ptr)}
    });
}

void TraceDbImpl::new_IoTag(void const* addr, std::string name)
{
    run_void(insert_io_tag,
    {
        {"Sequence", ++sequence},
        {"Address", format_ptr(addr)},
        {"Name", name}
    });
}

void TraceDbImpl::new_IoObject(void const* addr, void const* proto, char const* proto_name, void const* io_tag)
{
    run_void(insert_io_object,
    {
        {"Sequence", ++sequence},
        {"Address", format_ptr(addr)},
        {"IoTag", format_ptr(io_tag)},
        {"Proto", format_ptr(proto)},
        {"ProtoName", format_str(proto_name)}
    });
}

void TraceDbImpl::update_IoObject_data(void const* addr, void const* data)
{
    run_void(update_io_object_data,
    {
        {"Address", format_ptr(addr)},
        {"Data", format_ptr(data)}
    });
}

void TraceDbImpl::new_IoMessage(void const* addr)
{
    run_void(insert_io_message,
    {
        {"Sequence", ++sequence},
        {"Address", format_ptr(addr)}
    });
}

void TraceDbImpl::update_IoMessage_name(void const* addr, char const* name)
{
    run_void(update_io_message_name,
    {
        {"Address", format_ptr(addr)},
        {"Name", format_str(name)}
    });
}

void TraceDbImpl::update_IoMessage_label(void const* addr, char const* label)
{
    run_void(update_io_message_label,
    {
        {"Address", format_ptr(addr)},
        {"Label", format_str(label)}
    });
}

void TraceDbImpl::update_IoMessage_line(void const* addr, int line)
{
    run_void(update_io_message_line,
    {
        {"Address", format_ptr(addr)},
        {"LineNumber", line}
    });
}

void TraceDbImpl::update_IoMessage_character(void const* addr, int character)
{
    run_void(update_io_message_character,
    {
        {"Address", format_ptr(addr)},
        {"CharacterNumber", character}
    });
}

void TraceDbImpl::new_IoCall(void const* addr)
{
    run_void(insert_io_call,
    {
        {"Sequence", ++sequence},
        {"Address", format_ptr(addr)}
    });
}

void TraceDbImpl::update_IoCall_message(void const* addr, void const* message)
{
    run_void(update_io_call_message,
    {
        {"Address", format_ptr(addr)},
        {"Message", format_ptr(message)}
    });
}

void TraceDbImpl::IoStack_push_object(void const* object)
{
    run_void(insert_io_stack_object,
    {
        {"Sequence", ++sequence},
        {"PushObject", format_ptr(object)}
    });
}

void TraceDbImpl::IoStack_set_mark(size_t mark)
{
    run_void(insert_io_stack_mark,
    {
        {"Sequence", ++sequence},
        {"SetMark", (sqlite_int64)mark}
    });
}

void TraceDbImpl::IoStack_pop_mark(size_t mark)
{
    run_void(insert_io_stack_pop_mark,
    {
        {"Sequence", ++sequence},
        {"PopMark", (sqlite_int64)mark}
    });
}

void TraceDbImpl::delete_Expr(void const* addr)
{
    run_void(update_expr_when_freed,
    {
        {"Address", format_ptr(addr)},
        {"WhenFreed", ++sequence}
    });
}

void TraceDbImpl::delete_IoTag(void const* addr)
{
    run_void(update_io_tag_when_freed,
    {
        {"Address", format_ptr(addr)},
        {"WhenFreed", ++sequence}
    });
}

void TraceDbImpl::delete_IoObject(void const* addr)
{
    run_void(update_io_object_when_freed,
    {
        {"Address", format_ptr(addr)},
        {"WhenFreed", ++sequence}
    });
}

void TraceDbImpl::delete_IoMessage(void const* addr)
{
    run_void(update_io_message_when_freed,
    {
        {"Address", format_ptr(addr)},
        {"WhenFreed", ++sequence}
    });
}

void TraceDbImpl::delete_IoCall(void const* addr)
{
    run_void(update_io_call_when_freed,
    {
        {"Address", format_ptr(addr)},
        {"WhenFreed", ++sequence}
    });
}


