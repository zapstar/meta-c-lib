all:
	gcc -Wall -Wextra -std=c89 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition main.c
clean:
	rm a.out
