#ifndef __OBOTCHA_HTTP_HEADER_VARY_HPP__
#define __OBOTCHA_HTTP_HEADER_VARY_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderVary) {

public:
    _HttpHeaderVary();
    _HttpHeaderVary(String);

    void import(String);
    
    ArrayList<String> get();
    void set(ArrayList<String>);
    void add(String);

    String toString();

private:
    ArrayList<String> varies;
};

}
#endif
