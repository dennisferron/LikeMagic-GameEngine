
#include <iostream>

#include "LikeMagic/Utility/TupleForEach.hpp"

/*
std::string a() { return "a called"; }
std::string b() { return "b called"; }

template <typename F, F f>
struct IoCall
{
    static void doit() { std::cout << "IoCall " << (*f)() << std::endl; };
};

template <typename F, F f>
struct V8Call
{
    void doit() { std::cout << "V8Call " << (*f)() << std::endl; };
};



template<typename F, F f, template<typename F, F f> class... Policies >
struct Test
{
    struct Functor
    {
        template <typename Policy>
        void operator ()(Policy p)
        {
            p.doit();
        }
    };

    static void doit()
    {
        auto policies = std::make_tuple(Policies<F, f>()...);
        Functor action;
        LikeMagic::Utility::tuple_for_each(action, policies);
    }
};

struct Runner
{
    Runner()
    {
        Test<decltype(&a), &a, IoCall, V8Call>::doit();
        Test<decltype(&b), &b, IoCall, V8Call>::doit();
    }
} instance;
*/
