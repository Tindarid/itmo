#include <gtest/gtest.h>
#include <cstdlib>
#include <functional>
#include "parser.h"

TEST(lexer, single_grammar_term) {
  lexer x1("s"); x1.next();
  EXPECT_EQ(token::VAR, x1.cur());

  lexer x2("or"); x2.next();
  EXPECT_EQ(token::OR, x2.cur());

  lexer x3("and"); x3.next();
  EXPECT_EQ(token::AND, x3.cur());

  lexer x4("xor"); x4.next();
  EXPECT_EQ(token::XOR, x4.cur());

  lexer x5("not"); x5.next();
  EXPECT_EQ(token::NOT, x5.cur());

  lexer x6("("); x6.next();
  EXPECT_EQ(token::LPAREN, x6.cur());

  lexer x7(")"); x7.next();
  EXPECT_EQ(token::RPAREN, x7.cur());

  lexer x8(""); x8.next();
  EXPECT_EQ(token::END, x8.cur());
}


TEST(lexer, all_in_one_grammar_terms) {
  lexer x("(a and b) or (b xor d) and (not k)");
  x.next(); EXPECT_EQ(token::LPAREN, x.cur());
  x.next(); EXPECT_EQ(token::VAR,    x.cur());
  x.next(); EXPECT_EQ(token::AND,    x.cur());
  x.next(); EXPECT_EQ(token::VAR,    x.cur());
  x.next(); EXPECT_EQ(token::RPAREN, x.cur());
  x.next(); EXPECT_EQ(token::OR,     x.cur());
  x.next(); EXPECT_EQ(token::LPAREN, x.cur());
  x.next(); EXPECT_EQ(token::VAR,    x.cur());
  x.next(); EXPECT_EQ(token::XOR,    x.cur());
  x.next(); EXPECT_EQ(token::VAR,    x.cur());
  x.next(); EXPECT_EQ(token::RPAREN, x.cur());
  x.next(); EXPECT_EQ(token::AND,    x.cur());
  x.next(); EXPECT_EQ(token::LPAREN, x.cur());
  x.next(); EXPECT_EQ(token::NOT,    x.cur());
  x.next(); EXPECT_EQ(token::VAR,    x.cur());
  x.next(); EXPECT_EQ(token::RPAREN, x.cur());
  x.next(); EXPECT_EQ(token::END,    x.cur());
}

TEST(lexer, random_grammar_terms) {
  std::vector<int> tokens;
  std::string str = "";
  srand(time(0));
  for (int i = 0; i < 10000; ++i) {
    int r = rand() % 8;
    tokens.push_back(r);
    switch (r) {
      case token::VAR:
        str += "a";
        break;
      case token::LPAREN:
        str += "(";
        break;
      case token::RPAREN:
        str += ")";
        break;
      case token::AND:
        str += "and";
        break;
      case token::OR:
        str += "or";
        break;
      case token::XOR:
        str += "xor";
        break;
      case token::NOT:
        str += "not";
        break;
      case token::END:
        tokens.pop_back();
        break;
      default:
        throw std::runtime_error("undefined token ind");
        break;
    }
    r = rand() % 10 + 1;
    for (int j = 0; j < r; ++j) {
      str += " ";
    }
  }
  tokens.push_back(token::END);

  lexer x(str);
  for (int i = 0; i < tokens.size(); ++i) {
    x.next();
    EXPECT_EQ(tokens[i], x.cur());
  }
}

TEST(lexer, not_grammar_term) {
  int catches = 0;
  try {
    lexer x("'"); x.next();
  } catch(std::runtime_error &e) {
    catches++;
  }
  try {
    lexer x("andd"); x.next();
  } catch(std::runtime_error &e) {
    catches++;
  }
  try {
    lexer x("kk"); x.next();
  } catch(std::runtime_error &e) {
    catches++;
  }
  EXPECT_EQ(3, catches);
}

TEST(parser, correct) {
  parser p;
  p.parse("a and b");
  p.parse("a and b or c");
  p.parse("a and b xor d");
  p.parse("a and not b");
}

TEST(parser, incorrect) {
  int m_be = 0;
  int catches = 0;
  parser p;

  try { m_be++; p.parse("not a b"); } catch (std::runtime_error &e) { catches++; }
  try { m_be++; p.parse("a b"); } catch (std::runtime_error &e) { catches++; }
  try { m_be++; p.parse("and a b"); } catch (std::runtime_error &e) { catches++; }
  try { m_be++; p.parse("xor a b"); } catch (std::runtime_error &e) { catches++; }
  try { m_be++; p.parse("xor a"); } catch (std::runtime_error &e) { catches++; }
  try { m_be++; p.parse("xor or"); } catch (std::runtime_error &e) { catches++; }
  try { m_be++; p.parse("xor a or"); } catch (std::runtime_error &e) { catches++; }
  try { m_be++; p.parse("not not"); } catch (std::runtime_error &e) { catches++; }
  try { m_be++; p.parse("a and not not b"); } catch (std::runtime_error &e) { catches++; }

  EXPECT_EQ(m_be, catches);
}

TEST(parser, random) {
  srand(time(0));
  std::function<std::string(int)> gen_rand = [&](int deep){
    if (deep == 0) {
      if (rand() % 2) {
        return std::string(" not a ");
      } else {
        return std::string(" b ");
      }
    }
    int r = rand() % 3;
    std::string left = gen_rand(deep - 1);
    std::string right = gen_rand(deep - 1);
    if (r == 0) {
      return left + " and " + right;
    } else if (r == 1) {
      return left + " or " + right;
    } else {
      return left + " xor " + right;
    }
  };
  parser p;
  for (int i = 0; i < 50; ++i) {
    std::string lol = gen_rand(7);
    p.parse(lol);
  }
}
