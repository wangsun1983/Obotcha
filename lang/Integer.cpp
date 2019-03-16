#include <sstream>

#include "Integer.hpp"

namespace obotcha {

_Integer::_Integer(int v) : val(v) {

}

_Integer::_Integer(Integer v) {
    val = v->val;
}

int _Integer::toValue() {
    return val;
}

bool _Integer::equals(Integer p) {
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