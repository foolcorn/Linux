#include<stdlib.h>
#include "tlpi_hdr.h"
//-修改进程环境
//-引用全局变量
extern char **environ;

int changeEnv(int argc, char **argv){
    int j;//-命令行指针
    char **ep;
    clearenv();//-先清除现有的环境
    for(j = 0;j < argc; ++j){
        if(putenv(argv[j])!=0){
            errExit("put environ %s error",argv[j]);
        }
    }
    if(setenv("GREET","Hello world",0)==-1){
        errExit("setenv error");
    }
    unsetenv("BYE");
    for(ep = environ;*ep!=NULL;++ep){
        puts(*ep);
    }
    exit(EXIT_SUCCESS);
}

