#include <string.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "String.hpp"
#include "HashMap.hpp"
#include "HttpUrlParser.hpp"
#include "http_parser.h"
#include "HttpUrl.hpp"

namespace obotcha {

HttpUrl _HttpUrlParser::parseUrl(String urlstring) {
    struct http_parser_url u;
    const char *url = urlstring->toChars();
    if(0 == http_parser_parse_url(url, urlstring->size(), 0, &u)) {
        HttpUrl urlData = createHttpUrl();
        if(u.field_set & (1 << UF_PORT)) {
            urlData->setPort(u.port);
        } else {
            urlData->setPort(80);
        }

        if(u.field_set & (1 << UF_HOST)) {
            urlData->setHost(createString(url,u.field_data[UF_HOST].off,u.field_data[UF_HOST].len));
        }

        if(u.field_set & (1 << UF_PATH)) {
            //httpc->path = (char*)malloc(u.field_data[UF_PATH].len + 1);
            //strncpy(httpc->path, url+u.field_data[UF_PATH].off, u.field_data[UF_PATH].len);
            //httpc->path[u.field_data[UF_PATH].len] = 0;
            urlData->setPath(createString(url,u.field_data[UF_PATH].off,u.field_data[UF_PATH].len));
            printf("getPath is %s \n",urlData->getPath()->toChars());
        }

        if(u.field_set & (1 << UF_SCHEMA)) {
            //httpc->path = (char*)malloc(u.field_data[UF_PATH].len + 1);
            //strncpy(httpc->path, url+u.field_data[UF_PATH].off, u.field_data[UF_PATH].len);
            //httpc->path[u.field_data[UF_PATH].len] = 0;
            urlData->setSchema(createString(url,u.field_data[UF_SCHEMA].off,u.field_data[UF_SCHEMA].len));
        }

        if(u.field_set & (1 << UF_FRAGMENT)) {
            //httpc->path = (char*)malloc(u.field_data[UF_PATH].len + 1);
            //strncpy(httpc->path, url+u.field_data[UF_PATH].off, u.field_data[UF_PATH].len);
            //httpc->path[u.field_data[UF_PATH].len] = 0;
            urlData->setFragment(createString(url,u.field_data[UF_FRAGMENT].off,u.field_data[UF_FRAGMENT].len));
            printf("getFragment is %s \n",urlData->getFragment()->toChars());
        }

        if(u.field_set & (1 << UF_USERINFO)) {
            //httpc->path = (char*)malloc(u.field_data[UF_PATH].len + 1);
            //strncpy(httpc->path, url+u.field_data[UF_PATH].off, u.field_data[UF_PATH].len);
            //httpc->path[u.field_data[UF_PATH].len] = 0;
            urlData->setPath(createString(url,u.field_data[UF_USERINFO].off,u.field_data[UF_USERINFO].len));
        }

        if(u.field_set & (1 << UF_QUERY)) {
            //char * query = (char*)malloc(u.field_data[UF_QUERY].len + 1);
            //strncpy(query, url+u.field_data[UF_QUERY].off, u.field_data[UF_QUERY].len);
            //query[u.field_data[UF_QUERY].len] = 0;
            String query = createString(url,u.field_data[UF_QUERY].off,u.field_data[UF_QUERY].len);
            urlData->setQuery(parseQuery(query));
            //printf("query is %s \n",query->toChars());
            //ArrayList<HttpQuery> list = urlData->getQuery();
            //int size = list->size();
            //for(int index = 0; index < size;index++) {
            //    HttpQuery q = list->get(index);
            //    printf("q name is %s ; value is %s \n",q->getName()->toChars(),q->getValue()->toChars());
            //}
            //urlData->setPath(createString(url,url + u.field_data[UF_USERINFO].off,u.field_data[UF_USERINFO].len));
        }
        return urlData;
    }
    return nullptr;
}

ArrayList<HttpQuery> _HttpUrlParser::parseQuery(String query) {
    ArrayList<HttpQuery> mResult = createArrayList<HttpQuery>();
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
                //printf("parseQuery value is %s,start is %d,index is %d p is %s\n",value->toChars(),start,index,&p[start]);
                start = index;
                HttpQuery q = createHttpQuery(name,value);
                mResult->add(q);
                start = ++index;
                continue;
            }

            case '=': {
                //name end
                name = createString(&p[start],0,index - start);
                //printf("parseQuery name is %s ,start is %d,index is %d\n",name->toChars(),start,index);
                start = ++index;
                continue;
            }

            default:
            break;
        }

        index++;
    }

    value = createString(&p[start],0,index - start);
    HttpQuery q = createHttpQuery(name,value);
    mResult->add(q);

    return mResult;
}

}
