#include "Runnable.hpp"

namespace obotcha {

void _Runnable::setPriority(int p) {
    priority = p;
}

int _Runnable::getPriority() {
    return priority;
}

void _Runnable::setDelay(int p) {
    delay = p;
}

int _Runnable::getDelay() {
    return delay;
}

} // namespace obotcha
