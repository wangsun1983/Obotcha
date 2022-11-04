#include "co_routine_inner.h"

#include "Fila.hpp"
#include "Thread.hpp"

namespace obotcha {

int _Fila::sleep(long interval) {
    if(GetCurrThreadCo() != nullptr) {
        return poll(nullptr,0,interval);
    } 
    
    st(Thread)::sleep(interval);
    return 0;
}

} // namespace obotcha