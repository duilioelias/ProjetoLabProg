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
  char** mapa;
    char save[20];
    int m, n, xBarco, yBarco;
    srand((unsigned int)time(NULL));

    save_file(save);
    mapa = leia_mapa(&m, &n);
    escreva_mapa_tela(mapa, m, n);
    posiciona_barco(save, mapa, &xBarco, &yBarco, m, n);


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
    LiberaMatriz(mapa, m);
return 0;
}