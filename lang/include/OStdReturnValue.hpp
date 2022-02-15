#ifndef __OBOTCHA_STD_RETURN_VALUE_HPP__
#define __OBOTCHA_STD_RETURN_VALUE_HPP__
#include <tuple>
#include <type_traits>

namespace obotcha {
namespace ostd {

#define DefRet(...) std::tuple<__VA_ARGS__>
#define MakeRet(...) std::make_tuple(__VA_ARGS__)
#define FetchRet(...) std::tie(__VA_ARGS__)

}
};


#endif
