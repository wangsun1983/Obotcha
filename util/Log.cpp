#include <initializer_list>
#include "Log.hpp"

PrintStream Log::stream = createPrintStream();
int Log::level = Debug;

void Log::d(String s) {
    if(level >= Debug ) {
        stream->print(s);  
    }
}

void Log::d(long v) {
    Log::d(createString(v));
}

void Log::d(const char *s) {
    Log::d(createString(s));
}

void Log::d(int s) {
    Log::d(createString(s));
}

void Log::d(float s) {
    Log::d(createString(s));
}

void Log::d(double s) {
    Log::d(createString(s));
}

void Log::d(bool s){
    Log::d(createString(s));
}

void Log::d(Integer s) {
    Log::d(createString(s));
}

void Log::d(Float s){
    Log::d(createString(s));
}

void Log::d(Double s) {
    Log::d(createString(s));
}

void Log::d(Boolean s) {
    Log::d(createString(s));
}

void Log::d(Long s) {
    Log::d(createString(s));
}

void Log::i(String s) {
    if(level >= Info ) {
        stream->print(s);    
    }
}

void Log::i(const char *s) {
    Log::i(createString(s));
}

void Log::i(int s) {
    Log::i(createString(s));
}

void Log::i(float s) {
    Log::i(createString(s));
}

void Log::i(double s) {
    Log::i(createString(s));
}

void Log::i(bool s){
    Log::i(createString(s));
}

void Log::i(Integer s) {
    Log::i(createString(s));
}

void Log::i(Float s){
    Log::i(createString(s));
}

void Log::i(Double s) {
    Log::i(createString(s));
}

void Log::i(Boolean s) {
    Log::i(createString(s));
}

void Log::i(Long s) {
    Log::i(createString(s));
}


void Log::w(String s) {
    if(level >= Warning ) {
        stream->print(s);    
    }
}

void Log::w(const char *s) {
    Log::w(createString(s));
}

void Log::w(int s) {
    Log::w(createString(s));
}

void Log::w(float s) {
    Log::w(createString(s));
}

void Log::w(double s) {
    Log::w(createString(s));
}

void Log::w(bool s){
    Log::w(createString(s));
}

void Log::w(Integer s) {
    Log::w(createString(s));
}

void Log::w(Float s){
    Log::w(createString(s));
}

void Log::w(Double s) {
    Log::w(createString(s));
}

void Log::w(Boolean s) {
    Log::w(createString(s));
}

void Log::w(Long s) {
    Log::w(createString(s));
}

void Log::e(String s) {
    if(level >= Error ) {
        stream->print(s);    
    }
}

void Log::e(const char *s) {
    Log::e(createString(s));
}

void Log::e(int s) {
    Log::e(createString(s));
}

void Log::e(float s) {
    Log::e(createString(s));
}

void Log::e(double s) {
    Log::e(createString(s));
}

void Log::e(bool s){
    Log::e(createString(s));
}

void Log::e(Integer s) {
    Log::e(createString(s));
}

void Log::e(Float s){
    Log::e(createString(s));
}

void Log::e(Double s) {
    Log::e(createString(s));
}

void Log::e(Boolean s) {
    Log::e(createString(s));
}

void Log::e(Long s) {
    Log::e(createString(s));
}

void Log::setOutPath(String path) {
    stream->setOutPath(path);
    stream->open();
}

void Log::setLogLevel(LogLevel _level) {
    level = level;
}

void Log::newline() {
    stream->newline();
}

void LOGD() {
     Log::newline();
}

void LOGI() {
     Log::newline();
}

void LOGW() {
     Log::newline();
}

void LOGE() {
     Log::newline();
}
