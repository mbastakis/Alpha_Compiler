#!/bin/bash

cd src
flex --outfile=alpha_lexical_scanner.c lexical_scanner.l
cd ../dist
if g++ -o als -w ../src/alpha_lexical_scanner.c; then
echo "Compiled successfully.";
else
echo "Compilation failed";
fi