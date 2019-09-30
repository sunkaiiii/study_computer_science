#!/bin/bash
answer=y
while [ "$answer" = "y" ]
do
	echo -n "Enter a name :"
	read name
	echo "$name" >> file.names
	echo -n "Continue [y/n]; "
	read answer
done
