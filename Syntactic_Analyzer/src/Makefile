
all:
	flex --outfile=scanner.c scanner.l
	bison --output=parser.c -d -v --defines parser.y
	g++ scanner.c parser.c -o asa
	rm -f parser.c parser.h parser.output scanner.c
