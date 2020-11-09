CC = gcc
FILES = *.c
FLAGS = -Wall -Werror -Wconversion -std=c99

clear:
	clear

lista: $(FILES)
	$(CC) $(FILES) $(FLAGS) -o lista

run: lista
	./lista

minipruebas: lista
		valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista minipruebas

zip:
	zip A2_TDA1.zip *.c *.h *.pdf *.md Makefile

check: lista
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista
