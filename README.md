# Set-Interpreter

A command-line driven program that interprets sets of the specified grammar.

To interpret a file:
  - Go to the main directory in your preferred terminal
  - You can run the program through the provided executable; or you can compile one on your own, I'm not your boss
  - Provide the program with a path to the file you wish to have interpreted as an argument
  - You may also specify a path to a listing file for compile-time errors, otherwise they are directed to STDOUT
  
This program returns the evaluated result of the input file.

Grammar Productions:

  Prog    ::= StmtSeq
  
  StmtSeq ::= Stmt StmtSeq
  
  StmtSeq ::= 
  
  Stmt    ::= Id '=' Expr ';'
  
  Expr    ::= Expr '+' Term
  
  Expr    ::= Term
  
  Term    ::= Term '*' Factor
  
  Term    ::= Factor
  
  Factor  ::= '(' Expr ')'
  
  Factor  ::= Id
  
  Factor  ::= *SetLit*
  
  Id      ::= *Ident*
  
