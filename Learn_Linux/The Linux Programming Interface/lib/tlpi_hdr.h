//
//  tlpi_hdr.h
//  LearnLinux
//
//  Created by 孙楷 on 18/7/19.
//  Copyright © 2019 孙楷. All rights reserved.
//

#ifndef tlpi_hdr_h
#define tlpi_hdr_h //防止意外的重定义

#include <sys/types.h>
#include <stdio.h> //基础的IO功能
#include <stdlib.h> //常用的库函数都在这里

#include <unistd.h> //包含很多系统调用的原型
#include <errno.h> //声明了c错误代码和一些错误处理函数
#include <string.h> //最常用的处理string的方法

#include "get_number.h" //声明这里用到的一些数字处理方法

#include "error_functions.h"

typedef enum {FALSE,TRUE} Boolean;

#define min(m,n) ((m)<(n)?(m):(n))
#define max(m,n) ((m)>(n)?(m):(n))

#endif /* tlpi_hdr_h */
