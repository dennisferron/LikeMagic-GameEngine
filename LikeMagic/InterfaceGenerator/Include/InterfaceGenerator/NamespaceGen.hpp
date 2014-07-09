

#pragma once

#include "LikeMagic/Utility/TypeIndex.hpp"

#include <vector>
#include <memory>
#include <unordered_set>
#include <set>

namespace LM {

class TypeMirror;
class MethodGen;
class ClassGenList;

class NamespaceGen
{
public:
    virtual ~NamespaceGen();

    virtual std::set<ClassGen const*> get_child_classes() const = 0;

    virtual void add_child(NamespaceGen* child_ns) = 0;
    virtual void add_class(ClassGen const* class_gen) = 0;
    virtual void open(std::ostream& os) const = 0;
    virtual void close(std::ostream& os) const = 0;
    virtual void using_(std::ostream& os) const = 0;
    virtual void has_descendant_class(ClassGen const* class_gen) = 0;
    virtual TypeIndex get_type() const = 0;
};

class TypeMirrorNamespaceGen : public NamespaceGen
{
private:
    virtual ~TypeMirrorNamespaceGen();
    TypeMirror* type_mirror;
    ClassGenList const& classes;
    std::vector<NamespaceGen*> children;
    std::set<ClassGen const*> child_classes;

    void write_name(std::ostream& os) const;
    void write_namespace_name(std::ostream& os) const;
    std::string get_name() const;

public:
    TypeMirrorNamespaceGen(TypeMirror* type_mirror_, ClassGenList const& classes_);
    virtual void add_child(NamespaceGen* child_ns);
    virtual void add_class(ClassGen const* class_gen);
    virtual void open(std::ostream& os) const;
    virtual void close(std::ostream& os) const;
    virtual void using_(std::ostream& os) const;
    virtual void has_descendant_class(ClassGen const* class_gen);
    virtual std::set<ClassGen const*> get_child_classes() const;
    virtual TypeIndex get_type() const;
};

}
