#pragma once

#include <cstdio>
#include <numeric>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <list>
#include <set>
#include <cstring>
#include <unordered_map>
#include <algorithm>

constexpr int CODE = 16;
constexpr int M = ((1L << CODE) - 1);
constexpr int MAX_FREQ = (1 << 14) - 1;

constexpr int NUMBER_OF_CHARS = 256;
constexpr int MAX_CONTEXT = (1 << 16);
constexpr int EOF_SYMBOL = NUMBER_OF_CHARS + 1;
constexpr int NUMBER_OF_SYMBOLS = NUMBER_OF_CHARS + 1;

constexpr int F = (M / 4 + 1);
constexpr int H = (2 * F);
constexpr int T = (3 * F);

extern unsigned char index_to_char[MAX_CONTEXT][NUMBER_OF_SYMBOLS];
extern int char_to_index[MAX_CONTEXT][NUMBER_OF_CHARS];
extern int cum[MAX_CONTEXT][NUMBER_OF_SYMBOLS + 1];
extern int freq[MAX_CONTEXT][NUMBER_OF_SYMBOLS + 1];

class Base {
public:
  unsigned int context = 0;

protected:
  int CTX_SIZE;
  long long low = 0;
  long long high = M;
  std::vector<unsigned char> cur;

public:
  Base(int CTX_SIZE);
  void update_context(unsigned char ch);
  void update(int sym_index);
  void recalc(int symbol);
};

