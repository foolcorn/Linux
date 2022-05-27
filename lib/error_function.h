#ifndef ERROR_FUNCTION_H
#define ERROR_FUNCTION_H

//-在标准error流打印与当前errno有关的错误文本
void errMsg(const char * msg,...);

//-调用exit退出，如果环境变量EF_DUMPCORE非空,则调用abort退出，生成核心转储文件，仅供调试之用
void errExit(const char * msg,...);

//-调用_exit退出，不会刷新缓存，fork的时候比较有用，防止刷新父进程的缓冲区，同时也不会调用父进程注册的退出程序on_exit，atexit
void err_Exit(const char * msg,...);

//-根据errnum而不是errno来打印错误信息
//-使用errno实际是宏展开的系统调用，每次处理都很消耗资源，多线程的时候就用系统调动的返回值作为errnum更高效
void errExitWithNum(int errnum, const char * msg,...);

//-这几个暂时没用到,留个接口,先不实现了
void fatal(const char * msg,...);
void usageErr(const char * msg,...);
void cmdLineErr(const char * msg,...);

#endif