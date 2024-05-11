#include "HttpHeaderSecFetchDest.hpp"

namespace obotcha {

const String _HttpHeaderSecFetchDest::Audio = String::New("audio");
const String _HttpHeaderSecFetchDest::AudioWorklet = String::New("audioworklet");
const String _HttpHeaderSecFetchDest::Document = String::New("document");
const String _HttpHeaderSecFetchDest::Embed = String::New("embed");
const String _HttpHeaderSecFetchDest::Empty = String::New("empty");
const String _HttpHeaderSecFetchDest::Font = String::New("font");
const String _HttpHeaderSecFetchDest::Image = String::New("image");
const String _HttpHeaderSecFetchDest::Manifest = String::New("manifest");
const String _HttpHeaderSecFetchDest::Object = String::New("object");
const String _HttpHeaderSecFetchDest::PaintWorklet = String::New("paintworklet");
const String _HttpHeaderSecFetchDest::Report = String::New("report");
const String _HttpHeaderSecFetchDest::Script = String::New("script");
const String _HttpHeaderSecFetchDest::ServiceWorker = String::New("serviceworker");
const String _HttpHeaderSecFetchDest::SharedWorker = String::New("sharedworker");
const String _HttpHeaderSecFetchDest::Style = String::New("style");
const String _HttpHeaderSecFetchDest::Track = String::New("track");
const String _HttpHeaderSecFetchDest::Video = String::New("video");
const String _HttpHeaderSecFetchDest::Worker = String::New("worker");
const String _HttpHeaderSecFetchDest::Xslt = String::New("xslt");
const String _HttpHeaderSecFetchDest::NestedDocument = String::New("nested-document");

_HttpHeaderSecFetchDest::_HttpHeaderSecFetchDest(String s) {
    load(s);
}

void _HttpHeaderSecFetchDest::load(String s) {
    value = s->trim();
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
