#include "HttpHeaderExpectCT.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpHeaderExpectCT::_HttpHeaderExpectCT(String s) {
    load(s->trim());
}

void _HttpHeaderExpectCT::load(String s) {
    st(HttpHeaderContentParser)::load(s,[this](String directive,String parameter) {
        if(directive->equalsIgnoreCase("max-age")) {
            this->maxAge = parameter->toBasicInt();
        } else if(directive->equalsIgnoreCase("report-uri")) {
            this->reportUri = HttpUrl::New(parameter);
        } else if(directive->equalsIgnoreCase("enforce")) {
            this->mEnforce = true;
        }
    });
}

HttpUrl _HttpHeaderExpectCT::getReportUri() const {
    return reportUri;
}

int _HttpHeaderExpectCT::getMaxAge() const {
    return maxAge;
}

bool _HttpHeaderExpectCT::isEnforce() const {
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
    StringBuffer expect = StringBuffer::New();
    if(maxAge != -1) {
        expect->append("max-age=",String::New(maxAge),"; ");
    }

    if(mEnforce) {
        expect->append("enforce; ");
    }

    if(reportUri != nullptr) {
        expect->append("report-uri=\"",reportUri->toString(),"\"; ");
    }

    return expect->toString(0,expect->size() - 2);
}

}