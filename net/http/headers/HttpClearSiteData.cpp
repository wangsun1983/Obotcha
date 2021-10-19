#include "HttpClearSiteData.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

const String _HttpClearSiteData::Cache = "cache";
const String _HttpClearSiteData::Cookies = "cookies";
const String _HttpClearSiteData::ExecutionContexts = "executionContexts";
const String _HttpClearSiteData::Storage = "storage";

_HttpClearSiteData::_HttpClearSiteData() {
    types = createArrayList<String>();
}

_HttpClearSiteData::_HttpClearSiteData(String v):_HttpClearSiteData() {
    import(v);
}

void _HttpClearSiteData::import(String v) {
     st(HttpHeaderContentParser)::import(v,[this](String directive,String parameter) {
        types->add(directive);
    });
}

void _HttpClearSiteData::addType(String v) {
    types->add(v);
}

ArrayList<String> _HttpClearSiteData::getTypes() {
    return types;
}

String _HttpClearSiteData::toString() {
    String type = "";
    auto iterator = types->getIterator();
    while(iterator->hasValue()) {
        type = type->append("\"",iterator->getValue(),"\",");
        iterator->next();
    }
    return type->subString(0,type->size() - 1);
}
}
