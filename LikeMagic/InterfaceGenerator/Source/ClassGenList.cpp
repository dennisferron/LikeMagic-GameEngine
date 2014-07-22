#include "InterfaceGenerator/ClassGenList.hpp"
#include "InterfaceGenerator/ClassGen.hpp"
#include "InterfaceGenerator/MethodGen.hpp"
#include "InterfaceGenerator/ArgGen.hpp"
#include "InterfaceGenerator/RetGen.hpp"

using namespace LM;

ClassGenList::~ClassGenList()
{
    for (auto i : classes)
    {
        delete i.second;
    }
}

TypeIndex ClassGenList::get_class_type(TypeIndex index) const
{
    return get_index(index.get_info().class_type());
}

ClassGen* ClassGenList::get_class(TypeIndex index) const
{
    TypeIndex class_type = get_class_type(index);
    auto result = classes.find(class_type);
    if (result == classes.end())
    {
        std::cerr << "No ClassGen for type " + index.description() << " " << index.get_id() << std::endl;
        throw std::logic_error("No ClassGen for type " + index.description());
    }
    return result->second;
}

void ClassGenList::add_class(TypeIndex index, ClassGen* class_gen)
{
    TypeIndex class_type = get_class_type(index);
    auto result = classes.find(class_type);
    if (result != classes.end() && result->second != class_gen)
    {
        throw std::logic_error("Different ClassGen already registered for type " + index.description());
    }
    else
    {
        classes[class_type] = class_gen;
    }
}

bool ClassGenList::has_class(TypeIndex index) const
{
    TypeIndex class_type = get_class_type(index);
    auto result = classes.find(class_type);
    return result != classes.end();
}

std::set<ClassGen*> ClassGenList::get_all_classes() const
{
    std::set<ClassGen*> result;
    for (auto i : classes)
    {
        result.insert(i.second);
    }
    return result;
}


///// Example of return-by-value with forward declared classes.
///// Works because the methods are not used or defined until afterwards.

class BB;
class AA
{
public:
    BB get_b() const;
    void set_b(BB b);
};

class AA;
class BB
{
public:
    auto get_a() -> AA const;
    void set_a(AA a);
};

BB AA::get_b() const
{
    throw 0;
}

void AA::set_b(BB b)
{
    throw 0;
}

auto BB::get_a() -> AA const
{
    throw 0;
}

void BB::set_a(AA a)
{
    throw 0;
}

void testit()
{
    AA a;
    BB b;
    a.set_b(b);
    b.set_a(a);
    a = b.get_a();
    b = a.get_b();
}
