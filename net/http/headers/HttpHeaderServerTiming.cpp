#include "HttpHeaderServerTiming.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderServerTiming::_HttpHeaderServerTiming(String s) {
    load(s);
}

void _HttpHeaderServerTiming::load(String s) {
    String value = s->trim();
    HttpHeaderServerTimingItem item = nullptr;
    lists->clear();
    st(HttpHeaderContentParser)::load(s,[this,&item](String directive,String parameter) {
        if(parameter == nullptr) {
            if(item != nullptr) {
                lists->add(item);
            }

            item = createHttpHeaderServerTimingItem();
            item->name = directive;
        }  else {
            if(directive->sameAs("dur")) {
                item->dur = parameter;
            } else if(directive->sameAs("desc")) {
                item->desc = parameter;
            }
        }
    });

    lists->add(item); //last item
}

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

        timming->crop(0,timming->size() - 1);
        timming->append(", ");
    }

    return timming->toString(0,timming->size() - 2);
}

}