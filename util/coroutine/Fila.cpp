#include "co_routine_inner.h"
#include "co_routine.h"

#include "Fila.hpp"
#include "Thread.hpp"

namespace obotcha {

int _Fila::Sleep(long interval) {
    if(GetCurrThreadCo() != nullptr) {
        return poll(nullptr,0,interval);
    } 
    
    st(Thread)::Sleep(interval);
    return 0;
}

} // namespace obotcha