#include "HttpHeaderVia.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"
#include "Log.hpp"

namespace obotcha {

_HttpHeaderVia::_HttpHeaderVia(String s) {
    load(s);
}

void _HttpHeaderVia::jumpSpace(const char *p,size_t &i,size_t size) const {
    while(p[i] == ' ' && i < size && p[i] != ',') {
        i++;
    }
}

void _HttpHeaderVia::load(String s) {
    String value = s->trim();
    vias->clear();
    const char *p = value->toChars();
    size_t start = 0;
    size_t size = value->size();
    int status = ParseVersion;
    HttpHeaderViaItem item = nullptr;

    for(size_t i = 0;i < size;i++) {
        if(p[i] == '/' || p[i] == ' ' ||p[i] == '.' ||p[i] ==':' || p[i] == ',' || i == size - 1) {
            switch(status) {
                case ParseVersion: {
                    if(p[i] == '/') {
                        item = createHttpHeaderViaItem();
                        item->protocol = createString(p,start,i-start);
                        i++;
                        jumpSpace(p,i,size);
                        start = i;
                    } else if(p[i] == ' ' || p[i] == ',') {
                        if(item == nullptr) {
                            item = createHttpHeaderViaItem();
                        }
                        item->version = createString(p,start,i-start);
                        i++;
                        jumpSpace(p,i,size);
                        start = i;
                        status = ParseDect;
                    }
                }
                break;

                case ParseDect:{
                    if(p[i] == '.' || p[i] == ':') {
                        status = ParseUrl;
                    } else if(p[i] == ',') {
                        item->pseudonym = createString(p,start,i-start);
                        vias->add(item);
                        i++;
                        jumpSpace(p,i,size);
                        start = i;
                        item = nullptr;
                        status = ParseVersion;
                    } else if(i == size - 1) {
                        item->pseudonym = createString(p,start,i - start + 1);
                        vias->add(item);
                        return;
                    }
                }
                break;

                case ParseUrl: {
                    if(p[i] == ',') {
                        String url = createString(p,start,i-start);
                        item->url = createHttpUrl(url);
                        vias->add(item);
                        jumpSpace(p,i,size);
                        start = i;
                        item = nullptr;
                        status = ParseVersion;
                    } else if(i == size - 1) {
                        String url = createString(p,start,i-start + 1);
                        item->url = createHttpUrl(url);
                        vias->add(item);
                        return;
                    }
                }
                break;

                default:
                    LOG(ERROR)<<"HttpHeaderVia,load unknow status:"<<status;
                break;
            }
        }
    }
}

ArrayList<HttpHeaderViaItem> _HttpHeaderVia::get() const {
    return vias;
}

void _HttpHeaderVia::add(String protocol,String version,String url,String pseudonym) {
    HttpHeaderViaItem item = createHttpHeaderViaItem();
    item->protocol = protocol;
    item->version = version;
    if(url != nullptr) {
        item->url = createHttpUrl(url);
    }
    item->pseudonym = pseudonym;
    vias->add(item);
}

String _HttpHeaderVia::toString() {
    StringBuffer via = createStringBuffer();
    ForEveryOne(item,vias) {
        if(item->protocol != nullptr) {
            via->append(item->protocol,"/",item->protocol,", ");
        }

        if(item->version != nullptr) {
            via->append(item->version," ");
        }

        if(item->url != nullptr) {
            via->append(item->url->toString()," ");
        }

        if(item->pseudonym != nullptr) {
            via->append(item->pseudonym," ");
        }

        via->crop(0,via->size() - 1);
        via->append(", ");
    }

    return via->toString(0,via->size() - 2);
}

}
