#! /bin/bash

test=$1
clear
echo ---------------------- INPUT -----------------------
cat -n tests/$1.test
echo -e '\n'
echo ---------------------- OUTPUT ----------------------
./dist/als tests/$1.test