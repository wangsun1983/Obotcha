#include "HttpHeaderSecFetchDest.hpp"

namespace obotcha {

const String _HttpHeaderSecFetchDest::Audio = createString("audio");
const String _HttpHeaderSecFetchDest::AudioWorklet = createString("audioworklet");
const String _HttpHeaderSecFetchDest::Document = createString("document");
const String _HttpHeaderSecFetchDest::Embed = createString("embed");
const String _HttpHeaderSecFetchDest::Empty = createString("empty");
const String _HttpHeaderSecFetchDest::Font = createString("font");
const String _HttpHeaderSecFetchDest::Image = createString("image");
const String _HttpHeaderSecFetchDest::Manifest = createString("manifest");
const String _HttpHeaderSecFetchDest::Object = createString("object");
const String _HttpHeaderSecFetchDest::PaintWorklet = createString("paintworklet");
const String _HttpHeaderSecFetchDest::Report = createString("report");
const String _HttpHeaderSecFetchDest::Script = createString("script");
const String _HttpHeaderSecFetchDest::ServiceWorker = createString("serviceworker");
const String _HttpHeaderSecFetchDest::SharedWorker = createString("sharedworker");
const String _HttpHeaderSecFetchDest::Style = createString("style");
const String _HttpHeaderSecFetchDest::Track = createString("track");
const String _HttpHeaderSecFetchDest::Video = createString("video");
const String _HttpHeaderSecFetchDest::Worker = createString("worker");
const String _HttpHeaderSecFetchDest::Xslt = createString("xslt");
const String _HttpHeaderSecFetchDest::NestedDocument = createString("nested-document");

_HttpHeaderSecFetchDest::_HttpHeaderSecFetchDest() {
    
}

_HttpHeaderSecFetchDest::_HttpHeaderSecFetchDest(String s) {
    import(s);
}

void _HttpHeaderSecFetchDest::import(String s) {
    value = s;
}

void _HttpHeaderSecFetchDest::set(String s) {
    value = s->trim();
}

String _HttpHeaderSecFetchDest::get() {
    return value;
}

String _HttpHeaderSecFetchDest::toString() {
    return value;
}


}
