build:
	mkdir -p gen
	flex lexer.l 
	bison lexer.y -d -o gen/parser.cpp
	g++ lexer.cpp gen/lexer.cpp gen/parser.cpp -o gen/lexer

test: build
	g++ test.cpp gen/lexer.cpp gen/parser.cpp -o test/test
	./test/test

run: build
	./gen/lexer ./test/lexer.l
	cat ./test/lexer.h
	cat ./test/lexer.cpp

clean:
	rm -R -f gen
	rm -f test/test test/lexer test/lexer.cpp test/lexer.h
