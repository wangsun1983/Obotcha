#ifndef __OBOTCHA_HTTP_CONTENT_LANGUAGE_HPP__
#define __OBOTCHA_HTTP_CONTENT_LANGUAGE_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderContentLanguage) {

public:
    _HttpHeaderContentLanguage() = default;
    explicit _HttpHeaderContentLanguage(String);

    void load(String);

    ArrayList<String> get();
    void add(String);
    
    String toString() override;

private:
    ArrayList<String> languages = ArrayList<String>::New();
};

}
#endif
