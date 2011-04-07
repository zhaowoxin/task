#!/bin/bash

    a=1
    read -p "Please input the dir:" dir
    if [ -d $dir ]   
    then
        cd $dir
    else
        echo "PATH NOT EXIST"
        exit 5
    fi
    read -p "Please input the file:" ffile
    if [ -f $ffile ]
    then 
        read -p "please input the end char:" char 

        while read line;
        do 
        file=`echo $line | awk -F"$char" '{print $1}'`
            echo "The usr No is $a:" $file
        a=$(($a + 1))
        #a=`expr $a + 1`    equal as last line;
        done<$ffile
    else    echo "FILE NOT EXIST"; exit 3
    fi

