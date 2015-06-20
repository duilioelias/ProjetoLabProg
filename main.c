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
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "funcoes.h"
#include "xwc.h"


int main(int argc, char *argv[]){
/*Funções criadas para o EP3 */
    WINDOW *screen;
    PIC Map, barco, rastro;
    int i, j=0;

    int a, c, x=0, y=0;
    int tecla = 1;
    MASK msk;

/* Funções originais do EP2*/
    char** mapa;
    char save[20];
    int m, n, xBarco, yBarco;
    srand((unsigned int)time(NULL));

    save_file(save);
    mapa = leia_mapa(&m, &n);
    escreva_mapa_tela(mapa, m, n);

/* Alterado EP3*/
    screen=InitGraph(30*n,30*m, "Bombardeio Naval");
    WShow(screen);

    Map=ReadPic(screen, "sea.xpm", NULL);
    barco = ReadPic(screen, "barco.xpm", NULL);
    rastro = ReadPic(screen, "rastro.xpm", NULL);
    msk = NewMask(barco, 30, 30);


    for (i=0; i<30*n; i+=30) {
        for (j=0; j<30*m; j+=30) {
            PutPic(screen, Map, 0,0, 30, 30, i, j);
        }
    }


/* Fim das alterações do EP3*/


    posiciona_barco(save, mapa, &xBarco, &yBarco, m, n);

    printf("Controle o barco na tela: ");
    PutPic(screen, barco, 0,0, 30, 30, x, x);
    InitKBD(screen);
    while (tecla != 39){
        tecla = (int) WGetKey(screen);
        printf(">>> %d\n", tecla);
        PutPic(screen, rastro, 0, 0, 30, 30, x, y);
        if (tecla == 54)
          y-=30;
        else if (tecla == 40)
          x+=30;
        else if (tecla == 26)
          x-=30;
        else if (tecla == 56)
          y+=30;
        PutPic(screen, barco, 0, 0, 30, 30, x, y);
    }


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
