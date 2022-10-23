.PHONY: all run debug

all: run

run: build
	./shell

debug: buildd
	./debug

build: shell.cpp
	g++ shell.cpp -o shell

buildd: shell.cpp
	g++ -fsanitize=address -g3 shell.cpp -o debug

clean:
	rm shell | rm debug
