#include "XmlReader.hpp"

namespace obotcha {

_XmlValue::_XmlValue(xml_node<> *n) {
    node = n;
}

void _XmlValue::setParser(sp<_XmlReader> r) {
    reader = r;
}


}