#ifndef __OBOTCHA_STD_INSTANCE_OF_HPP__
#define __OBOTCHA_STD_INSTANCE_OF_HPP__

#include <typeinfo>
#include "StrongPointer.hpp"

namespace obotcha {
namespace ostd {

/*
template<typename T, typename U>
class OInstanceConversation {
    private:
      static char Test(U);
      static int Test(...);
      static T MakeT();
    public:
      enum { exists = sizeof(Test(MakeT())) == sizeof(char) };
};
*/

template<typename T,typename U>
bool instanceOf(sp<U> a) {
    //return std::is_base_of<T,U>::value;
    return typeid(T) == typeid(*a.get_pointer());
}

#define IsInstance(PARENT,Y) ostd::instanceOf<_##PARENT>(Y)

}
};


#endif
