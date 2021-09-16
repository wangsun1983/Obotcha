#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <functional>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"
#include "Integer.hpp"
#include "JsonReader.hpp"
#include <vector>

using namespace obotcha;

DECLARE_CLASS(Address) {
public:
    String street;
    String city;
    String country;
    DECLARE_REFLECT_FIELD(Address,street,city,country)
};

DECLARE_CLASS(Link) {
public:
    String name;
    String url;
    DECLARE_REFLECT_FIELD(Link,name,url);
};

DECLARE_CLASS(PersonInfo) {
public:
    String name;
    String url;
    String page;
    Address address;
    bool isNonProfit;
    ArrayList<Link>links;
    DECLARE_REFLECT_FIELD(PersonInfo,name,url,page,address,isNonProfit,links)
};

void testReflect() {

    JsonReader reader = createJsonReader(createFile("abc.json"));
    JsonValue value = reader->get();

    PersonInfo info = createPersonInfo();
    value->reflectTo(info);

    printf("info name is %s \n",info->name->toChars());
    printf("info url is %s \n",info->url->toChars());
    printf("info page is %s \n",info->page->toChars());
    printf("info street is %s \n",info->address->street->toChars());
    printf("info city is %s \n",info->address->city->toChars());
    printf("info country is %s \n",info->address->country->toChars());
    if(info->isNonProfit) {
        printf("info isNonProfit is true \n");
    } else {
        printf("info isNonProfit is false \n");
    }

    if(info->links != nullptr) {
        printf("size is %d \n",info->links->size());
        ListIterator<Link> iterator = info->links->getIterator();
        while(iterator->hasValue()) {
            Link ll = iterator->getValue();
            printf("Link name is %s,url is %s \n",ll->name->toChars(),ll->url->toChars());
            iterator->next();
        }
    }
}
