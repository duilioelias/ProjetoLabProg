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

*/

#ifndef _H_FUNCOES
#define _H_FUNCOES

typedef struct _grafico{
  PIC mar, mar2, barco_DIR, barco_ESQ, barco_BAIXO, barco_CIMA, barco_RASTRO,
    _EXPLOSAO, _AFUNDA, tiro_AGUA;
  MASK DIR, ESQ, BAIXO, CIMA, RASTRO, EXPLOSAO, AFUNDA, AGUA, APAGA;
    WINDOW *w;
  int m;
}grafico;

grafico *inicializar_graf(int m, int n, int x, int y);
void finalizar_graf (grafico* graf);
void save_file (char* filename);
char** AlocaMatriz(int m, int n);
void LiberaMatriz(char** M, int m);
void LeDados(FILE *arq, char** M, int m, int n);
void GravaDados(FILE *arq, char** M, int m, int n);
char** leia_mapa(int *m, int *n);
void escreva_mapa_arquivo(char filename[], char** M, int m, int n);
void escreva_mapa_tela(char** M, int m, int n);
void atualiza_mapa (char filename[], char** M, int m, int n);
int sorteia (int k);
void coordenadas_tiro (int* x, int* y, int m, int n);
char identifica_alvo_atingido (grafico* graf, char filename[], char** M, int x, int y);
void afundador (grafico* graf, char filename[], char** M, int m, int n, int x, int y, char alvo);
void afunda_destroyer (grafico* graf, char filename[], char** M, int m, int n, int x, int y, char alvo);
void afunda_cruzador (grafico* graf, char filename[], char** M, int m, int n, int x, int y, char alvo);
void afunda_porta_aviao (grafico* graf, char filename[], char** M, int m, int n, int x, int y, char alvo);
void afunda_hidro_aviao (grafico* graf, char filename[], char** M, int m, int n, int x, int y, char alvo);
void afunda_embarcacao (grafico* graf, char filename[], char** M, int m, int n, int x, int y, char alvo);
int dispara_tiros(grafico* graf, char filename[],char** M, int m, int n);
void posiciona_barco (char filename[], char** M, int* xBarco, int* yBarco, int m, int n);
char mov_valido (grafico* graf);



#endif