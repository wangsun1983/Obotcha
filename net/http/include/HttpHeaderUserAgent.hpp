#ifndef __OBOTCHA_HTTP_HEADER_USER_AGENT_HPP__
#define __OBOTCHA_HTTP_HEADER_USER_AGENT_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpUserAgentDetail) {
public:
    _HttpUserAgentDetail(String,String,String);
    _HttpUserAgentDetail() = default;
    String agentProduct;
    String agentVersion;
    String agentInfo;
};

DECLARE_CLASS(HttpHeaderUserAgent) {

public:
    _HttpHeaderUserAgent() = default;
    explicit _HttpHeaderUserAgent(String);

    void load(String);
    void add(String product,String version,String info);
    ArrayList<HttpUserAgentDetail> get();

    String toString() override;

private:
    enum {
        ParseProduct = 0,
        ParseVersion,
        ParseInfo
    };
    
    ArrayList<HttpUserAgentDetail> agents = createArrayList<HttpUserAgentDetail>();
};

}
#endif
