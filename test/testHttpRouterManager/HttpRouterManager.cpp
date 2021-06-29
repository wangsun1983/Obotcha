
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HttpRouter.hpp"
#include "HttpRouterMap.hpp"
#include "HttpRouterManager.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyTrigger) IMPLEMENTS(RouterListener) {
public:
    Object onInvoke(HashMap<String,String> m) {
        auto iterator = m->getIterator();
        while(iterator->hasValue()) {
          String key = iterator->getKey();
          String value = iterator->getValue();
          printf("key is %s,value is %s \n",key->toChars(),value->toChars());
          iterator->next();
        }

        return nullptr;
    }
};

int main() {

    HttpRouter router1 = createHttpRouter(createString("abc/:id/tag/:name"),createMyTrigger());
    HttpRouter router1_1 = createHttpRouter(createString("abc/:id/sure/:age"),createMyTrigger());
    HttpRouter router1_2 = createHttpRouter(createString("abc2/sure/:age/:no"),createMyTrigger());
    HttpRouter router1_3 = createHttpRouter(createString("fff/sure/:age/link"),createMyTrigger());
    HttpRouter router1_4 = createHttpRouter(createString(":ff/case/:age/link"),createMyTrigger());

    HttpRouterManager manager = st(HttpRouterManager)::getInstance();

    manager->addRouter(st(HttpMethod)::Get,router1);
    manager->addRouter(st(HttpMethod)::Get,router1_1);
    manager->addRouter(st(HttpMethod)::Get,router1_2);
    manager->addRouter(st(HttpMethod)::Get,router1_3);
    manager->addRouter(st(HttpMethod)::Get,router1_4);
    
    

    HashMap<String,String> m = createHashMap<String,String>();
    //HttpRouter router2 = map->findRouter("abc/123/tag/wangsl",m);
    //HttpRouter router2 = map->findRouter("abc/123/sure/22",m);
    //HttpRouter router2 = map->findRouter("abc2/sure/1/3",m);
    //HttpRouter router2 = map->findRouter("fff/sure/21/link?no1=1&no2=2",m);
    //HttpRouter router2 = map->findRouter("fff/sure/44/link?no1=1&no2=2&no3=100",m);
    //HttpRouter router2 = manager->getRouter(st(HttpMethod)::Get,"fff/sure/44/link?no1=1&no2=2&no3=100",m);
    HttpRouter router2 = manager->getRouter(st(HttpMethod)::Get,"23/case/44/link?no1=1&no2=2&no3=100",m);

    if(router2 != nullptr) {
        printf("find one!!!,result size is %d \n",m->size());
        auto listener = router2->getListener();
        printf("listener addr is %p \n",listener.get_pointer());
        listener->onInvoke(m);
    } else {
        printf("find empty!!! \n");
    }



}
