#include "UUID.hpp"

namespace obotcha {

_UUID::_UUID() {
    //uuid_generate(uuid1); 
    mType = Default;
}

_UUID::_UUID(int type) {
    mType = type;
}

String _UUID::generate() {
    uuid_t uuid1;
    switch(mType) {
        case Random:
        uuid_generate(uuid1);
        break;

        case Time:
        uuid_generate_random(uuid1);
        break;

        case TimeSafe:
        uuid_generate_time(uuid1);
        break;

        case Default:
        uuid_generate(uuid1);
        break;

        default:
        return nullptr;
    }

    char uuid1_str[37];
    uuid_unparse(uuid1, uuid1_str);
    return createString(uuid1_str);
}

}