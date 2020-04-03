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
#include <bitset>
#include <math.h>

#include "Integer.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "String.hpp"
#include "IllegalArgumentException.hpp"

namespace obotcha {

_Integer::_Integer(int v) : val(v) {

}

_Integer::_Integer(Integer &v) {
    if(v == nullptr) {
        throw InitializeException("Object is null");
    }

    val = v->toValue();
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

void _Integer::update(sp<_Integer> v) {
    if(v == nullptr) {
        throw IllegalArgumentException("integer update null");
    }

    val = v->val;
}

sp<_String> _Integer::toHexString() {
    return toHexString(val);
}

sp<_String> _Integer::toHexString(int i) {
    std::stringstream ss;
    ss<<std::hex<<i;

    std::string str;
    ss>>str;
    return createString(str);
}

sp<_String> _Integer::toOctalString() {
    return toOctalString(val);
}

sp<_String> _Integer::toOctalString(int i) {
    std::stringstream ss;
    ss<<std::oct<<i;
    std::string str;
    ss>>str;
    return createString(str);
}

sp<_String> _Integer::toBinaryString() {
    return toBinaryString(val);
}

sp<_String> _Integer::toBinaryString(int i) {
    std::stringstream ss;
    binaryRecursion(i,ss);
    std::string str;
    ss>>str;
    return createString(str);
}

sp<_String> _Integer::toString() {
    return toString(val);
}

sp<_String> _Integer::toString(int i) {
    std::stringstream ss;
    ss<<i;
    return createString(ss.str());
}

int _Integer::parseDecInt(sp<_String> v) {
    if(v == nullptr) {
        throw NullPointerException("Integer parserInt nullptr");
    }

    std::stringstream ss;
    ss<<v->getStdString();
    int value;
    ss>>value;

    return value;
}

int _Integer::parseHexInt(sp<_String> v) {
    if(v == nullptr) {
        throw IllegalArgumentException("parseHexInt nullptr");
    }
    std::stringstream ss;
    ss<< std::hex <<v->getStdString();
    int value;
    ss>>value;

    return value;
}

int _Integer::parseOctInt(sp<_String> v) {
    if(v == nullptr) {
        throw IllegalArgumentException("parseHexInt nullptr");
    }
    std::stringstream ss;
    ss<< std::oct <<v->getStdString();
    int value;
    ss>>value;

    return value;
}

int _Integer::parseBinaryInt(sp<_String> v) {
    if(v == nullptr) {
        throw IllegalArgumentException("parseHexInt nullptr");
    }

    int lastIndex = v->size() - 1;
    const char *str = v->toChars();

    int parseBinary = 0;
    for (int i = lastIndex; i >= 0; --i) {
        if (str[i] == '1') {
            parseBinary += pow(2.0, lastIndex - i);
        }
    }
    printf("parseBinaryInt v is %s,value is %d \n",v->toChars(),parseBinary);
    return parseBinary;
}

void _Integer::binaryRecursion(int n,std::stringstream &ss) {
    int a;
    a = n%2;
    n = n>>1;
    if (n==0) {
        //donothing
    } else {
        binaryRecursion(n,ss);
    }
    ss<<a;
}

_Integer::~_Integer() {
}

}