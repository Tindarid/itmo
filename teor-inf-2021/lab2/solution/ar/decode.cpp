#include "ar/decode.h"

std::vector<unsigned char> Decode::bwt_decode(const unsigned char *input, size_t size) {
  unsigned char temp[sizeof(size_t)];
  std::memcpy(temp, input, sizeof(size_t));
  size_t pos = *(size_t *)(temp);
  input += sizeof(size_t);
  size -= sizeof(size_t);

  std::vector<unsigned char> sorted(256);
  std::iota(sorted.begin(), sorted.end(), 0);

  std::unordered_map<unsigned char, size_t> c_first, c_second;
  std::vector<size_t> f;

  for (size_t i = 0; i < size; ++i) {
    f.push_back(c_first[input[i]]++);
  }

  for (size_t i = 1; i < sorted.size(); ++i) {
    c_second[sorted[i]] = c_second[sorted[i - 1]] + c_first[sorted[i - 1]];
  }

  std::vector<unsigned char> result = {input[pos]};
  for (size_t i = 0; i < size - 1; ++i) {
    pos = f[pos] + c_second[input[pos]];
    result.push_back(input[pos]);
  }
  std::reverse(result.begin(), result.end());

  return result;
}

std::vector<unsigned char> Decode::mtf_decode(const unsigned char *input, size_t size) {
  std::list<unsigned char> l(256);
  std::iota(l.begin(), l.end(), 0);
  std::vector<unsigned char> result;
  for (size_t i = 0; i < size; ++i) {
    auto rank = input[i];
    auto it = l.begin();
    std::advance(it, rank);
    auto ch = *it;
    result.push_back(ch);
    l.erase(it);
    l.push_front(ch);
  }
  return std::move(result);
}

std::vector<unsigned char> Decode::decode(const unsigned char *input, size_t size) {
  this->input = input;
  this->size = size;
  this->cur_pos = 0;

  for (int i = 1; i <= CODE; i++) {
    value = (value << 1) + get();
  }
  while (true) {
    int sym_index = decode_symbol();
    if (sym_index == EOF_SYMBOL || end) {
      break;
    }
    auto ch = index_to_char[context][sym_index];
    cur.push_back(ch);
    update(sym_index);
    update_context(ch);
  }
  auto mtf = mtf_decode(cur.data(), cur.size());
  return bwt_decode(mtf.data(), mtf.size());
}

int Decode::decode_symbol() {
  long long sum = ((((value - low) + 1) * cum[context][0] - 1) / (high - low));

  int symbol = 0;
  while (cum[context][++symbol] > sum);
  recalc(symbol);

  while (true) {
    if (high < H) {
    } else if (low >= H) {
      value -= H; low -= H; high -= H;
    } else if (low >= F && high < T) {
      value -= F; low -= F; high -= F;
    } else {
      break;
    }
    low <<= 1;
    high <<= 1;
    value = (value << 1) + get();
  }
  return symbol;
}

int Decode::get() {
  if (bits_in_buf == 0) {
    if (cur_pos == size) {
      end = true;
      return -1;
    }
    buffer = input[cur_pos++];
    bits_in_buf = 8;
  }
  int t = buffer & 1;
  buffer >>= 1;
  bits_in_buf--;
  return t;
}
