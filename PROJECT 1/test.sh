#! /bin/bash

declare -i num=1

echo -e "Hello $USER! Your script was executed succesfully!\n"

echo -e "$num. Creating a file named 'testfile.c'...\n"
touch testfile.c
num=1+$num

echo -e "$num. Writing a c code in 'testfile.c'...\n"
num=1+$num

echo '#include <stdio.h>

int main() {
    printf("\n\n====================\n\n");
    printf("In testfile...\nHello World\n");
    printf("\n====================\n\n");
    return 0;
}' >> testfile.c

echo -e "$num. Compiling 'testfile.c'...\n"
gcc -o testfile testfile.c
num=1+$num

printf "$num. Running 'testfile'...\n"
./testfile
num=1+$num

printf "$num. Removing files...\n"
rm testfile.c testfile
