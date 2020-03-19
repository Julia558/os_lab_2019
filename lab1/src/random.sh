#!/bin/bash

for ((count=1; count<151; count++))
do
#num=$RANDOM
num=$(od -A n -t d -N 2 /dev/random)
echo $num >> numbers.txt
done
echo "Numbers created"