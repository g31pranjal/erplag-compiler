# erplag-compiler
##### Term project for the course Compiler Construction  

### # modules of the project include :
- **Lexer (lexer.c)** : the module reads the source code in HLL as a stream of charaters and converts sequence of characters to meaningful tokens. 
	the tokens are passed to the parser and contains information about the line of occurance, name of the token, token id etc.
- **Parser (parser.c)** : parser takes in the sequence of tokens and verifies the syntactical correctness of the source code by constructing the parse tree. the Parser also has error recovery mechanism to parse the complete sequence of tokens even if a syntactical error exist.
- **AST Construction (ast.c)** : this module takes in the parse tree and 1). Delete all the irrelevant tokens, 2). Changes the structure of <expressions> to infix notation (for proper checking and evaluation), 3). removes chaining in tree and 4). removes empty non-terminals. 
- **Symbol Table and Scoping (scope.c)** : 	this module constructs the symbol-table for the corresponding AST. The symbol table has a tree structure that depicts the scoping of the blocks of code. Each node of the tree has a linked list of its locally defined variables. It also reports the errors related to redundant declaration, no declaration of variables and modules. 
- **Type Checker and Semantic Analyser (semantics.c)** : this module performs semantic checks on the AST for verifiying semantic correctness of the source code. It also determines the correctness of the expression. The following checks are performed :
	
	1. 	`WHILE` should have a valid `BOOLEAN` expression
	2. 	The identifier of the `FOR` should be an `INTEGER`
	3.  The identifier of type `ARRAY` should have an index
	4. 	If the index of the `ARRAY` identifier is a `NUM`, then it should be within limits.
	5.	Index of the array should always by `INTEGER`
	6.  Recursive module calling is not allowed. 
	7.  Function overloading is not allowed.
	8.  The identifier of the `SWITCH` construct should be `INTEGER` or `BOOLEAN`.
	9.  If the `SWITCH` has `INTEGER` identifier, all case statements must have `NUM` and should be followed by `DEFAULT` statement.
	10. If the `SWITCH` has `BOOLEAN` identifier, all case statements must have `TRUE` and `FALSE` and should not be followed by `DEFAULT`s tatement.
	11. The parameter list of the moduleReuseStmt should match the formal parameters of the called module.
	12. The idlist of the moduleReuseStmt should match the output_list of the called module.
	13. A module most be declared (or defined) before its used in other module.
	14. The called module should be definately defined and not only declared.
	15. `AND/OR` can only have `BOOLEAN` arguments, returns `BOOLEAN`.
	16. `PLUS/MINUS/MUL/DIV` can only have both `NUM` or `RNUM` arguments, returns `NUM` or `RNUM` respectively.
	17. type of LHS of the assignment statement should match the type of the RHS expression.
	18. `LT/LE/GT/GE/NE/EQ` can only have both `NUM` or `RNUM` arguments, returns BOOLEAN.
	
* **Code Generation (codegen.c)** : Generates the NASM-assembly code of the source code.

### # Compatibility

- gcc (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609
- NASM version 2.12.01
 

### # Usage

- use `make` to compile the client and server code for the game.
- the driver.c is compiled to the executable binary called `comiler`.
- run the executable as :
		
	- `./compiler <path-to-source> <asm-file>`
- Select the desired option from the driver menu to evaluate the source code uptill a specific module. 
- For producing the binary from .asm file : 

	- `nasm <asm-file> -f elf64 -o <o-file>`
	- `gcc <o-file> -o <executable>`
	- `./<executable>`

