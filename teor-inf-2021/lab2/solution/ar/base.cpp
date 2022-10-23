#include "ar/base.h"

unsigned char index_to_char[MAX_CONTEXT][NUMBER_OF_SYMBOLS];
int char_to_index[MAX_CONTEXT][NUMBER_OF_CHARS];
int cum[MAX_CONTEXT][NUMBER_OF_SYMBOLS + 1];
int freq[MAX_CONTEXT][NUMBER_OF_SYMBOLS + 1];

Base::Base(int CTX_SIZE) {
  this->CTX_SIZE = CTX_SIZE;

  for (int j = 0; j < CTX_SIZE; ++j) {
    std::iota(std::begin(char_to_index[j]), std::end(char_to_index[j]), 1);
    std::iota(std::begin(index_to_char[j]) + 1, std::end(index_to_char[j]), 0);
    std::fill(std::begin(freq[j]), std::end(freq[j]), 1);
    std::iota(std::rbegin(cum[j]), std::rend(cum[j]), 0);
    freq[j][0] = 0;
  }
}

void Base::update(int sym_index) {
  if (cum[context][0] == MAX_FREQ) {
    int sum = 0;
    for (int i = NUMBER_OF_SYMBOLS; i >= 0; i--) {
      freq[context][i] = (freq[context][i] + 1) / 2;
      cum[context][i] = sum;
      sum += freq[context][i];
    }
  }
  int i = sym_index;
  while (freq[i - 1] == freq[i]) { i--; };
  if (i < sym_index) {
    std::swap(index_to_char[context][i], index_to_char[context][sym_index]);
    char_to_index[context][index_to_char[context][sym_index]] = sym_index;
    char_to_index[context][index_to_char[context][i]] = i;
  }
  freq[context][i]++;
  while (i --> 0) {
    cum[context][i]++;
  }
}

void Base::update_context(unsigned char ch) {
  context <<= 8;
  context |= ch;
  context &= CTX_SIZE - 1;
}

void Base::recalc(int symbol) {
  const auto range = high - low;
  const auto low_mult  = cum[context][symbol];
  const auto high_mult = cum[context][symbol - 1];
  const auto base_mult = cum[context][0];

  high = low + (range * high_mult) / base_mult;
  low = low + (range * low_mult) / base_mult;
}
