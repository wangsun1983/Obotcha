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

HashMap<String,String> _HttpUrlParser::parseUrl(String urlstring) {
    struct http_parser_url u;
    const char *url = urlstring->toChars();
    if(0 == http_parser_parse_url(url, urlstring->size(), 0, &u)) {
        //TOOD
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
            urlData->setPath(createString(url,u.field_data[UF_FRAGMENT].off,u.field_data[UF_FRAGMENT].len));
        }

        if(u.field_set & (1 << UF_USERINFO)) {
            //httpc->path = (char*)malloc(u.field_data[UF_PATH].len + 1);  
            //strncpy(httpc->path, url+u.field_data[UF_PATH].off, u.field_data[UF_PATH].len);  
            //httpc->path[u.field_data[UF_PATH].len] = 0;  
            urlData->setPath(createString(url,u.field_data[UF_USERINFO].off,u.field_data[UF_USERINFO].len));
        }

        if(u.field_set & (1 << UF_QUERY)) {
            char * query = (char*)malloc(u.field_data[UF_QUERY].len + 1);  
            strncpy(query, url+u.field_data[UF_QUERY].off, u.field_data[UF_QUERY].len);  
            query[u.field_data[UF_QUERY].len] = 0;  
            printf("query is %s \n",query);
            //urlData->setPath(createString(url,url + u.field_data[UF_USERINFO].off,u.field_data[UF_USERINFO].len));
        }

    }
    return nullptr;
}

}

