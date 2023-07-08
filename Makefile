shell: shell.c ls.c cat.c date.c mkdir.c rm.c 
	gcc -o shell shell.c
	gcc -o ls ls.c
	gcc -o cat cat.c
	gcc -o date date.c
	gcc -o mkdir mkdir.c
	gcc -o rm rm.c
	


clean:
	rm -f shell ls cat date rm mkdir

run:
	./shell