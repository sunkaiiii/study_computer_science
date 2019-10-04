#!/bin/bash
number=1
set -x #x执行追踪
if [ $number = 1 ]; then
	echo "Number is equal to 1."
else
	echo "Number is not equal to 1."
fi
set +x #关闭追踪
