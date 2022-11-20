#ifndef __OBOTCHA_HTTP_URL_ENCODED_VALUE_HPP__
#define __OBOTCHA_HTTP_URL_ENCODED_VALUE_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "HashMap.hpp"

namespace obotcha {

DECLARE_CLASS(HttpUrlEncodedValue) {

public:
    _HttpUrlEncodedValue();
    _HttpUrlEncodedValue(String);

    void import(String);

    HashMap<String,String> getValues();

    void set(String,String);
    String get(String);

    String toString();

private:
    HashMap<String,String> encodedValues;
};

}
#endif
