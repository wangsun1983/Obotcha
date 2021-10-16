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
#include "HttpMethod.hpp"

using namespace obotcha;

void testHttpHeaderSet() {
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

    HttpHeader header = createHttpHeader();
    header->setMethod(st(HttpMethod)::Get);

    HttpUrl url = createHttpUrl();
    url->setPath("demo");
    header->setUrl(url);

    header->setVersion(createHttpVersion(1,1));
    header->set("Accept-Charset","utf-8, iso-8859-1;q=0.5");
    header->set("Accept-Encoding","deflate, gzip;q=1.0, *;q=0.5");
    header->set("Accept-Language","fr-CH, fr;q=0.9, en;q=0.8, de;q=0.7, *;q=0.5");
    header->set("Accept-Patch","application/example, text/example");
    header->set("Accept","text/html, application/xhtml+xml, application/xml;q=0.9, */*;q=0.8");
    header->set("Allow","GET, POST, HEAD");
    header->set("Authorization","Basic YWxhZGRpbjpvcGVuc2VzYW1l");
    header->set("Content-Disposition","form-data; name=\"fieldName\"; filename=\"filename.jpg\"");
    header->set("Content-Encoding","identity");
    header->set("Cache-Control","max-age=1000");
    header->set("Content-Length","2000");
    header->set("Link","<https://example.com>; rel=\"preload\"");
    header->set("X-Frame-Options","allow-from https://example.com/");

    //check
    if(header->getMethod() != st(HttpMethod)::Get) {
      printf("---[HttpHeader test Set case1] [FAILED]--- method is %d\n",header->getMethod());
      break;
    }

    if(!header->getUrl()->toString()->equals("/demo")) {
      printf("---[HttpHeader test Set case2] [FAILED]--- url is %s\n",header->getUrl()->toString()->toChars());
      break;
    }

    if(!header->getVersion()->toString()->equals("HTTP/1.1")) {
      printf("---[HttpHeader test Set case3] [FAILED]--- ver is %s\n",header->getVersion()->toString()->toChars());
      break;
    }

    //Charset
    auto charset = header->getAcceptCharSet();
    if(charset == nullptr) {
      printf("---[HttpHeader test Set case4] [FAILED]--- \n");
      break;
    }

    ArrayList<HttpAcceptCharSetItem> charsets = charset->getCharSets();
    if(charsets->size() != 2) {
      printf("---[HttpHeader test Set case5] [FAILED]--- \n");
      break;
    }

    HttpAcceptCharSetItem charSetItem1 = charsets->get(0);
    if(!charSetItem1->type->equalsIgnoreCase("utf-8")) {
      printf("---[HttpHeader test Set case6] [FAILED]--- char set is %s \n",charSetItem1->type->toChars());
      break;
    }

    HttpAcceptCharSetItem charSetItem2 = charsets->get(1);
    if(!charSetItem2->type->equalsIgnoreCase("iso-8859-1")) {
      printf("---[HttpHeader test Set case7] [FAILED]--- char set is %s \n",charSetItem2->type->toChars());
      break;
    }

    if(st(Math)::compareFloat(charSetItem2->weight,0.5) != st(Math)::AlmostEqual) {
      printf("---[HttpHeader test Set case8] [FAILED]--- char set is %s \n",charSetItem2->type->toChars());
      break;
    }

    //Encoding
    //Accept-Encoding: deflate, gzip;q=1.0, *;q=0.5\r\n
    HttpAcceptEncoding encoding = header->getAcceptEncoding();
    ArrayList<HttpAcceptEncodingItem> encodings = encoding->getEncodings();
    if(encodings->size() != 3) {
      printf("---[HttpHeader test Set case9] [FAILED]--- \n");
      break;
    }

    HttpAcceptEncodingItem encodingItem0 = encodings->get(0);
    if(!encodingItem0->type->equals("deflate")) {
      printf("---[HttpHeader test Set case9] [FAILED]--- \n");
      break;
    }

    HttpAcceptEncodingItem encodingItem1 = encodings->get(1);
    if(!encodingItem1->type->equals("gzip")) {
      printf("---[HttpHeader test Set case10] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(encodingItem1->weight,1.0) != st(Math)::AlmostEqual) {
      printf("---[HttpHeader test Set case11] [FAILED]--- weight is %lf \n",encodingItem1->weight);
      break;
    }

    HttpAcceptEncodingItem encodingItem2 = encodings->get(2);
    if(!encodingItem2->type->equals("*")) {
      printf("---[HttpHeader test Set case12] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(encodingItem2->weight,0.5) != st(Math)::AlmostEqual) {
      printf("---[HttpHeader test Set case13] [FAILED]--- \n");
      break;
    }

    //Accept-Language: fr-CH, fr;q=0.9, en;q=0.8, de;q=0.7, *;q=0.5
    HttpAcceptLanguage mAcceptLang = header->getAcceptLanguage();
    ArrayList<HttpAcceptLanguageItem> langs = mAcceptLang->getLanguages();
    if(langs->size() != 5) {
      printf("---[HttpHeader test Set case14] [FAILED]--- \n");
      break;
    }

    HttpAcceptLanguageItem langItem1 = langs->get(0);
    if(!langItem1->lang->equals("fr-CH")) {
      printf("---[HttpHeader test Set case15] [FAILED]--- \n");
      break;
    }

    HttpAcceptLanguageItem langItem2 = langs->get(1);
    if(!langItem2->lang->equals("fr")) {
      printf("---[HttpHeader test Set case16] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(langItem2->weight,0.9) != st(Math)::AlmostEqual) {
      printf("---[HttpHeader test Set case17] [FAILED]--- \n");
      break;
    }

    HttpAcceptLanguageItem langItem3 = langs->get(2);
    if(!langItem3->lang->equals("en")) {
      printf("---[HttpHeader test Set case18] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(langItem3->weight,0.8) != st(Math)::AlmostEqual) {
      printf("---[HttpHeader test Set case19] [FAILED]--- \n");
      break;
    }

    HttpAcceptLanguageItem langItem4 = langs->get(3);
    if(!langItem4->lang->equals("de")) {
      printf("---[HttpHeader test Set case20] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(langItem4->weight,0.7) != st(Math)::AlmostEqual) {
      printf("---[HttpHeader test Set case21] [FAILED]--- \n");
      break;
    }

    HttpAcceptLanguageItem langItem5 = langs->get(4);
    if(!langItem5->lang->equals("*")) {
      printf("---[HttpHeader test Set case22] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(langItem5->weight,0.5) != st(Math)::AlmostEqual) {
      printf("---[HttpHeader test Set case23] [FAILED]--- \n");
      break;
    }

    //Accept-Patch: application/example, text/example
    HttpAcceptPatch patch = header->getAcceptPatch();
    ArrayList<HttpAcceptPatchItem> patches = patch->getAcceptPatches();
    HttpAcceptPatchItem patchItem1 = patches->get(0);
    if(!patchItem1->type->equals("application/example")) {
      printf("---[HttpHeader test Set case24] [FAILED]--- \n");
      break;
    }

    HttpAcceptPatchItem patchItem2 = patches->get(1);
    if(!patchItem2->type->equals("text/example")) {
      printf("---[HttpHeader test Set case25] [FAILED]--- \n");
      break;
    }

    //Accept: text/html, application/xhtml+xml, application/xml;q=0.9, */*;q=0.8
    HttpAccept accept = header->getAccept();
    ArrayList<HttpAcceptItem> accepts = accept->getAccepts();
    if(accepts->size() != 4) {
      printf("---[HttpHeader test Set case26_0] [FAILED]--- \n");
      break;
    }

    HttpAcceptItem acceptItem1 = accepts->get(0);
    if(!acceptItem1->type->equals("text/html")) {
      printf("---[HttpHeader test Set case26] [FAILED]--- ,type is %s\n",acceptItem1->type->toChars());
      break;
    }

    HttpAcceptItem acceptItem2 = accepts->get(1);
    if(!acceptItem2->type->equals("application/xhtml+xml")) {
      printf("---[HttpHeader test Set case27] [FAILED]--- \n");
      break;
    }

    HttpAcceptItem acceptItem3 = accepts->get(2);
    if(!acceptItem3->type->equals("application/xml")) {
      printf("---[HttpHeader test Set case28] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(acceptItem3->weight,0.9) != st(Math)::AlmostEqual) {
      printf("---[HttpHeader test Set case29] [FAILED]--- \n");
      break;
    }

    HttpAcceptItem acceptItem4 = accepts->get(3);
    if(!acceptItem4->type->equals("*/*")) {
      printf("---[HttpHeader test Set case30] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(acceptItem4->weight,0.8) != st(Math)::AlmostEqual) {
      printf("---[HttpHeader test Set case31] [FAILED]--- \n");
      break;
    }

    //"Allow: GET, POST, HEAD\r\n"
    String allow = header->get("Allow");
    if(!allow->equals("GET, POST, HEAD")) {
      printf("---[HttpHeader test Set case32] [FAILED]--- ,allow is %s\n",allow->toChars());
      break;
    }

    //Authorization: Basic YWxhZGRpbjpvcGVuc2VzYW1l
    HttpAuthorization authorization = header->getAuthorization();
    if(!authorization->type->equals("Basic")) {
      printf("---[HttpHeader test Set case33] [FAILED]--- ,allow is %s\n",allow->toChars());
      break;
    }

    if(!authorization->credentials->equals("YWxhZGRpbjpvcGVuc2VzYW1l")) {
      printf("---[HttpHeader test Set case34] [FAILED]--- \n");
      break;
    }

    //Content-Disposition: form-data; name=\"fieldName\"; filename=\"filename.jpg\"
    HttpContentDisposition contentDisp = header->getContentDisposition();
    if(!contentDisp->type->equals("form-data")) {
      printf("---[HttpHeader test Set case35] [FAILED]--- \n");
      break;
    }

    if(!contentDisp->name->equals("fieldName")) {
      printf("---[HttpHeader test Set case36] [FAILED]--- \n");
      break;
    }

    if(!contentDisp->filename->equals("filename.jpg")) {
      printf("---[HttpHeader test Set case37] [FAILED]--- \n");
      break;
    }

    //Content-Encoding: identity
    String contentEncoding = header->get("Content-Encoding");
    if(!contentEncoding->equals("identity")) {
      printf("---[HttpHeader test Set case38] [FAILED]--- \n");
      break;
    }

    //Cache-Control: max-age=1000
    HttpCacheControl cachecontrol = header->getCacheControl();
    if(cachecontrol->maxAgeSeconds() != 1000) {
      printf("---[HttpHeader test Set case39] [FAILED]--- \n");
      break;
    }

    //Content-Length: 2000
    int contentLen = header->getContentLength();
    if(contentLen != 2000) {
      printf("---[HttpHeader test Set case40] [FAILED]--- \n");
      break;
    }

    //Link: <https://example.com>; rel="preload"
    ArrayList<HttpHeaderLink> links = header->getHeaderLinks();
    if(links->size() != 1) {
      printf("---[HttpHeader test Set case41] [FAILED]--- \n");
      break;
    }

    HttpHeaderLink link = links->get(0);
    if(!link->url->equals("https://example.com")) {
      printf("---[HttpHeader test Set case42] [FAILED]--- \n");
      break;
    }

    if(!link->rel->equals("preload")) {
      printf("---[HttpHeader test Set case43] [FAILED]--- \n");
      break;
    }

    //X-Frame-Options: allow-from https://example.com/
    HttpXFrameOptions xframeoption = header->getXFrameOptions();
    if(!xframeoption->option->equals("allow-from")) {
      printf("---[HttpHeader test Set case44] [FAILED]--- \n");
      break;
    }

    if(!xframeoption->uri->equals("https://example.com/")) {
      printf("---[HttpHeader test Set case45] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpHeader test Set case100] [OK]--- \n");

}
