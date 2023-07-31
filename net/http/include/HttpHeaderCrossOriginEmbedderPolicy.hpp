#ifndef __OBOTCHA_HTTP_CROSS_ORIGIN_EMBEDDER_POLICY_HPP__
#define __OBOTCHA_HTTP_CROSS_ORIGIN_EMBEDDER_POLICY_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderCrossOriginEmbedderPolicy) {

public:
    _HttpHeaderCrossOriginEmbedderPolicy() = default;
    explicit _HttpHeaderCrossOriginEmbedderPolicy(String);

    void load(String);
    bool isUnSafeNone() const;
    bool isRequireCorp() const;
    void setAsUnSafeNone();
    void setAsRequireCorp();

    String toString();
    static const String UnSafeNone;
    static const String RequireCorp;

private:
    //String policy;
    enum CorpType {
        TypeUnSafeNone = 0,
        TypeRequireCorp
    };

    int mType = -1;

};

}
#endif
