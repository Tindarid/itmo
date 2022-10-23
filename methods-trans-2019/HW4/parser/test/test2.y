%{
}%

%union {

}

%token LBR RBR NUM MUL PLUS
%start E

%%
E: T EE {}
EE: PLUS T EE {} | {}
T: F TT {}
TT: MUL F TT {} | {}
F: NUM {} | LBR E RBR {}
%%
