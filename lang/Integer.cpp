/**
 * @file Integer.cpp
 * @brief this class used for int
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include <stdio.h>
#include <memory.h>
#include <sstream>

#include "Integer.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "String.hpp"

namespace obotcha {

const static char digits[] = {
        '0' , '1' , '2' , '3' , '4' , '5' ,
        '6' , '7' , '8' , '9' , 'a' , 'b' ,
        'c' , 'd' , 'e' , 'f' , 'g' , 'h' ,
        'i' , 'j' , 'k' , 'l' , 'm' , 'n' ,
        'o' , 'p' , 'q' , 'r' , 's' , 't' ,
        'u' , 'v' , 'w' , 'x' , 'y' , 'z'
};    

_Integer::_Integer(int v) : val(v) {

}

_Integer::_Integer(Integer &v) {
    if(v == nullptr) {
        throw createInitializeException("Object is null");
    }

    val = 0;
}

int _Integer::toValue() {
    return val;
}

bool _Integer::equals(Integer &p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

bool _Integer::equals(int p) {
    return val == p;
}

bool _Integer::equals(const _Integer *p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

void _Integer::update(int v) {
    val = v;
}

String _Integer::toString(int i, int radix) {
    if (radix == 10) {
        return toString(i);
    }

    char buf[33];
    memset(buf,0,33);
    bool negative = (i < 0);
    int charPos = 32;

    if (!negative) {
        i = -i;
    }

    while (i <= -radix) {
        buf[charPos--] = digits[-(i % radix)];
        i = i / radix;
    }
    buf[charPos] = digits[-i];

    if (negative) {
        buf[--charPos] = '-';
    }

    return createString(buf);
}

sp<_String> _Integer::toHexString() {
    return toString(val,16);
}

sp<_String> _Integer::toHexString(int i) {
    return toString(i,16);
}

sp<_String> _Integer::toOctalString() {
    return toString(val);
}

sp<_String> _Integer::toOctalString(int i) {
    return toString(i);
}

sp<_String> _Integer::toBinaryString() {
    return toString(val,2);
}

sp<_String> _Integer::toBinaryString(int i) {
    return toString(i,2);
}

sp<_String> _Integer::toString() {
    return toString(val);
}

sp<_String> _Integer::toString(int i) {
    std::stringstream ss;
    ss<<i;
    return createString(ss.str());
}

int _Integer::parseInt(sp<_String> v) {
    if(v == nullptr) {
        throw createNullPointerException("Integer parserInt nullptr");
    }

    std::stringstream ss;
    ss<<v->getStdString();
    int value;
    ss>>value;

    return value;
}

_Integer::~_Integer() {
}

}