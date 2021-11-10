#ifndef __OBOTCHA_HTTP_CONTENT_LANGUAGE_HPP__
#define __OBOTCHA_HTTP_CONTENT_LANGUAGE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderContentLanguage) {

public:
    _HttpHeaderContentLanguage();
    _HttpHeaderContentLanguage(String);

    void import(String);

    ArrayList<String> get();
    void add(String);
    
    String toString();

private:
    ArrayList<String> languages;
};

}
#endif
