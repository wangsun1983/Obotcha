#include "HttpVersionParser.hpp"
#include "ArrayList.hpp"

namespace obotcha {

HttpVersion _HttpVersionParser::doParse(String content) {
    ArrayList<String> strings = content->split("/");
    if(strings->size() != 2) {
        return nullptr;
    }

    String versions = strings->get(1);
    ArrayList<String> vstrings = versions->split(".");
    if(vstrings->size() != 2) {
        return nullptr;
    }

    String major = vstrings->get(0);
    String minor = vstrings->get(1);
    return createHttpVersion(major->toBasicInt(),minor->toBasicInt());
}

}
