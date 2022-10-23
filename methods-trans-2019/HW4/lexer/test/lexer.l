%{
  // TODO: another in header
  #include "lexer.h"
  enum token {LBR, RBR, PLUS, MINUS, MUL, DIV, NUMBER, END};
  int main() { }
}%

%%

"[ \t\n]+" {                }
"\\("      { return LBR;    }
"\\)"      { return RBR;    }
"\\+"      { return PLUS;   }
"\\-"      { return MINUS;  }
"\\*"      { return MUL;    }
"\\/"      { return DIV;    }
"[0-9]+"   { return NUMBER; }

%%
