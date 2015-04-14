all: obj/plague.o obj/override.o
	mkdir -p bin
	ld obj/plague.o obj/override.o --wrap fork -o bin/ro-tmp
	objcopy --writable-text bin/ro-tmp bin/plague
obj/plague.o: src/plague.c
	mkdir -p obj
	gcc -c src/plague.c -o obj/plague.o
obj/override.o: src/override.c include/dumby.h include/constants.h
	mkdir -p obj
	gcc -c -Iinclude/ src/override.c -o obj/override.o
clean:
	-rm -r obj/ bin/ 
