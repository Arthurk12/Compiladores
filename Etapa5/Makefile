#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for three compiler calls
# Read the comments on Makefile2. All of them apply here too.
# But now the hash table is compiled in a separate gcc call
# Therefore, there must be a header of it to be included in scanner.l
#

etapa5: y.tab.o lex.yy.o hash.o ast.o functions.o semantic.o tac.o main.o 
	gcc -o etapa5 lex.yy.o y.tab.o hash.o ast.o functions.o semantic.o tac.o main.o -Wall
main.o: main.c
	gcc -c main.c -Wall
semantic.o: semantic.c
	gcc -c semantic.c -Wall
functions.o: functions.c
	gcc -c functions.c -Wall
ast.o: ast.c
	gcc -c ast.c -Wall
hash.o: hash.c
	gcc -c hash.c -Wall
tac.o: tac.c
	gcc -c tac.c -Wall
y.tab.o: y.tab.c
	gcc -c y.tab.c -Wall
y.tab.c: parser.y
	bison -y -d -v parser.y
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l 
clean:
	rm *.o lex.yy.c lex.yy.h y.tab.c y.tab.h parser.tab.c parser.tab.h y.output etapa5 Code*.txt
