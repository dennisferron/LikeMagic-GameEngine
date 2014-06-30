

namespace LM {

class HierarchyGen
{
public:
    virtual ~HierarchyGen();
    virtual void declare(std::ostream& os) const = 0;
    virtual void define(std::ostream& os) const = 0;
    virtual void forward_declare(std::ostream& os) const = 0;
    virtual void write_name(std::ostream& os) const = 0;
    virtual void write_class_name(std::ostream& os) const = 0;
    virtual std::unordered_set<TypeIndex> get_referenced_types() const = 0;
    virtual std::unordered_set<ClassGen const*> get_referenced_classes() const = 0;
    virtual std::string get_name() const = 0;
};

}
