#include <thread>
#include <mutex>

#include "HPackStaticTable.hpp"
#include "HPackTableItem.hpp"

namespace obotcha {

List<HPackTableItem> _HPackStaticTable::STATIC_TABLE = nullptr;
HashMap<String,HPackTableItem> _HPackStaticTable::INDEX_TABLE = nullptr;

int _HPackStaticTable::MaxSameNameFieldIndex = 0;

_HPackStaticTable::_HPackStaticTable() {
    static std::once_flag s_flag;

    std::call_once(s_flag, []() {
        int count = 0;

#define INIT_STATIC_TABLE_ITEM_WITH_VALUE(index,vname,val) \
        HPackTableItem item_##index = createHPackTableItem();\
        item_##index->name = vname;\
        item_##index->value = val;\
        item_##index->id = index;\
        STATIC_TABLE[count] = item_##index;\
        count++;\

        STATIC_TABLE = createList<HPackTableItem>(IdMax);
        /*  1 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(1,":authority",nullptr)

        /*  2 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(2,":method","GET")

        /*  3 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(3,":method","POST")

        /*  4 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(4,":path","/")

        /*  5 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(5,":path","/index.html")

        /*  6 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(6,":scheme","http")

        /*  7 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(7,":scheme","https")

        /*  8 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(8,":status","200")

        /*  9 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(9,":status","204")

        /* 10 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(10,":status","206")

        /* 11 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(11,":status","304")

        /* 12 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(12,":status","400")

        /* 13 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(13,":status","404")

        /* 14 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(14,":status","500")

        /* 15 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(15,"accept-charset",nullptr)

        /* 16 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(16,"accept-encoding","gzip, deflate")

        /* 17 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(17,"accept-language",nullptr)

        /* 18 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(18,"accept-ranges",nullptr)

        /* 19 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(19,"accept",nullptr)

        /* 20 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(20,"access-control-allow-origin",nullptr)

        /* 21 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(21,"age",nullptr)

        /* 22 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(22,"allow",nullptr)

        /* 23 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(23,"authorization",nullptr)

        /* 24 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(24,"cache-control",nullptr)

        /* 25 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(25,"content-disposition",nullptr)

        /* 26 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(26,"content-encoding",nullptr)

        /* 27 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(27,"content-language",nullptr)

        /* 28 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(28,"content-length",nullptr)

        /* 29 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(29,"content-location",nullptr)

        /* 30 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(30,"content-range",nullptr)

        /* 31 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(31,"content-type",nullptr)

        /* 32 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(32,"cookie",nullptr)

        /* 33 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(33,"data",nullptr)

        /* 34 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(34,"etag",nullptr)

        /* 35 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(35,"expect",nullptr)

        /* 36 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(36,"expires",nullptr)

        /* 37 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(37,"from",nullptr)

        /* 38 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(38,"host",nullptr)

        /* 39 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(39,"if-match",nullptr)

        /* 40 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(40,"if-modified-since",nullptr)

        /* 41 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(41,"if-none-match",nullptr)

        /* 42 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(42,"if-range",nullptr)

        /* 43 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(43,"if-unmodified-since",nullptr)

        /* 44 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(44,"last-modified",nullptr)

        /* 45 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(45,"link",nullptr)

        /* 46 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(46,"location",nullptr)

        /* 47 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(47,"max-forwards",nullptr)

        /* 48 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(48,"proxy-authenticate",nullptr)

        /* 49 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(49,"proxy-authorization",nullptr)

        /* 50 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(50,"range",nullptr)

        /* 51 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(51,"referer",nullptr)

        /* 52 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(52,"refresh",nullptr)

        /* 53 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(53,"retry-after",nullptr)

        /* 54 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(54,"server",nullptr)

        /* 55 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(55,"set-cookie",nullptr)

        /* 56 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(56,"strict-transport-security",nullptr)

        /* 57 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(57,"transfer-encoding",nullptr)

        /* 58 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(58,"user-agent",nullptr)

        /* 59 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(59,"vary",nullptr)

        /* 60 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(60,"via",nullptr)

        /* 61 */ INIT_STATIC_TABLE_ITEM_WITH_VALUE(61,"www-authenticate",nullptr)

#undef INIT_STATIC_TABLE_ITEM_WITH_VALUE

        //init index map
        INDEX_TABLE = createHashMap<String,HPackTableItem>();
        for(int i = 0;i<IdMax - 1;i++) {
            String tag = STATIC_TABLE[i]->name;
            if(STATIC_TABLE[i]->value != nullptr) {
                tag = tag->append(STATIC_TABLE[i]->value);
            }
            INDEX_TABLE->put(tag,STATIC_TABLE[i]);
        }

        /**
        * Returns the last position in the array that contains multiple
        * fields with the same name. Starting from this position, all
        * names are unique.
        */
        auto length = STATIC_TABLE->size();
        HPackTableItem cursor = getEntry(length - 1);
        for (auto index = length - 1; index != 0; index--) {
            HPackTableItem entry = getEntry(index);
            if (st(String)::Equals(entry->name,cursor->name)) {
                MaxSameNameFieldIndex = index + 1;
            } else {
                cursor = entry;
            }
        }

        MaxSameNameFieldIndex = length;
    });
}

HPackTableItem _HPackStaticTable::get(int id) const {
    if(id > IdMax || id < 1) {
        return nullptr;
    }

    return STATIC_TABLE[id - 1];
}

HPackTableItem _HPackStaticTable::get(String tag) const {
    return INDEX_TABLE->get(tag);
}

HPackTableItem _HPackStaticTable::get(String name,String val) const {
    HPackTableItem item = INDEX_TABLE->get(name);
    if(item != nullptr) {
        if(item->value == val) {
            return item;
        }

        if(st(String)::Equals(item->value,val)) {
            return item;
        }
    }

    return nullptr;
}

int _HPackStaticTable::getIndexInsensitive(String name, String value) {
    auto id = getIndex(name,value);
    if(id == -1) {
        return -1;
    }
    // Compare values for the first name match
    HPackTableItem entry = getEntry(id);
    if (entry != nullptr && 
        st(String)::Equals(value, entry->value)) {
        return id;
    }

    // Note this assumes all entries for a given header field are sequential.
    id++;

    // Note this assumes all entries for a given header field are sequential.
    while (id <= MaxSameNameFieldIndex) {
        entry = getEntry(id);
        if (!st(String)::Equals(name, entry->name)) {
            // As far as fields with the same name are placed in the table sequentially
            // and INDEX_BY_NAME returns index of the fist position, - it's safe to
            // exit immediately.
            return -1;
        }
        if (st(String)::Equals(value, entry->value)) {
            return id;
        }
        id++;
    }
    return -1;
}

size_t _HPackStaticTable::size() {
    return STATIC_TABLE->size();
}

HPackTableItem _HPackStaticTable::getEntry(int index) {
    return STATIC_TABLE[index - 1];
}

/**
 * Returns the lowest index value for the given header field name in the static table. Returns
 * -1 if the header field name is not in the static table.
 */
int _HPackStaticTable::getIndex(String name,String value) {
    String tag = name;
    if(value != nullptr) {
        tag = tag->append(value);
    }

    HPackTableItem item = INDEX_TABLE->get(tag);
    if (item == nullptr) {
        return -1;
    }
    return item->id;
}

}
