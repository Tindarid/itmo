#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <cmath>

#include <cassert>
#include <random>
#include <ctime>

#pragma pack(1)

size_t h[256] = {0};
size_t h2[256][256] = {0};
size_t h3[256 * 256][256] = {0};

struct Counter {
  uint32_t cur = 0;

  void send_byte(unsigned char c) {
    c &= 0xff;
    cur = (cur << 8) | c;
    h[c]++;
    h2[((cur & 0xff00) >> 8) & 0xff][c]++;
    h3[(cur & 0xffff00) >> 8][c]++;
  }

  double count1() {
    double s = 0;
    for (auto hh : h) {
      s += hh;
    }

    double ans = 0;
    for (auto hh : h) {
      double p = 1.0 * hh / s;
      if (p != 0) {
        ans -= p * std::log2(p);
      }
    }
    return ans;
  }

  double count2() {
    size_t s = 0;
    for (int i = 0; i < 256; ++i) {
      for (int j = 0; j < 256; ++j) {
        s += h2[i][j];
      }
    }

    double ans = 0;

    for (int i = 0; i < 256; ++i) {
      size_t ss = 0;
      for (int j = 0; j < 256; ++j) {
        ss += h2[i][j];
      }
      for (int j = 0; j < 256; ++j) {
        double pxy = 1.0 * h2[i][j] / s;
        double p = 1.0 * h2[i][j] / ss;
        if (pxy == 0 || p == 0) {
          continue;
        }
        ans -= pxy * std::log2(p);
      }
    }

    return ans;
  }

  double count3() {
    size_t s = 0;
    for (int i = 0; i < 256 * 256; ++i) {
      for (int j = 0; j < 256; ++j) {
        s += h3[i][j];
      }
    }

    double ans = 0;

    for (int i = 0; i < 256 * 256; ++i) {
      size_t ss = 0;
      for (int j = 0; j < 256; ++j) {
        ss += h3[i][j];
      }
      for (int j = 0; j < 256; ++j) {
        double pxy = 1.0 * h3[i][j] / s;
        double p = 1.0 * h3[i][j] / ss;
        if (pxy == 0 || p == 0) {
          continue;
        }
        ans -= pxy * std::log2(p);
      }
    }

    return ans;
  }
};

std::vector<unsigned char> read_file(const char *filename) {
  FILE* f = fopen(filename, "rb");
  assert(f != nullptr);
  fseek(f, 0, SEEK_END);
  auto f_len = ftell(f);
  fseek(f, 0, SEEK_SET);

  std::vector<unsigned char> result(f_len);
  for (size_t i = 0; i < result.size(); ++i) {
    result[i] = getc(f);
  }
  fclose(f);

  return result;
}

int main(int argc, char** argv) {
  if (argc < 2) return 1;

  auto in = read_file(argv[1]);

  Counter c;
  for (auto a : in) {
    c.send_byte(a);
  }

  std::cout << "H(X)    = " << c.count1() << std::endl;
  std::cout << "H(X|X)  = " << c.count2() << std::endl;
  std::cout << "H(X|XX) = " << c.count3() << std::endl;

  return 0;
}
