
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TcpClient.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "HttpParser.hpp"
#include "HttpHeader.hpp"
#include "System.hpp"
#include "HashMap.hpp"
#include "Integer.hpp"

using namespace obotcha;

int main() {
    
    int index = 0;
    long current = st(System)::currentTimeMillis();
    int i = 0;
    while(i < 100000) {
        for(int i = 0;i < Http_Header_Max;i++) {
            String str = st(HttpHeader)::getHeaderString(i);
            int headno = st(HttpHeader)::parseHttpHeader(str);
            if(headno != i) {
                printf("error ,index is %i,header is %s \n",i,str->toChars());
            }
        }
        i++;
    }
    printf("cost1 is %ld \n",st(System)::currentTimeMillis() - current);

    //start init
    HashMap<String,Integer>map = createHashMap<String,Integer>();
    for(int i = 0;i < Http_Header_Max;i++) {
        map->put(st(HttpHeader)::getHeaderString(i),createInteger(i));
    }

    current = st(System)::currentTimeMillis();
    i = 0;
    while(i < 100000) {
        for(int i = 0;i < Http_Header_Max;i++) {
            String str = st(HttpHeader)::getHeaderString(i);
            int headno = map->get(str)->toValue();
            if(headno != i) {
                printf("error ,index is %i,header is %s \n",i,str->toChars());
            }
        }
        i++;
    }
    printf("cost2 is %ld \n",st(System)::currentTimeMillis() - current);


    printf("OK \n");
    while(1) {}

}
