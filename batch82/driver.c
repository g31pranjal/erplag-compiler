/*
Batch no. 82

AUTHORS : 
Pranjal Gupta (2013B4A7470P)
Tanaya Jha (2013B3A7304P)
*/

#include <stdio.h>
#include "lexerDef.h"
#include "parserDef.h"

#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "scope.h"
#include "semantics.h"
#include "codegen.h"


int main(int argc, char ** argv) {

	printf("\n");

	printf("LEVEL 4 : AST / Symbol table / Type checking / Semantic analysis / ASM code generation works. \n\n");
	
	printf("ASSUMPTIONS : \n");
	printf("(a). In code generation, only integer-type variables are used and there is only the main function. \n");
	printf("(b). Type checking has been included in the semantics module itself. \n");
	printf("(c). The same data structure is used for both Parse Tree and AST. AST is generated by structural changes to the Parse tree in one traversal through the structure. \n");

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

		int option, countPT = 0, countAST = 0, ASTconstruct = 0, node_size;
		int synErrors = 0, scpErrors = 0, semErrors = 0, semChecks = 0;

		
		printf("\n----------------------------------------------------------------------------\n");
		printf("\nPress option for the defined task.\n"); 
		printf("%sDriver performs all the operations only once, if there are changes in the source code, rerun. %s\n\n", BOLDRED, RESET);
		printf("\n1.\tPrint the token list generated by the lexer.\n");
		printf("\n2.\tParse the source code to verify the syntactical correctness and print the parse tree. (Displays syntactic errors, if any)\n");
		printf("\n3.\tPrint the Abstract Syntax Tree \n");
		printf("\n4.\tDisplay the sizes and compression percentage of the AST\n");
		printf("\n5.\tPrint the symbol table.  (Displays scope resolution errors, if any)\n");
		printf("\n6.\tParse the source code for type checking and semantic correctness. (Displays semantic errors, if any)\n\t(To displays all the syntactic and semantic errors, call directly)\n");
		printf("\n7.\tGenerate assembly code.\n");
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
					head = parseInputSourceCode(gr, argv[1], tableHead, &synErrors);
					if(!countPT) {
						countPT = 0;
						countNodes(head, &countPT);		
					}
				}
				else {
					printf("Parse tree is already created.\n");
				}

				if(!ASTconstruct)
					printParseTreeOrig(head);
				else {
					printf("Cannot print parse tree after AST construction since the same structure is altered.\n");
				}

				break;

			case 3 : // construct AST and count AST nodes
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
					head = parseInputSourceCode(gr, argv[1], tableHead, &synErrors);
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


			case 4 : // compression calculations
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
					head = parseInputSourceCode(gr, argv[1], tableHead, &synErrors);
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

			case 5 : // scope
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
					head = parseInputSourceCode(gr, argv[1], tableHead, &synErrors);
					if(!countPT) {
						countPT = 0;
						countNodes(head, &countPT);		
					}
				}
				if(!ASTconstruct) {
					constructAST(head);
					ASTconstruct = 1;
				}
				
				if(synErrors) {
					printf("There are errors in the parse table. Cannot construct Symbol table.\n");
				}
				else {
					if(sHead == NULL) {
						sHead = initScopeStructure(head, &scpErrors);
						if(!scpErrors)
							printf("%s\nThe code has no scope resolution errors.%s\n\n", BOLDGREEN, RESET);
					}

					printf("\n\n");
					printf("IDENTIFIER \t\t USAGE \t\t TYPE \t\t LINE NO. \t\t SCOPE \t\t SCOPE LEVEL \t\t WIDTH \t\t OFFSET\n");
					printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

					printScopeStructure(sHead);
				}

				break;

			case 6 : // semantic correctness
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
					head = parseInputSourceCode(gr, argv[1], tableHead, &synErrors);
					if(!countPT) {
						countPT = 0;
						countNodes(head, &countPT);		
					}
				}
				if(!ASTconstruct) {
					constructAST(head);
					ASTconstruct = 1;
				}

				if(sHead == NULL) {
					if(synErrors) {
						printf("There are errors in the parse table. Cannot construct Symbol table.\n");
					}
					else 
						sHead = initScopeStructure(head, &scpErrors);	
				}
				else
					printf("\nScoping errors are listed only once at the time of creation of the scope structure.\n\n");

				if(synErrors) {
					printf("There are errors in the parse table. Cannot construct check semantics.\n" );
				}
				else {
					checkSemantics(head, sHead, &semErrors);
					semChecks = 1;
					if(!semErrors)
						printf("%s\nThe code has no semantic errors.%s\n\n", BOLDGREEN, RESET);
				}

				break;

			case 7 : // code generation
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
					head = parseInputSourceCode(gr, argv[1], tableHead, &synErrors);
					if(!countPT) {
						countPT = 0;
						countNodes(head, &countPT);		
					}
				}
				if(!ASTconstruct) {
					constructAST(head);
					ASTconstruct = 1;
				}

				if(sHead == NULL) {
					if(synErrors) {
						printf("There are errors in the parse table. Cannot construct Symbol table.\n");
					}
					else 
						sHead = initScopeStructure(head, &scpErrors);	
				}

				if(!semChecks) {
					if(synErrors) {
						printf("There are errors in the parse table. Cannot construct check semantics.\n" );
					}
					else {
						checkSemantics(head, sHead, &semErrors);
						if(!semErrors)
							printf("%s\nThe code has no semantic errors.%s\n\n", BOLDGREEN, RESET);
					}
				}

				if(synErrors || scpErrors || semErrors) {
					printf("There are errors in the source code. Cannot generate ASM\n" );
				}
				else {
					FILE * fp = fopen(argv[2], "w+");
					codeGenInit(head, sHead, fp);
					fclose(fp);
				}

				break;

			default : 
				break;
			
		}



	}
	printf("\n\n");

	return 0;

}


