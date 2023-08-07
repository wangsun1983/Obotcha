#ifndef __OBOTCHA_NUMBER_HPP__
#define __OBOTCHA_NUMBER_HPP__

#include <exception>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <regex>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TransformException.hpp"

namespace obotcha {

template <typename T> class _NumberParser_ {
public:
    explicit _NumberParser_(int p):mPrecision(p) {
    }

    _NumberParser_() {
    }

    T convert(const std::string &v) {
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
    int mPrecision = 0;
};

template <typename T> class _HexNumberParser_ {
  public:
    T convert(const std::string &v) {
        std::stringstream ss;
        ss << std::hex << v;
        T value;
        ss >> value;
        return value;
    }
};

template <> class _HexNumberParser_<uint8_t> {
  public:
    uint8_t convert(const std::string &v) {
        std::stringstream ss;
        ss << std::hex << v;
        uint16_t value;
        ss >> value;
        return value;
    }
};

template <typename T> class _OctNumberParser_ {
  public:
    T convert(const std::string &v) {
        std::stringstream ss;
        ss << std::oct << v;
        T value;
        ss >> value;
        return value;
    }
};

template <> class _OctNumberParser_<uint8_t> {
  public:
    uint8_t convert(const std::string &v) {
        std::stringstream ss;
        ss << std::oct << v;
        uint16_t value;
        ss >> value;
        return value;
    }
};

DECLARE_TEMPLATE_CLASS(Number, T) {

public:

enum TrimType {
    Hex = 0,
    Bin,
    Default,
};

static T ParseNumber(std::string v,int precision = 0){
    //check double && float
    if(precision != 0) {
        int dotCount = 0;
        size_t size = v.size();
        auto str = v.c_str();
        
        for(size_t i = 0; i<size;i++) {
            if(str[i] == '.') {
                dotCount++;
            } else if(str[i]<'0' || str[i] > '9') {
                Trigger(TransformException,"Fail to transfor")
            }
        }

        if(dotCount > 1) {
            Trigger(TransformException,"Fail to transfor")
        }
    }

    _NumberParser_<T> parser(precision);
    auto result = parser.convert(v);
    if(precision == 0) {
        std::string checkValue = ToDecString(result);
        if(v != checkValue) {
            Trigger(TransformException,"Fail to transfor")
        }
    }
    return result;
}

protected:
static void BinaryRecursion(T n, std::stringstream &ss) {
    T a;
    a = n % 2;
    n = n >> 1;
    if (n == 0) {
        // donothing
    } else {
        BinaryRecursion(n, ss);
    }
    ss << (int)a;
}

static std::string ToHexString(T i) {
    std::stringstream ss;
    std::string str;

    if(sizeof(T) > 1) {
        ss << std::hex << i;
        ss >> str;
    } else {
        ss << std::hex << (int)i;
        ss >> str;
    }
    return str;
}

static std::string ToOctalString(T i) {
    std::stringstream ss;
    std::string str;

    if(sizeof(T) > 1) {
        ss << std::oct << i;
        ss >> str;
    } else {
        ss << std::oct << (int)i;
        ss >> str;
    }
    
    return str;
}

static std::string ToBinaryString(T i) {
    std::stringstream ss;
    std::string str;
    if(sizeof(T) > 1) {
        BinaryRecursion(i, ss);
    } else {
        BinaryRecursion((int)i, ss);
    }

    ss >> str;
    return str;
}

static std::string ToDecString(T i) {
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

static std::string Trim(std::string v,int type = TrimType::Default) {
    std::string::iterator end_pos = std::remove(v.begin(), v.end(), ' ');
    v.erase(end_pos, v.end());
    v = std::regex_replace(v, std::regex("\n"), "");
    v = std::regex_replace(v, std::regex("\r"), "");
    auto size = v.size();
    if(size == 0) {
        Trigger(TransformException,"Fail to transfor")
    }
    
    //find zero like: 0000123;
    switch(type) {
        case Hex: {
            if (v.size() >= 3 && (v.c_str()[1] == 'x' || v.c_str()[1] == 'X')) {
                v = v.substr(2, v.size() - 2);
            }
        }
        break;

        case Bin: {
            if (v.size() >= 3 && (v.c_str()[1] == 'b' || v.c_str()[1] == 'B')) {
                v = v.substr(2, v.size() - 2);
            }
        }
        break;
    }

    const char *str = v.c_str();
    int start = 0;
    size = v.size();
    for(; start<size;start++) {
        if(str[start] != '0') {
            break;
        }
    }

    if(start == size) {
        return "0";
    } else if(start == 0) {
        return v;
    } else {
        return v.substr(start, v.size() - start);
    }

    return v;
}

static T ParseDecNumber(std::string v) {
    v = Trim(v);

    _NumberParser_<T> parser;
    auto result = parser.convert(v);

    if(v != ToDecString(result)) {
        Trigger(TransformException,"Fail to transfor")
    }

    return result;
}

static T ParseHexNumber(std::string v) {
    v = Trim(v,Hex);
    _HexNumberParser_<T> parser;
    auto result = parser.convert(v);
    std::string checkValue = ToHexString(result);
    
    int size = v.size();
    if(checkValue.size() != size) {
        Trigger(TransformException,"Fail to transfor")
    }
    const char *v_str = v.c_str();
    const char *c_str = checkValue.c_str();
    for(int i = 0;i < size;i++) {
        int value = std::abs(v_str[i] - c_str[i]);
        if(value != 0 && value != 0x20) {
            Trigger(TransformException,"Fail to transfor")
        }
    }
    
    return result;
}

static T ParseOctNumber(std::string v) {
    v = Trim(v);

    _OctNumberParser_<T> parser;
    auto result = parser.convert(v);
    if(v != ToOctalString(result)) {
        Trigger(TransformException,"Fail to transfor")
    }

    return result;
}

static T ParseBinaryNumber(std::string v) {
    v = Trim(v,Bin);
    
    int lastIndex = v.size() - 1;
    const char *str = v.c_str();

    for(int k = 0; k <= lastIndex;k++) {
        if(str[k] != '0' && str[k] != '1') {
            Trigger(TransformException,"Fail to transfor")
        }
    }

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
