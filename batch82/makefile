TARGET = stage1exe

all:
	gcc -g -c lexer.c  parser.c ast.c -w
	gcc -g driver.c lexer.o parser.o ast.o -o stage1exe -w

clean:
	rm -rf *.o
	rm -rf $(TARGET)