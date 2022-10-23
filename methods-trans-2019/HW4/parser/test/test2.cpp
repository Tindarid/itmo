#include <string>


unio parse(std::string &s) {
}

static unio consume(token t) {
  if (t != cur_token) throw std::runtime_error("unexpected token in consume");
  unio temp = cur_unio;
  cur_unio = unio();
  next_token();
  return temp;
}

unio E() {
  unio res = unio();
  switch (cur_token) {
    case LBR:
    case NUM:
      auto val1 = T();
      auto val2 = EE();

      
      break;
    default:
      throw std::runtime_error("unexpected token " + cur_token);
  }
  return res;
}

unio EE() {
  unio res = unio();
  switch (cur_token) {
    case PLUS:
      auto val1 = consume(PLUS);
      auto val2 = T();
      auto val3 = EE();

      
      break;
    // FOLLOW SECTION HERE
    case END:
    case RBR:
      break;
    default:
      throw std::runtime_error("unexpected token " + cur_token);
  }
  return res;
}

unio F() {
  unio res = unio();
  switch (cur_token) {
    case NUM:
      auto val1 = consume(NUM);

      
      break;
    case LBR:
      auto val1 = consume(LBR);
      auto val2 = E();
      auto val3 = consume(RBR);

      
      break;
    default:
      throw std::runtime_error("unexpected token " + cur_token);
  }
  return res;
}

unio T() {
  unio res = unio();
  switch (cur_token) {
    case LBR:
    case NUM:
      auto val1 = F();
      auto val2 = TT();

      
      break;
    default:
      throw std::runtime_error("unexpected token " + cur_token);
  }
  return res;
}

unio TT() {
  unio res = unio();
  switch (cur_token) {
    case MUL:
      auto val1 = consume(MUL);
      auto val2 = F();
      auto val3 = TT();

      
      break;
    // FOLLOW SECTION HERE
    case END:
    case PLUS:
    case RBR:
      break;
    default:
      throw std::runtime_error("unexpected token " + cur_token);
  }
  return res;
}

