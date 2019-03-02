#include "Properties.hpp"

_Properties::_Properties() {
    mProps = createHashMap<String,String>();
}
    
void _Properties::set(String key,String value) {
    mProps->set(key,value);
}
    
String _Properties::get(String key) {
    return mProps->get(key);
}

void _Properties::load(File file) {
    //TODO

}

void _Properties::save(String path) {
    //TODO
}