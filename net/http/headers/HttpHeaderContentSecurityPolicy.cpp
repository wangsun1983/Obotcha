#include <thread>
#include <mutex>

#include "HttpHeaderContentSecurityPolicy.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

HashMap<Integer,String> _HttpHeaderContentSecurityPolicy::CommandIdToStringMaps = nullptr;
HashMap<String,Integer> _HttpHeaderContentSecurityPolicy::CommandStringToIdMaps = nullptr; 
HashMap<Integer,String> _HttpHeaderContentSecurityPolicy::RuleIdToStringMaps = nullptr;
HashMap<String,Integer> _HttpHeaderContentSecurityPolicy::RuleStringToIdMaps = nullptr; 

const String _HttpHeaderContentSecurityPolicy::StringChildSrc = createString("child-src");
const String _HttpHeaderContentSecurityPolicy::StringConnectSrc = createString("connect-src");
const String _HttpHeaderContentSecurityPolicy::StringDefaultSrc = createString("default-src");
const String _HttpHeaderContentSecurityPolicy::StringFontSrc = createString("font-src");
const String _HttpHeaderContentSecurityPolicy::StringFrameSrc = createString("frame-src");
const String _HttpHeaderContentSecurityPolicy::StringImgSrc = createString("img-src");
const String _HttpHeaderContentSecurityPolicy::StringManifestSrc = createString("manifest-src");
const String _HttpHeaderContentSecurityPolicy::StringMediaSrc = createString("media-src");
const String _HttpHeaderContentSecurityPolicy::StringObjectSrc = createString("object-src");
const String _HttpHeaderContentSecurityPolicy::StringPrefetchSrc = createString("prefetch-src");
const String _HttpHeaderContentSecurityPolicy::StringScriptSrc = createString("script-src");
const String _HttpHeaderContentSecurityPolicy::StringScriptSrcElem = createString("script-src-elem");
const String _HttpHeaderContentSecurityPolicy::StringScriptSrcAttr = createString("script-src-attr");
const String _HttpHeaderContentSecurityPolicy::StringStyleSrc = createString("style-src");
const String _HttpHeaderContentSecurityPolicy::StringStyleSrcElem = createString("style-src-elem");
const String _HttpHeaderContentSecurityPolicy::StringStyleSrcAttr = createString("style-src-attr");
const String _HttpHeaderContentSecurityPolicy::StringWorkerSrc = createString("worker-src");
const String _HttpHeaderContentSecurityPolicy::StringBaseUri = createString("base-uri");
const String _HttpHeaderContentSecurityPolicy::StringSandBox = createString("sandbox");
const String _HttpHeaderContentSecurityPolicy::StringFormAction = createString("from-action");
const String _HttpHeaderContentSecurityPolicy::StringFrameAncestors = createString("frame-ancestors");
const String _HttpHeaderContentSecurityPolicy::StringNavigateTo = createString("navigation-to");
const String _HttpHeaderContentSecurityPolicy::StringReportUri = createString("report-uri");
const String _HttpHeaderContentSecurityPolicy::StringReportTo = createString("report-to");
const String _HttpHeaderContentSecurityPolicy::StringRequireSriFor = createString("require-sri-for");
const String _HttpHeaderContentSecurityPolicy::StringRequireTrustedTypesFor = createString("require-trusted-types-for");
const String _HttpHeaderContentSecurityPolicy::StringTrustedTypes = createString("trusted-types");
const String _HttpHeaderContentSecurityPolicy::StringUpgradeInsecureRequests = createString("upgrade-insecure-requests");

const String _HttpHeaderContentSecurityPolicy::StringNone = createString("none");
const String _HttpHeaderContentSecurityPolicy::StringSelf = createString("self");
const String _HttpHeaderContentSecurityPolicy::StringTrictDynamic = createString("strict-dynamic");
const String _HttpHeaderContentSecurityPolicy::StringReportSample = createString("report-sample");
const String _HttpHeaderContentSecurityPolicy::StringUnsafeInline = createString("unsafe-inline");
const String _HttpHeaderContentSecurityPolicy::StringUnSafeEval = createString("unsafe-eval");
const String _HttpHeaderContentSecurityPolicy::StringUnSafeHashes = createString("unsafe-hashes"); 
const String _HttpHeaderContentSecurityPolicy::StringUnSafeAllowRedirects = createString("unsafe-allow-redirects");

_HttpHeaderContentSecurityPolicyItem::_HttpHeaderContentSecurityPolicyItem() {
    command = -1;
    rules = createArrayList<Integer>();
    sources = createArrayList<String>();
}

_HttpHeaderContentSecurityPolicy::_HttpHeaderContentSecurityPolicy() {
    static std::once_flag s_flag;
    std::call_once(s_flag, [&]() {
        CommandIdToStringMaps = createHashMap<Integer,String>();
        CommandStringToIdMaps = createHashMap<String,Integer>();

        RuleIdToStringMaps = createHashMap<Integer,String>();
        RuleStringToIdMaps = createHashMap<String,Integer>();
        //save
#define SET_VALUE(X,Y) CommandIdToStringMaps->put(createInteger(X),Y);\
                       CommandStringToIdMaps->put(Y,createInteger(X));

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

#define SET_RULE_VALUE(X,Y) RuleIdToStringMaps->put(createInteger(X),Y);\
                       RuleStringToIdMaps->put(Y,createInteger(X));

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
    
    items = createArrayList<HttpHeaderContentSecurityPolicyItem>();
}

_HttpHeaderContentSecurityPolicy::_HttpHeaderContentSecurityPolicy(String s):_HttpHeaderContentSecurityPolicy() {
    load(s);
}

void _HttpHeaderContentSecurityPolicy::jumpSpace(const char *p,int &i,int size) {
    while(p[i] == ' ' && i < size && p[i] != ';') {
        i++;
    }
}

void _HttpHeaderContentSecurityPolicy::load(String s) {
    HttpHeaderContentSecurityPolicyItem item = nullptr;
    String value = s->trim();
    const char *p = value->toChars();
    int size = s->size();
    int start = 0;
    int status = ParseCommand;
    for(int i = 0;i < size;i++) {
        switch(status) {
            case ParseCommand:
            if(p[i] == ' ') {
                item = createHttpHeaderContentSecurityPolicyItem();
                String command = createString(p,start,i-start);
                item->command = CommandStringToIdMaps->get(command)->toValue();
                jumpSpace(p,i,size);
                start = i;
                status = ParseRuleOrSource;
            }
            break;

            case ParseRuleOrSource:
            if(p[i] == ';' || p[i] == ' ' || i == size -1) {
                //check rule or source;
                if(p[start] == '\'') {
                    int end = i;
                    while(p[end] != '\'') {
                        end--;
                    }

                    String rule = createString(p,start+1,end-start-1);
                    item->rules->add(RuleStringToIdMaps->get(rule));
                    jumpSpace(p,i,size);
                } else {
                    String src = nullptr;
                    if(i == size - 1) {
                        src = createString(p,start,size - start);
                    } else {
                        src = createString(p,start,i-start);
                    }
                    item->sources->add(src);
                    jumpSpace(p,i,size);
                }
                
                if(p[i] == ';' || i == size - 1) {
                    items->add(item);
                    status = ParseCommand;
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
    HttpHeaderContentSecurityPolicyItem item = createHttpHeaderContentSecurityPolicyItem();
    item->command = -1;
    //item->rule = -1;
    //TODO
}

String _HttpHeaderContentSecurityPolicy::toString() {
    StringBuffer policy = createStringBuffer();
    auto iterator = items->getIterator();
    while(iterator->hasValue()) {
        HttpHeaderContentSecurityPolicyItem item = iterator->getValue();
        if(item->command != -1) {
            policy->append(CommandIdToStringMaps->get(createInteger(item->command))," ");
        }

        auto ruleIterator = item->rules->getIterator();
        while(ruleIterator->hasValue()) {
            policy->append("\'",RuleIdToStringMaps->get(ruleIterator->getValue()),"\' ");
            ruleIterator->next();
        }

        if(item->sources != nullptr && item->sources->size() != 0) {
            //policy = policy->append(item->src);
            auto ite = item->sources->getIterator();
            while(ite->hasValue()) {
                policy->append(ite->getValue()," ");
                ite->next();
            }
        }
        policy->subString(0,policy->size() - 1);
        policy->append("; ");
        iterator->next();
    }

    return policy->toString(0,policy->size() - 2);
}

}
