#include "HttpHeaderContentDisposition.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"
#include "StringBuffer.hpp"
#include "Log.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpHeaderContentDisposition::_HttpHeaderContentDisposition(String s) {
    load(s);
}

void _HttpHeaderContentDisposition::load(String s) {
    st(HttpHeaderContentParser)::load(s,[this](String directive,String parameter) {
        if(parameter == nullptr) {
            //type = directive;
            if(directive->equalsIgnoreCase("inline")) {
                type = Inline;
            } else if(directive->equalsIgnoreCase("attachment")) {
                type = Attachment;
            } else {
                type = FormData;
            }
        } else {
            if(directive->equalsIgnoreCase("name")) {
                name = parameter;
            } else if(directive->equalsIgnoreCase("filename")) {
                filename = parameter;
            }
        }
    });
}

void _HttpHeaderContentDisposition::setFileName(String filename) {
    this->filename = filename;
}

String _HttpHeaderContentDisposition::getFileName() {
    return filename;
}

void _HttpHeaderContentDisposition::setName(String name) {
    this->name = name;
}

String _HttpHeaderContentDisposition::getName() {
    return name;
}

int _HttpHeaderContentDisposition::getType() {
    return type;
}

void _HttpHeaderContentDisposition::setType(int t) {
    type = t;
}

String _HttpHeaderContentDisposition::toString() {
    StringBuffer content = createStringBuffer();

    switch(type) {
        case Inline:
            content->append(createString("inline"));
        break;

        case FormData:
            content->append(createString("form-data"));
        break;

        case Attachment:
            content->append(createString("attachment"));
        break;

        default:
            LOG(ERROR)<<"Content-Disposition toString,invalid params";
        break;
    }

    if(name == nullptr && filename == nullptr) {
        return content->toString();
    }

    if(name != nullptr) {
        content->append("; name=\"",name,"\"");
    }

    if(filename != nullptr) {
        content->append("; filename=\"",filename,"\"");
    }

    return content->toString();
}

}
