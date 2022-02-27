#include "HttpHeaderContentDisposition.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"
#include "StringBuffer.hpp"
#include "Log.hpp"

namespace obotcha {

_HttpHeaderContentDisposition::_HttpHeaderContentDisposition() {
    
}

_HttpHeaderContentDisposition::_HttpHeaderContentDisposition(String s) {
    import(s);
}

void _HttpHeaderContentDisposition::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(parameter == nullptr) {
            //type = directive;
            if(directive->equalsIgnoreCase("inline")) {
                type = Inline;
            } else if(directive->equalsIgnoreCase("attachmemt")) {
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

String _HttpHeaderContentDisposition::toString() {
    String content = nullptr;

    switch(type) {
        case Inline:
            content = createString("inline");
        break;

        case FormData:
            content = createString("form-data");
        break;

        case Attachment:
            content = createString("attachment");
        break;

        default:
            LOG(ERROR)<<"Content-Disposition toString,invalid params";
        break;
    }

    if(name == nullptr && filename == nullptr) {
        return content;
    }

    if(name != nullptr) {
        content->append("; name=\"",name,"\"");
    }

    if(filename != nullptr) {
        content->append("; filename=\"",filename,"\"");
    }

    return content;
}

}
