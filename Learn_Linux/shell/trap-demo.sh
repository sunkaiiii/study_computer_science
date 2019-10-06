#!/bin/bash
trap "echo 'I am ignoring you.'" SIGINT SIGTERM
for i in {1..5}; do
	echo "Iteration $i of 5"
	sleep 5
done
