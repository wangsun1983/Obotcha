#include "HttpXFormUrlEncodedParser.hpp"

namespace obotcha {

ArrayList<KeyValuePair<String,String>> _HttpXFormUrlEncodedParser::parse(String content) {
    ArrayList<KeyValuePair<String,String>> result = createArrayList<KeyValuePair<String,String>>();
    ArrayList<String> pairs = content->split("&");
    pairs->foreach([&result](String str) {
        if(str != nullptr) {
            ArrayList<String> kv = str->split("=");
            if(kv->size() == 2) {
                result->add(createKeyValuePair<String,String>(kv->get(0),kv->get(1)));
            }
        }
        return 1;
    });

    return result;
}

}
