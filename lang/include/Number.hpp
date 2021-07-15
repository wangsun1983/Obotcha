#ifndef __OBOTCHA_NUMBER_HPP__
#define __OBOTCHA_NUMBER_HPP__

#include <sstream>
#include <string>
#include <math.h>
#include <iostream>
#include <exception>

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Number,1) {
public:
    static T parseNumber(std::string v) {
        std::stringstream ss;
        ss<< v;
        T value;
        ss>>value;

        std::string checkValue = toDecString(value);

        if(checkValue.compare(v) == 0) {
            return value;
        }

        throw("");
    }

protected:
    static void binaryRecursion(T n,std::stringstream &ss) {
        T a;
        a = n%2;
        n = n>>1;
        if (n==0) {
            //donothing
        } else {
            binaryRecursion(n,ss);
        }
        ss<<a;
    }

    static std::string toHexString(T i) {
        std::stringstream ss;
        ss<<std::hex<<i;

        std::string str;
        ss>>str;
        return str;
    }

    static std::string toOctalString(T i) {
        std::stringstream ss;
        ss<<std::oct<<i;
        std::string str;
        ss>>str;
        return str;
    }

    static std::string toBinaryString(T i) {
        std::stringstream ss;
        binaryRecursion(i,ss);
        std::string str;
        ss>>str;

        return str;
    }

    static std::string toDecString(T i) {
        std::stringstream ss;
        ss<<i;
        std::string str;
        ss>>str;
        return str;
    }

    static T parseDecNumber(std::string v) {
        std::stringstream ss;
        ss<<v;
        T value;
        ss>>value;

        std::string checkValue = toDecString(value);

        if(checkValue.compare(v) == 0) {
            return value;
        }

        throw("");
    }

    static T parseHexNumber(std::string v) {
        if(v.size() >= 3 && (v.c_str()[1] == 'x' || v.c_str()[1] == 'X')) {
            v = v.substr(2,v.size() - 2);
        }

        std::stringstream ss;
        ss<< std::hex <<v;
        T value;
        ss>>value;
        std::string checkValue = toHexString(value);
        if(checkValue.size() == v.size()) {
            //ingore Lower/Upper case
            int len = v.size();
            const char * str1 = v.c_str();
            const char * str2 = checkValue.c_str();
            for(int i = 0;i<len;i++) {
                if(str1[i] != str2[i] && std::abs((str1[i] - str2[i])) != 0x20) {
                    throw("");
                }
            }

            return value;
        }
        throw("");
    }

    static T parseOctNumber(std::string v) {
        std::stringstream ss;
        ss<< std::oct <<v;
        T value;
        ss>>value;

        std::string checkValue = toOctalString(value);

        if(checkValue.compare(v) == 0) {
            return value;
        }

        throw("");
    }

    static T parseBinaryNumber(std::string v) {
        if(v.size() >= 3 && (v.c_str()[1] == 'b' || v.c_str()[1] == 'B')) {
            v = v.substr(2,v.size() - 2);
        }

        int lastIndex = v.size() - 1;
        const char *str = v.c_str();

        T parseBinary = 0;
        for (int i = lastIndex; i >= 0; --i) {
            if (str[i] == '1') {
                parseBinary += pow(2.0, lastIndex - i);
            }
        }

        std::string checkValue = toBinaryString(parseBinary);

        if(checkValue.compare(v) == 0) {
            return parseBinary;
        }

        throw("");
    }

    bool isIntNumber(const char *p,int size) {
        for(int i = 0;i < size;i++) {
            if(p[i] >= '0' && p[i] <= '9') {
                continue;
            } else {
                if((i == size - 1) && p[i] == '\0') {
                    return true;
                }
                return false;
            }
        }

        return true;
    }

    bool isLongNumber(const char *p,int size) {
        for(int i = 0;i < size;i++) {
            if(p[i] >= '0' && p[i] <= '9') {
                continue;
            }
            return false;
        }

        return true;
    }

    bool isDoubleNumber(const char *p,int size) {
        int dotCount = 0;

        for(int i = 0;i < size;i++) {
            if(p[i] >= '0' && p[i] <= '9') {
                continue;
            } else if(p[i] == '.') {
                dotCount++;
                if(dotCount > 1) {
                    return false;
                }
                continue;
            }
            return false;
        }

        return true;
    }

    bool isFloatNumber(const char *p,int size) {
        int dotCount = 0;

        for(int i = 0;i < size;i++) {
            if(p[i] >= '0' && p[i] <= '9') {
                continue;
            } else if(p[i] == '.') {
                dotCount++;
                if(dotCount > 1) {
                    return false;
                }
                continue;
            }
            return false;
        }
        return true;
    }

};

}

#endif