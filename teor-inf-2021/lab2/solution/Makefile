coder: coder.cpp ar/base.cpp ar/encode.cpp ar/decode.cpp ar/base.h ar/encode.h ar/decode.h
	g++ -I . coder.cpp ar/base.cpp ar/encode.cpp ar/decode.cpp -o coder -O2

decoder: decoder.cpp ar/base.cpp ar/encode.cpp ar/decode.cpp ar/base.h ar/encode.h ar/decode.h
	g++ -I . decoder.cpp ar/base.cpp ar/encode.cpp ar/decode.cpp -o decoder -O2

clean:
	rm -f coder decoder

clean_for_pass: clean
	rm -fr .cache
	rm compile_commands.json

test: coder decoder
	./test.sh
