#ifndef __OBOTCHA_UUID_HPP__
#define __OBOTCHA_UUID_HPP__

#include "uuid.h"

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(UUID) {
public:
    enum class Type {
        Random = 0,
        Time,
        TimeSafe,
    };

    explicit _UUID(Type type = Type::Random);
    String generate() const;

private:
    _UUID::Type mType;
};

} // namespace obotcha
#endif