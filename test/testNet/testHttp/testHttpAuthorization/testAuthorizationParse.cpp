#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAuthorization.hpp"
#include "Math.hpp"

using namespace obotcha;

void testAuthorizationParse() {
  while(1) {
    HttpAuthorization auth = createHttpAuthorization();
    auth->import("Basic YWxhZGRpbjpvcGVuc2VzYW1l");
    if(!auth->type->equals("Basic")) {
      printf("---[HttpAuthorization test Parse case1] [FAILED]--- \n");
      break;
    }

    if(!auth->credentials->equals("YWxhZGRpbjpvcGVuc2VzYW1l")) {
      printf("---[HttpAuthorization test Parse case2] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpAuthorization auth = createHttpAuthorization();
    auth->import("Digest username=\"Mufasa\",realm=\"testrealm@host.com\",nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\",uri=\"/dir/index.html\",qop=auth,nc=00000001,cnonce=\"0a4f113b\",response=\"6629fae49393a05397450978507c4ef1\",opaque=\"5ccc069c403ebaf9f0171e9517f40e41\"");
    
    if(!auth->type->equals("Digest")) {
      printf("---[HttpAuthorization test Parse case3] [FAILED]--- \n");
      break;
    }

    if(!auth->username->equals("Mufasa")) {
      printf("---[HttpAuthorization test Parse case4] [FAILED]--- \n");
      break;
    }

    if(!auth->realm->equals("testrealm@host.com")) {
      printf("---[HttpAuthorization test Parse case5] [FAILED]--- \n");
      break;
    }

    if(!auth->nonce->equals("dcd98b7102dd2f0e8b11d0f600bfb0c093")) {
      printf("---[HttpAuthorization test Parse case6] [FAILED]--- \n");
      break;
    }

    if(!auth->uri->equals("/dir/index.html")) {
      printf("---[HttpAuthorization test Parse case7] [FAILED]--- \n");
      break;
    }

    if(!auth->qop->equals("auth")) {
      printf("---[HttpAuthorization test Parse case8] [FAILED]--- \n");
      break;
    }

    if(!auth->cnonce->equals("0a4f113b")) {
      printf("---[HttpAuthorization test Parse case9] [FAILED]--- \n");
      break;
    }

    if(!auth->response->equals("6629fae49393a05397450978507c4ef1")) {
      printf("---[HttpAuthorization test Parse case10] [FAILED]--- \n");
      break;
    }

    if(!auth->opaque->equals("5ccc069c403ebaf9f0171e9517f40e41")) {
      printf("---[HttpAuthorization test Parse case11] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpAuthorization test Parse case100] [OK]--- \n");

}
