#ifndef __OBOTCHA_HTTP_CROSS_RESOURCE_EMBEDDER_POLICY_HPP__
#define __OBOTCHA_HTTP_CROSS_RESOURCE_EMBEDDER_POLICY_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderCrossOriginResourcePolicy) {

public:
    _HttpHeaderCrossOriginResourcePolicy() = default;
    explicit _HttpHeaderCrossOriginResourcePolicy(String);

    void load(String);

    bool isSameSite() const;
    bool isSameOrigin() const;
    bool isCrossOrigin() const;

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

    int mType = -1;
};

}
#endif
