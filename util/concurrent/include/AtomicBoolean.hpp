/**
 * @file AtomicBoolean.hpp
 * @brief An bool value that may be updated atomically.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2022-10-19
 * @license none
 * @history
 */

#ifndef __OBOTCHA_ATOMIC_BOOLEAN_HPP__
#define __OBOTCHA_ATOMIC_BOOLEAN_HPP__

#include <atomic>

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(AtomicBoolean) {

  public:
    explicit _AtomicBoolean(bool val);

    void set(bool val);
    bool get() const;

  private:
    std::atomic_bool mValue;
};

} // namespace obotcha
#endif
