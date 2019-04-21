#ifndef __CALLABLE_H__
#define __CALLABLE_H__

namespace obotcha {

DECLARE_SIMPLE_CLASS(Callable)  {
public:
    virtual void call() = 0;  
};

}
#endif