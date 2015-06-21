#/*******************************************************************************
#*	Membros do Grupo:
#*	 Nome: Duilio Henrique Haroldo Elias                                        *
#*	 Numero USP: 6799722                                                        *
#*
#*	 Nome: Maurício Ozaki                                                       *
#*	 Numero USP:                                                                *
#*
#*	 Nome:Ricardo Oliveira                                                      *
#*	 Numero USP:                                                                *
#*
#*	Professor: Alair             					                           *
#*	Matéria: Laboratório de Programação I                                      *
#*
#*											    			                   *
#*******************************************************************************/


############################# Makefile ##########################
CFLAGS=-Wall -g  -I -g -O2
all: batalhaNaval

batalhaNaval: funcoes.o main.o xwc.o
	${CC} ${CFLAGS} -o batalhaNaval funcoes.o main.o xwc.o -lm -lXpm -lX11

funcoes.o: funcoes.c
	${CC} ${CFLAGS} -o funcoes.o -c funcoes.c

main.o: main.c funcoes.h xwc.h
	${CC} ${CFLAGS} -o main.o -c main.c

xwc.o : xwc.c

clean:
	rm -rf *.o

mrproper: clean
	rm -rf funcoes
