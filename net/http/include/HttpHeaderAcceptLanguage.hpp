#ifndef __OBOTCHA_HTTP_HEADER_ACCEPT_LANGUAGE_HPP__
#define __OBOTCHA_HTTP_HEADER_ACCEPT_LANGUAGE_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAcceptLanguageItem) {
public:
    _HttpHeaderAcceptLanguageItem(String,float w = 1.0);
    String lang;
    float weight;
};

DECLARE_CLASS(HttpHeaderAcceptLanguage) {

public:
    _HttpHeaderAcceptLanguage() = default;
    explicit _HttpHeaderAcceptLanguage(String);

    void load(String);
    ArrayList<HttpHeaderAcceptLanguageItem> get();
    void add(String,float w = 1.0);
    String toString() override;

private:
    ArrayList<HttpHeaderAcceptLanguageItem> languages = ArrayList<HttpHeaderAcceptLanguageItem>::New();
};

}
#endif
