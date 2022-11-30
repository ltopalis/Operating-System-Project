#!/bin/bash

function mining_usernames {
    awk '{print $3}' access.log | sort | uniq > temp.txt

    file="temp.txt"

    while read -r line; do
        echo -e  "$line\t$(awk '{print $3}' access.log | grep $line | wc -l)"
    done < $"temp.txt"

    rm temp.txt
}

case $# in
0 )
    echo "1084622|1088101";;
1 )
    if [ $1 == *".log" ]; then 
        cat $1
    else
        echo "Wrong File Argument"

    fi;;
2 )
    if [ $1 == *".log" ]; then
        if [ $2 == "--usrid" ]; then
            mining_usernames;
        else
            echo "Wrong Option Argument"
        fi
    else 
        echo "Wrong File Argument"
    fi;;
3 )
    if [ $1 == *".log" ]; then
        if [ $2 == "--usrid" ]; then
            cat $1 | grep $3
        elif [ $2 == "-method" ]; then 
            if [ $3 == "POST" ] || [ $3 == "GET" ]; then 
                cat $1 | grep $3
            else
                echo "Wrong Method Name"
            fi
        elif [ $2 == "--servprot" ]; then
            if [ $3 == "IPv4" ]; then 
                # here 
            else
                echo "Wrong Network Protocol"
            fi
        else
            echo "Wrong Option Argument"
        fi
    else 
        echo "Wrong File Argument"
    fi;;
esac