#include <thread>
#include <mutex>

#include "FilaCroutineManager.hpp"
#include "Log.hpp"

namespace obotcha {

FilaCroutineManager _FilaCroutineManager::mInstance = nullptr;

FilaCroutineManager _FilaCroutineManager::getInstance() {
   static std::once_flag s_flag;
   std::call_once(s_flag, [&]() {
        _FilaCroutineManager *p = new _FilaCroutineManager();
        mInstance = AutoClone(p);
    });

    return mInstance;
}

_FilaCroutineManager::_FilaCroutineManager() {
    croutines = createThreadLocal<FilaCroutine>();
    conditionMaps = createHashMap<FilaCondition,HashSet<FilaCroutine>>();
}

void _FilaCroutineManager::addWaitCondition(FilaCondition f) {
    auto croutine = croutines->get();
    if(croutine == nullptr) {
      LOG(ERROR)<<"FilaCroutineManager addWaitCondition,croutine is null";
      return;
    }
    HashSet<FilaCroutine> waitSets = conditionMaps->get(f);
    if(waitSets == nullptr) {
      waitSets = createHashSet<FilaCroutine>();
      conditionMaps->put(f,waitSets);
    }
    
    waitSets->add(croutine);
}

HashSet<FilaCroutine> _FilaCroutineManager::getWaitCroutine(FilaCondition f) {
    return conditionMaps->get(f);
}

void _FilaCroutineManager::removeWaitCondition(FilaCondition) {
    //TODO
}

void _FilaCroutineManager::addCroutine(FilaCroutine c) {
    croutines->set(c);
}

void _FilaCroutineManager::removeFilaCroutine() {
  //TODO
}


} // namespace obotcha
