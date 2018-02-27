all:	shell.o linkedlist.o

shell.o:	shell.c
	gcc shell.c -o shell

linkedlist.o:	linkedlist.c
	gcc linkedlist.c -o link

clean:
	rm -rf shell link
