#ifndef __OBOTCHA_HTTP_HEADER_SEC_FETCH_DEST_HPP__
#define __OBOTCHA_HTTP_HEADER_SEC_FETCH_DEST_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderSecFetchDest) {

public:
    _HttpHeaderSecFetchDest();
    _HttpHeaderSecFetchDest(String);

    void import(String);

    void set(String);

    String get();

    String toString();

    static const String Audio;
    static const String AudioWorklet;
    static const String Document;
    static const String Embed;
    static const String Empty;
    static const String Font;
    static const String Image;
    static const String Manifest;
    static const String Object;
    static const String PaintWorklet;
    static const String Report;
    static const String Script;
    static const String ServiceWorker;
    static const String SharedWorker;
    static const String Style;
    static const String Track;
    static const String Video;
    static const String Worker;
    static const String Xslt;
    static const String NestedDocument;

private:
    String value;
};

}
#endif
