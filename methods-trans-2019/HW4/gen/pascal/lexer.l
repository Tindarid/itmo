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
"and"      { return AND; }
"or"       { return OR;  }
"xor"      { return XOR; }
"not"      { return NOT; }
"[a-z]"    { cur_unio.t = new tree(cur_string); return VAR; }

%%

