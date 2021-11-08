#include "HttpHeaderExpectCT.hpp"
#include "HttpHeaderContentParser.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

_HttpHeaderExpectCT::_HttpHeaderExpectCT() {
    maxAge = -1;
    mEnforce = false;
    reportUri = nullptr;
}

_HttpHeaderExpectCT::_HttpHeaderExpectCT(String s) {
    import(s->trim());
}

void _HttpHeaderExpectCT::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(directive->equalsIgnoreCase("max-age")) {
            this->maxAge = parameter->toBasicInt();
        } else if(directive->equalsIgnoreCase("report-uri")) {
            this->reportUri = createHttpUrl(parameter);
        } else if(directive->equalsIgnoreCase("enforce")) {
            this->mEnforce = true;
        }
    });
}

HttpUrl _HttpHeaderExpectCT::getReportUri() {
    return reportUri;
}

int _HttpHeaderExpectCT::getMaxAge() {
    return maxAge;
}

bool _HttpHeaderExpectCT::isEnforce() {
    return mEnforce;
}

void _HttpHeaderExpectCT::setReportUri(HttpUrl url) {
    this->reportUri = url;
}

void _HttpHeaderExpectCT::setMaxAge(int s) {
    this->maxAge = s;
}

void _HttpHeaderExpectCT::setEnforce(bool s) {
    mEnforce  = s;
}

String _HttpHeaderExpectCT::toString() {
    String expect = "";
    if(maxAge != -1) {
        expect = expect->append("max-age=",createString(maxAge),"; ");
    }

    if(mEnforce) {
        expect = expect->append("enforce; ");
    }

    if(reportUri != nullptr) {
        expect = expect->append("report-uri=\"",reportUri->toString(),"\"; ");
    }

    return expect->subString(0,expect->size() - 2);
}

}