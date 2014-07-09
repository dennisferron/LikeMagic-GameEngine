

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
    virtual void write_name(std::ostream& os) const = 0;
    virtual void write_namespace_name(std::ostream& os) const = 0;
    virtual std::string get_name() const = 0;
    virtual void add_child(NamespaceGen* child_ns) = 0;
    virtual void add_class(ClassGen const* class_gen) = 0;
    virtual void open(std::ostream& os) const = 0;
    virtual void close(std::ostream& os) const = 0;
    virtual void using_(std::ostream& os) const = 0;
    virtual void has_descendant_class(ClassGen const* class_gen) = 0;
    virtual TypeIndex get_type() const = 0;
    virtual std::set<ClassGen const*> get_child_classes() const = 0;
    virtual std::set<NamespaceGen*> get_child_namespaces() const = 0;
    virtual void dump(std::ostream& os, int depth) const;
};

class TypeMirrorNamespaceGen : public NamespaceGen
{
private:
    virtual ~TypeMirrorNamespaceGen();
    TypeMirror* type_mirror;
    ClassGenList const& classes;
    std::set<NamespaceGen*> children;
    std::set<ClassGen const*> child_classes;

public:

    virtual void write_name(std::ostream& os) const;
    virtual void write_namespace_name(std::ostream& os) const;
    virtual std::string get_name() const;

    TypeMirrorNamespaceGen(TypeMirror* type_mirror_, ClassGenList const& classes_);
    virtual void add_child(NamespaceGen* child_ns);
    virtual void add_class(ClassGen const* class_gen);
    virtual void open(std::ostream& os) const;
    virtual void close(std::ostream& os) const;
    virtual void using_(std::ostream& os) const;
    virtual void has_descendant_class(ClassGen const* class_gen);
    virtual std::set<ClassGen const*> get_child_classes() const;
    virtual std::set<NamespaceGen*> get_child_namespaces() const;
    virtual TypeIndex get_type() const;
};

}
