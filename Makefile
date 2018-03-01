all:	hw3.o
	# shell.o	linkedlisttest.o test.o
	
# shell.o:	shell.c
# 	gcc shell.c -o shell
#
# linkedlisttest.o:	linkedlisttest.c
# 	gcc linkedlisttest.c -o link
#
hw3.o:	hw3.c
	gcc hw3.c -o 3
#
# test.o:	test.c
# 	gcc test.c -o t

clean:
	rm -rf 3
