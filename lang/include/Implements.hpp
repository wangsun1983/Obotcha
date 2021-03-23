#ifndef __OBOTCHA_IMPLEMENTS_H__
#define __OBOTCHA_IMPLEMENTS_H__

namespace obotcha {

#define FL_ARG_COUNT(...) FL_INTERNAL_ARG_COUNT_PRIVATE(0, ##__VA_ARGS__,\
	64, 63, 62, 61, 60, \
	59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
	49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
	39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
	29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
	19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
	 9,  8,  7,  6,  5,  4,  3,  2,  1,  0)

#define FL_INTERNAL_ARG_COUNT_PRIVATE(\
	 _0,  _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, \
	_10, _11, _12, _13, _14, _15, _16, _17, _18, _19, \
	_20, _21, _22, _23, _24, _25, _26, _27, _28, _29, \
	_30, _31, _32, _33, _34, _35, _36, _37, _38, _39, \
	_40, _41, _42, _43, _44, _45, _46, _47, _48, _49, \
	_50, _51, _52, _53, _54, _55, _56, _57, _58, _59, \
	_60, _61, _62, _63, _64, N, ...) N

#define _IMPLEMENTS_1(A) ,virtual public _##A
#define _IMPLEMENTS_2(A,B) ,virtual public _##A,virtual public _##B

#define IMPLEMENTS(...) IMPLEMENTS_FUNC_INNER(FL_ARG_COUNT(__VA_ARGS__),__VA_ARGS__)
#define IMPLEMENTS_FUNC_INNER(COUNT,...) IMPLEMENTS_FUNC_INNER_2(COUNT,__VA_ARGS__)
#define IMPLEMENTS_FUNC_INNER_2(COUNT,...) _IMPLEMENTS_##COUNT(__VA_ARGS__)

}
#endif
