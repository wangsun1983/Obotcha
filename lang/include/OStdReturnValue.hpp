#ifndef __OBOTCHA_STD_RETURN_VALUE_HPP__
#define __OBOTCHA_STD_RETURN_VALUE_HPP__

#include <tuple>
#include <type_traits>

#define DefRet(...) std::tuple<__VA_ARGS__>
#define MakeRet(...) std::make_tuple(__VA_ARGS__)
#define FetchRet(...) auto[__VA_ARGS__] //std::tie(__VA_ARGS__)


#endif
