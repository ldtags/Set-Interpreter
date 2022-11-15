%{
#include "semantics.h"
#include "IOMngr.h"
#include "SymTab.h"
#include <string.h>

extern int yylex(); /* The next token function. */
extern char *yytext; /* The matched token text. */
extern int yyerror(char *s);
%}

%union {
    char * string;
    SymTab * table;
}

%type <string> Id
%type <table> Expr
%type <table> Term
%type <table> Factor

%token SetLit
%token Ident

%%

Prog      : StmtSeq            {printSymTab();};
StmtSeq   : Stmt StmtSeq       { };
StmtSeq   :                    { };
Stmt      : Id '=' Expr ';'    {storeVar($1, $3);};
Expr      : Expr '+' Term      {$$ = doUNION($1, $3);};
Expr      : Term               {$$ = $1;};
Term      : Term '*' Factor    {$$ = doINTERSECTION($1, $3);};
Term      : Factor             {$$ = $1;};
Factor    : '(' Expr ')'       {$$ = $2;};
Factor    : Id                 {$$ = getVal($1);};
Factor    : SetLit             {$$ = makeSet($1);};
Id        : Ident              {$$ = strdup(yytext);};

%%

int yyerror(char *s) {
    writeIndicator(getCurrentColumnNum());
    writeMessage("Illegal Character in YACC");
    return 1;
}