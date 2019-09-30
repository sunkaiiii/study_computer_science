#!/bin/bash
if read -t 10 -sp "Enter secret pass phrase > " secret_pass; then
	echo "\nSecret pass phrase = '$secret_pass'"
else
	echo "\nInput time out" >&2
	exit 1
fi

