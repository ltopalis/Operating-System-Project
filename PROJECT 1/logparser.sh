#!/bin/bash

function mining_usernames () {
    awk '{print $3}' access.log | sort | uniq > temp.txt

    file="temp.txt"

    while read -r line; do
        echo -e "$line\t$(awk '{print $3}' access.log | grep $line | wc -l)"
    done <$"temp.txt"

    rm temp.txt
}

function match () {
    cat $1 | grep $2
}

function count_browsers () {
    for browser in Mozilla Chrome Safari Edg
    do
        echo -e "$browser\t$(match $1 $browser | wc -l)"
    done
}

case $# in
0 )
    echo "1084622|1088101";;
1 )
    if [ $1 == *".log" ]; then
        cat $1
        echo ""
    else
        echo "Wrong File Argument"

    fi;;
2 )
    if [ $1 == *".log" ]; then
        if [ $2 == "--usrid" ]; then
            mining_usernames
        elif [ $2 == "--browsers" ]; then
            count_browsers $1
        elif [ $2 == "--datum" ]; then
            echo "Wrong Date"
        else
            echo "Wrong Option Argument"
        fi
    else
        echo "Wrong File Argument"
    fi;;
3 )
    if [ $1 == *".log" ]; then
        if [ $2 == "--usrid" ]; then
            echo | awk -v s=$3 '
            BEGIN{ search=s }
            {
                if ( $3 ~ search ) {
                    print $0;
                }
            }' $1
        elif [ $2 == "-method" ]; then
            if [ $3 == "POST" ] || [ $3 == "GET" ]; then
                cat $1 | grep $3
            else
                echo "Wrong Method Name"
            fi
        elif [ $2 == "--servprot" ]; then
            if [ $3 == "IPv4" ]; then
                awk -e '$1 ~ /\./ {print $0}' $1
            elif [ $3 == "IPv6" ]; then 
                awk '$1 ~ /:/ {print $0}' $1
            else
                echo "Wrong Network Protocol"
            fi
        elif [ $2 == "--datum" ]; then
            if [[ $3 =~ ^(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec)$ ]]; then
                cat $1 | grep $3
            else
                echo "Wrong Date"
            fi
        else
            echo "Wrong Option Argument"
        fi
    else
        echo "Wrong File Argument"
    fi;;
esac
