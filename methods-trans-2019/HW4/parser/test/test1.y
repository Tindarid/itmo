%{
}%

%union {

}

%token LBR RBR
%start A

%%
A: LBR A RBR A {} | {}
B: B B {} | LBR B RBR {} | {}
%%
