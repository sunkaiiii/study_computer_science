#!/bin/bash
#shell function demo

function funct {
echo "Step 2"
return
}

#Main program starts here

echo 'Step 1'
funct
echo 'Step 3'
