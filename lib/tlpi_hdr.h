#ifndef TLPI_HDR_H
#define TLPI_HDR_H
//-一些错误处理函数的脚本
//-定义了linux一些常用的类型
#include <sys/types.h>
//-基本io
#include <stdio.h>
//-标准库函数
#include <stdlib.h>
//-linux系统调用原型
#include <unistd.h>
//-包含常见的错误标志宏
#include <errno.h>
//-常见的处理字符串的方法
#include <string.h>
//-处理命令行str的一些方法(getInt(),getLong())等
#include
//-自定义的错误处理函数
#include "error_function.h"
//-自定义一个Boolean类型，c语言没有bool类型
typedef enum { FALSE, TRUE } Boolean;
//-定义一个宏的max，min小工具
# define min(a,b) ((a)<(b)?(a):(b))
# define max(a,b) ((a)>(b)?(a):(b))

#endif