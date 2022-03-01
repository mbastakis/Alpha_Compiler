#!/bin/bash

cd lexical_scanner
flex --outfile=alpha_lexical_scanner.c lexical_scanner.l
cd ..
if g++ -o al lexical_scanner/alpha_lexical_scanner.c; then
echo "Compiled successfully.";
else
echo "Compilation failed";
fi