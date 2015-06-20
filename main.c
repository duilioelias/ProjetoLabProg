/*******************************************************************************
*	Membros do Grupo:
*	 Nome: Duilio Henrique Haroldo Elias                                        *
*	 Numero USP: 6799722                                                        *
*	 
*	 Nome: Maurício Ozaki                                                       *
*	 Numero USP:                                                                *
*	 
*	 Nome:Ricardo Oliveira                                                      *
*	 Numero USP:                                                                *
*	 
*	Professor: Alair             					                           *
*	Matéria: Laboratório de Programação I                                      *
*
*											    			                   *
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"


int main(){
    WINDOW *screen;
    int ii;

    char** mapa;
    char save[20];
    int m, n, xBarco, yBarco;
    srand((unsigned int)time(NULL));

    screen=InitGraph(600,600, "Bombardeio Naval");
    for (ii = 0; ii < 400; ii++)
        WPlot(screen,ii,200, 8);
    WLine(screen,1,1,300,300,2);
    NewPic(screen, 400, 400);
    WPrint(screen, 10, 10, "Testando");

    save_file(save);
    mapa = leia_mapa(&m, &n);
    escreva_mapa_tela(mapa, m, n);
    posiciona_barco(save, mapa, &xBarco, &yBarco, m, n);

    /*define o fim do jogo*/
    while (1){
            if (!dispara_tiros(save, mapa, m, n)){
                printf("Fim do jogo\n");
                break;
            }
            if (!rema_barco (save, mapa, &xBarco, &yBarco, m, n)){
                printf("Fim do jogo\n");
                break;
            }
    }
    /*libera matriz alocada*/
    LiberaMatriz(mapa, m);
return 0;
}
