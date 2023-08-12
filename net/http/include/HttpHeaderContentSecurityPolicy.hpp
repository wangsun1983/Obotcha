#ifndef __OBOTCHA_HTTP_CONTENT_SECURITY_POLICY_HPP__
#define __OBOTCHA_HTTP_CONTENT_SECURITY_POLICY_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "Integer.hpp"

namespace obotcha {

//https://www.jianshu.com/p/a8b769e7d4bd
//https://developer.mozilla.org/zh-CN/docs/Web/HTTP/Headers/Content-Security-Policy
DECLARE_CLASS(HttpHeaderContentSecurityPolicyItem) {
public:
    _HttpHeaderContentSecurityPolicyItem() = default;
    int command = -1;
    ArrayList<Integer> rules = createArrayList<Integer>();
    ArrayList<String> sources = createArrayList<String>();
};

DECLARE_CLASS(HttpHeaderContentSecurityPolicy) {

public:
    _HttpHeaderContentSecurityPolicy();
    explicit _HttpHeaderContentSecurityPolicy(String);

    void load(String);
    ArrayList<HttpHeaderContentSecurityPolicyItem> get();

    void add(int,int,String);

    String toString() override;

    enum Command {
        ////////Fetch directives
        //Defines the valid sources for web workers and nested browsing contexts 
        //loaded using elements such as <frame> and <iframe>.
        //child-src
        CommandChildSrc = 0,

        //Restricts the URLs which can be loaded using script interfaces
        //connect-src
        CommandConnectSrc,

        //Serves as a fallback for the other fetch directives.
        //default-src,
        CommandDefaultSrc,

        //Specifies valid sources for fonts loaded using @font-face.
        //font-src,
        CommandFontSrc,

        //Specifies valid sources for nested browsing contexts loading using 
        //elements such as <frame> and <iframe>.
        //frame-src,
        CommandFrameSrc,
        
        //Specifies valid sources of images and favicons.
        //img-src,
        CommandImgSrc,
        
        //Specifies valid sources of application manifest files.
        //manifest-src,
        CommandManifestSrc,
        
        //Specifies valid sources for loading media using the <audio> , <video> and <track> elements.
        //media-src,
        CommandMediaSrc,
        
        //Specifies valid sources for the <object>, <embed>, and <applet> elements.
        //object-src,
        CommandObjectSrc,

        //Specifies valid sources to be prefetched or prerendered.
        //prefetch-src,
        CommandPrefetchSrc,

        //Specifies valid sources for JavaScript.
        //script-src,
        CommandScriptSrc,

        //Specifies valid sources for JavaScript <script> elements.
        //script-src-elem,
        CommandScriptSrcElem,

        //Specifies valid sources for JavaScript inline event handlers.
        //script-src-attr,
        CommandScriptSrcAttr,

        //Specifies valid sources for stylesheets.
        //style-src,
        CommandStyleSrc,

        //Specifies valid sources for stylesheets <style> elements and <link> elements 
        //with rel="stylesheet".
        //style-src-elem,
        CommandStyleSrcElem,

        //Specifies valid sources for inline styles applied to individual DOM elements.
        //style-src-attr,
        CommandStyleSrcAttr,

        //Specifies valid sources for Worker, SharedWorker, or ServiceWorker scripts.
        //worker-src,
        CommandWorkerSrc,

        ////////Document directives
        //Restricts the URLs which can be used in a document's <base> element.
        //base-uri,
        CommandBaseUri,

        //Enables a sandbox for the requested resource similar to the <iframe> sandbox 
        //attribute.
        //sandbox,
        CommandSandBox,

        ////////Navigation directives
        //Restricts the URLs which can be used as the target of a form submissions 
        //from a given context.
        //form-action,
        CommandFormAction,

        //Specifies valid parents that may embed a page using <frame>, <iframe>, <object>, 
        //<embed>, or <applet>.
        //frame-ancestors,
        CommandFrameAncestors,

        //Restricts the URLs to which a document can initiate navigation by any means, 
        //including <form> (if form-action is not specified), <a>, window.location, window.open, etc.
        //navigate-to,
        CommandNavigateTo,

        //////Reporting directives
        //Instructs the user agent to report attempts to violate the Content Security Policy. 
        //These violation reports consist of JSON documents sent via an HTTP POST request to 
        //the specified URI.
        //report-uri,
        CommandReportUri,

        //Fires a SecurityPolicyViolationEvent.
        //report-to,
        CommandReportTo,

        //////Other directives
        //Requires the use of SRI for scripts or styles on the page.
        //require-sri-for,
        CommandRequireSriFor,

        //Enforces Trusted Types at the DOM XSS injection sinks.
        //require-trusted-types-for,
        CommandRequireTrustedTypesFor,

        //Used to specify an allow-list of Trusted Types policies. Trusted Types allows 
        //applications to lock down DOM XSS injection sinks to only accept non-spoofable,
        //typed values in place of strings.
        //trusted-types,
        CommandTrustedTypes,
        
        //Instructs user agents to treat all of a site's insecure URLs (those served over HTTP) 
        //as though they have been replaced with secure URLs (those served over HTTPS). 
        //This directive is intended for web sites with large numbers of insecure legacy URLs that need to be rewritten.
        //upgrade-insecure-requests,
        CommandUpgradeInsecureRequests,
    };

    enum Rule {
        //Won't allow loading of any resources.
        //none,
        RuleNone = 0,

        //Only allow resources from the current origin.
        //self,
        RuleSelf,

        //TBD
        //trict-dynamic,
        RuleTrictDynamic,

        //TBD
        //report-sample,
        RuleReportSample,

        //Allow use of inline resources.
        //unsafe-inline,
        RuleUnsafeInline,

        //Allow use of dynamic code evaluation such as eval, setImmediate, 
        //and window.execScript .
        //unsafe-eval,
        RuleUnSafeEval,

        //TBD
        //unsafe-hashes,
        RuleUnSafeHashes, 

        //TBD
        //unsafe-allow-redirects,
        RuleUnSafeAllowRedirects,
    };

    static const String StringChildSrc;
    static const String StringConnectSrc;
    static const String StringDefaultSrc;
    static const String StringFontSrc;
    static const String StringFrameSrc;
    static const String StringImgSrc;
    static const String StringManifestSrc;
    static const String StringMediaSrc;
    static const String StringObjectSrc;
    static const String StringPrefetchSrc;
    static const String StringScriptSrc;
    static const String StringScriptSrcElem;
    static const String StringScriptSrcAttr;
    static const String StringStyleSrc;
    static const String StringStyleSrcElem;
    static const String StringStyleSrcAttr;
    static const String StringWorkerSrc;
    static const String StringBaseUri;
    static const String StringSandBox;
    static const String StringFormAction;
    static const String StringFrameAncestors;
    static const String StringNavigateTo;
    static const String StringReportUri;
    static const String StringReportTo;
    static const String StringRequireSriFor;
    static const String StringRequireTrustedTypesFor;
    static const String StringTrustedTypes;
    static const String StringUpgradeInsecureRequests;


    static const String StringNone;
    static const String StringSelf;
    static const String StringTrictDynamic;
    static const String StringReportSample;
    static const String StringUnsafeInline;
    static const String StringUnSafeEval;
    static const String StringUnSafeHashes; 
    static const String StringUnSafeAllowRedirects;

private:
    enum class Status {
        ParseCommand = 0,
        ParseRuleOrSource,
    };
    ArrayList<HttpHeaderContentSecurityPolicyItem> items;
    static HashMap<Integer,String> CommandIdToStringMaps;
    static HashMap<String,Integer> CommandStringToIdMaps;

    static HashMap<Integer,String> RuleIdToStringMaps;
    static HashMap<String,Integer> RuleStringToIdMaps;
    void jumpSpace(const char *,size_t &,size_t size) const;
};

}
#endif
