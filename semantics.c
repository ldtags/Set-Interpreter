#include <stdio.h>
#include <stdlib.h>
#include "semantics.h"
#include "IOMngr.h"


extern SymTab *table;


void printSymTab() {
    int hasMore, hashasMoreMore = 0;
    SymTab * var = (SymTab*) malloc(sizeof(SymTab*));

    printf("%20s\t%10s\n", "Variable", "Value");

    hasMore = startIterator(table);
    while(hasMore) {
        // print each variable and it's associated value
        printf("%20s\t{", getCurrentName(table));
        var = getCurrentAttr(table);
        hashasMoreMore = startIterator(var);
        while(hashasMoreMore) {
            // prints the value (i.e. SymTab) associated with the current variable
            printf("%s", var->current->name);
            hashasMoreMore = nextEntry(var);
            if(hashasMoreMore)
                printf(", ");
        }
        printf("}\n");

        hasMore = nextEntry(table);
    }

    free(var);
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

    // add values from set1 to union_set
    hasMore = startIterator(set1);
    while(hasMore) {
        enterName(union_set, set1->current->name);
        hasMore = nextEntry(set1);
    }

    // add values from set2 to union_set
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

    // adds values that are in both set1 and set2 to inter_set
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
    char *c = (char*) malloc(sizeof(char)*2);
    SymTab * set = createSymTab(17);
    
    while((c[0] = setLit[i++]) != '\0') {   // iterating through string setLit
        if(c[0] >= 97 && c[0] <= 122) {     // if the current char is a lower-case letter
            c[1] = '\0';                    //   append the end-of-string char
            enterName(set, c);              //   enter name into set
        }
    }

    free(c);
    return set;
}