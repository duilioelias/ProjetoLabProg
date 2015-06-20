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
CFLAGS=-Wall -g  -I -g -O2
all: funcoes

funcoes: funcoes.o main.o xwc.o
	${CC} ${CFLAGS} -o funcoes funcoes.o main.o xwc.o -lm -lXpm -lX11 
# O compilador faz a ligação entre os dois objetos
 
#-----> Distancia com o botão TAB ### e não com espaços
funcoes.o: funcoes.c
	${CC} ${CFLAGS} -o funcoes.o -c funcoes.c

main.o: main.c funcoes.h
	${CC} ${CFLAGS} -o main.o -c main.c

xwc.o : xwc.c

clean:
	rm -rf *.o

mrproper: clean
	rm -rf funcoes

