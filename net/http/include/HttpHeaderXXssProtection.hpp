#ifndef __OBOTCHA_HTTP_HEADER_X_XXS_PROTECTION_HPP__
#define __OBOTCHA_HTTP_HEADER_X_XXS_PROTECTION_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderXXssProtection) {

public:
    enum Type {
        Disable,
        Enable,
        Block,
        Report,
        Unknown
    };

    _HttpHeaderXXssProtection() = default;
    explicit _HttpHeaderXXssProtection(String);

    void load(String);
    
    _HttpHeaderXXssProtection::Type getType();
    String getReportUrl();
    void set(_HttpHeaderXXssProtection::Type xxssType,String reporturl = nullptr);
    
    String toString() override;

private:
    static String DisableContent;
    static String EnableContent;
    _HttpHeaderXXssProtection::Type mType;
    String mReportUri;
};

}
#endif
