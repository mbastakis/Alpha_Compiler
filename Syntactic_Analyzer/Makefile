
all:
	flex --outfile=src/scanner.c src/scanner.l
	bison --output=src/parser.c -d -v --defines src/parser.y
	mkdir -p dist
	g++ src/scanner.c src/parser.c -o dist/asa
	rm -f src/parser.c src/parser.h src/parser.output src/scanner.c

clean:
	rm -rf dist
