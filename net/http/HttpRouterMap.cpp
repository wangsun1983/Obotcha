#include "HttpRouterMap.hpp"

using namespace obotcha;

_HttpRouterNode::_HttpRouterNode(String segment,HttpRouter router) {
    mSegment = segment;
    mRouter = router;
    mNextNodes = createHashMap<String,HttpRouterNode>();
}

_HttpRouterMap::_HttpRouterMap() {
    mRoots = createHashMap<String,HttpRouterNode>();
}

void _HttpRouterMap::addRouter(HttpRouter r) {
    String path = r->getPath();
    ArrayList<String>segments = path->split("/");
    ListIterator<String> iterator = segments->getIterator();
    HashMap<String,HttpRouterNode> current = mRoots;
    HttpRouterNode node = nullptr;
    while(iterator->hasValue()) {
        String segment = iterator->getValue();
        node = current->get(segment);
        if(node == nullptr) {
            node = createHttpRouterNode(segment,nullptr);
            printf("put node is %s \n",segment->toChars());
            current->put(segment,node);
        }
        current = node->mNextNodes;
        iterator->next();
    }

    node->mRouter = r;
    printf("add node is %p \n",node.get_pointer());
}

HttpRouter _HttpRouterMap::findRouter(String path,HashMap<String,String> params) {
    ArrayList<String>segments = path->split("/");
    return _findRouter(segments,0,this->mRoots,params);
}

HttpRouter _HttpRouterMap::_findRouter(ArrayList<String> &segments,
                                      int segmentStartIndex,
                                      HashMap<String,HttpRouterNode> searchNode,
                                      HashMap<String,String> &result) {

    printf("find segmentStartIndex is %d\n",segmentStartIndex);
    String segment = segments->get(segmentStartIndex);
    printf("find segment is %s \n",segment->toChars());
    HttpRouterNode node = searchNode->get(segment);
    HttpRouter router = nullptr;
    if(node != nullptr) {
        segmentStartIndex++;
        if(segmentStartIndex == segments->size()) {
            return node->mRouter;
        }

        printf("find router trace1 segment is %s\n",segment->toChars());
        router = _findRouter(segments,segmentStartIndex,node->mNextNodes,result);
        printf("find router trace1_1 segment is %s\n",segment->toChars());
        if(router != nullptr) {
            return router;
        }
        printf("find router trace2 segment is %s\n",segment->toChars());
    } else {
        printf("find param!!! \n");
        MapIterator<String,HttpRouterNode> mapIterator = searchNode->getIterator();
        while(mapIterator->hasValue()) {
            String key = mapIterator->getKey();
            printf("find param,key is %s!!! \n",key->toChars());
            if(key->charAt(0) == ':') {
                //maybe this is the right node
                String paramTag = key->subString(0,key->size() - 1);
                String paramValue = segment;
                HashMap<String,String> tempResult = createHashMap<String,String>();
                tempResult->put(paramTag,paramValue);
                node = mapIterator->getValue();
                printf("find param,may be right \n");
                if(segmentStartIndex == segments->size()-1) {
                    //TODO add hashmap
                    return node->mRouter;
                }

                router = _findRouter(segments,segmentStartIndex+1,node->mNextNodes,tempResult);
                printf("find param,may be right0_1 \n");
                if(router != nullptr) {
                    printf("find param!!!!,hahaha,node is %p,segment is %s\n",node.get_pointer(),segment->toChars());
                    if(router == nullptr) {
                        printf("woqu,find empty!!! \n");
                    } else {
                        printf("aha,not empty!!! \n");
                    }
                    //TODO add hashmap
                    return router;
                }
                printf("find param,may be right trace1,segment is %s \n",segment->toChars());
            }
            mapIterator->next();
        }
    }
    printf("return nullptr!!!!!,segment is %s \n",segment->toChars());
    return nullptr;
}

