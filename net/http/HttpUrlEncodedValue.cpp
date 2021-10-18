#include "HttpUrlEncodedValue.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpUrlEncodedValue::_HttpUrlEncodedValue() {
    encodedValues = createArrayList<KeyValuePair<String,String>>();
}

_HttpUrlEncodedValue::_HttpUrlEncodedValue(String v):_HttpUrlEncodedValue() {
    import(v);
}

void _HttpUrlEncodedValue::import(String value) {
    int pos = 0;
    while (pos < value->size()) {
        int tokenStart = pos;
        pos = st(HttpHeaderContentParser)::skipUntil(value, pos,
                                                        createString("=&"));
        String directive =
            value->subString(tokenStart, pos - tokenStart)->trim();
        String parameter = nullptr;

        if (pos == value->size() || value->charAt(pos) == '&') {
            pos++; // consume ',' or ';' (if necessary)
            parameter = nullptr;
        } else {
            pos++; // consume '='
            pos = st(HttpHeaderContentParser)::skipWhitespace(value, pos);
            // quoted string
            if (pos < value->size() && value->charAt(pos) == '\"') {
                pos++; // consume '"' open quote
                int parameterStart = pos;
                pos = st(HttpHeaderContentParser)::skipUntil(
                    value, pos, createString("\""));
                parameter = value->subString(parameterStart, pos - parameterStart);
                //pos++; // consume '"' close quote (if necessary)
                pos = st(HttpHeaderContentParser)::skipUntil(value, pos, createString("&"));
                // unquoted string
                pos++;
            } else {
                int parameterStart = pos;
                pos = st(HttpHeaderContentParser)::skipUntil(
                    value, pos, createString("&"));
                parameter =
                    value->subString(parameterStart, (pos - parameterStart))
                        ->trim();
                pos++;
            }
        }

        KeyValuePair<String,String> pair = createKeyValuePair<String,String>(directive,parameter);
        encodedValues->add(pair);
    }
}

ArrayList<KeyValuePair<String,String>> _HttpUrlEncodedValue::getValues() {
    return encodedValues;
}

void _HttpUrlEncodedValue::set(String k,String v) {
    encodedValues->add(createKeyValuePair<String,String>(k,v));
}

String _HttpUrlEncodedValue::toString() {
    String v =createString("");
    auto iterator = encodedValues->getIterator();
    while (iterator->hasValue()) {
        auto pair = iterator->getValue();
        String key = pair->getKey();
        String value = pair->getValue();
        v = v->append(key,"=",value,"&");
        iterator->next();
    }
    return v->subString(0,v->size()-1);
}

}

