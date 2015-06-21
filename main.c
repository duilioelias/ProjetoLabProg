#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "xwc.h"
#include "funcoes.h"



int main(){
  char** mapa;
  char save[20];
  int m, n, xBarco, yBarco;
  grafico* graf;
  srand((unsigned int)time(NULL));


  save_file(save);
  mapa = leia_mapa(&m, &n);
  escreva_mapa_tela(mapa, m, n);

  posiciona_barco(save, mapa, &xBarco, &yBarco, m, n);
  graf = inicializar_graf(m, n, xBarco, yBarco); /*funcoes graficas*/
  while (1){
    if (!dispara_tiros(graf, save, mapa, m, n)){
      printf("Fim do jogo\n");
      break;
    }
    if (!rema_barco (graf, save, mapa, &xBarco, &yBarco, m, n)){
      printf("Fim do jogo\n");
      break;
    }

    //glutTimeFunc(1000, ,);
  }

  LiberaMatriz(mapa, m);
  finalizar_graf(graf);
  return 0;
}
