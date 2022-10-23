#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cassert>
using namespace std;

#define WORD_SIZE 8
#define SIZE (1 << WORD_SIZE)

class generator {
  static constexpr size_t word_size = 8;
  static constexpr size_t size = 1 << word_size;

  size_t S[size];
  size_t i, j;

public: 
  generator(const string& key) {
    for (i = 0; i < size; ++i) {
      S[i] = i;
    }

    size_t len = key.length();
    for (i = 0, j = 0; i < size; ++i) {
      j = (j + S[i] + (uint8_t)key[i % len]) % size;
      swap(S[i], S[j]);
    }

    i = j = 0;
  }

  uint8_t next() {
    i = (i + 1) % size;
    j = (j + S[i]) % size;

    swap(S[i], S[j]);
    return S[(S[i] + S[j]) % size];
  }
};

void rc4(istream& in, ostream&out, const string& key) {
  generator g(key);
  while (true) {
    char next = in.get();
    if (next == EOF) {
      break;
    }
    out.put(g.next() ^ (uint8_t)next);
  }
}

int main() {
  string key = "lolollkekkek";
  string text = "Nice to meet you. 1234 lolll. jflkdsjfklsdjflkjds lkflkdsfj lksdj fkljds lkfjlkds";

  std::cout << "Key: " << key << std::endl;
  std::cout << "Text: " << text << std::endl;

  stringstream in1(text, stringstream::binary | stringstream::in);
  stringstream out1(stringstream::binary | stringstream::out);
  rc4(in1, out1, key);
  string encoded = out1.str();
  std::cout << "Encoded: " << encoded << std::endl;

  stringstream in2(encoded, stringstream::binary | stringstream::in);
  stringstream out2(stringstream::binary | stringstream::out);
  rc4(in2, out2, key);
  string decoded = out2.str();
  std::cout << "Decoded: " << decoded << std::endl;

  assert(decoded == text);
}
