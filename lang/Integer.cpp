#include <sstream>

#include "Integer.hpp"

namespace obotcha {

_Integer::_Integer(int v) : val(v) {

}

_Integer::_Integer(Integer v) {
    if(v != nullptr) {
        val = v->val;
        return; 
    }

    val = 0;
}

int _Integer::toValue() {
    return val;
}

bool _Integer::equals(Integer p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

bool _Integer::equals(int p) {
    return val == p;
}

/*
Integer _Integer::valueOf(String v) {
    std::stringstream ss;
    ss<<v->toChars();
    int v = 
}
*/
_Integer::~_Integer() {
}

}