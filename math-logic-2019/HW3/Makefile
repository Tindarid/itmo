HC=ghc
SOURCES=src/Main.hs src/Grammar.hs src/Generate.hs
GEN_SOURCES=src/Lexer.x src/Parser.y
GENERATED=src/Lexer.hs src/Parser.hs
PROOFS=proofs/10.txt proofs/MP.txt
PACKAGE_NAME=pack.zip
DEDUCTION=src/Deduction.hs

.PHONY: pack all run clean

all: parser

run:
	./parser

test: parser
	cat input.txt | ./parser

clean:
	rm -rf src/*.o src/*.hi
	rm -rf $(GENERATED)
	rm -f parser
	rm -f $(PACKAGE_NAME)

parser: $(GENERATED) $(SOURCES)
	$(HC) -i./src -tmpdir . ./src/Main.hs -o parser

$(GENERATED): $(GEN_SOURCES) $(SOURCES)
	alex src/Lexer.x -o src/Lexer.hs
	happy src/Parser.y -o src/Parser.hs

pack: $(GENERATED) $(PROOFS)
	7z a $(PACKAGE_NAME) -r Makefile src proofs

ded: $(DEDUCTION)
	$(HC) -i./src -tmpdir . ./src/Deduction.hs -o ded
