OBJ_ALL = snake_run.o upd_scrn.o set_tty.o snake_food.o init_scrn.o move_to.o main.o out_scrn.o next_level.o

SRC_ALL = snake_run.c upd_scrn.c snake_food.c init_scrn.c move_to.c out_scrn.c next_level.c


snake: $(OBJ_ALL)
	gcc -o snake $(OBJ_ALL) -std=gnu99 -O2


main.o:main.c
	gcc -c main.c -std=gnu99

$(OBJ_ALL): snake_def.h snake.h

snake_run.o: $(SRC_ALL)
	gcc -c snake_run.c -std=gnu99 -O2

snake_food.o: snake_food.c
	gcc -c snake_food.c -std=gnu99 -O2

init_scrn.o: init_scrn.c
	gcc -c init_scrn.c -std=gnu99

upd_scrn.o: upd_scrn.c
	gcc -c upd_scrn.c -std=gnu99 -O2

move_to.o: move_to.c
	gcc -c move_to.c -std=gnu99 -O2

out_scrn.o: out_scrn.c
	gcc -c out_scrn.c -std=gnu99 -O2

next_level.o: next_level.c
	gcc -c next_level.c -std=gnu99

set_tty.o: set_tty.c
	gcc -c set_tty.c -std=gnu99

clean:
	rm $(OBJ_ALL) snake
