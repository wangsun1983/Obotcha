#include "SqlConnectParam.hpp"

namespace obotcha {

_SqlConnectParam::_SqlConnectParam() {
    this->mParams = HashMap<String,String>::New();
}

void _SqlConnectParam::set(String key,String value) {
    this->mParams->put(key,value);
}

String _SqlConnectParam::get(String p) {
    return mParams->get(p);
}

} // namespace obotcha
