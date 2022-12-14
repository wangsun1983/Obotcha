#ifndef __OBOTCHA_NUMBER_HPP__
#define __OBOTCHA_NUMBER_HPP__

#include <exception>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <stdlib.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TransformException.hpp"

namespace obotcha {

template <typename T> class _NumberParser_ {
public:
    _NumberParser_(int p) {
        mPrecision = p;
    }

    _NumberParser_() {
        mPrecision = 0;
    }

    T convert(std::string v) {
        std::stringstream ss;
        T value;
        if(sizeof(T) > 1) {
           ss << v;
           ss >> value;   
        } else {
           value = atoi(v.c_str());
        }
        
        return value;
    }

private:
    int mPrecision;
};

template <typename T> class _HexNumberParser_ {
  public:
    T convert(std::string v) {
        std::stringstream ss;
        ss << std::hex << v;
        T value;
        ss >> value;
        return value;
    }
};

template <> class _HexNumberParser_<uint8_t> {
  public:
    uint8_t convert(std::string v) {
        std::stringstream ss;
        ss << std::hex << v;
        uint16_t value;
        ss >> value;
        return value;
    }
};

template <typename T> class _OctNumberParser_ {
  public:
    T convert(std::string v) {
        std::stringstream ss;
        ss << std::oct << v;
        T value;
        ss >> value;
        return value;
    }
};

template <> class _OctNumberParser_<uint8_t> {
  public:
    uint8_t convert(std::string v) {
        std::stringstream ss;
        ss << std::oct << v;
        uint16_t value;
        ss >> value;
        return value;
    }
};

DECLARE_TEMPLATE_CLASS(Number, T) {

public:
static T parseNumber(std::string v,int precision = 0){
    //check double && float
    if(precision != 0) {
        int dotCount = 0;
        int size = v.size();
        auto str = v.c_str();
        
        for(int i = 0; i<size;i++) {
            if(str[i] == '.') {
                dotCount++;
            } else if(str[i]<'0' && str[i] > '9') {
                Trigger(TransformException,"Fail to transfor");
            }
        }

        if(dotCount > 1) {
            Trigger(TransformException,"Fail to transfor");
        }
    }

    _NumberParser_<T> parser(precision);
    auto result = parser.convert(v);
    if(precision == 0) {
        std::string checkValue = toDecString(result);
        if(v != checkValue) {
            Trigger(TransformException,"Fail to transfor");
        }
    }
    return result;
}

protected:
static void binaryRecursion(T n, std::stringstream &ss) {
    T a;
    a = n % 2;
    n = n >> 1;
    if (n == 0) {
        // donothing
    } else {
        binaryRecursion(n, ss);
    }
    ss << a;
}

static std::string toHexString(T i) {
    std::stringstream ss;
    ss << std::hex << i;

    std::string str;
    ss >> str;
    return str;
}

static std::string toOctalString(T i) {
    std::stringstream ss;
    ss << std::oct << i;
    std::string str;
    ss >> str;
    return str;
}

static std::string toBinaryString(T i) {
    std::stringstream ss;
    binaryRecursion(i, ss);
    std::string str;
    ss >> str;

    return str;
}

static std::string toDecString(T i) {
    std::string str;
    std::stringstream ss;
        
    if(sizeof(T) > 1) {
        ss << i;
        ss >> str;
    } else {
        ss << (int)i;
        ss >> str;
    }
    return str;
}

static T parseDecNumber(std::string v) {
    _NumberParser_<T> parser;
    auto result = parser.convert(v);

    std::string checkValue = toDecString(result);
    if(v != checkValue) {
        Trigger(TransformException,"Fail to transfor");
    }

    return result;
}

static T parseHexNumber(std::string v) {
    _HexNumberParser_<T> parser;
    auto result = parser.convert(v);
    std::string checkValue = toHexString(result);
    if(v != checkValue) {
        Trigger(TransformException,"Fail to transfor");
    }

    return result;
}

static T parseOctNumber(std::string v) {
    _OctNumberParser_<T> parser;
    auto result = parser.convert(v);
    std::string checkValue = toOctalString(result);
    if(v != checkValue) {
        Trigger(TransformException,"Fail to transfor");
    }

    return result;
}

static T parseBinaryNumber(std::string v) {
    if (v.size() >= 3 && (v.c_str()[1] == 'b' || v.c_str()[1] == 'B')) {
        v = v.substr(2, v.size() - 2);
    }

    int lastIndex = v.size() - 1;
    const char *str = v.c_str();

    T parseBinary = 0;
    for (int i = lastIndex; i >= 0; --i) {
        if (str[i] == '1') {
            parseBinary += pow(2.0, lastIndex - i);
        }
    }

    return parseBinary;
}

protected:
    int mPrecision;
};

} // namespace obotcha

#endif
