#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#define ALPH_SIZE 26
#define FIRST_CHAR ('a')
#define MAX_KEY_LEN 20
using namespace std;

char tabula_recta[ALPH_SIZE][ALPH_SIZE];

void set_tabula_recta() {
  for (int i = 0; i < ALPH_SIZE; ++i) {
    for (int j = 0; j < ALPH_SIZE; ++j) {
      tabula_recta[i][j] = (i + j) % ALPH_SIZE + FIRST_CHAR;
    }
  }
}

int gcd(int a, int b) {
  return b ? gcd (b, a % b) : a;
}

int kasiski(const string& text) {
  unordered_map<string, vector<int>> entries;
  int size = text.size();

  for (int pos = 0; pos < size; ++pos) {
    for (int len = 3; len < size - pos + 1; ++len) {
      string temp = text.substr(pos, len);
      auto it = entries.find(temp);
      if (it == entries.end()) {
        it = entries.insert(make_pair(temp, std::vector<int>())).first;
      }
      it->second.push_back(pos);
    }
  }

  unordered_set<int> diffs;
  for (auto it = entries.begin(); it != entries.end(); ++it) {
    vector<int>& positions = it->second;

    if (positions.size() < 2) {
      continue;
    }
    sort(positions.begin(), positions.end());

    for (int i = 0; i < positions.size() - 1; ++i) {
      diffs.insert(positions[i + 1] - positions[i]);
    }
  }

  unordered_map<int, int> gcds;
  for (auto it = diffs.begin(); it != diffs.end(); ++it) {
    for (auto gt = diffs.begin(); gt != diffs.end(); ++gt) {
      if (it != gt) {
        int gc = gcd(*it, *gt);
        auto jt = gcds.find(gc);
        if (jt == gcds.end()) {
          jt = gcds.insert(make_pair(gc, 0)).first;
        }
        jt->second++;
      }
    }
  }

  int ans = -1, max_entries = 0;
  for (auto it = gcds.begin(); it != gcds.end(); ++it) {
    if (it->first <= MAX_KEY_LEN) {
      if (ans == -1 || it->second > max_entries || (it->first > ans && it->second == max_entries)) {
        ans = it->first;
        max_entries = it->second;
      }
    }
  }

  return ans;
}

char frequency_analysis(const string& text) {
  vector<pair<char, int>> frequency(ALPH_SIZE);
  for (int i = 0; i < ALPH_SIZE; ++i) {
    frequency[i] = make_pair(i + FIRST_CHAR, 0);
  }
  for (int i = 0; i < text.size(); ++i) {
    frequency[tolower(text[i]) - FIRST_CHAR].second++;
  }

  auto comp = [](pair<char, int> a, pair<char, int> b){
    return a.second > b.second;
  };
  sort(frequency.begin(), frequency.end(), comp);
  string default_frequency = "etaonrishdlfcmugypwbvkxjqz";

  vector<int> count(ALPH_SIZE, 0);
  int ans_ind = 0;
  int max_point = 0;
  for (int i = 0; i < ALPH_SIZE; ++i) {
    char was = default_frequency[i];
    char become = frequency[i].first;
    for (int j = 0; j < ALPH_SIZE; ++j) {
      if (tabula_recta[was - FIRST_CHAR][j] == become) {
        count[j]++;
        if (count[j] > max_point) {
          ans_ind = j;
          max_point = count[j];
        }
      }
    }
  }
  /*
  for (int i = 0; i < ALPH_SIZE; ++i) {
    if (count[i] == max_point) {
      cout << char(i + FIRST_CHAR) << " ";
    }
  }
  cout << endl;
  */
  return FIRST_CHAR + ans_ind;
}

string decode(const string& text) {
  int key_len = kasiski(text);
  if (key_len < 3) {
    return "Cannot decode file";
  }
  vector<string> cols(key_len, "");
  for (int i = 0; i < text.size(); ++i) {
    cols[i % key_len] += text[i];
  }

  string ans = "";
  for (int i = 0; i < key_len; ++i) {
    ans += frequency_analysis(cols[i]);
  }
  return ans;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "Usage: " + string(argv[0]) + " [filename]" << endl;
    return 0;
  }
  set_tabula_recta();

  string input_file = argv[1];
  fstream in(input_file, fstream::in);

  if (!in.is_open()) {
    cout << "Cannot open input file: " + input_file << endl;
    return 0;
  }
  
  string text;
  in >> text;
  cout << decode(text) << endl;
}
