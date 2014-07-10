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
#include "InterfaceGenerator/NamespaceGen.hpp"
#include "InterfaceGenerator/NamespaceGenList.hpp"

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
    ClassGenList classes;
    NamespaceGenList namespaces;

    std::string generate_return_type(TypeIndex type);
    std::string generate_arg_type(TypeIndex type);
    std::string generate_arg_name(TypeInfoList types, int index);

    void write_foward_declares(ostream& os, NamespaceGen const* ns, std::set<ClassGen const*> forward_types, int depth);

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

void Generator::generate_all(ostream& os)
{
    if (type_system == nullptr)
        throw std::logic_error("type_system pointer not set");

    TypeMirror& global_ns_mirror = type_system->global_namespace();
    TypeIndex global_ns_type = global_ns_mirror.get_class_type();
    NamespaceGen* global_ns = new TypeMirrorNamespaceGen(&global_ns_mirror, classes);
    namespaces.add_namespace(global_ns_type, global_ns);
    namespaces.set_root(global_ns);

    std::unordered_map<TypeIndex, TypeIndex> parent_ns_types;

    for (auto t : type_system->list_class_types())
    {
        TypeMirror* type = type_system->get_class(t);

        if (!(t == global_ns_type))
        {
            parent_ns_types[t] = type->parent_namespace();
            if (t.get_info().system == "namespace")
            {
                namespaces.add_namespace(t, new TypeMirrorNamespaceGen(type, classes));
            }
            else
            {
                classes.add_class(t, new TypeMirrorClassGen(type, classes));
            }
        }
    }

    TypeIndex bottom_ptr_type = create_bottom_ptr_type_index();
    parent_ns_types[bottom_ptr_type] = global_ns_type;
    auto bottom_ptr_class = new CustomClassGen("BottomPtr", bottom_ptr_type, {}, classes);
    classes.add_class(bottom_ptr_type, bottom_ptr_class);

    TypeIndex lang_block_type = TypId<std::shared_ptr<LangBlock>>::liberal();
    parent_ns_types[lang_block_type] = global_ns_type;
    auto lang_block_class = new CustomClassGen("LangBlockExpr", lang_block_type, {}, classes);
    classes.add_class(lang_block_type, lang_block_class);

    for (auto class_ : classes.get_all_classes())
    {
        TypeIndex parent = parent_ns_types[class_->get_type()];
        namespaces.add_class(parent, class_);
    }

    for (auto namespace_ : namespaces.get_all_namespaces())
    {
        if (!(namespace_ == global_ns))
        {
            TypeIndex parent = parent_ns_types[namespace_->get_type()];
            namespaces.add_child_namespace(parent, namespace_);
        }
    }

    NamespaceGen const* ns_root = namespaces.get_namespace(global_ns_type);
    ns_root->dump(cout, 0);

    write_foward_declares(cout, ns_root, classes.get_all_classes(), 0);
/*
    for (auto class_ : classes.get_all_classes())
    {
        try
        {
            os << class_->get_name() << " ";
            ofstream header(class_->get_name() + ".hpp");
            for (auto ref_class : class_->get_referenced_classes())
                ref_class->forward_declare(header);
            header << endl;
            class_->declare(header);
            ofstream source(class_->get_name() + ".cpp");
            class_->define(source);
        }
        catch (std::exception const& e)
        {
            cerr << endl << e.what() << endl;
        }
    }
*/
}

void Generator::write_foward_declares(ostream& os, NamespaceGen const* ns, std::set<ClassGen const*> forward_types, int depth)
{
    if (ns->has_descendant_class(forward_types))
    {
        ns->open(os, depth);

        for (auto child_ns : ns->get_child_namespaces())
            write_foward_declares(os, child_ns, forward_types, depth+1);

        for (auto class_ : ns->get_child_classes())
        {
            if (forward_types.find(class_) != forward_types.end())
                class_->forward_declare(os, depth+1);
        }

        ns->close(os, depth);
        os << endl;
    }
}
