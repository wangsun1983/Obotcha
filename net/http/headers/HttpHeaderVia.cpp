#include "HttpHeaderVia.hpp"

namespace obotcha {

_HttpHeaderVia::_HttpHeaderVia() {
    vias = createArrayList<HttpHeaderViaItem>();
}

_HttpHeaderVia::_HttpHeaderVia(String s) {
    import(s);
}

void _HttpHeaderVia::jumpSpace(const char *p,int &i,int size) {
    while(p[i] == ' ' && i < size && p[i] != ',') {
        i++;
    }
}

void _HttpHeaderVia::import(String s) {
    String value = s->trim();
    const char *p = value->toChars();
    int start = 0;
    int size = value->size();
    int status = ParseVersion;
    HttpHeaderViaItem item = nullptr;

    for(int i = 0;i<size;i++) {
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
                        printf("url create success \n");
                        vias->add(item);
                        return;
                    }
                }
                break;
            }
        }
    }
}

ArrayList<HttpHeaderViaItem> _HttpHeaderVia::get() {
    return vias;
}

void _HttpHeaderVia::add(HttpHeaderViaItem item) {
    vias->add(item);
}

String _HttpHeaderVia::toString() {
    String via = "";
    auto iterator = vias->getIterator();
    while(iterator->hasValue()) {
        HttpHeaderViaItem item = iterator->getValue();
        if(item->protocol != nullptr) {
            via = via->append(item->protocol,"/",item->protocol,", ");
        }

        if(item->version != nullptr) {
            via = via->append(item->version," ");
        }

        if(item->url != nullptr) {
            via = via->append(item->url->toString()," ");
        }

        if(item->pseudonym != nullptr) {
            via = via->append(item->pseudonym," ");
        }

        via = via->subString(0,via->size() - 1)->append(", ");

        iterator->next();
    }

    return via->subString(0,via->size() - 2);
}

}