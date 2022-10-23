.PHONY: all run debug

all: run

run: build
	./jit

debug: buildd
	./debug

build: jit.cpp
	g++ jit.cpp -o jit

buildd: jit.cpp
	g++ -fsanitize=address -g3 jit.cpp -o debug

clean:
	rm jit | rm debug
