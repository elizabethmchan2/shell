all:	shell.o newshell.o

shell.o:	shell.c
	gcc shell.c -o shell

newshell.o:	newshell.c
	gcc newshell.c -o s -lreadline

clean:
	rm -rf shell s
