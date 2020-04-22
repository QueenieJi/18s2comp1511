#!/bin/sh
#written by Mitchell Shelton
#for testing practice prac exam qc

if [ -f "./loop" ]
then
    rm ./loop
fi

gcc -Wall -Werror -O -o loop loop.c testLoop.c

if [ -f "./loop" ]
then
    echo "===Beginning tests==="

    ./loop

    echo "===Testing finished==="
else
    echo "File compilation went wrong, you probably have compile errors"
fi
