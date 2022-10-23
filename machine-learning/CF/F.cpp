#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct message_class;
int K, N, alpha;
std::vector<message_class> classes;

struct message_class {
  int lambda;
  int count = 0;
  std::unordered_map<std::string, int> words;
  long double initial_ans = 0.0;

  long double prob() {
    return 1.0L * count / N;
  }

  long double word_prob(const std::string &word, bool reversed) {
    auto it = words.find(word);
    int word_cnt = it == words.end() ? 0 : it->second;
    if (reversed) {
      word_cnt = count - word_cnt;
      //return 1 - 1.0L * (word_cnt + alpha) / (2 * alpha + count);
    }
    return 1.0L * (word_cnt + alpha) / (2 * alpha + count);
  }

  void increase_word(std::string &&word) {
    auto it = words.find(word);
    if (it == words.end()) {
      words.insert({std::move(word), 1});
    } else {
      it->second++;
    }
  }
};

int main() {
  cin >> K; classes.resize(K);
  for (int i = 0; i < K; ++i) {
    cin >> classes[i].lambda;
  }

  cin >> alpha >> N;
  std::unordered_set<std::string> all_words;
  for (int i = 0, c, l; i < N; ++i) {
    cin >> c >> l;
    auto &cl = classes[c - 1];

    cl.count++;
    std::unordered_set<std::string> words;
    for (int j = 0; j < l; ++j) {
      std::string word; cin >> word;
      if (words.insert(word).second) {
        all_words.insert(word);
        cl.increase_word(std::move(word));
      }
    }
  }

  for (int i = 0; i < K; ++i) {
    auto &ans = classes[i].initial_ans;
    ans = classes[i].prob() * classes[i].lambda;
    for (const auto &w : all_words) {
      ans *= classes[i].word_prob(w, true);
    }
  }

  int M; cin >> M;
  cout << fixed << setprecision(10);
  for (int i = 0, l; i < M; ++i) {
    std::vector<long double> ans(K);
    for (int j = 0; j < K; ++j) {
      ans[j] = classes[j].initial_ans;
    }

    cin >> l;
    std::unordered_set<std::string> words;
    for (int j = 0; j < l; ++j) {
      std::string word; cin >> word;
      if (!words.insert(word).second) {
        continue;
      }

      bool in_all_words = all_words.find(word) != all_words.end();
      for (int c = 0; c < K; ++c) {
        long double temp = classes[c].word_prob(word, false);
        if (!in_all_words) {
          // ans[c] *= temp;
        } else {
          long double reversed = classes[c].word_prob(word, true);
          ans[c] /= reversed;
          ans[c] *= temp;
        }
      }
    }

    long double sum = 0.0L;
    for (auto a : ans) {
      sum += a;
    }
    for (auto a : ans) {
      cout << a / sum << " ";
    }
    cout << endl;
  }

}
