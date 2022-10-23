all: encryptor.cpp decryptor.cpp
	g++ encryptor.cpp -o encryptor
	g++ decryptor.cpp -o decryptor
test: all
	./encryptor test/test3 crypto
	./decryptor test/test3_encoded
clean:
	rm encryptor decryptor
	rm test/test3_encoded
