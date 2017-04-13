
int checkSemantics(treeNode * head) {

	treeNode * child;
	child = head->childL;

	// semantics move in here 

	
	
	while(child != NULL) {

		checkSemantics(child);
		child = child->next;

	} 

}