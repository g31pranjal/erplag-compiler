TARGET = compiler

all:
	gcc -g -c lexer.c parser.c ast.c scope.c semantics.c codegen.c -w
	gcc -g driver.c lexer.o parser.o ast.o scope.o semantics.o codegen.o -o compiler -w

clean:
	rm -rf *.o
	rm -rf *.asm
	rm -rf $(TARGET)