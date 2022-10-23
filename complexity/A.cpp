#include <cstdio>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <vector>
#include <cassert>
using std::string;

constexpr int MOD = 239;

void print_poly(const std::vector<int> &p) {
  printf("%d\n", (int)p.size() - 1);
  for (int d : p) {
    printf("%d ", d);
  }
  printf("\n");
  fflush(stdout);
}

struct token {
  std::string src;
  enum {
    RBR, LBR, NOT, OR, AND, VAR, START, END
  } type;
};

struct tokenizer {
  std::vector<token> tokens;
  std::string expr;
  int cur = 0;

  tokenizer() { }

  tokenizer(const std::string &e) : expr(e) {
    tokens.push_back({"start", token::START});
    tokenize();
    tokens.push_back({"end", token::END});
  }

  bool has_next() {
    return (cur + 1 < tokens.size());
  }

  token next() {
    return tokens[++cur];
  }

  token prev() {
    return tokens[--cur];
  }

  bool is_x_or_digit(char c) {
    if (c == 'x') return true;
    if ('0' <= c && c <= '9') return true;
    return false;
  }

  int parse_str(int j) {
    while (j < expr.length() && is_x_or_digit(expr[j])) {
      j++;
    }
    return j - 1;
  }

  void tokenize() {
    for (int i = 0; i < expr.length(); i++) {
      char c = expr[i];
      if (c == ' ') {
        continue;
      }

      switch (c) {
        case '!':
          tokens.push_back({"!", token::NOT});
          break;
        case '|':
          tokens.push_back({"|", token::OR});
          break;
        case '&':
          tokens.push_back({"&", token::AND});
          break;
        case '(':
          tokens.push_back({"(", token::LBR});
          break;
        case ')':
          tokens.push_back({")", token::RBR});
          break;
        default:
          int j = parse_str(i);
          tokens.push_back({expr.substr(i, j - i + 1), token::VAR});
          assert(j > i);
          i = j;
          break;
      }
    }
  }
};

inline int e_m(int some) {
  return (some + 10 * MOD) % MOD;
}

std::vector<int> SUM(const std::vector<int> &v1, const std::vector<int> &v2) {
  int size = std::max(v1.size(), v2.size());
  std::vector<int> ans(size, 0);
  for (int i = 0; i < size; ++i) {
    if (i < v1.size()) {
      ans[i] = e_m(ans[i] + v1[i]);
    }
    if (i < v2.size()) {
      ans[i] = e_m(ans[i] + v2[i]);
    }
  }
  while (ans.size() > 1 && ans.back() == 0) {
    ans.pop_back();
  }
  return ans;
}

std::vector<int> MUL(const std::vector<int> &v1, const std::vector<int> &v2) {
  std::vector<int> ans(v1.size() + v2.size(), 0);
  for (int i = 0; i < v1.size(); ++i) {
    for (int j = 0; j < v2.size(); ++j) {
      ans[i + j] = e_m(ans[i + j] + v1[i] * v2[j]);
      fflush(stdout);
    }
  }
  while (ans.size() > 1 && ans.back() == 0) {
    ans.pop_back();
  }
  return ans;
}

void NOT_AND_PLUS(std::vector<int> &v) {
  for (int &t : v) {
    t = e_m(-t);
  }
  v[0] = e_m(v[0] + 1);
}

struct expression {
  virtual bool eval(const std::vector<bool> &x) { exit(3); return false; }
  virtual std::vector<int> poly(const std::vector<bool> &x, int cur) { exit(3); return {}; }
};
struct expr_or : expression { 
  expression *e1; expression *e2; 
  expr_or(expression *_e1, expression *_e2) : e1(_e1), e2(_e2) {} 
  virtual bool eval(const std::vector<bool> &x) { return e1->eval(x) || e2->eval(x); }
  virtual std::vector<int> poly(const std::vector<bool> &x, int cur) {
    auto a = e1->poly(x, cur);
    auto b = e2->poly(x, cur);
    NOT_AND_PLUS(a); NOT_AND_PLUS(b);
    auto ans = MUL(a, b);
    NOT_AND_PLUS(ans);
    return ans;
  }
};
struct expr_and : expression { 
  expression *e1; expression *e2; 
  expr_and(expression *_e1, expression *_e2) : e1(_e1), e2(_e2) {} 
  virtual bool eval(const std::vector<bool> &x) { return e1->eval(x) && e2->eval(x); }
  virtual std::vector<int> poly(const std::vector<bool> &x, int cur) {
    return MUL(e1->poly(x, cur), e2->poly(x, cur));
  }
};
struct expr_not : expression { 
  expression *e1;
  expr_not(expression *_e1) : e1(_e1) {} 
  virtual bool eval(const std::vector<bool> &x) { return !e1->eval(x); }
  virtual std::vector<int> poly(const std::vector<bool> &x, int cur) {
    auto some = e1->poly(x, cur);
    NOT_AND_PLUS(some);
    return some;
  }
};
struct expr_var : expression { 
  int ind;
  expr_var(const std::string &src) {
    ind = std::atoi(src.data() + 1) - 1;
  } 
  virtual bool eval(const std::vector<bool> &x) { return x[ind]; }
  virtual std::vector<int> poly(const std::vector<bool> &x, int cur) {
    if (cur == ind) {
      return {0, 1};
    }
    return { e_m(x[ind]) };
  }
};

struct parser {
  tokenizer tokens;

  parser() {}

  expression *parse(const std::string &s) {
    tokens = tokenizer(s);
    return expr(false);
  }

  // expr
  expression *expr(bool lb_open) {
    expression *temp = sum();
    if (tokens.has_next()) {
      switch(tokens.next().type) {
        case token::END:
          assert(!lb_open);
          break;
        case token::RBR: 
          assert(lb_open);
          break;
        default:
          assert(0 && "hm");
          break;
      }
    }
    return temp;
  }

  // or
  expression *sum() {
    expression *temp = term();
    while (tokens.has_next()) {
      switch(tokens.next().type) {
        case token::OR:
          temp = new expr_or(temp, term());
          break;
        default:
          tokens.prev();
          return temp;
      }
    }
    return temp;
  }

  // and
  expression *term() {
    expression *temp = prim();
    while (tokens.has_next()) {
      switch(tokens.next().type) {
        case token::AND:
          temp = new expr_and(temp, prim());
          break;
        default:
          tokens.prev();
          return temp;
      }
    }
    return temp;
  }

  // primary
  expression *prim() {
    token t = tokens.next();
    switch (t.type) {
      case token::VAR:
        if (t.src[0] != 'x') exit(3);
        return new expr_var(t.src);
      case token::NOT: 
        return new expr_not(prim());
      case token::LBR: 
        return expr(true);
      case token::RBR: 
      case token::END:
      default:
        assert(0);
        break;
    }
    exit(3);
  }
};

int subst(const std::vector<int> &p, int r) {
  if (r == 0) {
    return p.back();
  } else {
    int res = 0;

    for (int i = 0; i < p.size(); ++i) {
      res = (res + p[i]) % MOD;
    }

    return res;
  }
}

std::vector<bool> hm(10);
std::vector<bool> rs;
std::vector<int> get_global_poly(expression *e, int n, int cur, int cur2) {
  if (cur2 == n) {
    return e->poly(hm, cur);
  } else {
    if (cur == cur2) {
      return get_global_poly(e, n, cur, cur2 + 1);
    } else if (cur > cur2) {
      hm[cur2] = rs[cur2];
      return get_global_poly(e, n, cur, cur2 + 1);
    } else {
      hm[cur2] = true;
      auto a = get_global_poly(e, n, cur, cur2 + 1);

      hm[cur2] = false;
      auto b = get_global_poly(e, n, cur, cur2 + 1);

      return SUM(a, b);
    }
  }
}

std::vector<int> get_g_poly(expression *e, int n, int cur) {
  auto temp = get_global_poly(e, n, cur, 0);
  std::reverse(temp.begin(), temp.end());
  return temp;
}

int main() {
  srand(time(nullptr));

  char buffer[200];
  parser p;
  while (true) {
    rs.clear();
    int n = 0;
    scanf("%d", &n);

    if (n == 0) {
      break;
    }

    char c;
    scanf("%c", &c);

    scanf("%[^\n]", buffer);
    expression *e = p.parse(string(buffer));

    int k;
    scanf("%d", &k);

    bool cheated = false;
    int maybe_r = -1;
    std::vector<int> last_poly;
    for (int round = 1; round <= n; ++round) {
      if (round != 1) {
        int r;
        scanf("%d", &r);
        k = subst(last_poly, r);
        rs.push_back(r);

        if (maybe_r == r) {
          cheated = true;
        }
      }
      last_poly = get_g_poly(e, n, round - 1);
      //print_poly(last_poly);
      if (round == 1 || !cheated) {
        maybe_r = abs(rand()) % 2;
        int temp = subst(last_poly, maybe_r);

        //printf("my_k = %d, not yet cheated, maybe it is %d? (temp = %d)\n", k, maybe_r, temp); fflush(stdout);
        if (maybe_r == 0) {
          last_poly = {(k - 2 * temp + 10 * MOD) % MOD, temp % MOD};
        } else {
          last_poly = {(-k + 2 * temp + 10 * MOD) % MOD, (-temp + k + 10 * MOD) % MOD};
        }
      } else {
        //printf("my_k = %d, already cheated fool\n", k); fflush(stdout);
      }
      print_poly(last_poly);
    }
  }
}
