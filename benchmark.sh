#!/bin/bash

good=0

check=`ls . | grep naive`
if [ $? -eq 1 ]; then
    echo "Executable ./naive was not found."
else

for file in `ls simple_products | grep inp | sed s/inp//`; do
    /usr/bin/time --format "%U" ./strassen < simple_products/inp$file 1> /tmp/test.out 2> /tmp/test.time
    tim=`cat /tmp/test.time`
    ./compare /tmp/test.out < simple_products/out$file
    correct=$?

    if [ $correct -ne 0 ];  then
        echo -e "Test \e[0;33minp$file\e[00m \e[01;31mfailed\e[00m (wrong answer)";
    else
        sizes=`echo $file | sed 's/-\\([0-9]*\\)x\\([0-9]*\\)/\1\\t\2/g'`
        echo -e "$sizes\t$tim";
    fi
done;

fi

