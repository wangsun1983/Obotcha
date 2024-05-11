#include <thread>
#include <mutex>

#include "HttpHeaderContentSecurityPolicy.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

HashMap<Integer,String> _HttpHeaderContentSecurityPolicy::CommandIdToStringMaps = nullptr;
HashMap<String,Integer> _HttpHeaderContentSecurityPolicy::CommandStringToIdMaps = nullptr; 
HashMap<Integer,String> _HttpHeaderContentSecurityPolicy::RuleIdToStringMaps = nullptr;
HashMap<String,Integer> _HttpHeaderContentSecurityPolicy::RuleStringToIdMaps = nullptr; 

const String _HttpHeaderContentSecurityPolicy::StringChildSrc = String::New("child-src");
const String _HttpHeaderContentSecurityPolicy::StringConnectSrc = String::New("connect-src");
const String _HttpHeaderContentSecurityPolicy::StringDefaultSrc = String::New("default-src");
const String _HttpHeaderContentSecurityPolicy::StringFontSrc = String::New("font-src");
const String _HttpHeaderContentSecurityPolicy::StringFrameSrc = String::New("frame-src");
const String _HttpHeaderContentSecurityPolicy::StringImgSrc = String::New("img-src");
const String _HttpHeaderContentSecurityPolicy::StringManifestSrc = String::New("manifest-src");
const String _HttpHeaderContentSecurityPolicy::StringMediaSrc = String::New("media-src");
const String _HttpHeaderContentSecurityPolicy::StringObjectSrc = String::New("object-src");
const String _HttpHeaderContentSecurityPolicy::StringPrefetchSrc = String::New("prefetch-src");
const String _HttpHeaderContentSecurityPolicy::StringScriptSrc = String::New("script-src");
const String _HttpHeaderContentSecurityPolicy::StringScriptSrcElem = String::New("script-src-elem");
const String _HttpHeaderContentSecurityPolicy::StringScriptSrcAttr = String::New("script-src-attr");
const String _HttpHeaderContentSecurityPolicy::StringStyleSrc = String::New("style-src");
const String _HttpHeaderContentSecurityPolicy::StringStyleSrcElem = String::New("style-src-elem");
const String _HttpHeaderContentSecurityPolicy::StringStyleSrcAttr = String::New("style-src-attr");
const String _HttpHeaderContentSecurityPolicy::StringWorkerSrc = String::New("worker-src");
const String _HttpHeaderContentSecurityPolicy::StringBaseUri = String::New("base-uri");
const String _HttpHeaderContentSecurityPolicy::StringSandBox = String::New("sandbox");
const String _HttpHeaderContentSecurityPolicy::StringFormAction = String::New("from-action");
const String _HttpHeaderContentSecurityPolicy::StringFrameAncestors = String::New("frame-ancestors");
const String _HttpHeaderContentSecurityPolicy::StringNavigateTo = String::New("navigation-to");
const String _HttpHeaderContentSecurityPolicy::StringReportUri = String::New("report-uri");
const String _HttpHeaderContentSecurityPolicy::StringReportTo = String::New("report-to");
const String _HttpHeaderContentSecurityPolicy::StringRequireSriFor = String::New("require-sri-for");
const String _HttpHeaderContentSecurityPolicy::StringRequireTrustedTypesFor = String::New("require-trusted-types-for");
const String _HttpHeaderContentSecurityPolicy::StringTrustedTypes = String::New("trusted-types");
const String _HttpHeaderContentSecurityPolicy::StringUpgradeInsecureRequests = String::New("upgrade-insecure-requests");

const String _HttpHeaderContentSecurityPolicy::StringNone = String::New("none");
const String _HttpHeaderContentSecurityPolicy::StringSelf = String::New("self");
const String _HttpHeaderContentSecurityPolicy::StringTrictDynamic = String::New("strict-dynamic");
const String _HttpHeaderContentSecurityPolicy::StringReportSample = String::New("report-sample");
const String _HttpHeaderContentSecurityPolicy::StringUnsafeInline = String::New("unsafe-inline");
const String _HttpHeaderContentSecurityPolicy::StringUnSafeEval = String::New("unsafe-eval");
const String _HttpHeaderContentSecurityPolicy::StringUnSafeHashes = String::New("unsafe-hashes"); 
const String _HttpHeaderContentSecurityPolicy::StringUnSafeAllowRedirects = String::New("unsafe-allow-redirects");

_HttpHeaderContentSecurityPolicy::_HttpHeaderContentSecurityPolicy() {
    static std::once_flag s_flag;
    std::call_once(s_flag, []() {
        CommandIdToStringMaps = HashMap<Integer,String>::New();
        CommandStringToIdMaps = HashMap<String,Integer>::New();

        RuleIdToStringMaps = HashMap<Integer,String>::New();
        RuleStringToIdMaps = HashMap<String,Integer>::New();
        //save
#define SET_VALUE(X,Y) CommandIdToStringMaps->put(Integer::New(X),Y);\
                       CommandStringToIdMaps->put(Y,Integer::New(X));

        SET_VALUE(CommandChildSrc,StringChildSrc)
        SET_VALUE(CommandConnectSrc,StringConnectSrc)
        SET_VALUE(CommandDefaultSrc,StringDefaultSrc)
        SET_VALUE(CommandFontSrc,StringFontSrc)
        SET_VALUE(CommandFrameSrc,StringFrameSrc)
        SET_VALUE(CommandImgSrc,StringImgSrc)
        SET_VALUE(CommandManifestSrc,StringManifestSrc)
        SET_VALUE(CommandMediaSrc,StringMediaSrc)
        SET_VALUE(CommandObjectSrc,StringObjectSrc)
        SET_VALUE(CommandPrefetchSrc,StringPrefetchSrc)
        SET_VALUE(CommandScriptSrc,StringScriptSrc)
        SET_VALUE(CommandScriptSrcElem,StringScriptSrcElem)
        SET_VALUE(CommandScriptSrcAttr,StringScriptSrcAttr)
        SET_VALUE(CommandStyleSrc,StringStyleSrc)
        SET_VALUE(CommandStyleSrcElem,StringStyleSrcElem)
        SET_VALUE(CommandStyleSrcAttr,StringStyleSrcAttr)
        SET_VALUE(CommandWorkerSrc,StringWorkerSrc)
        SET_VALUE(CommandBaseUri,StringBaseUri)
        SET_VALUE(CommandSandBox,StringSandBox)
        SET_VALUE(CommandFormAction,StringFormAction)
        SET_VALUE(CommandFrameAncestors,StringFrameAncestors)
        SET_VALUE(CommandNavigateTo,StringNavigateTo)
        SET_VALUE(CommandReportUri,StringReportUri)
        SET_VALUE(CommandReportTo,StringReportTo)
        SET_VALUE(CommandRequireSriFor,StringRequireSriFor)
        SET_VALUE(CommandRequireTrustedTypesFor,StringRequireTrustedTypesFor)
        SET_VALUE(CommandTrustedTypes,StringTrustedTypes)
        SET_VALUE(CommandUpgradeInsecureRequests,StringUpgradeInsecureRequests)

#undef SET_VALUE

#define SET_RULE_VALUE(X,Y) RuleIdToStringMaps->put(Integer::New(X),Y);\
                       RuleStringToIdMaps->put(Y,Integer::New(X));

        SET_RULE_VALUE(RuleNone,StringNone)
        SET_RULE_VALUE(RuleSelf,StringSelf)
        SET_RULE_VALUE(RuleTrictDynamic,StringTrictDynamic)
        SET_RULE_VALUE(RuleReportSample,StringReportSample)
        SET_RULE_VALUE(RuleUnsafeInline,StringUnsafeInline)
        SET_RULE_VALUE(RuleUnSafeEval,StringUnSafeEval)
        SET_RULE_VALUE(RuleUnSafeHashes,StringUnSafeHashes) 
        SET_RULE_VALUE(RuleUnSafeAllowRedirects,StringUnSafeAllowRedirects)

#undef SET_RULE_VALUE
    });
    
    items = ArrayList<HttpHeaderContentSecurityPolicyItem>::New();
}

_HttpHeaderContentSecurityPolicy::_HttpHeaderContentSecurityPolicy(String s):_HttpHeaderContentSecurityPolicy() {
    load(s);
}

void _HttpHeaderContentSecurityPolicy::jumpSpace(const char *p,size_t &i,size_t size) const {
    while(p[i] == ' ' && i < size && p[i] != ';') {
        i++;
    }
}

void _HttpHeaderContentSecurityPolicy::load(String s) {
    HttpHeaderContentSecurityPolicyItem item = nullptr;
    String value = s->trim();
    const char *p = value->toChars();
    size_t size = s->size();
    size_t start = 0;
    Status status = Status::ParseCommand;
    for(size_t i = 0;i < size;i++) {
        switch(status) {
            case Status::ParseCommand:
            if(p[i] == ' ') {
                item = HttpHeaderContentSecurityPolicyItem::New();
                String command = String::New(p,start,i-start);
                item->command = CommandStringToIdMaps->get(command)->toValue();
                jumpSpace(p,i,size);
                start = i;
                status = Status::ParseRuleOrSource;
            }
            break;

            case Status::ParseRuleOrSource:
            if(p[i] == ';' || p[i] == ' ' || i == size -1) {
                //check rule or source;
                if(p[start] == '\'') {
                    auto end = i;
                    while(p[end] != '\'') {
                        end--;
                    }

                    String rule = String::New(p,start+1,end-start-1);
                    item->rules->add(RuleStringToIdMaps->get(rule));
                    jumpSpace(p,i,size);
                } else {
                    String src = nullptr;
                    if(i == size - 1) {
                        src = String::New(p,start,size - start);
                    } else {
                        src = String::New(p,start,i-start);
                    }
                    item->sources->add(src);
                    jumpSpace(p,i,size);
                }
                
                if(p[i] == ';' || i == size - 1) {
                    items->add(item);
                    status = Status::ParseCommand;
                    i++;
                }

                jumpSpace(p,i,size);
                start = i;
            }
            break;
        }
    }


}

ArrayList<HttpHeaderContentSecurityPolicyItem> _HttpHeaderContentSecurityPolicy::get() {
    return items;
}

void _HttpHeaderContentSecurityPolicy::add(int c,int r,String src) {
    HttpHeaderContentSecurityPolicyItem securityPolicyItem = nullptr;
    ForEveryOne(item,items) {
        if(item->command == c) {
            securityPolicyItem = item;
            break;
        }
    }
    
    if(securityPolicyItem == nullptr) {
        securityPolicyItem = HttpHeaderContentSecurityPolicyItem::New();
        items->add(securityPolicyItem);
    }

    securityPolicyItem->command = c;
    securityPolicyItem->rules->add(Integer::New(r));
    securityPolicyItem->sources->add(src);
}

String _HttpHeaderContentSecurityPolicy::toString() {
    StringBuffer policy = StringBuffer::New();
    auto iterator = items->getIterator();
    while(iterator->hasValue()) {
        HttpHeaderContentSecurityPolicyItem item = iterator->getValue();
        if(item->command != -1) {
            policy->append(CommandIdToStringMaps->get(Integer::New(item->command))," ");
        }

        auto ruleIterator = item->rules->getIterator();
        while(ruleIterator->hasValue()) {
            policy->append("\'",RuleIdToStringMaps->get(ruleIterator->getValue()),"\' ");
            ruleIterator->next();
        }

        if(item->sources != nullptr && item->sources->size() != 0) {
            auto ite = item->sources->getIterator();
            while(ite->hasValue()) {
                policy->append(ite->getValue()," ");
                ite->next();
            }
        }
        policy->crop(0,policy->size() - 1);
        policy->append("; ");
        iterator->next();
    }

    return policy->toString(0,policy->size() - 2);
}

}
