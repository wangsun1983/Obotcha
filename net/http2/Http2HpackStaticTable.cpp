#include <thread>
#include <mutex>

#include "Http2HpackStaticTable.hpp"

namespace obotcha {

List<Http2HpackTableItem> _Http2HpackStaticTable::STATIC_TABLE = nullptr;

_Http2HpackStaticTable::_Http2HpackStaticTable() {
    static std::once_flag s_flag;
    std::call_once(s_flag, [&]() {
        STATIC_TABLE = createList<Http2HpackTableItem>(IdMax);
        /*  1 */ STATIC_TABLE[1]->headerName = ":authority",
        /*  2 */ STATIC_TABLE[2]->headerName = ":method";
                 STATIC_TABLE[2]->headerValue = "GET";

        /*  3 */ STATIC_TABLE[3]->headerName = ":method";
                 STATIC_TABLE[3]->headerValue = "POST";

        /*  4 */ STATIC_TABLE[4]->headerName = ":path"; 
                 STATIC_TABLE[4]->headerValue = "/",

        /*  5 */ STATIC_TABLE[5]->headerName = ":path";
                 STATIC_TABLE[5]->headerValue = "/index.html";

        /*  6 */ STATIC_TABLE[6]->headerName = ":scheme";
                 STATIC_TABLE[6]->headerValue = "http";

        /*  7 */ STATIC_TABLE[7]->headerName = ":scheme";
                 STATIC_TABLE[7]->headerValue = "https";

        /*  8 */ STATIC_TABLE[8]->headerName = ":status";
                 STATIC_TABLE[8]->headerValue = "200";

        /*  9 */ STATIC_TABLE[9]->headerName = ":status";
                 STATIC_TABLE[9]->headerValue = "204";
                 
        /* 10 */ STATIC_TABLE[10]->headerName = ":status";
                 STATIC_TABLE[10]->headerValue =  "206";

        /* 11 */ STATIC_TABLE[11]->headerName = ":status";
                 STATIC_TABLE[11]->headerValue =  "304";
        
        /* 12 */ STATIC_TABLE[12]->headerName = ":status";
                 STATIC_TABLE[12]->headerValue =  "400";

        /* 13 */ STATIC_TABLE[13]->headerName = ":status";
                 STATIC_TABLE[13]->headerValue =  "404";

        /* 14 */ STATIC_TABLE[14]->headerName = ":status";
                 STATIC_TABLE[14]->headerValue =  "500";

        /* 15 */ STATIC_TABLE[15]->headerName = "accept-charset";

        /* 16 */ STATIC_TABLE[16]->headerName = "accept-encoding";
                 STATIC_TABLE[16]->headerValue = "gzip, deflate";

        /* 17 */ STATIC_TABLE[17]->headerName = "accept-language";
        /* 18 */ STATIC_TABLE[18]->headerName = "accept-ranges";
        /* 19 */ STATIC_TABLE[19]->headerName = "accept";
        /* 20 */ STATIC_TABLE[20]->headerName = "access-control-allow-origin";
        /* 21 */ STATIC_TABLE[21]->headerName = "age";
        /* 22 */ STATIC_TABLE[22]->headerName = "allow";
        /* 23 */ STATIC_TABLE[23]->headerName =  "authorization";
        /* 24 */ STATIC_TABLE[24]->headerName =  "cache-control";
        /* 25 */ STATIC_TABLE[25]->headerName =  "content-disposition";
        /* 26 */ STATIC_TABLE[26]->headerName = "content-encoding";
        /* 27 */ STATIC_TABLE[27]->headerName = "content-language";
        /* 28 */ STATIC_TABLE[28]->headerName = "content-length";
        /* 29 */ STATIC_TABLE[29]->headerName = "content-location";
        /* 30 */ STATIC_TABLE[30]->headerName = "content-range";
        /* 31 */ STATIC_TABLE[31]->headerName = "content-type";
        /* 32 */ STATIC_TABLE[32]->headerName = "cookie";
        /* 33 */ STATIC_TABLE[33]->headerName = "date";
        /* 34 */ STATIC_TABLE[34]->headerName = "etag";
        /* 35 */ STATIC_TABLE[35]->headerName = "expect";
        /* 36 */ STATIC_TABLE[36]->headerName = "expires";
        /* 37 */ STATIC_TABLE[37]->headerName = "from";
        /* 38 */ STATIC_TABLE[38]->headerName = "host";
        /* 39 */ STATIC_TABLE[39]->headerName = "if-match";
        /* 40 */ STATIC_TABLE[40]->headerName = "if-modified-since";
        /* 41 */ STATIC_TABLE[41]->headerName = "if-none-match";
        /* 42 */ STATIC_TABLE[42]->headerName = "if-range";
        /* 43 */ STATIC_TABLE[43]->headerName = "if-unmodified-since";
        /* 44 */ STATIC_TABLE[44]->headerName = "last-modified";
        /* 45 */ STATIC_TABLE[45]->headerName = "link";
        /* 46 */ STATIC_TABLE[46]->headerName = "location";
        /* 47 */ STATIC_TABLE[47]->headerName = "max-forwards";
        /* 48 */ STATIC_TABLE[48]->headerName = "proxy-authenticate";
        /* 49 */ STATIC_TABLE[49]->headerName = "proxy-authorization";
        /* 50 */ STATIC_TABLE[50]->headerName = "range";
        /* 51 */ STATIC_TABLE[51]->headerName = "referer";
        /* 52 */ STATIC_TABLE[52]->headerName = "refresh";
        /* 53 */ STATIC_TABLE[53]->headerName = "retry-after";
        /* 54 */ STATIC_TABLE[54]->headerName = "server";
        /* 55 */ STATIC_TABLE[55]->headerName = "set-cookie";
        /* 56 */ STATIC_TABLE[56]->headerName = "strict-transport-security";
        /* 57 */ STATIC_TABLE[57]->headerName = "transfer-encoding";
        /* 58 */ STATIC_TABLE[58]->headerName = "user-agent";
        /* 59 */ STATIC_TABLE[59]->headerName = "vary";
        /* 60 */ STATIC_TABLE[60]->headerName = "via";
        /* 61 */ STATIC_TABLE[61]->headerName = "www-authenticate";
    });
}

Http2HpackTableItem _Http2HpackStaticTable::get(int id) {
    if(id > IdMax || id < 1) {
        return nullptr;
    }

    return STATIC_TABLE[id];
}

}
