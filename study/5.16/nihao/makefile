all:lajilaji laji

lajilaji:laji.c laji2.c
	gcc $^ -o $@
laji:laji.o laji2.o
	gcc $^ -o $@
laji2.o:laji2.c
	gcc -c $< -o $@
laji.o:laji.c
	gcc -c $< -o $@
.PHONY:clean
clean:
	rm laji lajilaji *.o
