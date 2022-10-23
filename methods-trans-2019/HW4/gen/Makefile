run-pascal:
	make -C "../lexer/" build
	../lexer/gen/lexer pascal/lexer.l
	make -C "../parser/" build
	../parser/gen/parser pascal/parser.y
	g++ pascal/lexer.cpp pascal/parser.cpp pascal/main.cpp -o pascal/pascal
	./pascal/pascal

run-calc-simple:
	make -C "../lexer/" build
	../lexer/gen/lexer calc-simple/lexer.l
	make -C "../parser/" build
	../parser/gen/parser calc-simple/parser.y
	g++ calc-simple/lexer.cpp calc-simple/parser.cpp calc-simple/main.cpp -o calc-simple/calc-simple
	./calc-simple/calc-simple


run-calc:
	make -C "../lexer/" build
	../lexer/gen/lexer calc/lexer.l
	make -C "../parser/" build
	../parser/gen/parser calc/parser.y
	g++ calc/lexer.cpp calc/parser.cpp calc/main.cpp -o calc/calc
	./calc/calc
