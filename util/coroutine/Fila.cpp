#include "co_routine_inner.h"
#include "co_routine.h"

#include "Fila.hpp"
#include "Thread.hpp"
#include "TimeWatcher.hpp"
#include "InterruptedException.hpp"

namespace obotcha {

int _Fila::Sleep(long interval) {
    if(GetCurrThreadCo() != nullptr) {
        TimeWatcher watcher = nullptr;
        if(interval != st(Concurrent)::kWaitForEver) {
            watcher = createTimeWatcher();
            watcher->start();
        }

        int ret = poll(nullptr,0,interval);
        auto current = st(Thread)::Current();

        if(current != nullptr 
            && current->getStatus() == st(Concurrent)::Status::Interrupt
            && watcher != nullptr
            && watcher->stop() < (interval - 10)) {
            Trigger(InterruptedException,"interrupt")
        }

        return ret;
    } 
    
    st(Thread)::Sleep(interval);
    return 0;
}

} // namespace obotcha