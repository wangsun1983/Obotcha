#include "HttpUrlEncodedValue.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpUrlEncodedValue::_HttpUrlEncodedValue() {
    encodedValues = HashMap<String,String>::New();
}

_HttpUrlEncodedValue::_HttpUrlEncodedValue(String v):_HttpUrlEncodedValue() {
    load(v);
}

void _HttpUrlEncodedValue::load(String value) {
    int pos = 0;
    while (pos < value->size()) {
        int tokenStart = pos;
        pos = st(HttpHeaderContentParser)::skipUntil(value, pos,String::New("=&"));
        String directive = value->subString(tokenStart, pos - tokenStart)->trim();
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
                    value, pos, String::New("\""));
                parameter = value->subString(parameterStart, pos - parameterStart);
                //pos++; // consume '"' close quote (if necessary)
                pos = st(HttpHeaderContentParser)::skipUntil(value, pos, String::New("&"));
                // unquoted string
                pos++;
            } else {
                int parameterStart = pos;
                pos = st(HttpHeaderContentParser)::skipUntil(
                    value, pos, String::New("&"));
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
    StringBuffer v = StringBuffer::New();
    auto iterator = encodedValues->getIterator();
    while (iterator->hasValue()) {
        String key = iterator->getKey();
        String value = iterator->getValue();
        v->append(key,"=",value,"&");
        iterator->next();
    }
    return v->toString(0,v->size()-1);
}

}

