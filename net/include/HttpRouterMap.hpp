#ifndef __OBOTCHA_HTTP_ROUTER_MAP_HPP__
#define __OBOTCHA_HTTP_ROUTER_MAP_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpRouter.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpRouterNode) {
public:
    _HttpRouterNode(String segment,HttpRouter router);
    String mSegment;
    HttpRouter mRouter;
    HashMap<String,HttpRouterNode> mNextNodes;
    String mParamTag;//:id
};

DECLARE_SIMPLE_CLASS(HttpRouterMap) {
public:
    _HttpRouterMap();
    void addRouter(HttpRouter r);
    HttpRouter findRouter(String path,HashMap<String,String> params);
    

private:
    HttpRouter _findRouter(ArrayList<String> &segments,
                                      int segmentStartIndex,
                                      HashMap<String,HttpRouterNode> searchNode,
                                      HashMap<String,String> &result);
    
    HashMap<String,String> _parseQuery(String);
    
    HashMap<String,HttpRouterNode> mRoots;
};

}

#endif