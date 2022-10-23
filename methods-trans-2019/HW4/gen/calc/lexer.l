%{
  #include "parser.h"
}%

%{
  #include "lexer.h"
}%

%%

"[ \t\n]+" {                }
"\\("      { return LBR;    }
"\\)"      { return RBR;    }
"\\*"      { return MUL; }
"\\/"      { return DIV;  }
"\\-"      { return MINUS; }
"\\+"      { return PLUS; }
"\\="      { return EQUAL; }
"\\>\\>"   { return SHIFT; }
"[0-9]+"   { cur_unio.num = std::stoi(cur_string); return NUM; }
"[a-z]"    { cur_unio.ch = cur_string[0]; return VAR; }

%%

