#Para escrever comentários ##
############################# Makefile ##########################
all: teste

teste: teste.o main.o 
	gcc -o teste teste.o main.o
# O compilador faz a ligação entre os dois objetos
 
#-----> Distancia com o botão TAB ### e não com espaços
teste.o: teste.c
	gcc -o teste.o -c teste.c -W -Wall -ansi -pedantic

main.o: main.c teste.h
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o

mrproper: clean
	rm -rf teste
