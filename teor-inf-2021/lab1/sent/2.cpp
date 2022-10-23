#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

#include <algorithm>
#include <vector>
#include <map>
#include <set>

#include <cassert>
#include <random>
#include <ctime>

#pragma pack(1)

using uint = unsigned int;
using word = unsigned short;

struct fsm {
  word s[2]{};
  uint pp{};

  fsm(word a, word b) {
    s[0] = a; s[1] = b;
    pp = 0;
  }

  fsm() : fsm(0, 0) { }
};

struct my_fsm {
  fsm in{};
  size_t count[2]{};

  my_fsm(word a, word b) {
    in = {a, b};
    count[0] = count[1] = 0;
  }

  my_fsm() : my_fsm(0, 0) {}
};

std::vector<my_fsm> fsm0 {
  {193,100},
  {  1,  5},
  { 17,  4},
  {  8,  3},
  { 94,  2},
  { 94,  2},
  { 16, 13},
  { 83, 26},
  { 84,  3},
  { 57,  1},
  {114,  9},
  { 79, 10},
  {106, 36},
  { 69, 94},
  { 83,  7},
  { 83, 14},
  {101, 15},
  {113, 71},
  {108, 50},
  {125, 18},
  {116, 39},
  { 24, 20},
  {  9, 21},
  { 24, 96},
  {  0,106},
  { 22,  8},
  { 83, 11},
  { 36, 25},
  { 35, 31},
  {106, 28},
  {  9, 66},
  { 58, 12},
  {110, 32},
  {110, 32},
  {118, 33},
  { 33,102},
  {104, 27},
  { 32, 29},
  { 23,  6},
  {116, 93},
  { 75, 34},
  {143,113},
  {110, 55},
  {110, 46},
  {108, 65},
  {117, 42},
  {124, 45},
  {117, 44},
  {118, 59},
  {117, 73},
  {117, 60},
  {117, 56},
  {118, 43},
  {110, 63},
  {118, 47},
  {110, 40},
  {117, 57},
  {108, 61},
  {117, 49},
  {117, 51},
  {108, 38},
  {108, 67},
  {144, 19},
  {118, 52},
  {118, 53},
  {118, 64},
  { 56, 68},
  {118, 54},
  {120, 72},
  {124, 58},
  {124, 74},
  { 99, 16},
  { 32, 37},
  {124, 48},
  {124, 69},
  {121, 76},
  {121, 77},
  {124, 70},
  {131, 62},
  {230, 14},
  {135, 41},
  {104, 82},
  {126, 92},
  {  4, 97},
  {121, 75},
  {122, 81},
  {122, 87},
  {122, 88},
  {122, 85},
  {126, 75},
  {121,  8},
  {122, 86},
  {104, 89},
  { 93, 19},
  { 95, 30},
  {122, 91},
  { 38, 22},
  {122, 95},
  {132,107},
  {122, 97},
  {171, 78},
  {122, 99},
  {139, 80},
  {132,105},
  {125,107},
  {132, 98},
  {105,101},
  {125,101},
  {121, 99},
  {128,112},
  {154, 84},
  {130,109},
  {132,103},
  {136,  6},
  {130,111},
  {125,104},
  {172,110},
  {154, 97},
  {154, 95},
  {130,109},
  {137,114},
  {154,108},
  {138,115},
  {137,120},
  {154,108},
  {138,115},
  {138,101},
  {143,123},
  {137,123},
  {137,128},
  {142,128},
  {175,136},
  {142,119},
  {172,116},
  {148,127},
  {148,134},
  {150,132},
  {143,129},
  {147,119},
  {153,133},
  {158,134},
  {149,135},
  {153,128},
  {149,137},
  {142,120},
  {157,141},
  {173,133},
  {164,132},
  {149,141},
  {159,141},
  {155,140},
  {166,139},
  {158,141},
  {166,130},
  {179,122},
  {167,150},
  {174,150},
  {165,150},
  {161,152},
  {161,148},
  {175,151},
  {167,152},
  {174,150},
  {186,160},
  {181,138},
  {176,158},
  {180,150},
  {165,158},
  {200,133},
  {184,160},
  {184,146},
  {202,133},
  {183,151},
  {188,160},
  {176,157},
  {180,155},
  {175,161},
  {189,146},
  {195,146},
  {198,133},
  {185,156},
  {179,138},
  {189,160},
  {195,160},
  {189,174},
  {184,162},
  {184,169},
  {189,147},
  {191,163},
  {188,166},
  {191,146},
  {192,169},
  {194,163},
  {201,138},
  {196,182},
  {200,177},
  {197,182},
  {195,169},
  {238,146},
  {202,177},
  {199,190},
  {210,160},
  {203,177},
  {205,190},
  {211,190},
  {206,190},
  {204,192},
  {208,190},
  {212,173},
  {214,178},
  {249,171},
  {207,190},
  {209,190},
  {217,195},
  {216,190},
  {213,168},
  {215,190},
  {219,183},
  {245,249},
  {231,178},
  {242,168},
  {232,168},
  {233,178},
  {229,168},
  {239,171},
  {254,215},
  {243,168},
  {222,168},
  {237,195},
  {236,190},
  {227,196},
  {230,178},
  {241,168},
  {228,195},
  {235,168},
  {223,178},
  {240,168},
  {238,190},
  {224,168},
  {226,171},
  {220,171},
  {244,168},
  {221,168},
  {234,168},
  {247,168},
  {250,179},
  {225,183},
  {248,179},
  {248,179},
  {253,169},
  {246,189},
  {252,179},
  {251,226},
  {251,239},
  {249,223},
  {252,237}
};

struct Estimator {
  static constexpr int sss = 15;
  uint ctx = 1 << 16;
  std::vector<word> p;
  std::vector<my_fsm> states;

  Estimator() : p(0x100<<16), states(1 << sss) {
    gen_graph_from_fsm0();
    // gen_graph_random();
    // gen_graph_binary();
  }

  void gen_graph_from_fsm0() { 
    states = fsm0;
    return;
    for (size_t i = 0; i < states.size(); ++i) {
      if (states[i].in.s[0] == i || states[i].in.s[1] == i) {
        // std::cout << "cycle " << i << std::endl;
      }
    }

    add_binary_tree(113, 6);
    int sz = states.size();
    for (int i = 1; i < sz; ++i) {
      // add_binary_tree(i, 6);
    }
    // add_binary_tree(1, 13);
    // add_binary_tree(93, 13);
  }

  void add_binary_tree(int n, int sz) {
    gen_graph_binary(1, states.size() - 1, sz, states[n].in.s[0], states[n].in.s[1], n);
  }

  void gen_graph_random() {
    for (auto &f : states) {
      f.in.s[0] = rand() % states.size();
      f.in.s[1] = rand() % states.size();
    }
  }

  void gen_graph_binary(int cur, int offset, int sz, int ret0, int ret1, int st) {
    if (cur == 1) {
      states.resize(states.size() + (1 << sz) - 2);
    }
    auto &f = cur == 1 ? states[st] : states[cur + offset - 1];
    auto temp = std::array{2 * cur, 2 * cur + 1};

    for (size_t i = 0; i < temp.size(); ++i) {
      auto k = temp[i] + offset;

      if (k - 1 >= states.size()) {
        f.in.s[i] = i == 0 ? ret0 : ret1;
        continue;
      }

      f.in.s[i] = k - 1;
      gen_graph_binary(temp[i], offset, sz, ret0, ret1, st);
    }
  }

  void fill_graph() {
    for (size_t i = 0; i < states.size(); ++i) {
      auto &f = states[i];
      auto sum = f.count[0] + f.count[1];
      // std::cout << i << " visited: " << sum << std::endl;
      if (sum == 0) {
        // std::cout << "never visited: " << i << std::endl;
        sum = 1;
      }
      f.in.pp = 32768LL * f.count[0] / sum;
      if (f.in.pp == 32768) {
        f.in.pp--;
      }
    }
  }

  void output(std::ofstream &out) {
    fill_graph();
    for (auto f : states) {
      out << f.in.s[0] << ", " << f.in.s[1] << ", " << f.in.pp << std::endl;
    }
  }

  void byte() { ctx=(ctx&0xFFFF)|(1<<16); }

  void update( uint bit ) {
    bit = (bit>0);

    auto &f = states[p[ctx]];
    f.count[bit]++;
    p[ctx] = f.in.s[bit];

    (ctx*=2)+=bit;
  }
};

std::vector<unsigned char> read_file(const char *filename) {
  FILE* f = fopen(filename, "rb");
  assert(f != nullptr);
  fseek(f, 0, SEEK_END);
  uint f_len = ftell(f);
  fseek(f, 0, SEEK_SET);

  std::vector<unsigned char> result(f_len);
  for (size_t i = 0; i < result.size(); ++i) {
    result[i] = getc(f);
  }
  fclose(f);

  return result;
}

int main(int argc, char** argv) {
  srand(time(nullptr));
  if (argc < 3) return 1;

  auto in = read_file(argv[1]);
  auto out = std::ofstream(argv[2]);

  Estimator P;

  for (auto c : in) {
    P.update(c&0x80); P.update(c&0x40); P.update(c&0x20); P.update(c&0x10);
    P.update(c&0x08); P.update(c&0x04); P.update(c&0x02); P.update(c&0x01);
    P.byte();
  }

  P.output(out);

  return 0;
}
