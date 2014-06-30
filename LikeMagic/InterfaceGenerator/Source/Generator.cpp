#include "InterfaceGenerator/Generator.hpp"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Mirrors/TypeMirror.hpp"
#include "LikeMagic/Mirrors/CallTarget.hpp"

#include "LikeMagic/Utility/TypeIndex.hpp"

#include "InterfaceGenerator/ClassGen.hpp"
#include "InterfaceGenerator/ClassGenList.hpp"
#include "InterfaceGenerator/MethodGen.hpp"
#include "InterfaceGenerator/RetGen.hpp"
#include "InterfaceGenerator/ArgGen.hpp"

#include <ostream>
#include <sstream>
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

namespace LM {
    class LangBlock;
}
using namespace LM;


namespace LM {
class Generator
{
private:
    void print_class(TypeMirror& type, ostream& os);
    void print_method(std::string name, CallTarget& method, ostream& os);
    std::string generate_return_type(TypeIndex type);
    std::string generate_arg_type(TypeIndex type);
    std::string generate_arg_name(TypeInfoList types, int index);
public:
    void generate_all(std::ostream& os);
};

LIKEMAGIC_API void generate_interface_classes()
{
    Generator g;
    g.generate_all(cout);
}

}

using namespace LM;

std::string Generator::generate_return_type(TypeIndex type)
{
    return "std::shared_ptr<" + type.get_info().name + ">";
}

std::string Generator::generate_arg_type(TypeIndex type)
{
    return type.get_info().name;
}

std::string Generator::generate_arg_name(TypeInfoList types, int index)
{
    stringstream ss;
    ss << "arg";
    ss << index;
    return ss.str();
}

void Generator::print_class(TypeMirror& type, ostream& os)
{
    string name = type.get_class_name();
    os << name << endl;

    std::vector<std::pair<std::string, CallTarget*>> methods = type.get_all_methods();
    for (auto kv : methods)
    {
        print_method(kv.first, *kv.second, os);
    }
}

void Generator::print_method(std::string name, CallTarget& method, ostream& os)
{
    os << "    auto ";
    os << name;
    os << "(";

    TypeInfoList arg_types = method.get_arg_types();
    for (size_t i = 0; i < arg_types.size(); ++i)
    {
        if (i > 0)
            os << ", ";

        os << generate_arg_type(arg_types[i]);
        os << " ";
        os << generate_arg_name(arg_types, i);
    }

    os << ") -> ";
    TypeIndex rtype = method.get_return_type();
    os << generate_return_type(rtype);
    //os << ";" << endl;
    os << endl;
    os << "    "  << "{" << endl;

    os << "    " << "    ";

    if (rtype.get_id() != TypId<void>::liberal().get_id())
        os << "return call_retv";
    else
        os << "call_void";

    os << "(\"" << name << "\"";
    if (arg_types.size() > 0)
    {
        os << ", ";
        os << "{";
        for (size_t i = 0; i < arg_types.size(); ++i)
        {
            if (i > 0)
                os << ", ";
            os << generate_arg_name(arg_types, i);
        }
        os << endl;
        os << "}";
    }
    os << ");" << endl;

    os << "    " << "}" << endl;
}

void Generator::generate_all(ostream& os)
{
    if (type_system == nullptr)
        throw std::logic_error("type_system pointer not set");

    ClassGenList classes;

    for (auto t : type_system->list_class_types())
    {
        RefType ref_type = t.get_info().ref_type;
        if (ref_type == RefType::Metaclass)
            cout << "Skipping " << t.description() << endl;
        else
        {
            TypeMirror* type = type_system->get_class(t);
            classes.add_class(t, new TypeMirrorClassGen(type, classes));
        }
    }

    auto bottom_ptr_class = new CustomClassGen("BottomPtr", {}, classes);
    classes.add_class(create_bottom_ptr_type_index(), bottom_ptr_class);

    auto lang_block_class = new CustomClassGen("LangBlockExpr", {}, classes);
    classes.add_class(TypId<std::shared_ptr<LangBlock>>::liberal(), lang_block_class);

    for (auto t : type_system->list_class_types())
    {
        try
        {
            auto _class = classes.get_class(t);
            os << _class->get_name() << " ";
            ofstream header(_class->get_name() + ".hpp");
            for (auto ref_class : _class->get_referenced_classes())
                ref_class->forward_declare(header);
            header << endl;
            _class->declare(header);
            ofstream source(_class->get_name() + ".cpp");
            _class->define(source);
        }
        catch (std::exception const& e)
        {
            cerr << endl << e.what() << endl;
        }
    }
}
