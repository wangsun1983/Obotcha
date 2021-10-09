#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAcceptLanguage.hpp"
#include "Math.hpp"

using namespace obotcha;

void testLanguageParse() {
  while(1) {
    HttpAcceptLanguage encoding1 = createHttpAcceptLanguage();
    encoding1->import("fr-CH,fr;q=0.9,en;q=0.8,de;q=0.7,*;q=0.5");
    auto languages = encoding1->getLanguages();
    if(languages->size() != 5) {
      printf("---[HttpAcceptLanguage test Parse case1] [FAILED]--- \n");
      break;
    }

    if(!languages->get(0)->lang->equals("fr-CH")
      || !languages->get(1)->lang->equals("fr")
      || !languages->get(2)->lang->equals("en")
      || !languages->get(3)->lang->equals("de")
      || !languages->get(4)->lang->equals("*")) {
        printf("---[HttpAcceptLanguage test Parse case2] [FAILED]--- \n");
        break;
    }

    if(st(Math)::compareFloat(languages->get(1)->weight,0.9) != st(Math)::AlmostEqual) {
      printf("---[HttpAcceptLanguage test Parse case3] [FAILED]---,weight is %f \n",languages->get(1)->weight);
      break;
    }

    if(st(Math)::compareFloat(languages->get(2)->weight,0.8) != st(Math)::AlmostEqual) {
      printf("---[HttpAcceptLanguage test Parse case4] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(languages->get(3)->weight,0.7) != st(Math)::AlmostEqual) {
      printf("---[HttpAcceptLanguage test Parse case5] [FAILED]--- \n");
      break;
    }

    if(st(Math)::compareFloat(languages->get(4)->weight,0.5) != st(Math)::AlmostEqual) {
      printf("---[HttpAcceptLanguage test Parse case6] [FAILED]--- \n");
      break;
    }
    break;
  }


  printf("---[HttpAcceptLanguage test Parse case100] [OK]--- \n");

}
