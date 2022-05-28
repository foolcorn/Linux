//-尝试setjmp和longjmp
#include<setjmp.h>
#include "tlpi_hdr.h"
//-声明一个静态变量的jmp_buf，保存上下文和程序计数器，栈顶寄存器
static jmp_buf env;
static void jumpWithStatus(int num){
    longjmp(env,num);
}
int jumptest(int argc,char *argv[]){
    switch(setjmp(env)){
        case 0:
            fprintf(stdout, "try jmp begin\n");
            int status = getInt(argv[2],GN_ANY_BASE,"status param");
            jumpWithStatus(status);
            break;
        case 1:
            fprintf(stdout,"trans into status 1");
            break;
        case 2:
            fprintf(stdout,"trans into status 2");
            break;
    }
    exit(EXIT_SUCCESS);
}

