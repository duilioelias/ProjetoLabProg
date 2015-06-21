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

void posiciona_barco (WINDOW *screen, PIC barco, char filename[], char** M, int* xBarco, int* yBarco, int m, int n, int * x, int *y){
    
    int digito=0;

    while (1){
        printf("\nEscolha uma posicao incial (1 a %d) para o barco: ", n);
        scanf("%d", &digito);
        while (!(digito>0 && digito<=n)){
            printf("\nEste nao eh um valor valido para posicao. Digite novamente: ");
            scanf("%d", &digito);
        }
        if (M[0][digito - 1] != '.')
            printf("Esta posicao esta ocupada. Escolha outra posicao\n\n");
        else {
            
			M[0][digito - 1] = 'B';
            *xBarco = 1;
            *yBarco = digito;
			*x = (digito-1)*30;
			PutPic(screen, barco, 0,0, 30, 30, *x, 0);
            break;
        }
    }
    atualiza_mapa(filename, M, m, n);
}

/*Dispara tiros*/
int dispara_tiros(char filename[],char** M, int m, int n){
    int x, y, cont, time;
    char alvo;

    for (cont = 0; cont < 3; cont++){
        coordenadas_tiro(&x, &y, m, n);
        alvo = identifica_alvo_atingido (M, x, y);
        atualiza_mapa(filename, M, m, n);
        afunda_embarcacao (filename, M, m, n, x, y, alvo);
        atualiza_mapa(filename, M, m, n);
        if (alvo == 'B'){
            printf("O barco afundou\n\n");
            return 0;
        }
        for (time = 0; time < 200000000; time++){} /*intervalo de tempo entre os tiros*/
    }
    return 1;
}


int main(int argc, char *argv[]){
/*Funções criadas para o EP3 */
    
	WINDOW *screen;
    
	PIC sea, barco, rastro;
    int i, j=0;

    int x=0, y=0;
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
    

    sea = ReadPic(screen, "sea.xpm", NULL);
    barco = ReadPic(screen, "barco.xpm", NULL);
    rastro = ReadPic(screen, "rastro.xpm", NULL);
	
    msk = NewMask(barco, 30, 30);

	/*Criar o mar*/
    for (i=0; i<30*n; i+=30) {
        for (j=0; j<30*m; j+=30) {
            PutPic(screen, sea, 0,0, 30, 30, i, j);
        }
    }
	
	

/* Fim das alterações do EP3*/


    posiciona_barco(screen, barco, save, mapa, &xBarco, &yBarco, m, n,&x,&y);

    printf("Controle o barco na tela: ");
    
    
	/*Inicializa a captura de eventos do teclado*/
	WShow(screen);
	InitKBD(screen);
    
	while (tecla != 39){
		/*Pega a proxima tecla e retorna o codigo X*/
        tecla = (int) WGetKey(screen);
        PutPic(screen, rastro, 0, 0, 30, 30, x, y);
        if (tecla == 54 || tecla == 111 || tecla == 31)
          y-=30;
        else if (tecla == 40 || tecla == 114 || tecla == 46)
          x+=30;
        else if (tecla == 26 || tecla == 113 || tecla == 44)
          x-=30;
        else if (tecla == 56 || tecla == 116 || tecla == 45)
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
