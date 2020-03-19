#!/bin/bash
i=0
sum=0
for in_arg in "$@";
do
sum=$(($sum+${in_arg}))
i=$(($i+1))
done
echo "Number of input arguments"
echo $i
echo "Result"
res=$(($sum/$i))
echo $res