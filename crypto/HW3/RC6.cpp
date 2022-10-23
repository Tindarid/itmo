#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <vector>

// RC6-32/20/16
#define WORD_SIZE 32
#define LOG_W 5
#define ROUNDS 20
#define KEY_LEN 16
#define P_CONST 0xB7E15163
#define Q_CONST 0x9E3779B9
#define BLOCK_SIZE (4 * WORD_SIZE / 8)

using namespace std;

inline uint32_t cycle_l(uint32_t a, uint8_t n) {
  n &= WORD_SIZE - 1;
  return (a << n) | (a >> (WORD_SIZE - n));
}

inline uint32_t cycle_r(uint32_t a, uint8_t n) {
  n &= WORD_SIZE - 1;
  return (a >> n) | (a << (WORD_SIZE - n));
}

int get_block(istream &in, uint8_t *block) {
  for (int i = 0; i < BLOCK_SIZE; ++i) {
    block[i] = 0;
  }

  for (int i = 0; i < BLOCK_SIZE; ++i) {
    char next = in.get();
    if (next == EOF and i == 0) {
      return 0;
    } else if (next == EOF) {
      return 1;
    } else {
      block[i] = next;
    }
  }

  return 1;
}

void put_block(ostream &out, uint8_t *block) {
  for (int i = 0; i < BLOCK_SIZE; ++i) {
    if (!block[i]) {
      return;
    }
    out << block[i];
  }
}

void swap(uint32_t &A, uint32_t &B, uint32_t &C, uint32_t &D, uint8_t *block) {
  uint32_t *temp = reinterpret_cast<uint32_t*>(block);
  swap(A, temp[0]);
  swap(B, temp[1]);
  swap(C, temp[2]);
  swap(D, temp[3]);
}

void encrypt(uint8_t *block, vector<uint32_t> &keys) {
  uint32_t A, B, C, D;
  swap(A, B, C, D, block);

  B = B + keys[0];
  D = D + keys[1];

  for (uint32_t i = 1, t, u; i <= ROUNDS; ++i) {
    t = cycle_l((B * (2 * B + 1)), LOG_W);
    u = cycle_l((D * (2 * D + 1)), LOG_W);
    A = cycle_l(A ^ t, u) + keys[2 * i];
    C = cycle_l(C ^ u, t) + keys[2 * i + 1];
    t = A; A = B; B = C; C = D; D = t;
  }

  A = A + keys[2 * ROUNDS + 2];
  C = C + keys[2 * ROUNDS + 3];

  swap(A, B, C, D, block);
}

void decrypt(uint8_t *block, vector<uint32_t> &keys) {
  uint32_t A, B, C, D;
  swap(A, B, C, D, block);

  C = C - keys[2 * ROUNDS + 3];
  A = A - keys[2 * ROUNDS + 2];
  
  for (uint32_t i = ROUNDS, t, u; i >= 1; --i) {
    t = D; D = C; C = B; B = A; A = t;
    u = cycle_l(D * (2 * D + 1), LOG_W);
    t = cycle_l(B * (2 * B + 1), LOG_W);
    C = cycle_r(C - keys[2 * i + 1], t) ^ u;
    A = cycle_r(A - keys[2 * i], u) ^ t;
  }

  D = D - keys[1];
  B = B - keys[0];

  swap(A, B, C, D, block);
}

void rc6(istream &in, ostream&out, const string& key, bool encode) {
  // Generating subkeys
  assert(key.size() == KEY_LEN);
  vector<uint32_t> subkeys(2 * ROUNDS + 4, 0);

  subkeys[0] = P_CONST;
  for (int i = 1; i < subkeys.size(); ++i) {
    subkeys[i] = subkeys[i - 1] + Q_CONST;
  }

  vector<uint32_t> key_c;
  for (int i = 0; i < KEY_LEN; i += WORD_SIZE / 8) {
    uint32_t next = 0;
    for (int j = i; j < WORD_SIZE / 8; ++j) {
      next <<= 8;
      next |= (j < KEY_LEN ? key[j] : 0);
    }
    key_c.push_back(next);
  }

  int v = 3 * max(key_c.size(), subkeys.size());
  int A, B, I, J;
  A = B = I = J = 0;

  for (int i = 0; i < v; ++i) {
    A = subkeys[I] = cycle_l((subkeys[I] + A + B), 3);
    B = key_c[J] = cycle_l(key_c[J] + A + B, A + B);
    I = (I + 1) % subkeys.size();
    J = (J + 1) % key_c.size();
  }

  // Encode or decode
  uint8_t block[BLOCK_SIZE];
  while (get_block(in, block)) {
    if (encode) {
      encrypt(block, subkeys);
    } else {
      decrypt(block, subkeys);
    }
    put_block(out, block);
  }
}

int main() {
  string key = "lolollololkekkek";
  string text = "Nice to meet you. 1234 lolll. jflkdsjfklsdjflkjds lkflkdsfj lksdj fkljds lkfjlkds";

  std::cout << "Key: " << key << std::endl;
  std::cout << "Text: " << text << std::endl;

  stringstream in1(text, stringstream::binary | stringstream::in);
  stringstream out1(stringstream::binary | stringstream::out);
  rc6(in1, out1, key, true);
  string encoded = out1.str();
  std::cout << "Encoded: " << encoded << std::endl;

  stringstream in2(encoded, stringstream::binary | stringstream::in);
  stringstream out2(stringstream::binary | stringstream::out);
  rc6(in2, out2, key, false);
  string decoded = out2.str();
  std::cout << "Decoded: " << decoded << std::endl;

  assert(decoded == text);
}
