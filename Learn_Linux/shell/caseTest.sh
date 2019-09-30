#!/bin/bash

echo -n "Enter A,B,C or C:"
read character
case "$character" in
	a|A)
		echo You entered a/A
		;;
	b|b)
		echo You entered b/B
		;;
	c|C)
		echo you entered c/C
		;;
	*)
		echo you did not enter A,B, or C
esac
