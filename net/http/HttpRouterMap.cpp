#include "HttpRouterMap.hpp"

using namespace obotcha;

_HttpRouterNode::_HttpRouterNode(String segment, HttpRouter router) {
    mSegment = segment;
    mRouter = router;
    mNextNodes = createHashMap<String, HttpRouterNode>();
    mParamTag = nullptr;
}

_HttpRouterMap::_HttpRouterMap() {
    mRoots = createHashMap<String, HttpRouterNode>();
}

void _HttpRouterMap::addRouter(HttpRouter r) {
    String path = r->getPath();
    ArrayList<String> segments = path->split("/");
    ListIterator<String> iterator = segments->getIterator();
    HashMap<String, HttpRouterNode> current = mRoots;
    HttpRouterNode node = nullptr;
    while (iterator->hasValue()) {
        String segment = iterator->getValue();
        node = current->get(segment);
        if (node == nullptr) {
            node = createHttpRouterNode(segment, nullptr);
            current->put(segment, node);
            node->mParamTag = segment->subString(1, segment->size() - 1);
        }
        current = node->mNextNodes;
        iterator->next();
    }

    node->mRouter = r;
}

HttpRouter _HttpRouterMap::findRouter(String path,
                                      HashMap<String, String> params) {
    ArrayList<String> segments = path->split("/");
    return _findRouter(segments, 0, this->mRoots, params);
}

HttpRouter
_HttpRouterMap::_findRouter(ArrayList<String> &segments, int segmentStartIndex,
                            HashMap<String, HttpRouterNode> searchNode,
                            HashMap<String, String> &result) {
    String segment = segments->get(segmentStartIndex);
    HttpRouterNode node = searchNode->get(segment);
    HttpRouter router = nullptr;
    if (node != nullptr) {
        segmentStartIndex++;
        if (segmentStartIndex == segments->size()) {
            return node->mRouter;
        }
        router =
            _findRouter(segments, segmentStartIndex, node->mNextNodes, result);
        if (router != nullptr) {
            return router;
        }
    } else {
        // check whether it is a query
        ArrayList<String> querySegments = segment->split("?");
        if (querySegments != nullptr && querySegments->size() == 2) {
            String queryTag = querySegments->get(0);
            String queryContent = querySegments->get(1);
            node = searchNode->get(queryTag);
            if (node != nullptr) {
                ArrayList<String> list = queryContent->split("#");

                if (list != nullptr) {
                    queryContent = list->get(0);
                }

                HashMap<String, String> queryResult = _parseQuery(queryContent);
                result->append(queryResult);
                return node->mRouter;
            }
        }

        MapIterator<String, HttpRouterNode> mapIterator =
            searchNode->getIterator();
        while (mapIterator->hasValue()) {
            String key = mapIterator->getKey();
            if (key->charAt(0) == ':') {
                // maybe this is the right node
                node = mapIterator->getValue();
                String paramTag = node->mParamTag;
                String paramValue = segment;
                HashMap<String, String> tempResult =
                    createHashMap<String, String>();
                tempResult->put(paramTag, paramValue);
                if (segmentStartIndex == segments->size() - 1) {
                    result->append(tempResult);
                    return node->mRouter;
                }

                router = _findRouter(segments, segmentStartIndex + 1,
                                     node->mNextNodes, tempResult);
                if (router != nullptr) {
                    result->append(tempResult);
                    return router;
                }
            }
            mapIterator->next();
        }
    }
    return nullptr;
}

HashMap<String, String> _HttpRouterMap::_parseQuery(String content) {

    HashMap<String, String> result = createHashMap<String, String>();
    const char *p = content->toChars();
    int index = 0;
    int start = 0;
    int size = content->size();
    int status = 0;
    String value;
    String name;
    while (index < size) {
        switch (p[index]) {
        case '&': {
            // value end
            value = createString(&p[start], 0, index - start);
            result->put(name, value);
            start = ++index;
            continue;
        }

        case '=': {
            // name end
            name = createString(&p[start], 0, index - start);
            start = ++index;
            continue;
        }

        default:
            break;
        }

        index++;
    }

    value = createString(&p[start], 0, index - start);
    result->put(name, value);
    return result;
}
