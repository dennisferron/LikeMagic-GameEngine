#pragma once

#include "Exception.hpp"
#include "boost/variant.hpp"

#include <iostream>

namespace IoDbg {

struct GdbBreakpoint
{
    int number;

    bool operator ==(GdbBreakpoint const& that)
    {
        return this->number == that.number;
    }
};

struct IoBreakpoint
{
    int number;
    std::string file_name;
    int line_number;

    bool operator ==(IoBreakpoint const& that)
    {
        return this->number == that.number;
    }
};

struct UserBreakpoint
{
    int number;

    bool operator ==(UserBreakpoint const& that)
    {
        return this->number == that.number;
    }
};

struct OurBreakpoint
{
    int number;

    bool operator ==(OurBreakpoint const& that)
    {
        return this->number == that.number;
    }
};

class BreakpointMap
{
private:
    typedef boost::variant<UserBreakpoint, OurBreakpoint> breakpoint_user;
    typedef boost::variant<GdbBreakpoint, IoBreakpoint> breakpoint_provider;

    struct row_t
    {
        breakpoint_user user_bkpt;
        breakpoint_provider prov_bkpt;
    };

    std::vector<row_t> tbl;

    template <typename Result>
    Result next_user_breakpoint()
    {
        // TODO:  right now this returns max, perhaps it should return first free?
        // (To handle the case of deleting a breakpoint.)

        int max = 0;

        try
        {
            for (row_t row : tbl)
                if (Result* m = boost::get<Result>(&row.user_bkpt))
                    if (m->number > max)
                        max = m->number;
        }
        catch (std::exception const& e)
        {
            std::cerr << "Error getting next_user_breakpoint exception was " << e.what() << std::endl;
            throw;
        }

        return {max+1};
    }

public:

    template <typename Result, typename Source>
    Result get_user_breakpoint(Source t)
    {
        try
        {
            for (row_t row : tbl)
            {
                Source* p = boost::get<Source>(&row.prov_bkpt);
                Result* u = boost::get<Result>(&row.user_bkpt);
                if (p && !u && *p == t)
                    raiseError(LogicError("Wrong provider type for this user breakpoint."));
                else if (p && u && *p == t)
                    return *u;
            }
        }
        catch (std::exception const& e)
        {
            std::cerr << "Error in get_user_breakpoint " << t.number << " exception was " << e.what() << std::endl;
            raiseError(e);
        }

        // If we didn't find an existing user breakpoint, just pull the next available number.
        Result r = next_user_breakpoint<Result>();
        tbl.push_back( { r, t } );
        return r;
    }

    template <typename Result, typename Source>
    bool has_user_breakpoint(Source t)
    {
        try
        {
            for (row_t row : tbl)
            {
                Source* p = boost::get<Source>(&row.prov_bkpt);
                Result* u = boost::get<Result>(&row.user_bkpt);
                if (p && u && *p == t)
                    return true;
            }
        }
        catch (std::exception const& e)
        {
            std::cerr << "Error in has_user_breakpoint " << t.number << " exception was " << e.what() << std::endl;
            raiseError(e);
        }

        return false;
    }

    template <typename Result, typename Source>
    Result get_provider_breakpoint(Source t)
    {
        try
        {
            for (row_t row : tbl)
            {
                Source* u = boost::get<Source>(&row.user_bkpt);
                Result* p = boost::get<Result>(&row.prov_bkpt);
                if (u && !p && *u == t)
                    raiseError(LogicError("Wrong provider type for this user breakpoint number."));
                else if (u && p && *u == t)
                    return *p;
            }
        }
        catch (std::exception const& e)
        {
            std::cerr << "Error in get_provider_breakpoint " << t.number << " exception was " << e.what() << std::endl;
            raiseError(e);
        }

        // If we don't find a provider breakpoint, that's an error.
        raiseError(LogicError("No provider breakpoint for this user breakpoint number."));

        // Never get here
        return { -1 };
    }

};

}
