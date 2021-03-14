#include "HttpXFormUrlEncodedParser.hpp"

namespace obotcha {

ArrayList<KeyValuePair<String,String>> _HttpXFormUrlEncodedParser::parse(String content) {
    printf("HttpXFormUrlEncodedParser parser start \n");
    ArrayList<KeyValuePair<String,String>> result = createArrayList<KeyValuePair<String,String>>();
    ArrayList<String> pairs = content->split("&");
    printf("HttpXFormUrlEncodedParser parser trace1 \n");
    pairs->foreach([&result](String str) {
        if(str != nullptr) {
            ArrayList<String> kv = str->split("=");
            printf("HttpXFormUrlEncodedParser parser trace2,str is %s \n",str->toChars());
            if(kv->size() == 2) {
                result->add(createKeyValuePair<String,String>(kv->get(0),kv->get(1)));
            }
        }
        return 1;
    });

    return result;
}

}
