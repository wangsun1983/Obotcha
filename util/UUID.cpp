#include "UUID.hpp"

namespace obotcha {

_UUID::_UUID(_UUID::Type type):mType(type) { 
}

String _UUID::generate() const {
    uuid_t uuid1;
    switch (mType) {
        case _UUID::Type::Random:
            uuid_generate(uuid1);
            break;

        case _UUID::Type::Time:
            uuid_generate_random(uuid1);
            break;

        case _UUID::Type::TimeSafe:
            uuid_generate_time(uuid1);
            break;
    }

    char uuid1_str[37] = {0};
    uuid_unparse(uuid1, uuid1_str);
    return String::New(uuid1_str);
}

} // namespace obotcha