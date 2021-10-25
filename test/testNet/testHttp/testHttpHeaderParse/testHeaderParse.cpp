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

using namespace obotcha;

void testHttpHeaderParse() {
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
    HttpHeader header = parser->doParse();

    if(header->getMethod() != st(HttpMethod)::Get) {
      printf("---[HttpHeaderParse test Parse case1] [FAILED]--- method is %d\n",header->getMethod());
      break;
    }

    if(!header->getUrl()->toString()->equals("/demo")) {
      printf("---[HttpHeaderParse test Parse case2] [FAILED]--- url is %s\n",header->getUrl()->toString()->toChars());
      break;
    }

    if(!header->getVersion()->toString()->equals("HTTP/1.1")) {
      printf("---[HttpHeaderParse test Parse case3] [FAILED]--- ver is %s\n",header->getVersion()->toString()->toChars());
      break;
    }

    //Charset
    auto charset = header->getAcceptCharSet();
    if(charset == nullptr) {
      printf("---[HttpHeaderParse test Parse case4] [FAILED]--- \n");
      break;
    }

    ArrayList<HttpAcceptCharSetItem> charsets = charset->get();
    if(charsets->size() != 2) {
      printf("---[HttpHeaderParse test Parse case5] [FAILED]--- \n");
      break;
    }

    HttpAcceptCharSetItem charSetItem1 = charsets->get(0);
    if(!charSetItem1->type->equalsIgnoreCase("utf-8")) {
      printf("---[HttpHeaderParse test Parse case6] [FAILED]--- char set is %s \n",charSetItem1->type->toChars());
      break;
    }

    HttpAcceptCharSetItem charSetItem2 = charsets->get(1);
    if(!charSetItem2->type->equalsIgnoreCase("iso-8859-1")) {
      printf("---[HttpHeaderParse test Parse case7] [FAILED]--- char set is %s \n",charSetItem2->type->toChars());
      break;
    }

    if(st(Math)::compareFloat(charSetItem2->weight,0.5) != st(Math)::AlmostEqual) {
      printf("---[HttpHeaderParse test Parse case8] [FAILED]--- charSetItem2->weight is %lf \n",charSetItem2->weight);
      break;
    }

    //Encoding
    //Accept-Encoding: deflate, gzip;q=1.0, *;q=0.5\r\n
    HttpAcceptEncoding encoding = header->getAcceptEncoding();
    ArrayList<HttpAcceptEncodingItem> encodings = encoding->get();
    if(encodings->size() != 3) {
      printf("---[HttpHeaderParse test Parse case9] [FAILED]--- \n");
      break;
    }

    HttpAcceptEncodingItem encodingItem0 = encodings->get(0);
    if(!encodingItem0->type->equals("deflate")) {
      printf("---[HttpHeaderParse test Parse case9] [FAILED]--- \n");
      break;
    }

    HttpAcceptEncodingItem encodingItem1 = encodings->get(1);
    if(!encodingItem1->type->equals("gzip")) {
      printf("---[HttpHeaderParse test Parse case10] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(encodingItem1->weight,1.0) != st(Math)::AlmostEqual) {
      printf("---[HttpHeaderParse test Parse case11] [FAILED]--- weight is %lf \n",encodingItem1->weight);
      break;
    }

    HttpAcceptEncodingItem encodingItem2 = encodings->get(2);
    if(!encodingItem2->type->equals("*")) {
      printf("---[HttpHeaderParse test Parse case12] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(encodingItem2->weight,0.5) != st(Math)::AlmostEqual) {
      printf("---[HttpHeaderParse test Parse case13] [FAILED]--- \n");
      break;
    }

    //Accept-Language: fr-CH, fr;q=0.9, en;q=0.8, de;q=0.7, *;q=0.5
    HttpAcceptLanguage mAcceptLang = header->getAcceptLanguage();
    ArrayList<HttpAcceptLanguageItem> langs = mAcceptLang->get();
    if(langs->size() != 5) {
      printf("---[HttpHeaderParse test Parse case14] [FAILED]--- \n");
      break;
    }

    HttpAcceptLanguageItem langItem1 = langs->get(0);
    if(!langItem1->lang->equals("fr-CH")) {
      printf("---[HttpHeaderParse test Parse case15] [FAILED]--- \n");
      break;
    }

    HttpAcceptLanguageItem langItem2 = langs->get(1);
    if(!langItem2->lang->equals("fr")) {
      printf("---[HttpHeaderParse test Parse case16] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(langItem2->weight,0.9) != st(Math)::AlmostEqual) {
      printf("---[HttpHeaderParse test Parse case17] [FAILED]--- \n");
      break;
    }

    HttpAcceptLanguageItem langItem3 = langs->get(2);
    if(!langItem3->lang->equals("en")) {
      printf("---[HttpHeaderParse test Parse case18] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(langItem3->weight,0.8) != st(Math)::AlmostEqual) {
      printf("---[HttpHeaderParse test Parse case19] [FAILED]--- \n");
      break;
    }

    HttpAcceptLanguageItem langItem4 = langs->get(3);
    if(!langItem4->lang->equals("de")) {
      printf("---[HttpHeaderParse test Parse case20] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(langItem4->weight,0.7) != st(Math)::AlmostEqual) {
      printf("---[HttpHeaderParse test Parse case21] [FAILED]--- \n");
      break;
    }

    HttpAcceptLanguageItem langItem5 = langs->get(4);
    if(!langItem5->lang->equals("*")) {
      printf("---[HttpHeaderParse test Parse case22] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(langItem5->weight,0.5) != st(Math)::AlmostEqual) {
      printf("---[HttpHeaderParse test Parse case23] [FAILED]--- \n");
      break;
    }

    //Accept-Patch: application/example, text/example
    HttpAcceptPatch patch = header->getAcceptPatch();
    ArrayList<HttpAcceptPatchItem> patches = patch->get();
    HttpAcceptPatchItem patchItem1 = patches->get(0);
    if(!patchItem1->type->equals("application/example")) {
      printf("---[HttpHeaderParse test Parse case24] [FAILED]--- \n");
      break;
    }

    HttpAcceptPatchItem patchItem2 = patches->get(1);
    if(!patchItem2->type->equals("text/example")) {
      printf("---[HttpHeaderParse test Parse case25] [FAILED]--- \n");
      break;
    }

    //Accept: text/html, application/xhtml+xml, application/xml;q=0.9, */*;q=0.8
    HttpAccept accept = header->getAccept();
    ArrayList<HttpAcceptItem> accepts = accept->get();
    if(accepts->size() != 4) {
      printf("---[HttpHeaderParse test Parse case26_0] [FAILED]--- \n");
      break;
    }

    HttpAcceptItem acceptItem1 = accepts->get(0);
    if(!acceptItem1->type->equals("text/html")) {
      printf("---[HttpHeaderParse test Parse case26] [FAILED]--- ,type is %s\n",acceptItem1->type->toChars());
      break;
    }

    HttpAcceptItem acceptItem2 = accepts->get(1);
    if(!acceptItem2->type->equals("application/xhtml+xml")) {
      printf("---[HttpHeaderParse test Parse case27] [FAILED]--- \n");
      break;
    }

    HttpAcceptItem acceptItem3 = accepts->get(2);
    if(!acceptItem3->type->equals("application/xml")) {
      printf("---[HttpHeaderParse test Parse case28] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(acceptItem3->weight,0.9) != st(Math)::AlmostEqual) {
      printf("---[HttpHeaderParse test Parse case29] [FAILED]--- \n");
      break;
    }

    HttpAcceptItem acceptItem4 = accepts->get(3);
    if(!acceptItem4->type->equals("*/*")) {
      printf("---[HttpHeaderParse test Parse case30] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(acceptItem4->weight,0.8) != st(Math)::AlmostEqual) {
      printf("---[HttpHeaderParse test Parse case31] [FAILED]--- \n");
      break;
    }

    //"Allow: GET, POST, HEAD\r\n"
    ArrayList<Integer> allows = header->getAllow()->get();
    if(allows->size() != 3) {
      printf("---[HttpHeaderParse test Parse case32] [FAILED]--- \n");
      break;
    }

    if(allows->get(0)->toValue() != st(HttpMethod)::Get) {
      printf("---[HttpHeaderParse test Parse case32_1] [FAILED]--- \n");
      break;
    }

    if(allows->get(1)->toValue() != st(HttpMethod)::Post) {
      printf("---[HttpHeaderParse test Parse case32_2] [FAILED]--- \n");
      break;
    }

    if(allows->get(2)->toValue() != st(HttpMethod)::Head) {
      printf("---[HttpHeaderParse test Parse case32_3] [FAILED]--- \n");
      break;
    }

    //Authorization: Basic YWxhZGRpbjpvcGVuc2VzYW1l
    HttpAuthorization authorization = header->getAuthorization();
    if(!authorization->type->equals("Basic")) {
      printf("---[HttpHeaderParse test Parse case33] [FAILED]--- \n");
      break;
    }

    if(!authorization->credentials->equals("YWxhZGRpbjpvcGVuc2VzYW1l")) {
      printf("---[HttpHeaderParse test Parse case34] [FAILED]--- \n");
      break;
    }

    //Content-Disposition: form-data; name=\"fieldName\"; filename=\"filename.jpg\"
    HttpContentDisposition contentDisp = header->getContentDisposition();
    if(!contentDisp->type->equals("form-data")) {
      printf("---[HttpHeaderParse test Parse case35] [FAILED]--- \n");
      break;
    }

    if(!contentDisp->name->equals("fieldName")) {
      printf("---[HttpHeaderParse test Parse case36] [FAILED]--- \n");
      break;
    }

    if(!contentDisp->filename->equals("filename.jpg")) {
      printf("---[HttpHeaderParse test Parse case37] [FAILED]--- \n");
      break;
    }

    //Content-Encoding: identity
    ArrayList<String> contentEncoding = header->getContentEncoding()->get();
    if(contentEncoding->size() != 1) {
      printf("---[HttpHeaderParse test Parse case38] [FAILED]--- \n");
      break;
    }

    if(!contentEncoding->get(0)->equals("identity")) {
      printf("---[HttpHeaderParse test Parse case38_1] [FAILED]--- \n");
      break;
    }

    //Cache-Control: max-age=1000
    HttpCacheControl cachecontrol = header->getCacheControl();
    if(cachecontrol->maxAgeSeconds() != 1000) {
      printf("---[HttpHeaderParse test Parse case39] [FAILED]--- \n");
      break;
    }

    //Content-Length: 2000
    int contentLen = header->getContentLength()->get();
    if(contentLen != 2000) {
      printf("---[HttpHeaderParse test Parse case40] [FAILED]--- \n");
      break;
    }

    //Link: <https://example.com>; rel="preload"
    ArrayList<HttpHeaderLink> links = header->getLinks();
    if(links->size() != 1) {
      printf("---[HttpHeaderParse test Parse case41] [FAILED]--- \n");
      break;
    }

    HttpHeaderLink link = links->get(0);
    if(!link->url->equals("https://example.com")) {
      printf("---[HttpHeaderParse test Parse case42] [FAILED]--- \n");
      break;
    }

    if(!link->rel->equals("preload")) {
      printf("---[HttpHeaderParse test Parse case43] [FAILED]--- \n");
      break;
    }

    //X-Frame-Options: allow-from https://example.com/
    HttpXFrameOptions xframeoption = header->getXFrameOptions();
    if(!xframeoption->option->equals("allow-from")) {
      printf("---[HttpHeaderParse test Parse case44] [FAILED]--- \n");
      break;
    }

    if(!xframeoption->uri->equals("https://example.com/")) {
      printf("---[HttpHeaderParse test Parse case45] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpHeaderParse test Parse case100] [OK]--- \n");

}
