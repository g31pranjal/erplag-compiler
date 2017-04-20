

extern symbolScope * initScopeStructure(treeNode * head, int * errors);

extern int printScopeStructure(symbolScope * head);

extern symbolScope * resolveCurrentModule(symbolScope * currScope);
