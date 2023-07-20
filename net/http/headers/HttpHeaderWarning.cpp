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

_HttpHeaderWarning::_HttpHeaderWarning() {
    code = -1;
    agent = nullptr;
    text = nullptr;
    date = nullptr;
}

_HttpHeaderWarning::_HttpHeaderWarning(String s) {
    load(s);
}

void _HttpHeaderWarning::jumpSpace(const char *p,int &i,int size) {
    while(p[i] == ' ' && i < size) {
        i++;
    }
}

void _HttpHeaderWarning::load(String s) {
    String value = s->trim();
    int start = 0;
    int size = value->size();
    int status = ParseCode;
    const char *p = value->toChars();

    int fullText = 0;

    for(int i = 0;i < size;i++) {
        if(p[i] == ' ' || i == size - 1 || p[i] == '\"') {
            switch(status) {
                case ParseCode: {
                    String code = createString(p,start,i - start);
                    this->code = code->toBasicInt();
                    jumpSpace(p,i,size);
                    status = ParseAgent;
                    start = i;
                }
                break;

                case ParseAgent: {
                    this->agent = createString(p,start,i - start); //remove ""
                    jumpSpace(p,i,size);
                    if(p[i] == '\"') {
                        status = ParseText;
                        start = i + 1;
                    } else {
                        return;
                    }
                }
                break;

                case ParseText: {
                    if(p[i] == '\"') {
                        this->text = createString(p,start,i - start); //remove ""
                        i++;

                        jumpSpace(p,i,size);
                        if(p[i] == '\"') {
                            status = ParseDate;
                            start = i + 1;
                        } else {
                            return;
                        }
                    }
                }
                break;

                case ParseDate: {
                    if(p[i] == '\"') {
                        String date = createString(p,start,i - start); //remove ""
                        this->date = createHttpDate(date);
                        jumpSpace(p,i,size);
                        return;
                    }
                }
                break;
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

int _HttpHeaderWarning::getCode() {
    return code;
}

String _HttpHeaderWarning::getAgent() {
    return agent;
}

String _HttpHeaderWarning::getText() {
    return text;
}

HttpDate _HttpHeaderWarning::getDateTime() {
    return date;
}

String _HttpHeaderWarning::toString() {
    StringBuffer warning = createStringBuffer();
    if(code != -1) {
        warning->append(createString(code)," ");
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
