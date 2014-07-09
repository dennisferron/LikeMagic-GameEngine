
#pragma once

#include "LikeMagic/Utility/TypeIndex.hpp"

#include <vector>
#include <memory>
#include <unordered_set>

namespace LM {

class TypeMirror;
class MethodGen;
class ClassGenList;

class ClassGen
{
public:
    virtual ~ClassGen();
    virtual void declare(std::ostream& os) const = 0;
    virtual void define(std::ostream& os) const = 0;
    virtual void forward_declare(std::ostream& os) const = 0;
    virtual void write_name(std::ostream& os) const = 0;
    virtual void write_class_name(std::ostream& os) const = 0;
    virtual std::unordered_set<TypeIndex> get_referenced_types() const = 0;
    virtual std::unordered_set<ClassGen const*> get_referenced_classes() const = 0;
    virtual std::string get_name() const = 0;
    virtual TypeIndex get_type() const = 0;
};

class TypeMirrorClassGen : public ClassGen
{
private:
    TypeMirror* type_mirror;
    ClassGenList const& classes;
    std::vector<std::unique_ptr<MethodGen>> methods;

public:
    TypeMirrorClassGen(TypeMirror* type_mirror_, ClassGenList const& classes_);
    virtual void declare(std::ostream& os) const;
    virtual void define(std::ostream& os) const;
    virtual void forward_declare(std::ostream& os) const;
    virtual void write_name(std::ostream& os) const;
    virtual void write_class_name(std::ostream& os) const;
    virtual std::unordered_set<TypeIndex> get_referenced_types() const;
    virtual std::unordered_set<ClassGen const*> get_referenced_classes() const;
    virtual std::string get_name() const;
    virtual TypeIndex get_type() const;
};

class CustomClassGen : public ClassGen
{
private:
    std::string name;
    TypeIndex type;
    std::vector<std::unique_ptr<MethodGen>> methods;
    ClassGenList const& classes;

public:
    CustomClassGen(std::string name_, TypeIndex type_, std::vector<MethodGen*> methods_, ClassGenList const& classes_);
    virtual void declare(std::ostream& os) const;
    virtual void define(std::ostream& os) const;
    virtual void forward_declare(std::ostream& os) const;
    virtual void write_name(std::ostream& os) const;
    virtual void write_class_name(std::ostream& os) const;
    virtual std::unordered_set<TypeIndex> get_referenced_types() const;
    virtual std::unordered_set<ClassGen const*> get_referenced_classes() const;
    virtual std::string get_name() const;
    virtual TypeIndex get_type() const;
};

}
