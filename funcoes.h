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
/*Funções que estão faltando:
    - rema_barco
    - afunda_embarcação
        -afunda_destroyer
        -afunda_cruzador
        -afunda_porta_aviao
        -afunda_hidro_aviao
*/

#ifndef _H_FUNCOES
#define _H_FUNCOES
/*imprime dados na tela*/
void escreva_mapa_tela(char** M, int m, int n);
void save_file (char* filename);

/*alocar memoria para matriz*/
char** AlocaMatriz(int m, int n);
void LiberaMatriz(char** M, int m);
/*ler dados no arquivo*/
void LeDados(FILE *arq, char** M, int m, int n);

/*gravar dados no arquivo*/
void GravaDados(FILE *arq, char** M, int m, int n);

/*abrir arquivo*/
char** leia_mapa(int *m, int *n);
void escreva_mapa_arquivo(char filename[], char** M, int m, int n);
void atualiza_mapa (char filename[], char** M, int m, int n);
int sorteia (int k);
void coordenadas_tiro (int* x, int* y, int m, int n);
char identifica_alvo_atingido (char filename[], char** M, int x, int y);
void dispara_tiros(char filename[],char** M, int m, int n);
void posiciona_barco (char filename[], char** M, int* xBarco, int* yBarco, int m, int n);
#endif