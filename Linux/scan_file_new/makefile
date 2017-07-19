bwrd: main.o set_tty.o scan.o
	gcc -o bwrd main.o set_tty.o scan.o -std=gnu99 -g

main.o: main.c
	gcc -c main.c -std=gnu99 -g

set_tty.o:set_tty.c read_def.h
	gcc -c set_tty.c -std=gnu99 -g

scan.o: scan.c read_def.h
	gcc -c scan.c -std=gnu99 -g

clean:
	rm bwrd main.o set_tty.o scan.o
