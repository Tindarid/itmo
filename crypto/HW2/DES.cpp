#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

#define BLOCK_SIZE 64
#define MAIN_KEY_SIZE 56
#define KEY_SIZE 48
#define ROUNDS 16

using std::string;
using std::stringstream;
using std::istream;
using std::ostream;

const int IP[BLOCK_SIZE] = {
  58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
  62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
  57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
  61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7,
};

const int FP[BLOCK_SIZE] = {
  40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
  38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
  36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
  34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25,
};

const int KEYS_SHIFT[ROUNDS] = {
  1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1,
};

const int CD[MAIN_KEY_SIZE] = {
  57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
  10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
  63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
  14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4,
};

const int KP[KEY_SIZE] = {
  14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4,
  26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40,
  51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32,
};

const int EXT[KEY_SIZE] = {
  32, 1, 2, 3, 4, 5,
  4, 5, 6, 7, 8, 9,
  8, 9, 10, 11, 12, 13,
  12, 13, 14, 15, 16, 17,
  16, 17, 18, 19, 20, 21,
  20, 21, 22, 23, 24, 25,
  24, 25, 26, 27, 28, 29,
  28, 29, 30, 31, 32, 1,
};

const int SBOX[8][4][16] = {
  {
    {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
    {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
    {4,   1,   14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
    {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13, },
  },
  {
    {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
    {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
    {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15, },
    {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9, },
  },
  {
    {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8, },
    {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
    {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7, },
      {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12, },
  },
  {
    {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15, },
    {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
    {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4, },
    {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14, },
  },
  {
    {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9, },
    {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
    {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14, },
    {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3, },
  },
  {
    {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11, },
    {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
    {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6, },
    {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13, },
  },
  {
    {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1, },
    {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
    {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2, },
    {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12, },
  },
  {
    {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7, },
    {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
    {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8, },
    {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11, },
  },
};

const int PERM[32] = {
  16, 7	, 20, 21, 29, 12, 28, 17,
  1	, 15, 23, 26, 5	, 18, 31, 10,
  2	, 8	, 24, 14, 32, 27, 3	, 9,
  19, 13, 30, 6	, 22, 11, 4	, 25,
};

void block_permutation(bool *block, const int *perm) {
  bool temp_block[BLOCK_SIZE];

  for (int i = 0; i < BLOCK_SIZE; ++i) {
    temp_block[i] = block[perm[i] - 1];
  }

  memcpy(block, temp_block, BLOCK_SIZE);
}

void do_func(bool *dest, bool *src, bool *key) {
  bool temp_block[KEY_SIZE];

  // Ext
  for (int i = 0; i < KEY_SIZE; ++i) {
    temp_block[i] = src[EXT[i] - 1];
  }

  // Xor
  for (int i = 0; i < KEY_SIZE; ++i) {
    temp_block[i] ^= key[i];
  }

  bool temp_block2[BLOCK_SIZE / 2];
  for (int i = 0; i < 8; ++i) {
    bool* B = &temp_block[i * 6];

    // 0 <= a <= 3
    unsigned int a = ((unsigned)B[0] << 1) + B[5];
    // 0 <= b <= 15
    unsigned int b = (((unsigned)B[1]) << 3) + (((unsigned)B[2]) << 2) + (((unsigned)B[3]) << 1) + (((unsigned)B[4]) << 0);

    // Get from SBOX
    unsigned int temp = SBOX[i][a][b];
    bool* B2 = &temp_block2[i * 4];

    B2[0] = (temp >> 3) & 1; B2[1] = (temp >> 2) & 1; B2[2] = (temp >> 1) & 1; B2[3] = (temp >> 0) & 1;
  }

  for (int i = 0; i < BLOCK_SIZE / 2; ++i) {
    dest[i] = temp_block2[PERM[i] - 1];
  }
}

void round_encrypt(bool *block, bool *key, bool encode) {
  bool temp_block[BLOCK_SIZE];

  if (encode) {
    // L_i = R_i-1
    memcpy(temp_block, block + BLOCK_SIZE / 2, BLOCK_SIZE / 2);

    // R_i = f(R_i-1, k_i)
    do_func(temp_block + BLOCK_SIZE / 2, block + BLOCK_SIZE / 2, key);
    
    // R_i ^= L_i-1
    for (int i = 0; i < BLOCK_SIZE / 2; ++i) {
      temp_block[i + BLOCK_SIZE / 2] ^= block[i];
    }
  } else {
    // R_i = L_i-1
    memcpy(temp_block + BLOCK_SIZE / 2, block, BLOCK_SIZE / 2);

    // L_i = f(L_i-1, k_i)
    do_func(temp_block, block, key);
    
    // L_i ^= R_i-1
    for (int i = 0; i < BLOCK_SIZE / 2; ++i) {
      temp_block[i] ^= block[i + BLOCK_SIZE / 2];
    }
  }

  memcpy(block, temp_block, BLOCK_SIZE);
}

void des(istream &in, ostream &out, const string &key, bool encode) {
  // Preparing
  bool main_key_ext[BLOCK_SIZE];
  for (int i = 0; i < BLOCK_SIZE; ++i) {
    if ((i + 1) % 8 == 0) {
      continue; // we do not need parity
    }
    main_key_ext[i] = ((unsigned char)key[i / 8] >> (7 - (i % 8))) & 1;
  }

  bool main_key[MAIN_KEY_SIZE];
  for (int i = 0; i < MAIN_KEY_SIZE; ++i) {
    main_key[i] = main_key_ext[CD[i] - 1];
  }

  // Generating keys
  bool keys[ROUNDS][KEY_SIZE];
  int cur_shift = 0;
  for (int round = 0; round < ROUNDS; ++round) {
    cur_shift += KEYS_SHIFT[round];
    for (int i = 0; i < KEY_SIZE; ++i) {
      keys[round][i] = main_key[(KP[i] - 1 + MAIN_KEY_SIZE - cur_shift) % MAIN_KEY_SIZE];
    }
  }

  // Encrypting/decrypting blocks
  while (true) {
    // Get block
    unsigned char in_block[BLOCK_SIZE / 8];
    memset(in_block, 0, BLOCK_SIZE / 8);
    for (int i = 0; i < BLOCK_SIZE / 8; ++i) {
      char next = in.get();
      if (next == EOF and i == 0) {
        return;
      } else if (next == EOF) {
        break;
      } else {
        in_block[i] = next;
      }
    }

    // Preparing
    bool block[BLOCK_SIZE];
    for (int i = 0; i < BLOCK_SIZE; ++i) {
      block[i] = (in_block[i / 8] >> (7 - (i % 8))) & 1;
    }

    // Initial permutation (IP)
    block_permutation(block, IP);

    // Rounds
    for (int round = 0; round < ROUNDS; ++round) {
      round_encrypt(block, keys[encode ? round : ROUNDS - round - 1], encode);
    }

    // Final permutation (IP^(-1))
    block_permutation(block, FP);

    // Put block
    unsigned char out_block[BLOCK_SIZE / 8];
    memset(out_block, 0, BLOCK_SIZE / 8);
    for (int i = 0; i < BLOCK_SIZE; ++i) {
      out_block[i / 8] |= (((unsigned char)block[i]) << (7 - (i % 8)));
    }
    out << out_block;
  }
}

int main() {
  string key = "Hello world!";
  string text = "Nice to meet you. Lol. 1234. Lol?";
  std::cout << "Key: " << key << std::endl;
  std::cout << "Text: " << text << std::endl;

  stringstream in1(text, stringstream::binary | stringstream::in);
  stringstream out1(stringstream::binary | stringstream::out);
  des(in1, out1, key, true);
  string encoded = out1.str();
  std::cout << "Encoded: " << encoded << std::endl;

  stringstream in2(encoded, stringstream::binary | stringstream::in);
  stringstream out2(stringstream::binary | stringstream::out);
  des(in2, out2, key, false);
  string decoded = out2.str();
  std::cout << "Decoded: " << decoded << std::endl;
}
