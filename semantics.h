#include "SymTab.h"


extern void printSymTab();
extern void storeVar(char * name, SymTab * set);
extern SymTab * getVal(char * name);
extern SymTab * makeSet(char * setLit);
extern SymTab * doUNION(SymTab * set1, SymTab * set2);
extern SymTab * doINTERSECTION(SymTab * set1, SymTab * set2);