#ifndef __OBOTCHA_HTTP_CONTENT_DISPOSITION_HPP__
#define __OBOTCHA_HTTP_CONTENT_DISPOSITION_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

//https://m.php.cn/manual/view/35599.html

namespace obotcha {

DECLARE_CLASS(HttpContentDisposition) {

public:
    _HttpContentDisposition();
    _HttpContentDisposition(String);

    void import(String);

    String toString();
    
    String type;
    String filename;
    String name;
};

}
#endif
