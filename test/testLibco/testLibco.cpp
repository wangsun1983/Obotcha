#include "co_routine.h"


#include<iostream>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <stack>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

using namespace std;

static void* A(void *arg) {
   printf("1 ");
   co_yield_ct();  // 切出到主协程
   printf("2 ");
}

static void* B(void *arg) {
    using namespace std;
  printf("x ");
  co_yield_ct();  // 切出到主协程
  printf("y ");
}

struct task_t
{
    stCoRoutine_t *co;
    int fd;
};

typedef struct task_t task_t;

int main(void) {
    stCoRoutine_t *coa,*cob;
    //taska->fd=-1;
    //taskb->fd=-1;
    co_create(&coa,NULL,A,NULL);//**stCoRoutine_t, *attr(shareMem),pfn,*arg
    co_create(&cob,NULL,B,NULL);
    co_resume(coa);
    co_resume(cob);
    //co_resume(coa);
    //co_resume(cob);
    printf("\n");
}
