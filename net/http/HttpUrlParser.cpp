#include <string.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "String.hpp"
#include "HashMap.hpp"
#include "HttpUrlParser.hpp"
#include "HttpUrl.hpp"
#include "HttpHeader.hpp"

namespace obotcha {

String _HttpUrlParser::HttpScheme = createString("http");
String _HttpUrlParser::HttpsScheme = createString("https");

HttpUrl _HttpUrlParser::parseUrl(String url) {
    const char *input = url->toChars();
    //printf("parseUrl url is %s \n",url->toChars());
    int size = url->size();
    int index = 0;
    int start = 0;
    int status = Scheme;
    HttpUrl urlData = createHttpUrl();
    urlData->setRawUrl(url);
    bool userParsed = false;

    while(index < size) {
        //printf("input is %c \n",input[index]);

        switch(status) {
            case Scheme:{
                if(input[index] == ':') {
                    String scheme_str = createString(input,start,index - start);
                    urlData->setSchema(scheme_str);
                    //printf("scheme is %s \n",scheme_str->toChars());
                    index++;
                    start = index;
                    status = Slash;
                    continue;
                } else if(input[index] == '/') {
                    index++;
                    start = index;
                    status = PathOrQuery;
                    continue;
                }
                index++;
                continue;
            }

            case Slash: {
                if(input[index] == '/' || input[index] == '\\') {
                    index++;
                } else {
                    status = AuthorityOrHost;
                }
                start = index;
                continue;
            }

            case AuthorityOrHost: {
                if(input[index] == '@') {
                    //check username/password
                    String authority = createString(input,start,index - start);
                    ArrayList<String> list = authority->split(":");
                    if(list == nullptr) {
                        urlData->setUser(authority);
                    } else if(list->size() == 2) {
                        urlData->setUser(list->get(0));
                        urlData->setPassword(list->get(1));
                    } 

                    status = AuthorityOrHost;
                    userParsed = true;
                    index++;
                    start = index;
                    continue;
                } else if(input[index] == '/') {
                    String host = createString(input,start,index - start);
                    ArrayList<String> list = host->split(":");
                    if(list == nullptr) {
                        urlData->setHost(host);
                    } else if(list->size() == 2) {
                        urlData->setHost(list->get(0));
                        urlData->setPort(list->get(1)->toBasicInt());
                    }
                    
                    status = PathOrQuery;
                    index++;
                    start = index;
                    continue;
                } else if(input[index] == '?') {
                    String host = createString(input,start,index - start);
                    ArrayList<String> list = host->split(":");
                    if(list == nullptr) {
                        urlData->setHost(host);
                    } else if(list->size() == 2) {
                        urlData->setHost(list->get(0));
                        urlData->setPort(list->get(1)->toBasicInt());
                    }

                    String query = createString(input,index + 1,size - index - 1);
                    list = query->split("#");
                    if(list == nullptr) {
                        parseQuery(urlData,query);
                        urlData->setRawQuery(query);
                    } else {
                        parseQuery(urlData,list->get(0));
                        urlData->setRawQuery(list->get(0));
                        urlData->setFragment(list->get(1));
                    }
                    return urlData;
                }
                index++;
                continue;
            }

            case PathOrQuery: {
                if(input[index] == '?') {
                    String path = createString(input,start,index - start);
                    urlData->setPath(path);
                    index++;
                    start = index;
                    String query = createString(input,start,size - start);
                    ArrayList<String> list = query->split("#");
                    if(list == nullptr) {
                        parseQuery(urlData,query);
                        urlData->setRawQuery(query);
                    } else {
                        parseQuery(urlData,list->get(0));
                        urlData->setRawQuery(list->get(0));
                        urlData->setFragment(list->get(1));
                    }
                    return urlData;
                }
                index++; 
                continue;
            }
        }
    }

    if(size == 1) {
        //only /
        urlData->setPath(url);
    } else {
        switch(status) {
            case PathOrQuery: {
                    String data = createString(input,start,size - start);
                    urlData->setPath(data);
            }
            break;

            case AuthorityOrHost: {
                String host = createString(input,start,index - start);
                    ArrayList<String> list = host->split(":");
                    if(list == nullptr) {
                        urlData->setHost(host);
                    } else if(list->size() == 2) {
                        urlData->setHost(list->get(0));
                        urlData->setPort(list->get(1)->toBasicInt());
                    }
            }
            break;
        }
    }
    return urlData;
}

//wangsl

void _HttpUrlParser::parseQuery(HttpUrl url,String query) {
    //HashMap<String,String> mResult = createHashMap<String,String>();
    const char *p = query->toChars();
    int index = 0;
    int start = 0;
    int size = query->size();
    int status = 0;
    String value;
    String name;
    while(index < size) {
        switch(p[index]) {
            case '&': {
                //value end
                value = createString(&p[start],0,index - start);
                url->addQuery(name,value);
                start = ++index;
                continue;
            }

            case '=': {
                //name end
                name = createString(&p[start],0,index - start);
                start = ++index;
                continue;
            }

            default:
            break;
        }

        index++;
    }

    value = createString(&p[start],0,index - start);
    url->addQuery(name,value);
}

}
