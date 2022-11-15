#include <stdio.h>
#include <stdlib.h>
#include "SymTab.h"
#include "semantics.h"


extern struct SymTab *table;


void printSymTab() {
    int hasMore = startIterator(table);
    int hashasMoreMore = 0;
    printf("%20s\t%10s\n", "Variable", "Value");
    SymTab * current = (SymTab*) malloc(sizeof(SymTab*));

    while(hasMore) {
        printf("%20s\t{", getCurrentName(table));
        current = getCurrentAttr(table);
        hashasMoreMore = startIterator(current);
        while(hashasMoreMore) {
            printf("%s", current->current->name);
            hashasMoreMore = nextEntry(current);
            if(hashasMoreMore)
                printf(", ");
        }
        printf("}\n");

        destroySymTab(current);
        hasMore = nextEntry(table);
    }

    free(current);
}

void storeVar(char * name, SymTab * set) {
    enterName(table, name);
    setCurrentAttr(table, set);
}

SymTab * getVal(char * name) {
    if(enterName(table, name)) {
        writeIndicator(getCurrentColumnNum());
        writeMessage("Initialize variable to empty set");
        setCurrentAttr(table, createSymTab(17));
    }
    return getCurrentAttr(table);
}

SymTab * doUNION(SymTab * set1, SymTab * set2) {
    int hasMore = 0;
    SymTab * union_set = createSymTab(17);

    hasMore = startIterator(set1);
    while(hasMore) {
        enterName(union_set, set1->current->name);
        hasMore = nextEntry(set1);
    }

    hasMore = startIterator(set2);
    while(hasMore) {
        enterName(union_set, set2->current->name);
        hasMore = nextEntry(set2);
    }

    return union_set;
}

SymTab * doINTERSECTION(SymTab * set1, SymTab * set2) {
    int hasMore = startIterator(set2);
    SymTab * inter_set = createSymTab(17);

    while(hasMore) {
        if(findName(set1, set2->current->name)) {
            enterName(inter_set, set2->current->name);
        }
        hasMore = nextEntry(set2);
    }

    return inter_set;
}

SymTab * makeSet(char * setLit) {
    int i = 0;
    char c = setLit[i];
    SymTab * set = createSymTab(17);
    
    while(c != '\0') {
        if(c >= 97 && c <= 122) {
            enterName(set, c);
        }
        c = setLit[i++];
    }

    return set;
}