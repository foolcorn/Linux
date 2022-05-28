#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>//-干啥用
#include <errno.h>
#include "get_num.h"


static void gnFail(const char * fname, const char *msg, const char *arg, const char *name){
    //-把发生错误的源头（方法名，文件名）打印到错误流
    fprintf(stderr,"%s error", fname);
    //-指出文件中发生错误的内容，具体到输入的哪个错误的命令行参数name打印出来
    if(name!=NULL){
        fprintf(stderr, "(in %s)", name);
    }
    //-打印具体的错误细节，是方法的哪个部分出了问题
    fprintf(stderr, "%s\n",msg);
    //-打印转换成数字出错的字符文本部分
    if(arg != NULL && *arg !='\0'){
        fprintf(stderr, "      offending text:%s\n", arg);
    }
    //-退出程序
    exit(EXIT_FAILURE);
}

static long getNum(const char * fname, const char * arg, int flags, const char*name){
    long res;
    char *endptr;
    int base;
    if(arg == NULL || *arg=='\0'){
        gnFail(fname,"arg param is empty",arg,name);
    }
    base = (flags & GN_ANY_BASE)?0:(flags & GN_BASE_8)?8:(flags & GN_BASE_16)?16:10;
    errno = 0;
    // *long int strtol(const char *str, char **endptr, int base)
    // *把参数 str 所指向的字符串根据给定的 base 转换为一个长整数（类型为 long int 型），
    // *base 必须介于 2 和 36（包含）之间，或者是特殊值 0.
    // *endptr会指向读到的末尾指针
    res = strtol(arg, &endptr, base);
    if(errno != 0){
        gnFail(fname, "strtol() failed",arg,name);
    }
    if(*endptr != '\0'){
        gnFail(fname,"param is not a num",arg,name);
    }
    if((flags& GN_NONNEG) && res<0){
        gnFail(fname,"no allow negative num",arg,name);
    }
    if((flags & GN_GT_O) && res<=0){
        gnFail(fname,"num must > 0",arg,name);
    }
    return res;
}

//-字符串转int
int getInt(const char* arg, int flags, const char* name){
    long res;
    res = getNum("getInt",arg,flags,name);
    if(res > INT_MAX || res < INT_MIN){
        gnFail("getInt","interger out of range",arg,name);
    }
    return (int)res;
}
//-字符串转long arg指向首字符的指针，name主要是用来打印错误信息用的
long getLong(const char* arg, int flags, const char* name){
    return getNum("getLong",arg,flags,name);
}
