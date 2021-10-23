#include "HttpUrlEncodedValue.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpUrlEncodedValue::_HttpUrlEncodedValue() {
    encodedValues = createHashMap<String,String>();
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

        encodedValues->put(directive,parameter);
    }
}

HashMap<String,String> _HttpUrlEncodedValue::getValues() {
    return encodedValues;
}

void _HttpUrlEncodedValue::set(String k,String v) {
    encodedValues->put(k,v);
}

String _HttpUrlEncodedValue::get(String k) {
    return encodedValues->get(k);
}

String _HttpUrlEncodedValue::toString() {
    String v =createString("");
    auto iterator = encodedValues->getIterator();
    while (iterator->hasValue()) {
        String key = iterator->getKey();
        String value = iterator->getValue();
        v = v->append(key,"=",value,"&");
        iterator->next();
    }
    return v->subString(0,v->size()-1);
}

}

