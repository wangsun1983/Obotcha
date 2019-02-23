#include "String.hpp"
#include <sys/time.h>
#include <unistd.h>

 _String::_String() {
    m_str = new std::string();
}

_String::_String(String v) {
    
}

_String::_String(char *v) {
    m_str = new std::string(v);
}

_String::_String(char *v,int start,int length) {
    //TODO
}

_String::~_String() {
    if(m_str != nullptr) {
        delete m_str;
    }
}

char * _String::toChars() {
    //TODO
}

char _String::charAt(int index) {
    //TODO
}

String _String::subString(int start,int end) {
    //TODO
}

bool _String::contains(String val) {
    //TODO
}

String _String::trim() {
    //TODO
}

int _String::length() {
    //TODO
}

int _String::indexOf(String v) {
    //TODO
}
    
String _String::valueOf(Integer v) {
    //TODO
}

String _String::valueOf(Boolean v) {
    //TODO
}

String _String::valueOf(Double v) {

}

String _String::valueOf(Float v) {

}

String _String::valueOf(char *p) {

}

bool _String::equals() {
    
}