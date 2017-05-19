

### scope checks 

1.  The identifier moust be declared before it can be used.
2.  Identifier cannot be declared multiple times in the scope.

### semantics : 

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

### type checks for expressions : 

1.  `AND/OR` can only have `BOOLEAN` arguments, returns `BOOLEAN`.
2.  `PLUS/MINUS/MUL/DIV` can only have both `NUM` or `RNUM` arguments, returns `NUM` or `RNUM` respectively.
3.  `LT/LE/GT/GE/NE/EQ` can only have both `NUM` or `RNUM` arguments, returns BOOLEAN.
4.  type of LHS of the assignment statement should match the type of the RHS expression.
