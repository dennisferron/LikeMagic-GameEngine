
// Thanks to user sehe on StackOverflow -
// http://stackoverflow.com/questions/9404189/detecting-the-parameter-types-in-a-spirit-semantic-action/9405265#9405265

#include <cxxabi.h>
#include <stdlib.h>
#include <string>
#include <iostream>

template <typename T> std::string nameofType(const T& v) {
    int     status;
    char   *realname = abi::__cxa_demangle(typeid(v).name(), 0, 0, &status);
    std::string name(realname? realname : "????");
    free(realname);
    return name;
}

struct what_is_the_attr {
    template <typename> struct result { typedef bool type; };

    template <typename T> bool operator()(T& attr) const {
        std::cerr << "what_is_the_attr: " << nameofType(attr) << std::endl;
        return true;
    }
};

/* Example Usage:

template <typename Exp>
    void detect_attr_type(const Exp& exp)
{
    using namespace boost::spirit::qi;

    const char input[] = "1 2 3 4";
    auto f(std::begin(input)), l(std::end(input)-1);

    bool dummy = phrase_parse(
            f, l,
            exp [ what_is_the_attr() ],
            space);
}

*/
