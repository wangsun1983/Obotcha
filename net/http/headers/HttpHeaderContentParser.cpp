#include "HttpHeaderContentParser.hpp"
#include "Integer.hpp"

namespace obotcha {

_HttpHeaderContentParser::_HttpHeaderContentParser() {
    // Nothing
}

int _HttpHeaderContentParser::skipUntil(String input, int pos,
                                        String characters) {
    for (; pos < input->size(); pos++) {
        if (characters->indexOf(input->charAt(pos)) != -1) {
            break;
        }
    }
    return pos;
}

int _HttpHeaderContentParser::skipWhitespace(String input, int pos) {
    for (; pos < input->size(); pos++) {
        char c = input->charAt(pos);
        if (c != ' ' && c != '\t') {
            break;
        }
    }
    return pos;
}

int _HttpHeaderContentParser::parseSeconds(String value, int defaultValue) {
    long seconds = value->toBasicLong();
    if (seconds > st(Integer)::MAX_VALUE) {
        return st(Integer)::MAX_VALUE;
    } else if (seconds < 0) {
        return 0;
    } else {
        return (int)seconds;
    }
}

int _HttpHeaderContentParser::load(String content,const _ParseResult &func) {
    return load(content,createString("=,;"),createString(",;"),func);
}

int _HttpHeaderContentParser::load(String value,String skipDirective,String skipParam,const _ParseResult &callback) {
    if (value != nullptr) {
        int pos = 0;
        while (pos < value->size()) {
            int tokenStart = pos;
            pos = st(HttpHeaderContentParser)::skipUntil(value, pos,
                                                         skipDirective/*createString("=,;")*/);
            String directive =
                value->subString(tokenStart, pos - tokenStart)->trim();
            String parameter = nullptr;

            if (pos == value->size() || value->charAt(pos) == ',' || value->charAt(pos) == ';') {
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
                    pos = st(HttpHeaderContentParser)::skipUntil(value, pos, createString(",;"));
                    // unquoted string
                    pos++;
                } else {
                    int parameterStart = pos;
                    pos = st(HttpHeaderContentParser)::skipUntil(
                        value, pos, skipParam/*createString(",;")*/);
                    
                    if((pos - parameterStart) == 0) {
                        parameter = createString("");
                    } else {
                        parameter =
                            value->subString(parameterStart, (pos - parameterStart))
                                ->trim();
                    }
                    pos++;
                }
            }
            
            callback(directive,parameter);
        }
    }

    return 0;
}

} // namespace obotcha
