#ifndef __OBOTCHA_HTTP_ACCEPT_LANGUAGE_HPP__
#define __OBOTCHA_HTTP_ACCEPT_LANGUAGE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpAcceptLanguageItem) {
public:
    _HttpAcceptLanguageItem(String,float w = 1.0);
    String lang;
    float weight;
};

DECLARE_CLASS(HttpAcceptLanguage) {

public:
    _HttpAcceptLanguage();
    _HttpAcceptLanguage(String);

    void import(String);

    ArrayList<HttpAcceptLanguageItem> get();
    void add(String,float w = 1.0);

    String toString();

private:
    ArrayList<HttpAcceptLanguageItem> languages;
};

}
#endif
