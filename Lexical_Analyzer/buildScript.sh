#!/bin/bash

cd lexical_scanner
flex --outfile=alpha_lexical_scanner.c lexical_scanner.l
cd ..
g++ -o al lexical_scanner/alpha_lexical_scanner.c