.PHONY: all run debug

all: run

run: build
	./find

debug: buildd
	./debug

build: find.cpp
	g++ find.cpp -o find

buildd: find.cpp
	g++ -fsanitize=address -g3 find.cpp -o debug

clean:
	rm find | rm debug
