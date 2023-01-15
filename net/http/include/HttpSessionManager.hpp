#ifndef __OBOTCHA_HTTP_SESSION_MANAGER_HPP__
#define __OBOTCHA_HTTP_SESSION_MANAGER_HPP__

#include "Object.hpp"
#include "ThreadScheduledPoolExecutor.hpp"
#include "HttpSession.hpp"
#include "ConcurrentHashMap.hpp"
#include "Future.hpp"

namespace obotcha {

DECLARE_CLASS(HttpSessionManager) {

public:
	static sp<_HttpSessionManager> getInstance();

	HttpSession get(String);
	void add(HttpSession);
	void remove(HttpSession);
	
	HttpSession createSession(int interval = 120);

	void refresh(String id);

private:
    static sp<_HttpSessionManager> mInstance;

	ThreadScheduledPoolExecutor mExecutor;
    _HttpSessionManager();

	ConcurrentHashMap<String,HttpSession> mSessions;
	ConcurrentHashMap<String,Future> mFutures;


};

}
#endif
