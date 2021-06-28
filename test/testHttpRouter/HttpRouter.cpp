
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HttpRouter.hpp"
#include "HttpRouterMap.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyTrigger) IMPLEMENTS(RouterListener) {
public:    
    Object onTrigger(HashMap<String,String> map) {
        printf("hit!!!! \n");
    }
};

int main() {
    
    HttpRouterMap map = createHttpRouterMap();
    HttpRouter router = createHttpRouter(createString("abc/:id/tag/:name"),createMyTrigger());
    map->addRouter(router);

    HashMap<String,String> m = createHashMap<String,String>();
    HttpRouter router2 = map->findRouter("abc/123/tag/wangsl",m);

    if(router2 != nullptr) {
        printf("find one!!!,result size is %d \n",m->size());
    } else {
        printf("find empty!!! \n");
    }

}
