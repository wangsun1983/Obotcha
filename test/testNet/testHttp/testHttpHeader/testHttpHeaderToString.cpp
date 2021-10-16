#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderParser.hpp"
#include "ByteRingArrayReader.hpp"
#include "HttpMethod.hpp"
#include "HttpAcceptCharSet.hpp"
#include "Math.hpp"
#include "HttpProtocol.hpp"

using namespace obotcha;

void testHttpHeaderToString() {
  while(1) {
    const char *raw= "GET /demo HTTP/1.1\r\n"
                 "Accept-Charset: utf-8, iso-8859-1;q=0.5\r\n"
                 "Accept-Encoding: deflate, gzip;q=1.0, *;q=0.5\r\n"
                 "Accept-Language: fr-CH, fr;q=0.9, en;q=0.8, de;q=0.7, *;q=0.5\r\n"
                 "Accept-Patch: application/example, text/example\r\n"
                 "Accept: text/html, application/xhtml+xml, application/xml;q=0.9, */*;q=0.8\r\n"
                 "Allow: GET, POST, HEAD\r\n"
                 "Authorization: Basic YWxhZGRpbjpvcGVuc2VzYW1l\r\n"
                 "Content-Disposition: form-data; name=\"fieldName\"; filename=\"filename.jpg\"\r\n"
                 "Content-Encoding: identity\r\n"
                 "Cache-Control: max-age=1000\r\n"
                 "Content-Length: 2000\r\n"
                 "Link: <https://example.com>; rel=\"preload\"\r\n"
                 "X-Frame-Options: allow-from https://example.com/\r\n"
                 "\r\n"
                 "Hot diggity dogg";

    ByteRingArray ringArray = createByteRingArray(1024*4);
    ringArray->push((byte *)raw,0,strlen(raw));
    ByteRingArrayReader reader = createByteRingArrayReader(ringArray);
    HttpHeaderParser parser = createHttpHeaderParser(reader);
    HttpHeader header1 = parser->doParse();

    String result = header1->toString(st(HttpProtocol)::HttpRequest);

    result = result->append("\r\n\r\n");
    //reparse again
    ByteRingArray ringArray2 = createByteRingArray(1024*4);
    ringArray2->push(result->toByteArray());
    ByteRingArrayReader reader2 = createByteRingArrayReader(ringArray2);
    HttpHeaderParser parser2 = createHttpHeaderParser(reader2);
    HttpHeader header2 = parser2->doParse();

    //check header1 && header2
    if(header1->getMethod() != header2->getMethod()) {
      printf("---[HttpHeaderToString test Parse case1] [FAILED]--- method is %d\n",header1->getMethod());
      break;
    }

    if(!header1->getUrl()->toString()->equals(header2->getUrl()->toString())) {
      printf("---[HttpHeaderToString test Parse case2] [FAILED]--- url is %s\n",header2->getUrl()->toString()->toChars());
      break;
    }

    if(header1->getVersion()->getMajorVer() != header2->getVersion()->getMajorVer()) {
      printf("---[HttpHeaderToString test Parse case3] [FAILED]--- ver is %s\n",header1->getVersion()->toString()->toChars());
      break;
    }

    if(header1->getVersion()->getMinorVer() != header2->getVersion()->getMinorVer()) {
      printf("---[HttpHeaderToString test Parse case3_1] [FAILED]--- ver is %s\n",header1->getVersion()->toString()->toChars());
      break;
    }

    //Charset
    auto charset1 = header1->getAcceptCharSet();
    auto charset2 = header2->getAcceptCharSet();
    if(charset1 == nullptr || charset2 == nullptr) {
      printf("---[HttpHeaderToString test Parse case4] [FAILED]--- \n");
      break;
    }

    ArrayList<HttpAcceptCharSetItem> charsets1 = charset1->getCharSets();
    ArrayList<HttpAcceptCharSetItem> charsets2 = charset1->getCharSets();
    if(charsets1->size() != 2 || charsets2->size() != 2) {
      printf("---[HttpHeaderToString test Parse case5] [FAILED]--- \n");
      break;
    }

    HttpAcceptCharSetItem charSetItem1_0 = charsets1->get(0);
    HttpAcceptCharSetItem charSetItem2_0 = charsets2->get(0);
    if(!charSetItem1_0->type->equalsIgnoreCase(charSetItem2_0->type)) {
      printf("---[HttpHeaderToString test Parse case6] [FAILED]--- \n");
      break;
    }

    HttpAcceptCharSetItem charSetItem1_1 = charsets1->get(1);
    HttpAcceptCharSetItem charSetItem2_1 = charsets2->get(1);
    if(!charSetItem1_1->type->equalsIgnoreCase(charSetItem2_1->type)) {
      printf("---[HttpHeaderToString test Parse case7] [FAILED]--- \n");
      break;
    }

    HttpAcceptCharSetItem charSetItem1_2 = charsets1->get(1);
    HttpAcceptCharSetItem charSetItem2_2 = charsets2->get(1);
    if(st(Math)::compareFloat(charSetItem1_2->weight,charSetItem2_2->weight) != st(Math)::AlmostEqual) {
      printf("---[HttpHeaderToString test Parse case8] [FAILED]--- \n");
      break;
    }

    //Encoding
    //Accept-Encoding: deflate, gzip;q=1.0, *;q=0.5\r\n
    HttpAcceptEncoding encoding1 = header1->getAcceptEncoding();
    HttpAcceptEncoding encoding2 = header2->getAcceptEncoding();

    ArrayList<HttpAcceptEncodingItem> encodings1 = encoding1->getEncodings();
    ArrayList<HttpAcceptEncodingItem> encodings2 = encoding2->getEncodings();
    if(encodings1->size() != 3 || encodings2->size() != 3) {
      printf("---[HttpHeaderToString test Parse case9] [FAILED]--- \n");
      break;
    }

    HttpAcceptEncodingItem encodingItem1_0 = encodings1->get(0);
    HttpAcceptEncodingItem encodingItem2_0 = encodings2->get(0);
    if(!encodingItem1_0->type->equals(encodingItem1_0->type)) {
      printf("---[HttpHeaderToString test Parse case9] [FAILED]--- \n");
      break;
    }

    HttpAcceptEncodingItem encodingItem1_1 = encodings1->get(1);
    HttpAcceptEncodingItem encodingItem2_1 = encodings2->get(1);
    if(!encodingItem1_1->type->equals(encodingItem2_1->type)) {
      printf("---[HttpHeaderToString test Parse case10] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(encodingItem1_1->weight,encodingItem2_1->weight) != st(Math)::AlmostEqual) {
      printf("---[HttpHeaderToString test Parse case11] [FAILED]--- weight is %lf \n",encodingItem2_1->weight);
      break;
    }

    HttpAcceptEncodingItem encodingItem1_2 = encodings1->get(2);
    HttpAcceptEncodingItem encodingItem2_2 = encodings2->get(2);
    if(!encodingItem1_2->type->equals(encodingItem2_2->type)) {
      printf("---[HttpHeaderToString test Parse case12] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(encodingItem1_2->weight,encodingItem2_2->weight) != st(Math)::AlmostEqual) {
      printf("---[HttpHeaderToString test Parse case13] [FAILED]--- \n");
      break;
    }

    //Accept-Language: fr-CH, fr;q=0.9, en;q=0.8, de;q=0.7, *;q=0.5
    HttpAcceptLanguage mAcceptLang1 = header1->getAcceptLanguage();
    HttpAcceptLanguage mAcceptLang2 = header2->getAcceptLanguage();

    ArrayList<HttpAcceptLanguageItem> langs1 = mAcceptLang1->getLanguages();
    ArrayList<HttpAcceptLanguageItem> langs2 = mAcceptLang2->getLanguages();

    if(langs1->size() != 5 || langs2->size() != 5) {
      printf("---[HttpHeaderToString test Parse case14] [FAILED]--- \n");
      break;
    }

    HttpAcceptLanguageItem langItem1_0 = langs1->get(0);
    HttpAcceptLanguageItem langItem2_0 = langs2->get(0);

    if(!langItem1_0->lang->equals(langItem2_0->lang)) {
      printf("---[HttpHeaderToString test Parse case15] [FAILED]--- \n");
      break;
    }

    HttpAcceptLanguageItem langItem1_1 = langs1->get(1);
    HttpAcceptLanguageItem langItem2_1 = langs2->get(1);

    if(!langItem1_1->lang->equals(langItem2_1->lang)) {
      printf("---[HttpHeaderToString test Parse case16] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(langItem1_1->weight,langItem2_1->weight) != st(Math)::AlmostEqual) {
      printf("---[HttpHeaderToString test Parse case17] [FAILED]--- \n");
      break;
    }

    HttpAcceptLanguageItem langItem1_2 = langs1->get(2);
    HttpAcceptLanguageItem langItem2_2 = langs2->get(2);
    if(!langItem1_2->lang->equals(langItem2_2->lang)) {
      printf("---[HttpHeaderToString test Parse case18] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(langItem1_2->weight,langItem2_2->weight) != st(Math)::AlmostEqual) {
      printf("---[HttpHeaderToString test Parse case19] [FAILED]--- \n");
      break;
    }

    HttpAcceptLanguageItem langItem1_3 = langs1->get(3);
    HttpAcceptLanguageItem langItem2_3 = langs2->get(3);
    if(!langItem1_3->lang->equals(langItem2_3->lang)) {
      printf("---[HttpHeaderToString test Parse case20] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(langItem1_3->weight,langItem2_3->weight) != st(Math)::AlmostEqual) {
      printf("---[HttpHeaderToString test Parse case21] [FAILED]--- \n");
      break;
    }

    HttpAcceptLanguageItem langItem1_4 = langs1->get(4);
    HttpAcceptLanguageItem langItem2_4 = langs2->get(4);
    if(!langItem1_4->lang->equals(langItem2_4->lang)) {
      printf("---[HttpHeaderToString test Parse case22] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(langItem1_4->weight,langItem2_4->weight) != st(Math)::AlmostEqual) {
      printf("---[HttpHeaderToString test Parse case23] [FAILED]--- \n");
      break;
    }

    //Accept-Patch: application/example, text/example
    HttpAcceptPatch patch1 = header1->getAcceptPatch();
    HttpAcceptPatch patch2 = header2->getAcceptPatch();

    ArrayList<HttpAcceptPatchItem> patches1 = patch1->getAcceptPatches();
    ArrayList<HttpAcceptPatchItem> patches2 = patch2->getAcceptPatches();

    HttpAcceptPatchItem patchItem1_0 = patches1->get(0);
    HttpAcceptPatchItem patchItem2_0 = patches2->get(0);
    if(!patchItem1_0->type->equals(patchItem2_0->type)) {
      printf("---[HttpHeaderToString test Parse case24] [FAILED]--- \n");
      break;
    }

    HttpAcceptPatchItem patchItem1_1 = patches1->get(1);
    HttpAcceptPatchItem patchItem2_1 = patches2->get(1);
    if(!patchItem1_1->type->equals(patchItem2_1->type)) {
      printf("---[HttpHeaderToString test Parse case25] [FAILED]--- \n");
      break;
    }

    //Accept: text/html, application/xhtml+xml, application/xml;q=0.9, */*;q=0.8
    HttpAccept accept1 = header1->getAccept();
    HttpAccept accept2 = header2->getAccept();
    ArrayList<HttpAcceptItem> accepts1 = accept1->getAccepts();
    ArrayList<HttpAcceptItem> accepts2 = accept2->getAccepts();
    if(accepts1->size() != accepts2->size()) {
      printf("---[HttpHeaderToString test Parse case26_0] [FAILED]--- \n");
      break;
    }

    HttpAcceptItem acceptItem1_0 = accepts1->get(0);
    HttpAcceptItem acceptItem2_0 = accepts2->get(0);
    if(!acceptItem1_0->type->equals(acceptItem2_0->type)) {
      printf("---[HttpHeaderToString test Parse case26] [FAILED]---\n");
      break;
    }

    HttpAcceptItem acceptItem1_1 = accepts1->get(1);
    HttpAcceptItem acceptItem2_1 = accepts2->get(1);
    if(!acceptItem1_1->type->equals(acceptItem2_1->type)) {
      printf("---[HttpHeaderToString test Parse case27] [FAILED]--- \n");
      break;
    }

    HttpAcceptItem acceptItem1_2 = accepts1->get(2);
    HttpAcceptItem acceptItem2_2 = accepts2->get(2);
    if(!acceptItem1_2->type->equals(acceptItem2_2->type)) {
      printf("---[HttpHeaderToString test Parse case28] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(acceptItem1_2->weight,acceptItem2_2->weight) != st(Math)::AlmostEqual) {
      printf("---[HttpHeaderToString test Parse case29] [FAILED]--- \n");
      break;
    }

    HttpAcceptItem acceptItem1_3 = accepts1->get(3);
    HttpAcceptItem acceptItem2_3 = accepts2->get(3);
    if(!acceptItem1_3->type->equals(acceptItem2_3->type)) {
      printf("---[HttpHeaderToString test Parse case30] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(acceptItem1_3->weight,acceptItem2_3->weight) != st(Math)::AlmostEqual) {
      printf("---[HttpHeaderToString test Parse case31] [FAILED]--- \n");
      break;
    }

    //"Allow: GET, POST, HEAD\r\n"
    String allow1 = header1->get("Allow");
    String allow2 = header2->get("Allow");
    if(!allow1->equals(allow2)) {
      printf("---[HttpHeaderToString test Parse case32] [FAILED]--- ,allow is %s\n",allow1->toChars());
      break;
    }

    //Authorization: Basic YWxhZGRpbjpvcGVuc2VzYW1l
    HttpAuthorization authorization1 = header1->getAuthorization();
    HttpAuthorization authorization2 = header2->getAuthorization();
    if(!authorization1->type->equals(authorization2->type)) {
      printf("---[HttpHeaderToString test Parse case33] [FAILED]--- \n");
      break;
    }

    if(!authorization1->credentials->equals(authorization2->credentials)) {
      printf("---[HttpHeaderToString test Parse case34] [FAILED]--- \n");
      break;
    }

    //Content-Disposition: form-data; name=\"fieldName\"; filename=\"filename.jpg\"
    HttpContentDisposition contentDisp1 = header1->getContentDisposition();
    HttpContentDisposition contentDisp2 = header2->getContentDisposition();
    if(!contentDisp1->type->equals(contentDisp2->type)) {
      printf("---[HttpHeaderToString test Parse case35] [FAILED]--- \n");
      break;
    }

    if(!contentDisp1->name->equals(contentDisp2->name)) {
      printf("---[HttpHeaderToString test Parse case36] [FAILED]--- \n");
      break;
    }

    if(!contentDisp1->filename->equals(contentDisp2->filename)) {
      printf("---[HttpHeaderToString test Parse case37] [FAILED]--- \n");
      break;
    }

    //Content-Encoding: identity
    String contentEncoding1 = header1->get("Content-Encoding");
    String contentEncoding2 = header2->get("Content-Encoding");
    if(!contentEncoding1->equals(contentEncoding2)) {
      printf("---[HttpHeaderToString test Parse case38] [FAILED]--- \n");
      break;
    }

    //Cache-Control: max-age=1000
    HttpCacheControl cachecontrol1 = header1->getCacheControl();
    HttpCacheControl cachecontrol2 = header2->getCacheControl();
    if(cachecontrol1->maxAgeSeconds() != cachecontrol2->maxAgeSeconds()) {
      printf("---[HttpHeaderToString test Parse case39] [FAILED]--- \n");
      break;
    }

    //Content-Length: 2000
    int contentLen1 = header1->getContentLength();
    int contentLen2 = header2->getContentLength();
    if(contentLen1 != contentLen2) {
      printf("---[HttpHeaderToString test Parse case40] [FAILED]--- \n");
      break;
    }

    //Link: <https://example.com>; rel="preload"
    ArrayList<HttpHeaderLink> links1 = header1->getHeaderLinks();
    ArrayList<HttpHeaderLink> links2 = header2->getHeaderLinks();
    if(links1->size() != 1 || links2->size() != 1) {
      printf("---[HttpHeaderToString test Parse case41] [FAILED]--- \n");
      break;
    }

    HttpHeaderLink link1_0 = links1->get(0);
    HttpHeaderLink link2_0 = links2->get(0);
    if(!link1_0->url->equals(link2_0->url)) {
      printf("---[HttpHeaderToString test Parse case42] [FAILED]--- \n");
      break;
    }

    if(!link1_0->rel->equals(link2_0->rel)) {
      printf("---[HttpHeaderToString test Parse case43] [FAILED]--- \n");
      break;
    }

    //X-Frame-Options: allow-from https://example.com/
    HttpXFrameOptions xframeoption1 = header1->getXFrameOptions();
    HttpXFrameOptions xframeoption2 = header2->getXFrameOptions();
    if(!xframeoption1->option->equals(xframeoption2->option)) {
      printf("---[HttpHeaderToString test Parse case44] [FAILED]--- \n");
      break;
    }

    if(!xframeoption1->uri->equals(xframeoption2->uri)) {
      printf("---[HttpHeaderToString test Parse case45] [FAILED]--- \n");
      break;
    }

    break;
  }

  printf("---[HttpHeader test toString case100] [OK]--- \n");

}
