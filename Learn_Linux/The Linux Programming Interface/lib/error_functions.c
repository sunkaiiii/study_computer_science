//
//  error_functions.c
//  LearnLinux
//
//  Created by 孙楷 on 18/7/19.
//  Copyright © 2019 孙楷. All rights reserved.
//

#include <stdarg.h>
#include "error_functions.h"
#include "tlpi_hdr.h"
#include "ename.c.inc"

#ifdef __GNUC__
__attribute__((__noreturn__))
#endif
static void terminate(Boolean useExit3)
{
    char *s;
    //如果定义了EF_DUMPCORE环境变量且非空则dump。如果没有则根据useExit3的值执行exit(3)或者_exit(2)
    s=getenv("EF_DUMPCORE");
    
    if(s!=NULL&&*s!='\0')
        abort();
    else if (useExit3)
        exit(EXIT_FAILURE);
    else
        _exit(EXIT_FAILURE);
}

static void outputError(Boolean useErr, int err, Boolean flushStdout, const char *format, va_list ap)
{
#define BUF_SIZE 500
    char buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE]long
    vsnprintf(userMsg, BUF_SIZE, format, ap);
    
    if(useErr)
        snprintf(errText, BUF_SIZE, " [%s %s]",(err>0 && err<= MAX_ENAME)? ename[err]:"?UNKNOWN?",strerror(err));
    else
        snprintf(buf, BUF_SIZE, ":");
    
    if(flushStdout)
        fflush(stdout);
    fputs(buf,stderr);
    fflush(stderr); //以防stderr没有line-buffered
}

void errMsg(const char *format,...)
{
    va_list argList;
    int savedErrno;
    
    savedErrno=errno; //以防修改他
    
    va_start(argList, format);
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);
    
    errno=savedErrno;
}

void errExit(const char *format,...)
{
    va_list argList;
    
    va_start(argList, format);
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);
    
    terminate(TRUE);
}

void err_exit(const char *format,...)
{
    va_list argList;
    
    va_start(argList, format);
    outputError(TRUE, errno, FALSE, format, argList);
    va_end(argList);
    
    terminate(FALSE);
}

void errExitEN(int errnum,const char *format,...)
{
    va_list argList;
    
    va_start(argList, format);
    outputError(TRUE, errnum, TRUE, format, argList);
    va_end(argList);
    
    terminate(TRUE);
}

void fatal(const char *format,...)
{
    va_list argList;
    
    va_start(argList, format);
    outputError(FALSE, 0, TRUE, format, argList);
    va_end(argList);
    
    terminate(TRUE);
}

void usageErr(const char *format,...)
{
    va_list argList;
    
    fflush(stdout);
    
    fprintf(stderr, "Usage: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);
    
    fflush(stderr);
    exit(EXIT_FAILURE);
}

void cmdLineErr(const char *format,...)
{
    va_list argList;
    
    fflush(stdout);
    
    fprintf(stderr, "Command-Line usage error: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);
    
    fflush(stderr);
    exit(EXIT_FAILURE);
}
