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

} // namespace obotcha
