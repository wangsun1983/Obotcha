#ifndef __OBOTCHA_HTTP_HEADER_VARY_HPP__
#define __OBOTCHA_HTTP_HEADER_VARY_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderVary) {

public:
    _HttpHeaderVary() = default;
    explicit _HttpHeaderVary(String);

    void load(String);
    
    ArrayList<String> get() const;
    void set(ArrayList<String>);
    void add(String);

    String toString();

private:
    ArrayList<String> varies = createArrayList<String>();
};

}
#endif
