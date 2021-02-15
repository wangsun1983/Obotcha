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
            urlData->setPath(createString(url,u.field_data[UF_PATH].off,u.field_data[UF_PATH].len));
        }

        if(u.field_set & (1 << UF_SCHEMA)) {
            urlData->setSchema(createString(url,u.field_data[UF_SCHEMA].off,u.field_data[UF_SCHEMA].len));
        }

        if(u.field_set & (1 << UF_FRAGMENT)) {
            urlData->setFragment(createString(url,u.field_data[UF_FRAGMENT].off,u.field_data[UF_FRAGMENT].len));
        }

        if(u.field_set & (1 << UF_USERINFO)) {
            String userInfo = createString(url,u.field_data[UF_USERINFO].off,u.field_data[UF_USERINFO].len);
            ArrayList<String> user = userInfo->split(":");

            if(user->size() == 2) {
                urlData->setUser(user->get(0));
                urlData->setPassword(user->get(1));
            } else {
                urlData->setUser(userInfo);
            }
        }

        if(u.field_set & (1 << UF_QUERY)) {
            String query = createString(url,u.field_data[UF_QUERY].off,u.field_data[UF_QUERY].len);
            parseQuery(urlData,query);
        }
        return urlData;
    }
    return nullptr;
}

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
