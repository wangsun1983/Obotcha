#ifndef __OBOTCHA_HTTP_SESSION_HPP__
#define __OBOTCHA_HTTP_SESSION_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ConcurrentHashMap.hpp"
#include "ArrayList.hpp"
#include "System.hpp"

namespace obotcha {

//according javax.servlet.http.HttpSession
DECLARE_CLASS(HttpSession) {

public:
    static int kInfiniteDuration;
    
    _HttpSession(int maxInactiveInterval = 120);
    long getCreationTime();
    String getId();

    long getLastAccessedTime();

    void setMaxInactiveInterval(int interval);
    int getMaxInactiveInterval();

    void setAttribute(String name, Object value);
    void removeAttribute(String);

    template <typename T>
    T getAttribute(String name) {
        Object o = sessions->get(name);
        mLastAccessTime = st(System)::CurrentTimeMillis();
        return Cast<T>(o);
    }

    void invalidate();
    bool isNew();
  
    ArrayList<String> getAttributeNames();
    int size();

    bool isValid();

private:
    ConcurrentHashMap<String,Object> sessions;
    long mCreationTime;
    String mId;
    long mLastAccessTime;
    int mMaxInactiveInterval;
    bool mIsValid;

};

}
#endif
