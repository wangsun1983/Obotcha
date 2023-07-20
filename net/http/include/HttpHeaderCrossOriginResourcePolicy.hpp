#ifndef __OBOTCHA_HTTP_CROSS_RESOURCE_EMBEDDER_POLICY_HPP__
#define __OBOTCHA_HTTP_CROSS_RESOURCE_EMBEDDER_POLICY_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderCrossOriginResourcePolicy) {

public:
    _HttpHeaderCrossOriginResourcePolicy();
    explicit _HttpHeaderCrossOriginResourcePolicy(String);

    void load(String);

    bool isSameSite();
    bool isSameOrigin();
    bool isCrossOrigin();

    void setAsSameSite();
    void setAsSameOrigin();
    void setAsCrossOrigin();

    
    String toString();
    static const String SameSite;
    static const String SameOrigin;
    static const String CrossOrigin;
    
private:
    enum CorpType {
        TypeSameSite = 0,
        TypeSameOrigin,
        TypeCrossOrigin,
    };

    int mType;
};

}
#endif
