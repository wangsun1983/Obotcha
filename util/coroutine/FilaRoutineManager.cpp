#include <thread>
#include <mutex>

#include "FilaRoutineManager.hpp"
#include "Log.hpp"

namespace obotcha {

FilaRoutineManager _FilaRoutineManager::mInstance = nullptr;

FilaRoutineManager _FilaRoutineManager::getInstance() {
   static std::once_flag s_flag;
   std::call_once(s_flag, [&]() {
        _FilaRoutineManager *p = new _FilaRoutineManager();
        mInstance = AutoClone(p);
    });

    return mInstance;
}

_FilaRoutineManager::_FilaRoutineManager() {
    croutines = createThreadLocal<FilaRoutine>();
    conditionMaps = createHashMap<FilaCondition,HashSet<FilaRoutine>>();
}

void _FilaRoutineManager::addWaitCondition(FilaCondition f) {
    auto croutine = croutines->get();
    if(croutine == nullptr) {
      LOG(ERROR)<<"FilaRoutineManager addWaitCondition,croutine is null";
      return;
    }
    HashSet<FilaRoutine> waitSets = conditionMaps->get(f);
    if(waitSets == nullptr) {
      waitSets = createHashSet<FilaRoutine>();
      conditionMaps->put(f,waitSets);
    }
    
    waitSets->add(croutine);
}

HashSet<FilaRoutine> _FilaRoutineManager::getWaitCroutine(FilaCondition f) {
    return conditionMaps->get(f);
}

void _FilaRoutineManager::removeWaitCondition(FilaCondition) {
    //TODO
}

void _FilaRoutineManager::addCroutine(FilaRoutine c) {
    croutines->set(c);
}

void _FilaRoutineManager::removeFilaRoutine() {
  //TODO
}


} // namespace obotcha
