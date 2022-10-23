#pragma once

#include "ar/base.h"

class Encode : public Base {
  int left_bits = 0;
  unsigned int buffer = 0;
  int bits_in_buf = 0;

public:
  using Base::Base;

  void encode_symbol(int symbol);
  void write_bit(int bit);
  void flush(int bit);
  void end();
  std::vector<unsigned char> encode(const unsigned char *input, size_t size);
  std::vector<unsigned char> mtf_encode(const unsigned char *input, size_t size);
  std::vector<unsigned char> bwt_encode(const unsigned char *input, size_t size);
};
