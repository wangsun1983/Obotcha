#ifndef __NUMBER_HPP__
#define __NUMBER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include <sstream>
#include <string>
#include <math.h>

namespace obotcha {

class _String;

DECLARE_CLASS(Number,1) {
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
        ss<<(long long)a;
    }

    static std::string toHexString(T i) {
        std::stringstream ss;
        ss<<std::hex<<(long long)i;

        std::string str;
        ss>>str;
        return str;
    }

    static std::string toOctalString(T i) {
        std::stringstream ss;
        ss<<std::oct<<(long long)i;
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
        ss<<(long long)i;
        std::string str;
        ss>>str;
        return str;
    }

    static T parseDecNumber(std::string v) {
        std::stringstream ss;
        ss<<v;
        long long value;
        ss>>value;

        return (T)value;
    }

    static T parseHexNumber(std::string v) {
        std::stringstream ss;
        ss<< std::hex <<v;
        long long value;
        ss>>value;
        return (T)value;
    }

    static T parseOctNumber(std::string v) {
        std::stringstream ss;
        ss<< std::oct <<v;
        long long value;
        ss>>value;
        return (T)value;
    }

    static T parseBinaryNumber(std::string v) {
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
};

}

#endif