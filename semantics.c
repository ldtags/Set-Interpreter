#include <stdio.h>
#include <stdlib.h>
#include "SymTab.h"
#include "semantics.h"


extern struct SymTab *table;


void printSymTab() {
    startIterator(table);
    printf("%20s\t%10s\n", "Variable", "Value");
    SymTab * current = (SymTab*) malloc(sizeof(SymTab*));
    do {
        printf("%20s\t{", getCurrentName(table));
        current = getCurrentAttr(table);
        startIterator(current);
        do {
            printf("%s, ", current->current->name);
        } while(nextEntry(current) != 0);
        printf("}\n");
        destroySymTab(current);
    } while(nextEntry(table) != 0);
}

void storeVar(char * name, SymTab * set) {
    enterName(table, name);
    setCurrentAttr(table, set);
}

SymTab * getVal(char * name) {
    if(enterName(table, name)) {
        WriteIndicator(getCurrentColumnNum());
        WriteMessage("Initialize variable to empty set");
        setCurrentAttr(table, createSymTab(17));
    }
    return getCurrentAttr(table);
}

SymTab * doUNION(SymTab * set1, SymTab * set2) {
    if(startIterator(set2) == 0) { 
        destroySymTab(set2);
        return set1; 
    }

    do {
        enterName(set1, set2->current->name);
    } while(nextEntry(set2) != 0);

    destroySymTab(set2);
    return set1;
}

SymTab * doINTERSECTION(SymTab * set1, SymTab * set2) {
    if(startIterator(set2) == 0) { 
        destroySymTab(set2);
        return set1; 
    }

    SymTab * intersect = createSymTab(17);
    do {
        if(findName(set1, set2->current->name)) {
            enterName(intersect, set2->current->name);
        }
    } while(nextEntry(set2) != 0);

    destroySymTab(set1);
    destroySymTab(set2);
    return intersect;
}

SymTab * makeSet(char * setLit) {
    
}