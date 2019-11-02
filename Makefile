all: sgbd

CFLAGS = -W
LFLAGS = -Isrc/external/

sgbd: makedir/shell.o makedir/main.o makedir/utils.o makedir/comandos.o
	gcc -o sgbd makedir/shell.o makedir/main.o makedir/utils.o makedir/comandos.o -g $(CFLAGS) -no-pie -Lsrc/external -lcranbtree
makedir/shell.o: src/shell.c makedir/comandos.o makedir/utils.o
	gcc -o makedir/shell.o -c src/shell.c $(CFLAGS)
makedir/main.o: src/main.c makedir/utils.o
	gcc -o makedir/main.o -c src/main.c $(CFLAGS)	
makedir/comandos.o: src/comandos.c makedir/utils.o
	gcc -o makedir/comandos.o -c src/comandos.c $(CFLAGS) $(LFLAGS)
makedir/utils.o: src/utils.c
	gcc -o makedir/utils.o -c src/utils.c $(CFLAGS) $(LFLAGS)
clean:
	rm -rf makedir/*.o
clean_data:
	rm -rf Data/*.txt
run:
	./sgbd