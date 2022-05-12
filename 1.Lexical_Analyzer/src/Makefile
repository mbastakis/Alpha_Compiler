all:
        flex lexical_scanner.l
        g++ -std=c++11 lex.alpha_yy.c -w
clean:
        rm *.out
		rm *.c