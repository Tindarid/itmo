build:
	mkdir -p gen
	flex parser.l 
	bison parser.y -d -o gen/parser.cpp
	g++ parser.cpp gen/lexer.cpp gen/parser.cpp -o gen/parser

test: build
	g++ test.cpp gen/lexer.cpp gen/parser.cpp -o test/test
	./test/test

test1: build
	./gen/parser ./test/test1.y

test2: build
	./gen/parser ./test/test2.y
	cat ./test/test2.h
	cat ./test/test2.cpp

run: build
	./gen/parser ./test/parser.y
	cat ./test/parser.h
	cat ./test/parser.cpp

clean:
	rm -R -f gen
	rm -f test/test test/parser test/parser.cpp test/parser.h
