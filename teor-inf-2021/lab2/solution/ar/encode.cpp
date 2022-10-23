#include "ar/encode.h"

std::vector<unsigned char> Encode::bwt_encode(const unsigned char *input, size_t size) {
  std::vector<size_t> indexes(size);
  std::iota(indexes.begin(), indexes.end(), 0);

  std::vector<unsigned char> copy;
  for (int j = 0; j < 2; ++j) {
    for (size_t i = 0; i < size; ++i) {
      copy.push_back(input[i]);
    }
  }

  std::sort(indexes.begin(), indexes.end(), [&](auto a, auto b) {
    for (size_t i = 0; i < size; ++i) {
      if (copy[a + i] != copy[b + i]) {
        return copy[a + i] < copy[b + i];
      }
    }
    return false;
  });

  std::vector<unsigned char> result;
  for (int i = 0; i < size; ++i) {
    result.push_back(input[(indexes[i] + size - 1) % size]);
  }

  size_t pos = std::find(indexes.begin(), indexes.end(), 0) - indexes.begin();
  unsigned char temp[sizeof(size_t)];
  auto *ptr = (size_t *)temp;
  *ptr = pos;
  result.insert(result.begin(), std::begin(temp), std::end(temp));

  return result;
}

std::vector<unsigned char> Encode::mtf_encode(const unsigned char *input, size_t size) {
  std::list<unsigned char> l(256);
  std::iota(l.begin(), l.end(), 0);
  for (size_t i = 0; i < size; ++i) {
    auto ch = input[i];
    auto it = std::find(l.begin(), l.end(), ch);
    int rank = std::distance(l.begin(), it);
    cur.push_back(rank);
    l.erase(it);
    l.push_front(ch);
  }
  return std::move(cur);
}

std::vector<unsigned char> Encode::encode(const unsigned char *input, size_t size) {
  auto bwt = bwt_encode(input, size);
  auto mtf = mtf_encode(bwt.data(), bwt.size());
  for (auto ch : mtf) {
    int symbol = char_to_index[context][ch];
    encode_symbol(symbol);
    update(symbol);
    update_context(ch);
  }
  encode_symbol(EOF_SYMBOL);
  end();
  return std::move(cur);
}

void Encode::encode_symbol(int symbol) {
  recalc(symbol);
  while (true) {
    if (high < H) {
      flush(0);
    } else if (low >= H) {
      flush(1);
      low -= H; high -= H;
    } else if (low >= F && high < T) {
      low -= F; high -= F;
      left_bits++;
    } else {
      break;
    }
    low <<= 1;
    high <<= 1;
  }
}

void Encode::end() {
  encode_symbol(EOF_SYMBOL);
  left_bits++;
  flush(!(low < F));
  cur.push_back(buffer >> bits_in_buf);
}

void Encode::flush(int bit) {
  write_bit(bit);
  while (left_bits > 0) {
    write_bit(!bit);
    left_bits--;
  }
}

void Encode::write_bit(int bit) {
  buffer >>= 1;
  if (bit) {
    buffer |= 0x80;
  }
  if (++bits_in_buf == 8) {
    cur.push_back(buffer);
    bits_in_buf = 0;
  }
}
