#ifndef __OBOTCHA_HTTP2_HPACK_STATIC_TABLE_HPP__
#define __OBOTCHA_HTTP2_HPACK_STATIC_TABLE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "List.hpp"
#include "Http2HpackTableItem.hpp"

namespace obotcha {

//https://datatracker.ietf.org/doc/html/rfc7541#appendix-A
DECLARE_CLASS(Http2HpackStaticTable) {
public:
    enum Id {
    /*  0 */ IdIdle = 0,
    /*  1 */ IdAuthority,   //(":authority"),
    /*  2 */ IdMethodGet,   //(":method", "GET"),
    /*  3 */ IdMethodPost,  //(":method", "POST"),
    /*  4 */ IdPathRoot,    //(":path", "/"),
    /*  5 */ IdPathIndex,   //(":path", "/index.html"),
    /*  6 */ IdSchemeHttp,  //(":scheme", "http"),
    /*  7 */ IdSchemeHttps, //(":scheme", "https"),
    /*  8 */ IdStatus200,   //(":status", "200"),
    /*  9 */ IdStatus204,   //(":status", "204"),
    /* 10 */ IdStatus206,   //(":status", "206"),
    /* 11 */ IdStatus304,   //(":status", "304"),
    /* 12 */ IdStatus400,   //(":status", "400"),
    /* 13 */ IdStatus404,   //(":status", "404"),
    /* 14 */ IdStatus500,   //(":status", "500"),
    /* 15 */ IdAcceptCharSet, //("accept-charset"),
    /* 16 */ IdAcceptEncodingGzipDeflate, //("accept-encoding", "gzip, deflate"),
    /* 17 */ IdAcceptLanguage,            //("accept-language"),
    /* 18 */ IdAcceptRanges,              //("accept-ranges"),
    /* 19 */ IdAccept,                    //("accept"),
    /* 20 */ IdAccessControlAllowOrigin,  //("access-control-allow-origin"),
    /* 21 */ IdAge,                       //("age"),
    /* 22 */ IdAllow,                     //("allow"),
    /* 23 */ IdAuthorization,             //("authorization"),
    /* 24 */ IdCacheControl,              //("cache-control"),
    /* 25 */ IdContentDisposition,        //("content-disposition"),
    /* 26 */ IdContentEncoding,           //("content-encoding"),
    /* 27 */ IdContentLanguage,           //("content-language"),
    /* 28 */ IdContentLength,             //("content-length"),
    /* 29 */ IdContentLocation,           //("content-location"),
    /* 30 */ IdContentRange,              //("content-range"),
    /* 31 */ IdContentType,               //("content-type"),
    /* 32 */ IdCookie,                    //("cookie"),
    /* 33 */ IdDate,                      //("date"),
    /* 34 */ IdEtag,                      //("etag"),
    /* 35 */ IdExpect,                    //("expect"),
    /* 36 */ IdExpires,                   //("expires"),
    /* 37 */ IdFrom,                      //("from"),
    /* 38 */ IdHost,                      //("host"),
    /* 39 */ IdIfMatch,                   //("if-match"),
    /* 40 */ IdIfModifiedSince,           //("if-modified-since"),
    /* 41 */ IdIfNoneMatch,               //("if-none-match"),
    /* 42 */ IdIfRange,                   //("if-range"),
    /* 43 */ IdIfUnmodifiedSince,         //("if-unmodified-since"),
    /* 44 */ IdLastModified,              //("last-modified"),
    /* 45 */ IdLink,                      //("link"),
    /* 46 */ IdLocation,                  //("location"),
    /* 47 */ IdMaxForwards,               //("max-forwards"),
    /* 48 */ IdProxyAuthenticate,         //("proxy-authenticate"),
    /* 49 */ IdProxyAuthorization,        //("proxy-authorization"),
    /* 50 */ IdRange,                     //("range"),
    /* 51 */ IdReferer,                   //("referer"),
    /* 52 */ IdRefresh,                   //("refresh"),
    /* 53 */ IdRetryAfter,                //("retry-after"),
    /* 54 */ IdServer,                    //("server"),
    /* 55 */ IdSetCookie,                 //("set-cookie"),
    /* 56 */ IdStrictTransportSecurity,   //("strict-transport-security"),
    /* 57 */ IdTransferEncoding,          //("transfer-encoding"),
    /* 58 */ IdUserAgent,                 //("user-agent"),
    /* 59 */ IdVary,                      //("vary"),
    /* 60 */ IdVia,                       //("via"),
    /* 61 */ IdWwwAuthenticate,           //("www-authenticate")
    /* 62 */ IdMax
    };

    _Http2HpackStaticTable();

    Http2HpackTableItem get(int);

private:
    static List<Http2HpackTableItem> STATIC_TABLE;
};

}
#endif
