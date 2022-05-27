#include "error_function.h"
#include <stdarg.h>//-处理可变参数列表
#include "tlpi_hdr.h"

//-打印错误
static void outputError(Boolean useErr,int errnum,Boolean flushStdout,const char*msg,va_list ap){
#define BUFFER_SIZE 500
    char buf[BUFFER_SIZE];//-最后汇总的信息
    char userMsg[BUFFER_SIZE];//-用户自定义的错误信息
    char errText[BUFFER_SIZE];//-系统提供的错误信息
    //-将可变参数列表va_list数据写入到缓冲区中 int vsnprintf(char *s, size_t n, const char *format, va_list arg)
    vsnprintf(userMsg,BUFFER_SIZE,msg,ap);
    //-是否要打印系统提供的错误信息
    if (useErr){
        //-写个简化版系统msg
        snprintf(errText,BUFFER_SIZE,"[sys error msg: %s]","sys error", strerror(errnum));
        // snprintf(errText,BUFFER_SIZE,"[%s %s]",(errnum>0&&errnum<=MAX_ENAME)?ename[errnum]:"??unknown error", strerror(errnum));
    }
    else{
        snprintf(errText,BUFFER_SIZE,":");
    }

    //-将用户和系统的错误buff融合到一起
    snprintf(buf,BUFFER_SIZE,"Error:%s %s\n",errText,userMsg);
    //-是否要刷新标准输出的缓冲区
    if(flushStdout){
        fflush(stdout);
    }
    //-写入标准错误流，并刷新缓冲区
    fputs(buf,stderr);
    fflush(stderr);
}

//-控制调用哪种接口退出程序
static void terminate(Boolean useExit){
    //-试探环境变量EF_DUMPCORE,看看是不是要调试，调用abort
    char *s;
    s = getenv("EF_DUMPCORE");
    if(s!=NULL&&*s!='\0'){
        abort();
    }else if(useExit){
        exit(EXIT_FAILURE);
    }else{
        _exit(EXIT_FAILURE);
    }
}

//-在标准error流打印与当前errno有关的错误文本
void errMsg(const char * msg,...){
    va_list argList;
    int errno_temp = errno;//-防止传入errno的时候，errno被修改，所以留个副本
    va_start(argList,msg);
    outputError(TRUE,errno,TRUE,msg,argList);
    va_end(argList);
    errno = errno_temp;//-恢复原来的errno

}

//-调用exit退出，如果环境变量EF_DUMPCORE非空,则调用abort退出，生成核心转储文件，仅供调试之用
void errExit(const char * msg,...){
    va_list argList;//-实际是个char指针
    va_start(argList, msg);//-将指针指向不定参数第一个参数,需要不定参数...前的第一个参数的地址来做锚点，所以还要传入msg
    //-在错误流输出错误，刷新输出流
    outputError(TRUE,errno,TRUE,msg,argList);//-TRUE定义在"tlpi_hdr.h"里
    //-列表访问完，必须要把列表指针收回，否则出现野指针
    va_end(argList);
    //-exit退出程序
    terminate(TRUE);
}

//-调用_exit退出，不会刷新缓存，fork的时候比较有用，防止刷新父进程的缓冲区，同时也不会调用父进程注册的退出程序on_exit，atexit
void err_Exit(const char * msg,...){
    va_list argList;//-实际是个char指针
    va_start(argList, msg);//-将指针指向不定参数第一个参数,需要不定参数...前的第一个参数的地址来做锚点，所以还要传入msg
    //-在错误流输出错误，不刷输出流
    outputError(TRUE,errno,FALSE,msg,argList);//-TRUE定义在"tlpi_hdr.h"里
    //-列表访问完，必须要把列表指针收回，否则出现野指针
    va_end(argList);
    //-_exit退出程序
    terminate(FALSE);
}

//-根据errnum而不是errno来打印错误信息
//-使用errno实际是宏展开的系统调用，每次处理都很消耗资源，多线程的时候就用系统调动的返回值作为errnum更高效
void errExitWithNum(int errnum, const char * msg,...){
    va_list argList;
    va_start(argList,msg);
    //-使用特定的errno，刷新输出流
    outputError(TRUE,errnum,TRUE,msg,argList);
    va_end(argList);
    //-调用exit
    terminate(TRUE);
}