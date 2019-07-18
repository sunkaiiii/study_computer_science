//
//  error_functions.h
//  LearnLinux
//
//  Created by 孙楷 on 18/7/19.
//  Copyright © 2019 孙楷. All rights reserved.
//

#ifndef error_functions_h
#define error_functions_h

void errMsg(const char *format,...);

#ifdef _GNUC_
/*
 这个宏的作用是停止编译器的警告如果我们尝试终止一些非void的函数的时候。
 */
#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif

void errExit(const char *format,...) NORETURN; //会在标准错误设备上打印信息
void err_exit(const char *format,...)NORETURN; //操作方式和errMsg类似，但会用两种方式终止程序
void errExitEN(int errnum,const char *format,...)NORETURN; //只会打印错误号而并不是错误信息
void fatal(const char *format,...)NORETURN; //用来诊断一般性错误
void usageErr(const char *format,...)NORETURN; //针对来自命令行参数使用方面的错误
void cmdLineErr(const char *format,...)NORETURN; //针对特定程序的命令行的诊断错误

#endif /* error_functions_h */
