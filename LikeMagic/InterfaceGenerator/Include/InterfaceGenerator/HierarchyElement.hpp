#include <set>

namespace LM {

class HierarchyElement
{
private:
    std::set<HierarchyElement*> child_elements;

public:
    virtual ~HierarchyElement();

    virtual void open_for_declare(std::ostream& os) const = 0;
    virtual void declare(std::ostream& os) const = 0;
    virtual void close_for_declare(std::ostream& os) const = 0;

    virtual void open_for_forward_declare(std::ostream& os) const = 0;
    virtual void forward_declare(std::ostream& os) const = 0;
    virtual void close_for_forward_declare(std::ostream& os) const = 0;

    virtual void open_for_define(std::ostream& os) const = 0;
    virtual void define(std::ostream& os) const = 0;
    virtual void close_for_define(std::ostream& os) const = 0;

    virtual std::set<HierarchyElement*> get_needed_forward_declares() const = 0;

    virtual std::set<HierarchyElement*> get_child_elements() const;
    virtual void add_child_element(HierarchyElement* child) const;
};

}
