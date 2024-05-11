#include "HttpHeaderWarning.hpp"
#include "StringBuffer.hpp"

namespace obotcha {
    
const int _HttpHeaderWarning::ResponseIsStale = 110;
const int _HttpHeaderWarning::RevalidationFailed = 111;
const int _HttpHeaderWarning::DisconnectedOperation = 112;
const int _HttpHeaderWarning::HeuristicExpiration = 113;
const int _HttpHeaderWarning::MiscellaneousWarning = 199;
const int _HttpHeaderWarning::TransformationApplied = 214;
const int _HttpHeaderWarning::PersistentMiscellaneousWarning = 299;

_HttpHeaderWarning::_HttpHeaderWarning(String s) {
    load(s);
}

void _HttpHeaderWarning::jumpSpace(const char *p,size_t &i,size_t size) const {
    while(p[i] == ' ' && i < size) {
        i++;
    }
}

void _HttpHeaderWarning::load(String s) {
    String value = s->trim();
    size_t start = 0;
    size_t size = value->size();
    _HttpHeaderWarning::ParseStatus status = _HttpHeaderWarning::ParseStatus::ParseCode;
    const char *p = value->toChars();

    for(size_t i = 0;i < size;i++) {
        if(p[i] == ' ' || i == size - 1 || p[i] == '\"') {
            switch(status) {
                case _HttpHeaderWarning::ParseStatus::ParseCode: {
                    String codestr = String::New(p,start,i - start);
                    this->code = codestr->toBasicInt();
                    jumpSpace(p,i,size);
                    status = _HttpHeaderWarning::ParseStatus::ParseAgent;
                    start = i;
                } break;

                case _HttpHeaderWarning::ParseStatus::ParseAgent: {
                    this->agent = String::New(p,start,i - start); //remove ""
                    jumpSpace(p,i,size);
                    if(p[i] == '\"') {
                        status = _HttpHeaderWarning::ParseStatus::ParseText;
                        start = i + 1;
                    } else {
                        return;
                    }
                } break;

                case _HttpHeaderWarning::ParseStatus::ParseText: {
                    if(p[i] == '\"') {
                        this->text = String::New(p,start,i - start); //remove ""
                        i++;

                        jumpSpace(p,i,size);
                        if(p[i] == '\"') {
                            status = _HttpHeaderWarning::ParseStatus::ParseDate;
                            start = i + 1;
                        } else {
                            return;
                        }
                    }
                } break;

                case _HttpHeaderWarning::ParseStatus::ParseDate: {
                    if(p[i] == '\"') {
                        String dateStr = String::New(p,start,i - start); //remove ""
                        this->date = HttpDate::New(dateStr);
                        jumpSpace(p,i,size);
                        return;
                    }
                } break;
            }
        }
    }
}

void _HttpHeaderWarning::setCode(int s) {
    this->code = s;
}

void _HttpHeaderWarning::setAgent(String s) {
    this->agent = s->trim();
}

void _HttpHeaderWarning::setText(String s) {
    this->text = s->trim();
}

void _HttpHeaderWarning::setDateTime(HttpDate s) {
    this->date = s;
}

int _HttpHeaderWarning::getCode() const {
    return code;
}

String _HttpHeaderWarning::getAgent() const {
    return agent;
}

String _HttpHeaderWarning::getText() const {
    return text;
}

HttpDate _HttpHeaderWarning::getDateTime() const {
    return date;
}

String _HttpHeaderWarning::toString() {
    StringBuffer warning = StringBuffer::New();
    if(code != -1) {
        warning->append(String::New(code)," ");
    }

    if(agent != nullptr) {
        warning->append(agent," ");
    }

    if(text != nullptr) {
        warning->append("\"",text,"\" ");
    }

    if(date != nullptr) {
        warning->append("\"",date->toString(),"\" ");
    }

    return warning->toString(0,warning->size() - 1);
}


}
