#ifndef __OBOTCHA_INSPECT_HPP__
#define __OBOTCHA_INSPECT_HPP__

#include "Object.hpp"

namespace obotcha {

#define Inspect(X,...) Inspect_Inner(X,GET_ARG_COUNT(__VA_ARGS__),__VA_ARGS__)
#define Inspect_Inner(X,Y,Z) Inspect_Convert(X,Y,Z)
#define Inspect_Convert(X,Y,Z) Inspect_##Y(X,Z)

#define Inspect_0(X) if(X) {return;}
#define Inspect_1(X,Y) if(X) {return Y;} 

} // namespace obotcha

#endif
