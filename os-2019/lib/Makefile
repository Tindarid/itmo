CUR_PATH = $(shell pwd)
STATIC_SRC = libs/static/factorial.cpp
DYNAMIC1_SRC = libs/dynamic1/binpow.cpp
DYNAMIC2_SRC = libs/dynamic2/pow.c

run: 
	./main

all: static dynamic1 dynamic2
	g++ main.cpp -L . -lfactorial -L $(CUR_PATH) -lbinpow -ldl -o main

static: $(STATIC_SRC)
	g++ -c $(STATIC_SRC) -o factorial.o
	ar rcs libfactorial.a factorial.o

dynamic1: $(DYNAMIC1_SRC)
	g++ -c -shared $(DYNAMIC1_SRC) -o libbinpow.so

dynamic2: $(DYNAMIC2_SRC)
	g++ -shared $(DYNAMIC2_SRC) -o libpow.so
