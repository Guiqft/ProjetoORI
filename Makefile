all: sgbd

CFLAGS = -W -g
VALGRINDFLAGS = -Werror -fshort-enums -std=gnu11 -Og -g3 -dg -gdwarf-2 -rdynamic

sgbd: makedir/shell.o makedir/main.o makedir/utils.o makedir/comandos.o makedir/btree.o makedir/queue.o
	gcc $(VALGRINDFLAGS) -o sgbd makedir/shell.o makedir/main.o makedir/utils.o makedir/btree.o makedir/queue.o makedir/comandos.o $(CFLAGS)
makedir/shell.o: src/shell.c makedir/comandos.o makedir/utils.o
	gcc -o makedir/shell.o -c src/shell.c $(CFLAGS)
makedir/main.o: src/main.c makedir/utils.o
	gcc -o makedir/main.o -c src/main.c $(CFLAGS)	
makedir/comandos.o: src/comandos.c makedir/utils.o makedir/btree.o
	gcc -o makedir/comandos.o -c src/comandos.c $(CFLAGS)
makedir/utils.o: src/utils.c
	gcc -o makedir/utils.o -c src/utils.c $(CFLAGS)
makedir/btree.o: src/external/btree.c
	gcc -o makedir/btree.o -c src/external/btree.c $(CFLAGS)
makedir/queue.o: src/external/queue.c
	gcc -o makedir/queue.o -c src/external/queue.c $(CFLAGS)
clean:
	rm -rf makedir/*.o
clean_data:
	rm -rf Data/*.txt
run:
	./sgbd