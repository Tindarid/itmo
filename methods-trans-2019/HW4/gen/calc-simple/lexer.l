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
"[0-9]+"   { cur_unio.num = std::stoi(cur_string); return NUM; }

%%

