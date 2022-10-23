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

using uint = unsigned int;
using word = unsigned short;
using byte = unsigned char;
using qword = unsigned long long int;

struct fsm {
  word s[2]{};
  uint pp{};
  size_t count[2]{};

  fsm(word a, word b) {
    s[0] = a;
    s[1] = b;
    pp = 0;
    count[0] = count[1] = 0;
  }

  fsm() : fsm(0, 0) {}
};

using graph = std::vector<fsm>;

graph fsm0 {
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

int start_time = 0;

int time_spented() {
  return time(nullptr) - start_time;
}

constexpr int root_node = 0;
word ctx_state[0x100<<16];
bool visited[1 << 16];
std::vector<std::pair<int, int>> cur_chain;

struct Predictor {
  uint ctx;
  graph states;
  bool count_pp;

  Predictor(const graph &states_, bool count_pp) : states(states_), count_pp(count_pp) {
    ctx = (1 << 16);
    std::fill(std::begin(ctx_state), std::end(ctx_state), root_node);
      for (auto &s : states) {
        s.count[0] = 0;
        s.count[1] = 0;
        if (count_pp ) {
          s.pp = 0;
        }
      }
  }

  static graph delete_redundant(std::vector<int> to_delete, const graph &src) {
    std::map<int, int> mapping;
    for (size_t i = 0; i < src.size(); ++i) {
      auto it = std::lower_bound(to_delete.begin(), to_delete.end(), i);
      if (it != to_delete.end() && *it == i) {
        mapping[i] = -1;
      } else {
        mapping[i] = i - std::distance(to_delete.begin(), it);
      }
    }

    graph new_states;
    new_states.reserve(src.size());
    for (size_t i = 0; i < src.size(); ++i) {
      auto new_i = mapping[i];
      if (new_i == -1) {
        continue;
      }

      new_states.push_back(src[i]);

      auto &f = new_states.back();
      auto a = mapping[f.s[0]];
      auto b = mapping[f.s[1]];

      f.s[0] = a == -1 ? new_i : a;
      f.s[1] = b == -1 ? new_i : b;
    }

    return new_states;
  }

  struct dfs_res {
    int end;
    int count;
  };

  static dfs_res dfs(int a, const graph &res, int v) {
    cur_chain.emplace_back(a, v);
    const auto &f = res[a];
    if (visited[a]) {
      cur_chain.pop_back();
      return {-1, -1};
    }
    visited[a] = true;
    assert(f.count[0] + f.count[1] != 0);
    if (f.count[0] == 0 || f.count[1] == 0) {
      auto to = f.count[0] == 0 ? 1 : 0;
      if (f.s[to] == a) {
        cur_chain.pop_back();
        return {-2, -2};
      }
      auto r = dfs(f.s[to], res, to);
      if (r.end < 0) {
        cur_chain.pop_back();
        return r;
      }
      r.count++;
      return r;
    } else {
      return {a, 1};
    }
  }

  static int get_style(const std::vector<std::pair<int, int>> &chain, int style_param) {
    int res = 0;
    for (int i = 0; i < std::min(static_cast<int>(chain.size()), style_param); ++i) {
      auto a = chain[chain.size() - style_param + i].second;
      if (a == -1) {
        continue;
      }
      res <<= 1;
      res += a == 0 ? 0 : 1;
    }

    assert(res <= (1 << style_param));
    return res;
  }

  static graph squash_chains(graph src, int style_param) {
    assert(style_param <= 31);
    std::vector<std::vector<std::pair<int, int>>> best_chains(1 << style_param);
    for (size_t i = 0; i < src.size(); ++i) {
      const auto &f = src[i];
      if (f.count[0] == 0 || f.count[1] == 0) {
        if (!(f.count[0] == 0 && f.count[1] == 0)) {
          std::fill(std::begin(visited), std::end(visited), false);
          cur_chain.resize(0);
          auto r = dfs(i, src, -1);
          if (r.count < 0 || cur_chain.size() == 0) {
            continue;
          }
          auto s = get_style(cur_chain, style_param);
          assert(s <= best_chains.size());
          if (best_chains[s].size() < cur_chain.size()) {
            best_chains[s] = std::move(cur_chain);
          }
        }
      }
    }

    std::map<int, int> mapping;
    for (int cur_start = 0; cur_start < src.size(); ++cur_start) {
      bool bad = false;
      for (const auto &b : best_chains) {
        if (std::find_if(b.begin(), b.end(), [cur_start](auto &a) { return a.first == cur_start; }) != b.end()) {
          bad = true;
          break;
        }
      }
      if (bad || mapping.count(cur_start)) {
        continue;
      }
      const auto &f = src[cur_start];
      if (f.count[0] == 0 || f.count[1] == 0) {
        if (!(f.count[0] == 0 && f.count[1] == 0)) {
          std::fill(std::begin(visited), std::end(visited), false);
          cur_chain.resize(0);
          auto cur = dfs(cur_start, src, -1);
          if (cur.count < 0 || cur_chain.size() == 0) {
            continue;
          }
          assert(cur_chain.front().first == cur_start);
          assert(cur_chain.back().first == cur.end);
          assert(cur_chain.size() == cur.count);
          auto s = get_style(cur_chain, style_param);
          if (cur_chain.size() > best_chains[s].size()) {
            continue;
          }
          assert(cur_chain.size() <= best_chains[s].size());
          if (cur_chain.size() <= style_param) {
            continue;
          }

          for (size_t i = 0; i < cur_chain.size(); ++i) {
            mapping[cur_chain[i].first] = best_chains[s][best_chains[s].size() - cur_chain.size() + i].first;
          }
        }
      }
    }

    for (size_t i = 0; i < src.size(); ++i) {
      for (auto &a : src[i].s) {
        auto it = mapping.find(a);
        a = it == mapping.end() ? a : it->second;
      }
    }

    return src;
  }

  static int get_pp(int a, int b) {
    auto sum = a + b;
    auto res = 32768UL * a / (sum ? sum : 1);
    return res == 32768 ? 32767 : res;
  }

  graph output() {
    assert(count_pp);

    std::vector<int> never_visited;
    for (size_t i = 0; i < states.size(); ++i) {
      auto &f = states[i];
      auto sum = f.count[0] + f.count[1];
      if (sum == 0) {
        never_visited.push_back(i);
      }
      f.pp = get_pp(f.count[0], f.count[1]);
    }

    return delete_redundant(std::move(never_visited), states);
  }

  uint freq() { return states[ctx_state[ctx]].pp; }
  void byte() { ctx=(ctx&0xFFFF)|(1<<16); }

  void update(uint bit) {
    bit = (bit>0);

    assert(ctx_state[ctx] < states.size());
    auto &f = states[ctx_state[ctx]];
    f.count[bit]++;
    ctx_state[ctx] = f.s[bit];

    (ctx*=2)+=bit;
  }
};

struct RangeCoder {
  enum { NUM=4, sTOP=0x01000000U, Thres=0xFF000000U };
  enum { SCALElog=15, SCALE=1<<SCALElog, mSCALE=SCALE-1, hSCALE=SCALE/2, eSCALE=16*SCALE };

  uint range, FFNum, Cache; qword lowc;
  size_t total;

  void Init() {
    range = 0xFFFFFFFF; lowc = 0; FFNum = 0; Cache = -1; total = 0;
    total += 4; // f_len
  }

  size_t Quit() { for( uint _=0; _<NUM+1; _++ ) ShiftLow(); return total; }

  uint process( uint freq, uint bit ) {
    uint rnew = (qword(range)*(freq<<(32-SCALElog)))>>32;
    bit ? range-=rnew, lowc+=rnew : range=rnew;
    while( range<sTOP ) range<<=8, ShiftLow();
    return bit;
  }

  uint ShiftLow() {
    uint Carry = uint(lowc>>32), low = uint(lowc);
    if( low<Thres || Carry ) {
      if( Cache!=-1 ) total++;
      for (;FFNum != 0;FFNum--) total++;
      Cache = low>>24;
    } else FFNum++;
    return lowc = (low<<8);
  }
};

inline void proc_byte_count_pp(Predictor &P, unsigned char c) {
  P.update(c&0x80); P.update(c&0x40); P.update(c&0x20); P.update(c&0x10);
  P.update(c&0x08); P.update(c&0x04); P.update(c&0x02); P.update(c&0x01);
  P.byte();
}

inline void proc_byte(Predictor &P, RangeCoder &R, unsigned char c) {
  P.update(R.process(P.freq(), c&0x80)); P.update(R.process(P.freq(), c&0x40));
  P.update(R.process(P.freq(), c&0x20)); P.update(R.process(P.freq(), c&0x10));
  P.update(R.process(P.freq(), c&0x08)); P.update(R.process(P.freq(), c&0x04));
  P.update(R.process(P.freq(), c&0x02)); P.update(R.process(P.freq(), c&0x01));
  P.byte();
}

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

void flush_states(std::ofstream &out, const graph &states) {
  for (auto f : states) {
    out << f.s[0] << ", " << f.s[1] << ", " << f.pp << std::endl;
  }
}

graph recalc(const std::vector<unsigned char> &in, const graph &states) {
  Predictor P(states, true);
  for (auto c : in) {
    proc_byte_count_pp(P, c);
  }
  return P.output();
}

size_t compress(const std::vector<unsigned char> &in, const graph &states) {
  Predictor P(states, false);
  static RangeCoder R;
  R.Init();
  for (auto c : in) {
    proc_byte(P, R, c);
  }
  return R.Quit();
}

graph new_graph(graph old) {
  std::vector<std::vector<std::pair<int, int>>> parents(old.size());
  for (size_t i = 0; i < old.size(); ++i) {
    for (size_t j = 0; j < 2; ++j) {
      auto to = old[i].s[j];
      if (to != i) {
        parents[to].emplace_back(i, j);
      }
    }
  }
  std::vector<int> have_more_than_1_parent;
  for (size_t i = 0; i < parents.size(); ++i) {
    if (parents[i].size() > 1) {
      have_more_than_1_parent.push_back(i);
    }
  }

  auto new_g = old;

  if (have_more_than_1_parent.empty()) {
    return new_g;
  }

  // int target = *std::max_element(have_more_than_1_parent.begin(), have_more_than_1_parent.end(),
      // [&](int a, int b) { return old[a].count[0] + old[a].count[1] < old[b].count[0] + old[b].count[1]; });
  int target = have_more_than_1_parent[rand() % std::min(256UL, have_more_than_1_parent.size())];
  std::random_shuffle(parents[target].begin(), parents[target].end());
  int remove_parents = rand() % (parents[target].size() - 1) + 1;

  new_g.reserve(old.size() * remove_parents);

  for (int i = 0; i < remove_parents; ++i) {
    auto to_remove_src = parents[target][i].first;
    auto edge = parents[target][i].second;
    int shift = old.size() * (i + 1);
    for (size_t j = 0; j < old.size(); j++) {
      new_g.emplace_back(new_g[j].s[0] + shift, new_g[j].s[1] + shift);
    }
  }
  for (int i = 0; i < remove_parents; ++i) {
    auto to_remove_src = parents[target][i].first;
    auto edge = parents[target][i].second;
    int shift = old.size() * (i + 1);
    new_g[to_remove_src].s[edge] = target + shift;
  }

  return new_g;
}

int main(int argc, char** argv) {
  if (argc < 3) return 1;
  start_time = time(nullptr);
  srand(start_time);

  // std::cout << "rand seed: " << start_time << std::endl;

  auto in = read_file(argv[1]);
  auto out = std::ofstream(argv[2]);

  auto best_states = recalc(in, fsm0);
  auto best_total = compress(in, best_states);
  auto start = best_total;
  std::cout << "start: " << start << std::endl;

  int big_graph_times = 0;

  while (time_spented() < 60) {
    auto new_g = new_graph(best_states);
    // std::cout << "before recalc: " << new_g.size() << std::endl;
    new_g = recalc(in, new_g);
    auto a = compress(in, new_g);
    // std::cout << "after  recalc: " << new_g.size() << " " << a << std::endl;

    /*
    if (new_g.size() > (1 << 15)) {
      auto new_gg = Predictor::squash_chains(new_g, 15);
      new_gg = recalc(in, new_gg);
      auto b = compress(in, new_gg);
      std::cout << "after  squash: " << new_gg.size() << " " << b << std::endl;
      //break;
    }
    */

    if (new_g.size() > (1 << 15) /*|| new_gg.size() > (1 << 15)*/) {
      // std::cout << "skip big graph" << std::endl;
      if (big_graph_times++ >= 500) break;
      continue;
    }

    if (a < best_total) {
      best_total = a;
      best_states = std::move(new_g);
      std::cout << "new best: " << best_total << ", graph_size: " << best_states.size() << std::endl;
    }

    /*
    if (new_gg.size() <= new_g.size() && double(b - a) / a <= 0.03) {
      best_total = b;
      best_states = std::move(new_gg);
    }
    */
  }

  flush_states(out, best_states);
  std::cout << "best: " << best_total << " vs " << "start: " << start << std::endl;
  // std::cout << "time(s): " << time_spented() << std::endl;
  return 0;
}
