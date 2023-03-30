#include "HttpHeaderServerTiming.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderServerTimingItem::_HttpHeaderServerTimingItem() {
    name = nullptr;
    dur = nullptr;
    desc = nullptr;
}

_HttpHeaderServerTiming::_HttpHeaderServerTiming() {
    lists = createArrayList<HttpHeaderServerTimingItem>();
}

_HttpHeaderServerTiming::_HttpHeaderServerTiming(String s):_HttpHeaderServerTiming(){
    import(s);
}

void _HttpHeaderServerTiming::import(String s) {
    String value = s->trim();
    HttpHeaderServerTimingItem item = nullptr;
    lists->clear();
    st(HttpHeaderContentParser)::import(s,[this,&item](String directive,String parameter) {
        if(parameter == nullptr) {
            if(item != nullptr) {
                lists->add(item);
            }

            item = createHttpHeaderServerTimingItem();
            item->name = directive;
        }  else {
            if(directive->equals("dur")) {
                item->dur = parameter;
            } else if(directive->equals("desc")) {
                item->desc = parameter;
            }
        }
    });

    lists->add(item); //last item
}

//void _HttpHeaderServerTiming::add(HttpHeaderServerTimingItem item) {
void _HttpHeaderServerTiming::add(String name,String dur,String desc) {
    HttpHeaderServerTimingItem item = createHttpHeaderServerTimingItem();
    item->name = name;
    item->dur = dur;
    item->desc = desc;
    lists->add(item);
}

ArrayList<HttpHeaderServerTimingItem> _HttpHeaderServerTiming::get() {
    return lists;
}

String _HttpHeaderServerTiming::toString() {
    StringBuffer timming = createStringBuffer();
    ForEveryOne(item,lists) {
        if(item->name != nullptr) {
            timming->append(item->name,";");
        }

        if(item->desc != nullptr) {
            timming->append("desc=\"",item->desc,"\";");
        }

        if(item->dur != nullptr) {
            timming->append("dur=",item->dur,";");
        }

        timming->subString(0,timming->size() - 1)->append(", ");
    }

    return timming->toString(0,timming->size() - 2);
}

}