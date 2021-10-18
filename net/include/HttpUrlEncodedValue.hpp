#ifndef __OBOTCHA_HTTP_URL_ENCODED_VALUE_HPP__
#define __OBOTCHA_HTTP_URL_ENCODED_VALUE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "KeyValuePair.hpp"

namespace obotcha {

DECLARE_CLASS(HttpUrlEncodedValue) {

public:
    _HttpUrlEncodedValue();
    _HttpUrlEncodedValue(String);

    void import(String);

    ArrayList<KeyValuePair<String,String>> getValues();

    void set(String,String);

    String toString();

private:
    ArrayList<KeyValuePair<String,String>> encodedValues;
};

}
#endif
