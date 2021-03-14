#ifndef __OBOTCHA_HTTP_XFORM_URL_ENCODED_PARSER_HPP__
#define __OBOTCHA_HTTP_XFORM_URL_ENCODED_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "KeyValuePair.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpXFormUrlEncodedParser) {
public:
    static ArrayList<KeyValuePair<String,String>> parse(String);
};

}
#endif
