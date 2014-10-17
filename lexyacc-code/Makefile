all: calc1 calc2 calc3a calc3b calc3g calc3i

calc1:
	bison -y -d calc1.y
	flex calc1.l
	gcc -c y.tab.c lex.yy.c
	gcc y.tab.o lex.yy.o -o calc1

calc2:
	bison -y -d calc2.y
	flex calc2.l
	gcc -c y.tab.c lex.yy.c
	gcc y.tab.o lex.yy.o -o calc2

calc3.y.c: calc3.y
	bison -y --defines=calc3.y.h -o calc3.y.c calc3.y
	
calc3.l.c: calc3.l
	flex -o calc3.l.c calc3.l
	
calc3a: calc3.y.o calc3.l.o calc3a.c
	gcc calc3.y.o calc3.l.o calc3a.c -lm -o calc3a
	
calc3b: calc3.y.o calc3.l.o calc3b.c
	gcc calc3.y.o calc3.l.o calc3b.c -o calc3b
	
calc3g: calc3.y.o calc3.l.o calc3g.c
	gcc calc3.y.o calc3.l.o calc3g.c -o calc3g
	
calc3i: calc3.y.o calc3.l.o calc3i.c
	gcc calc3.y.o calc3.l.o calc3i.c -o calc3i
	
.c.o:
	gcc -c $< -o $@
	