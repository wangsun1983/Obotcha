#include <string.h>

#include "OStdNew.hpp"

namespace obotcha {

void * zmalloc(uint32_t size) {
    void *data = malloc(size);
    memset(data,0,size);
    return data;
}

};
