#include <thread>
#include <mutex>

#include "HttpContentSecurityPolicy.hpp"

namespace obotcha {

HashMap<Integer,String> _HttpContentSecurityPolicy::CommandIdToStringMaps = nullptr;
HashMap<String,Integer> _HttpContentSecurityPolicy::CommandStringToIdMaps = nullptr; 
HashMap<Integer,String> _HttpContentSecurityPolicy::RuleIdToStringMaps = nullptr;
HashMap<String,Integer> _HttpContentSecurityPolicy::RuleStringToIdMaps = nullptr; 

const String _HttpContentSecurityPolicy::StringChildSrc = createString("child-src");
const String _HttpContentSecurityPolicy::StringConnectSrc = createString("connect-src");
const String _HttpContentSecurityPolicy::StringDefaultSrc = createString("default-src");
const String _HttpContentSecurityPolicy::StringFontSrc = createString("font-src");
const String _HttpContentSecurityPolicy::StringFrameSrc = createString("frame-src");
const String _HttpContentSecurityPolicy::StringImgSrc = createString("img-src");
const String _HttpContentSecurityPolicy::StringManifestSrc = createString("manifest-src");
const String _HttpContentSecurityPolicy::StringMediaSrc = createString("media-src");
const String _HttpContentSecurityPolicy::StringObjectSrc = createString("object-src");
const String _HttpContentSecurityPolicy::StringPrefetchSrc = createString("prefetch-src");
const String _HttpContentSecurityPolicy::StringScriptSrc = createString("script-src");
const String _HttpContentSecurityPolicy::StringScriptSrcElem = createString("script-src-elem");
const String _HttpContentSecurityPolicy::StringScriptSrcAttr = createString("script-src-attr");
const String _HttpContentSecurityPolicy::StringStyleSrc = createString("style-src");
const String _HttpContentSecurityPolicy::StringStyleSrcElem = createString("style-src-elem");
const String _HttpContentSecurityPolicy::StringStyleSrcAttr = createString("style-src-attr");
const String _HttpContentSecurityPolicy::StringWorkerSrc = createString("worker-src");
const String _HttpContentSecurityPolicy::StringBaseUri = createString("base-uri");
const String _HttpContentSecurityPolicy::StringSandBox = createString("sandbox");
const String _HttpContentSecurityPolicy::StringFormAction = createString("from-action");
const String _HttpContentSecurityPolicy::StringFrameAncestors = createString("frame-ancestors");
const String _HttpContentSecurityPolicy::StringNavigateTo = createString("navigation-to");
const String _HttpContentSecurityPolicy::StringReportUri = createString("report-uri");
const String _HttpContentSecurityPolicy::StringReportTo = createString("report-to");
const String _HttpContentSecurityPolicy::StringRequireSriFor = createString("require-sri-for");
const String _HttpContentSecurityPolicy::StringRequireTrustedTypesFor = createString("require-trusted-types-for");
const String _HttpContentSecurityPolicy::StringTrustedTypes = createString("trusted-types");
const String _HttpContentSecurityPolicy::StringUpgradeInsecureRequests = createString("upgrade-insecure-requests");

const String _HttpContentSecurityPolicy::StringNone = createString("none");
const String _HttpContentSecurityPolicy::StringSelf = createString("self");
const String _HttpContentSecurityPolicy::StringTrictDynamic = createString("strict-dynamic");
const String _HttpContentSecurityPolicy::StringReportSample = createString("report-sample");
const String _HttpContentSecurityPolicy::StringUnsafeInline = createString("unsafe-inline");
const String _HttpContentSecurityPolicy::StringUnSafeEval = createString("unsafe-eval");
const String _HttpContentSecurityPolicy::StringUnSafeHashes = createString("unsafe-hashes"); 
const String _HttpContentSecurityPolicy::StringUnSafeAllowRedirects = createString("unsafe-allow-redirects");

_HttpContentSecurityPolicyItem::_HttpContentSecurityPolicyItem() {
    command = -1;
    rules = createArrayList<Integer>();
    sources = createArrayList<String>();
}

_HttpContentSecurityPolicy::_HttpContentSecurityPolicy() {
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
    
    items = createArrayList<HttpContentSecurityPolicyItem>();
}

_HttpContentSecurityPolicy::_HttpContentSecurityPolicy(String s):_HttpContentSecurityPolicy() {
    import(s);
}

void _HttpContentSecurityPolicy::jumpSpace(const char *p,int &i,int size) {
    while(p[i] == ' ' && i < size && p[i] != ';') {
        i++;
    }
}

void _HttpContentSecurityPolicy::import(String s) {
    HttpContentSecurityPolicyItem item = nullptr;
    String value = s->trim();
    const char *p = value->toChars();
    int size = s->size();
    int start = 0;
    int status = ParseCommand;
    for(int i = 0;i < size;i++) {
        switch(status) {
            case ParseCommand:
            if(p[i] == ' ') {
                item = createHttpContentSecurityPolicyItem();
                String command = createString(p,start,i-start);
                item->command = CommandStringToIdMaps->get(command)->toValue();
                printf("command is %s,id is %d \n",command->toChars(),item->command);
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
                    printf("rule is %s \n",rule->toChars());
                    item->rules->add(RuleStringToIdMaps->get(rule));
                    jumpSpace(p,i,size);
                } else {
                    String src = nullptr;
                    if(i == size - 1) {
                        src = createString(p,start,size - start);
                    } else {
                        src = createString(p,start,i-start);
                    }
                    printf("src is %s \n",src->toChars());
                    item->sources->add(src);
                    jumpSpace(p,i,size);
                }
                
                if(p[i] == ';' || i == size - 1) {
                    printf("add item!!! \n");
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

ArrayList<HttpContentSecurityPolicyItem> _HttpContentSecurityPolicy::get() {
    return items;
}

void _HttpContentSecurityPolicy::add(int c,int r,String src) {
    HttpContentSecurityPolicyItem item = createHttpContentSecurityPolicyItem();
    item->command = -1;
    //item->rule = -1;
    //TODO
}

String _HttpContentSecurityPolicy::toString() {
    String policy = "";
    auto iterator = items->getIterator();
    while(iterator->hasValue()) {
        HttpContentSecurityPolicyItem item = iterator->getValue();
        if(item->command != -1) {
            policy = policy->append(CommandIdToStringMaps->get(createInteger(item->command))," ");
        }

        auto ruleIterator = item->rules->getIterator();
        while(ruleIterator->hasValue()) {
            policy = policy->append("\'",RuleIdToStringMaps->get(ruleIterator->getValue()),"\' ");
            ruleIterator->next();
        }

        if(item->sources != nullptr && item->sources->size() != 0) {
            //policy = policy->append(item->src);
            auto ite = item->sources->getIterator();
            while(ite->hasValue()) {
                policy = policy->append(ite->getValue()," ");
                ite->next();
            }
        }
        policy = policy->subString(0,policy->size() - 1);
        policy = policy->append("; ");
        iterator->next();
    }

    return policy->subString(0,policy->size() - 2);
}

}
