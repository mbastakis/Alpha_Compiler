
all:
	@flex --outfile=src/scanner.c src/scanner.l
	@bison --output=src/parser.c -d -v --defines src/parser.y
	@mkdir -p dist
	@g++ -std=c++17 -g src/scanner.c src/parser.c public/Symbol.hpp public/SymbolTable.hpp public/IntermediateCode.cpp -o dist/asa
	@rm -f src/parser.c src/parser.h src/parser.output src/scanner.c

clean:
	@rm -f src/parser.c src/parser.h src/parser.output src/scanner.c
	@rm -rf dist