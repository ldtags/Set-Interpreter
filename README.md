# Set-Interpreter

A command-line driven program that interprets sets of the specified grammar.

To interpret a file:
  - Go to the main directory in your preferred terminal
  - You can run the program through the provided executable; or you can compile one on your own, I'm not your boss
  - Provide the program with a path to the file you wish to have interpreted as an argument
  - You may also specify a path to a listing file for compile-time errors, otherwise they are directed to STDOUT
  
This program returns the evaluated result of the input file.

Syntax:
  - (set1 '+' set2) => set1 'union' set2
  - (set1 '\*' set2) => set1 'intersect' set2
  - x = (set)
