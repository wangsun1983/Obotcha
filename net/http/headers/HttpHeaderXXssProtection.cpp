#include "HttpHeaderXXssProtection.hpp"

namespace obotcha {

String _HttpHeaderXXssProtection::DisableContent = String::New("0");
String _HttpHeaderXXssProtection::EnableContent = String::New("1");

_HttpHeaderXXssProtection::_HttpHeaderXXssProtection(String content) {
    load(content);
}

void _HttpHeaderXXssProtection::load(String content) {
    content = content->trimAll();
    if(content->sameAs("0")) {
        mType = Disable;
    } else if(content->sameAs("1")) {
        mType = Enable;
    } else if(content->sameAs("1;mode=block")) {
        mType = Block;
    } else {
        //analyse:1;report=xxx.hpp
        int report_index = content->indexOf("1;");
        if(report_index >= 0) {
            auto report_context = content->subString(report_index + 2,content->size() - report_index - 2);
            auto report_url_index = report_context->indexOf("report=");
            if(report_url_index >= 0) {
                auto report_url = report_context->subString(report_url_index + 7,
                                                            report_context->size() - report_url_index - 7);
                mType = Report;
                mReportUri = report_url;
            }
        }
    }
}
    
_HttpHeaderXXssProtection::Type _HttpHeaderXXssProtection::getType() {
    return mType;
}

String _HttpHeaderXXssProtection::getReportUrl() {
    return mReportUri;
}

void _HttpHeaderXXssProtection::set(_HttpHeaderXXssProtection::Type xxssType,String reporturl) {
    mType = xxssType;
    if(mType == Type::Report) {
        mReportUri = reporturl;
    }
}
    
String _HttpHeaderXXssProtection::toString() {
    switch(mType) {
        case Type::Disable:
            return String::New("0");
        case Type::Enable:
            return String::New("1");
        case Type::Report:
            return String::New("1; report=")->append(mReportUri);
        case Type::Block:
            return String::New("1; mode=block");
        default:
            return nullptr;
    }
}

}
