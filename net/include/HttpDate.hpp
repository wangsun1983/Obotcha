#ifndef __HTTP_DATE_HPP__
#define __HTTP_DATE_HPP__

#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpDate) {

public:
    _HttpHeader();
    
    static String getHeaderString(int header);
    
    void setValue(int,String);
    
    String getValue(int);

    MapIterator<Integer,String> getIterator();

    void addCookie(HttpCookie);

    ArrayList<HttpCookie> getCookies();

    String genHtml();

private:
    static String mHeaderList[];
    HashMap<Integer,String> mValues;

    ArrayList<HttpCookie> mCookies;
};

}
#endif
