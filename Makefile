#/******************************************************************************
#*	Membros do Grupo:
#*	 Nome: Duilio Henrique Haroldo Elias                                       *
#*	 Numero USP: 6799722                                                       *
#*	 
#*	 Nome: Maurício Ozaki                                                      *
#*	 Numero USP: 7577427                                                       *
#*	 
#*	 Nome:Ricardo de Oliveira                                                  *
#*	 Numero USP:3683165                                                        *
#*	 
#*	Professor: Alair             					                           *
#*	Matéria: Laboratório de Programação I                                      *
#*
#*											    			                   *
#******************************************************************************/


############################# Makefile ##########################
all: funcoes

funcoes: funcoes.o main.o 
	gcc -o funcoes funcoes.o main.o
# O compilador faz a ligação entre os dois objetos
 
#-----> Distancia com o botão TAB ### e não com espaços
funcoes.o: funcoes.c
	gcc -o funcoes.o -c funcoes.c -W -Wall -ansi -pedantic

main.o: main.c funcoes.h
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o

mrproper: clean
	rm -rf funcoes
