#ifndef __OBOTCHA_HTTP_SESSION_HPP__
#define __OBOTCHA_HTTP_SESSION_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HashMap.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpSession) {

public:
    _HttpSession();
    String get(String);
    void set(String,String);
    String operator[] (String key) {
        return data->get(key);
    }
private:
    HashMap<String,String> data;
};

}
#endif
