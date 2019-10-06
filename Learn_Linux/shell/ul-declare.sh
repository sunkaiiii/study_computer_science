#!/bin/bash
declare -u upper
declare -l lower
if [[ $1 ]]; then
	upper="$1"
	lower="$1"
	echo $upper
	echo "$lower"
fi
