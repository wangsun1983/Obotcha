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

template<typename T, typename U>
bool instanceOf(sp<U> a) {
    T b;
    return (dynamic_cast<decltype(b.get_pointer())>(a.get_pointer()) != nullptr);
}

}
};


#endif
