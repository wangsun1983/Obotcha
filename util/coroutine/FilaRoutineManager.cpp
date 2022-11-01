#include <thread>
#include <mutex>

#include "FilaRoutineManager.hpp"
#include "Log.hpp"

namespace obotcha {

FilaRoutineManager _FilaRoutineManager::mInstance = nullptr;

FilaRoutineManager _FilaRoutineManager::getInstance() {
   static std::once_flag s_flag;
   std::call_once(s_flag, [&]() {
        mInstance = AutoClone(new _FilaRoutineManager());
    });

    return mInstance;
}

_FilaRoutineManager::_FilaRoutineManager() {
    //routines = createThreadLocal<FilaRoutine>();
    conditionMaps = createHashMap<FilaCondition,ConcurrentHashSet<FilaRoutine>>();
}

void _FilaRoutineManager::addWaitCondition(FilaCondition f) {
    auto croutine = Cast<FilaRoutine>(st(Thread)::current());
    if(croutine == nullptr) {
      LOG(ERROR)<<"FilaRoutineManager addWaitCondition,croutine is null";
      return;
    }

    ConcurrentHashSet<FilaRoutine> waitSets = conditionMaps->get(f);
    if(waitSets == nullptr) {
      waitSets = createConcurrentHashSet<FilaRoutine>();
      conditionMaps->put(f,waitSets);
    }
    
    waitSets->add(croutine);
}

HashSet<FilaRoutine> _FilaRoutineManager::getWaitRoutine(FilaCondition f) {
    auto sets = conditionMaps->get(f);
    if(sets != nullptr) {
        return sets->toSet();
    }

    return nullptr;
}

void _FilaRoutineManager::removeWaitCondition(FilaCondition f) {
    conditionMaps->remove(f);
}

//void _FilaRoutineManager::addRoutine(FilaRoutine c) {
//    routines->set(c);
//}

//void _FilaRoutineManager::removeRoutine() {
//    routines->remove();
//}

//FilaRoutine _FilaRoutineManager::getRoutine() {
//    return routines->get();
//}

} // namespace obotcha
