#ifndef __OBOTCHA_HTTP_CROSS_ORIGIN_EMBEDDER_POLICY_HPP__
#define __OBOTCHA_HTTP_CROSS_ORIGIN_EMBEDDER_POLICY_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderCrossOriginEmbedderPolicy) {

public:
    _HttpHeaderCrossOriginEmbedderPolicy();
    _HttpHeaderCrossOriginEmbedderPolicy(String);

    void import(String);
    bool isUnSafeNone();
    bool isRequireCorp();
    void setAsUnSafeNone();
    void setAsRequireCorp();

    // String get();
    // void set(String);
    
    String toString();
    static const String UnSafeNone;
    static const String RequireCorp;

private:
    //String policy;
    enum CorpType {
        TypeUnSafeNone = 0,
        TypeRequireCorp
    };

    int mType;

};

}
#endif
