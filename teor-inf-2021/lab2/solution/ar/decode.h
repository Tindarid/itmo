#pragma once

#include "ar/base.h"

class Decode : public Base {
  long long value = 0;

  int buffer = 0;
  int bits_in_buf = 0;
  bool end = false;
  const unsigned char *input = nullptr;
  size_t size = 0;
  size_t cur_pos = 0;

public:
  using Base::Base;
  int decode_symbol();
  int get();
  std::vector<unsigned char> decode(const unsigned char *input, size_t size);
  std::vector<unsigned char> mtf_decode(const unsigned char *input, size_t size);
  std::vector<unsigned char> bwt_decode(const unsigned char *input, size_t size);
};
