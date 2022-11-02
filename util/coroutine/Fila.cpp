#include "Fila.hpp"

namespace obotcha {

int _Fila::sleep(long interval) {
    return poll(nullptr,0,interval);
}

} // namespace obotcha