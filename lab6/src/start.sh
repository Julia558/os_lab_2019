#!/bin/bash
make -f makefile clean
make
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/projects/os_lab_2019/lab6/src
./server --port 20001 --tnum 2 &
./server --port 20002 --tnum 3 &
./client --k 20 --mod 58 --servers ./servers.txt
#chmod ugo+x 
#./start.sh
#kill $(pgrep server)