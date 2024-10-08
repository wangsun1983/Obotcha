#ifndef __OBOTCHA_HTTP_HEADER_DNT_HPP__
#define __OBOTCHA_HTTP_HEADER_DNT_HPP__

#include "Object.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderDnt) {

public:
    _HttpHeaderDnt() = default;
    explicit _HttpHeaderDnt(String);

    void load(String);

    void set(int);

    int get() const;

    String toString() override;

private:
    int dnt = -1;
};

}
#endif
