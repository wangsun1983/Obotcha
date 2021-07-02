
#include "HttpResponseEntity.hpp"

namespace obotcha {

int _HttpResponseEntity::getStatus() {
    return mStatus;
}

TextContent _HttpResponseEntity::getContent() {
    return mContent;
}

}
