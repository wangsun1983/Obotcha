#include "HttpHeaderSaveData.hpp"

namespace obotcha {
    
const String _HttpHeaderSaveData::ON = "on";
const String _HttpHeaderSaveData::OFF = "off";

_HttpHeaderSaveData::_HttpHeaderSaveData() {
    saveData = nullptr;
}

_HttpHeaderSaveData::_HttpHeaderSaveData(String s) {
    load(s);
}

void _HttpHeaderSaveData::load(String s) {
    if(s->trim()->equalsIgnoreCase(ON)) {
        saveData = ON;
    } else {
        saveData = OFF;
    }
}

void _HttpHeaderSaveData::set(String s) {
    load(s);
}

String _HttpHeaderSaveData::get() {
    return saveData;
}

String _HttpHeaderSaveData::toString() {
    return saveData;
}

    

}