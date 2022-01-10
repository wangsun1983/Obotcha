#ifndef __OBOTCHA_NUMBER_HPP__
#define __OBOTCHA_NUMBER_HPP__

#include <exception>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

class _String;

template <typename T> class _NumberChecker_ {
  public:
    bool _isCorrectDecInputNumber(std::string v) { return false; }
    bool _isCorrectHexInputNumber(std::string v) { return false; }
    bool _isCorrectBinInputNumber(std::string v) { return false; }
    bool _isCorrectOctInputNumber(std::string v) { return false; }

  private:
    T v;
};

#define _NUMBER_CHECK_DECLARE(X)                                               \
    template <> class _NumberChecker_<X> {                                     \
      public:                                                                  \
        bool _isCorrectDecInputNumber(std::string v) {                         \
            const char *p = v.c_str();                                         \
            int size = v.size();                                               \
            for (int i = 0; i < size; i++) {                                   \
                if (p[i] == '-' && i == 0) {                                   \
                    continue;                                                  \
                } else if (p[i] < '0' || p[i] > '9') {                         \
                    return false;                                              \
                }                                                              \
            }                                                                  \
            return true;                                                       \
        }                                                                      \
        bool _isCorrectHexInputNumber(std::string v) {                         \
            const char *p = v.c_str();                                         \
            int size = v.size();                                               \
            for (int i = 0; i < size; i++) {                                   \
                switch (p[i]) {                                                \
                case '0':                                                      \
                case '1':                                                      \
                case '2':                                                      \
                case '3':                                                      \
                case '4':                                                      \
                case '5':                                                      \
                case '6':                                                      \
                case '7':                                                      \
                case '8':                                                      \
                case '9':                                                      \
                case 'a':                                                      \
                case 'A':                                                      \
                case 'b':                                                      \
                case 'B':                                                      \
                case 'c':                                                      \
                case 'C':                                                      \
                case 'd':                                                      \
                case 'D':                                                      \
                case 'e':                                                      \
                case 'E':                                                      \
                case 'f':                                                      \
                case 'F':                                                      \
                    continue;                                                  \
                default:                                                       \
                    return false;                                              \
                }                                                              \
            }                                                                  \
            return true;                                                       \
        }                                                                      \
        bool _isCorrectBinInputNumber(std::string v) {                         \
            const char *p = v.c_str();                                         \
            int size = v.size();                                               \
            for (int i = 0; i < size; i++) {                                   \
                switch (p[i]) {                                                \
                case '0':                                                      \
                case '1':                                                      \
                    continue;                                                  \
                default:                                                       \
                    return false;                                              \
                }                                                              \
            }                                                                  \
            return true;                                                       \
        }                                                                      \
        bool _isCorrectOctInputNumber(std::string v) {                         \
            const char *p = v.c_str();                                         \
            int size = v.size();                                               \
            for (int i = 0; i < size; i++) {                                   \
                switch (p[i]) {                                                \
                case '0':                                                      \
                case '1':                                                      \
                case '2':                                                      \
                case '3':                                                      \
                case '4':                                                      \
                case '5':                                                      \
                case '6':                                                      \
                case '7':                                                      \
                    continue;                                                  \
                default:                                                       \
                    return false;                                              \
                }                                                              \
            }                                                                  \
            return true;                                                       \
        }                                                                      \
      private:                                                                 \
        X v;                                                                   \
    };

_NUMBER_CHECK_DECLARE(int)
_NUMBER_CHECK_DECLARE(long)
_NUMBER_CHECK_DECLARE(uint8_t)
_NUMBER_CHECK_DECLARE(uint16_t)
_NUMBER_CHECK_DECLARE(uint32_t)
_NUMBER_CHECK_DECLARE(uint64_t)

#define _NUMBER_CHECK_DECLARE_DOUBLE(X)                                        \
    template <> class _NumberChecker_<X> {                                     \
      public:                                                                  \
        bool _isCorrectDecInputNumber(std::string v) {                         \
            int dotCount = 0;                                                  \
            const char *p = v.c_str();                                         \
            int size = v.size();                                               \
            for (int i = 0; i < size; i++) {                                   \
                if (p[i] == '-' && i == 0) {                                   \
                    continue;                                                  \
                } else if (p[i] >= '0' && p[i] <= '9') {                       \
                    continue;                                                  \
                } else if (p[i] == '.') {                                      \
                    dotCount++;                                                \
                    if (dotCount > 1) {                                        \
                        return false;                                          \
                    }                                                          \
                    continue;                                                  \
                }                                                              \
                return false;                                                  \
            }                                                                  \
            return true;                                                       \
        }                                                                      \
        bool _isCorrectHexInputNumber(std::string v) { return false; }         \
        bool _isCorrectBinInputNumber(std::string v) { return false; }         \
        bool _isCorrectOctInputNumber(std::string v) { return false; }         \
      private:                                                                 \
        X v;                                                                   \
    };

_NUMBER_CHECK_DECLARE_DOUBLE(double)
_NUMBER_CHECK_DECLARE_DOUBLE(float)

DECLARE_TEMPLATE_CLASS(Number, 1) {

  public:
    static T parseNumber(std::string v) {
        _NumberChecker_<T> checker;
        if (!checker._isCorrectDecInputNumber(v)) {
            throw(-1);
        }

        std::stringstream ss;
        ss << v;
        T value;
        ss >> value;

        return value;
    }

  protected:
    static void binaryRecursion(T n, std::stringstream & ss) {
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
        std::stringstream ss;
        ss << i;
        std::string str;
        ss >> str;
        return str;
    }

    static T parseDecNumber(std::string v) {
        _NumberChecker_<T> checker;
        if (!checker._isCorrectDecInputNumber(v)) {
            throw(-1);
        }

        std::stringstream ss;
        ss << v;
        T value;
        ss >> value;

        return value;
    }

    static T parseHexNumber(std::string v) {
        if (v.size() >= 3 && (v.c_str()[1] == 'x' || v.c_str()[1] == 'X')) {
            v = v.substr(2, v.size() - 2);
        }

        _NumberChecker_<T> checker;
        if (!checker._isCorrectHexInputNumber(v)) {
            throw(-1);
        }

        std::stringstream ss;
        ss << std::hex << v;
        T value;
        ss >> value;
        return value;
    }

    static T parseOctNumber(std::string v) {
        _NumberChecker_<T> checker;
        if (!checker._isCorrectOctInputNumber(v)) {
            throw(-1);
        }

        std::stringstream ss;
        ss << std::oct << v;
        T value;
        ss >> value;
        return value;
    }

    static T parseBinaryNumber(std::string v) {
        if (v.size() >= 3 && (v.c_str()[1] == 'b' || v.c_str()[1] == 'B')) {
            v = v.substr(2, v.size() - 2);
        }

        _NumberChecker_<T> checker;
        if (!checker._isCorrectBinInputNumber(v)) {
            throw(-1);
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
};

} // namespace obotcha

#endif