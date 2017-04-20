/*
Batch no. 82

AUTHORS : 
Pranjal Gupta (2013B4A7470P)
Tanaya Jha (2013B3A7304P)
*/

#include <stdio.h>
#include "lexerDef.h"
#include "parserDef.h"
#include "parser.h"
#include "ast.h"
#include "lexer.h"



int main(int argc, char ** argv) {

	printf("\n");

	printf("(a). Lexical Analysis module is fully developed with Error reporting \n");
	printf("(b). Buffer Pair technique is implemented in lexical analysis\n");
	printf("(c). Syntacitic Analysis module is fully developed with error reporting and recovery using panic mode \n");
	printf("(d). Loading of grammer is automated to read from file \n");
	printf("(e). First and Follow set computation has been automated.\n");
	printf("(f). Both the modules works with all the provided testcases.\n");
	printf("(g). Parse tree construction can be done and printed using option 4 in the given format \n");

	printf("\n");

	if(argc < 3) {
		printf("Too few arguments. \n");
	}
	else {

		grammar * gr = NULL;
		firstAndFollowSets * ff = NULL;
		parseList * tableHead = NULL;
		treeNode * head = NULL;
		symbolScope * sHead = NULL;

		int option, errors, countPT = 0, countAST = 0, ASTconstruct = 0, node_size;

		do {

			printf("\n----------------------------------------------------------------------------\n");
			printf("\nPress option for the defined task.\n");
			printf("1.\tPrint the token list generated by the lexer.\n");
			printf("2.\tParse the source code to verify the syntactical correctness.\n");
			printf("3.\tPrint the parse tree.\n");
			printf("4.\tPrint the Abstract Syntax Tree \n");
			printf("5.\tDisplay the sizes and compression percentage of the AST\n");
			printf("6.\tPrint the symbol table.\n");
			
			printf("7.\tParse the source code for type checking and semantic correctness.\n");
			printf("8.\tGenerate assembly code.\n");
			printf("9.\tExit\n");
			printf("\n\n");

			scanf("%d", &option);

			switch(option) {

				case 1 : // tokens print  
						
					setUpStream(argv[1]);

					printf("\nPrinting the tokens generated by lexical analyzer...\n");

					token * got;
					got = getToken();

					for(int i=0; got->id != 57 ;i++) {
						printf("%s\t%s\t%d\n", got->lxm, got->val, got->lno);
						got = getToken();
					}
					
					break;
				
				case 2 : // syntactical errors reporting and parse tree formation

					if(gr == NULL) {
						gr = readGrammarFromFile("grammar.txt");
					}
					if(ff == NULL) {
						ff = computeFirstAndFollowSets(gr);
					}
					if(tableHead == NULL) {
						tableHead = createParseTable(gr, ff);
					}
					if(head == NULL) {
						head = parseInputSourceCode(gr, argv[1], tableHead, &errors);
						if(!countPT) {
							countPT = 0;
							countNodes(head, &countPT);		
						}
					}
					else {
						printf("Parse tree is already created.\n");
					}
					break;

				case 3 : // parse tree print

					if(gr == NULL) {
						gr = readGrammarFromFile("grammar.txt");
					}
					if(ff == NULL) {
						ff = computeFirstAndFollowSets(gr);
					}
					if(tableHead == NULL) {
						tableHead = createParseTable(gr, ff);
					}
					if(head == NULL) {
						head = parseInputSourceCode(gr, argv[1], tableHead, &errors);
						if(!countPT) {
							countPT = 0;
							countNodes(head, &countPT);		
						}
					}
					if(!ASTconstruct)
						printParseTreeOrig(head);
					else {
						printf("cannot print\n");
					}

					break;

				case 4 : // construct AST and count AST nodes
					if(gr == NULL) {
						gr = readGrammarFromFile("grammar.txt");
					}
					if(ff == NULL) {
						ff = computeFirstAndFollowSets(gr);
					}
					if(tableHead == NULL) {
						tableHead = createParseTable(gr, ff);
					}
					if(head == NULL) {
						head = parseInputSourceCode(gr, argv[1], tableHead, &errors);
						if(!countPT) {
							countPT = 0;
							countNodes(head, &countPT);		
						}
					}
					if(!ASTconstruct) {
						constructAST(head);
						ASTconstruct = 1;
					}

					printf("The printing format of the AST is the same as that of the parse table. \n");
					printf("In-order traversal : first child -> parent ->rest of the childs \n");
					printf("-----------------------------------------------------------------------------------------------------------------------\n");
					printf("LEXEME\t\tLINE\t\tTERMINAL\tVALUE\t\tPARENT\t\t\tLEAF\t\tNON TERMINAL\n");
					printf("-----------------------------------------------------------------------------------------------------------------------\n");

					printAST(head);

					if(!countAST) {
						countAST = 0;
						countNodes(head, &countAST);		
					}

					break;


				case 5 : // compression calculations
					if(gr == NULL) {
						gr = readGrammarFromFile("grammar.txt");
					}
					if(ff == NULL) {
						ff = computeFirstAndFollowSets(gr);
					}
					if(tableHead == NULL) {
						tableHead = createParseTable(gr, ff);
					}
					if(head == NULL) {
						head = parseInputSourceCode(gr, argv[1], tableHead, &errors);
						if(!countPT) {
							countPT = 0;
							countNodes(head, &countPT);		
						}
					}
					if(!ASTconstruct) {
						constructAST(head);
						ASTconstruct = 1;
					}
					if(!countAST) {
						countAST = 0;
						countNodes(head, &countAST);		
					}

					node_size = sizeof(treeNode);

					printf("PARSE TREE : \t\t Number of nodes = %d, \tAllocated memory = %d bytes\n", countPT, countPT*node_size);
					printf("ABSTRACT SYNTAX TREE : \t Number of nodes = %d, \tAllocated memory = %d bytes\n", countAST, countAST*node_size);
					printf("\nCompression percentage : %f \n" , ((double)countPT-(double)countAST)*100/(double)countPT );
					break;

				case 6 : // scope
					if(gr == NULL) {
						gr = readGrammarFromFile("grammar.txt");
					}
					if(ff == NULL) {
						ff = computeFirstAndFollowSets(gr);
					}
					if(tableHead == NULL) {
						tableHead = createParseTable(gr, ff);
					}
					if(head == NULL) {
						head = parseInputSourceCode(gr, argv[1], tableHead, &errors);
						if(!countPT) {
							countPT = 0;
							countNodes(head, &countPT);		
						}
					}
					if(!ASTconstruct) {
						constructAST(head);
						ASTconstruct = 1;
					}
					
					if(errors) {
						printf("There are errors in the parse table. Cannot construct Symbol table.\n");
					}
					else {
						if(sHead == NULL) {
							sHead = initScopeStructure(head, &errors);
						}

						printf("IDENTIFIER \t\t USAGE \t\t TYPE \t\t LINE NO. \t\t SCOPE LEVEL \t\t WIDTH \t\t OFFSET\n");
						printf("----------------------------------------------------------------------------------------------------------------\n\n");

						printScopeStructure(sHead);
					}

					break;


				// case 5 : 
				// 	printf("\n\nExiting...\n");
				// 	break;
				// default : 
				// 	break;
				
			}

		} while(option != 9);


	}

	return 0;

}


