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
    int m, n, xbarco, ybarco, a = 0;
    srand((unsigned int)time(NULL));

    save_file(save);
    mapa = leia_mapa(&m, &n);
    posiciona_barco(save, mapa, &xbarco, &ybarco, m, n);
    printf("Inicio do jogo \n");
    escreva_mapa_tela(mapa, m, n);

    /* O Jogo termina quando o barco:
       - fica na mesma possição por três jogadas consecutivas
       - O barco é atinngido
       - Se atinge o objetivo chegar na ultima linha da matriz
    */
    
    while (a < 2){
            dispara_tiros(save, mapa, m, n);
            a++;
    }
    LiberaMatriz(mapa, m);
    return 0;
}