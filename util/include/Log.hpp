#ifndef __LOG_HPP__
#define __LOG_HPP__

#include <initializer_list>
#include <iostream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "PrintStream.hpp"
using namespace std;

class Log {
public:
    enum LogLevel {
        Debug,
        Info,
        Warning,
        Error
    };
    
    static void d(String s);
    static void d(int s);
    static void d(float s);
    static void d(double s);
    static void d(bool s);
    static void d(const char *);
    static void d(long v);

    static void d(Integer s);
    static void d(Float s);
    static void d(Double s);
    static void d(Boolean s);
    static void d(Long s);


    static void i(String s);
    static void i(int s);
    static void i(float s);
    static void i(double s);
    static void i(bool s);
    static void i(const char *);
    static void i(long v);

    static void i(Integer s);
    static void i(Float s);
    static void i(Double s);
    static void i(Boolean s);
    static void i(Long s);

    static void w(String s);
    static void w(int s);
    static void w(float s);
    static void w(double s);
    static void w(bool s);
    static void w(const char *);
    static void w(long v);

    static void w(Integer s);
    static void w(Float s);
    static void w(Double s);
    static void w(Boolean s);
    static void w(Long s);

    static void e(String s);
    static void e(int s);
    static void e(float s);
    static void e(double s);
    static void e(bool s);
    static void e(const char *);
    static void e(long v);

    static void e(Integer s);
    static void e(Float s);
    static void e(Double s);
    static void e(Boolean s);
    static void e(Long s);

    static void setOutPath(String path);

    static void setLogLevel(LogLevel level);

    static void newline();

private:
    static PrintStream stream;
    static int level;    
};

void LOGD();

template <typename T, typename ...Args>
void LOGD(T head, Args... rest){
   Log::d(head);
   LOGD(rest...);
}

void LOGI();

template <typename T, typename ...Args>
void LOGI(T head, Args... rest){
   Log::i(head);
   LOGI(rest...);
}

void LOGW();

template <typename T, typename ...Args>
void LOGW(T head, Args... rest){
   Log::w(head);
   LOGW(rest...);
}

void LOGE();

template <typename T, typename ...Args>
void LOGE(T head, Args... rest){
   Log::e(head);
   LOGE(rest...);
}
#endif