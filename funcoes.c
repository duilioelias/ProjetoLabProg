#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "xwc.h"

typedef struct _grafico{
  PIC mar, mar2, barco_DIR, barco_ESQ, barco_BAIXO, barco_CIMA, barco_RASTRO,
    _EXPLOSAO, _AFUNDA, tiro_AGUA;
  MASK DIR, ESQ, BAIXO, CIMA, RASTRO, EXPLOSAO, AFUNDA, AGUA, APAGA;
    WINDOW *w;
  int m;
}grafico;

grafico *inicializar_graf(int m, int n, int x, int y){

  grafico* graf;
  graf = (grafico*) malloc(sizeof(grafico));
  graf -> m = m;
  graf -> w = InitGraph(n * 30, m * 30 + 30, "Bombardeio Naval"); /*construir janela*/
  graf -> mar = ReadPic(graf -> w, "oceano.xpm", NULL);

  PutPic(graf -> w, graf -> mar, 0, 0, n * 30, m * 30, 0, 0);
  graf -> DIR = NewMask(graf -> w, 30, 30);
  graf -> ESQ = NewMask(graf -> w, 30, 30);
  graf -> BAIXO = NewMask(graf -> w, 30, 30);
  graf -> CIMA = NewMask(graf -> w, 30, 30);
  graf -> RASTRO = NewMask(graf -> w, 30, 30);
  graf -> EXPLOSAO = NewMask(graf -> w, 30, 30);
  graf -> AFUNDA = NewMask(graf -> w, 30, 30);
  graf -> AGUA = NewMask(graf -> w, 30, 30);
  graf -> APAGA = NewMask(graf -> w, 30, 30);

  graf -> barco_DIR = ReadPic(graf -> w, "barco_dir.xpm", graf -> DIR);
  graf -> barco_ESQ = ReadPic(graf -> w, "barco_esq.xpm", graf -> ESQ);
  graf -> barco_BAIXO = ReadPic(graf -> w, "barco_baixo.xpm", graf -> BAIXO);
  graf -> barco_CIMA = ReadPic(graf -> w, "barco_cima.xpm", graf -> CIMA);
  graf -> barco_RASTRO = ReadPic(graf -> w, "rastro.xpm", graf -> RASTRO);
  graf -> _EXPLOSAO = ReadPic(graf -> w, "explosao.xpm", graf -> EXPLOSAO);
  graf -> _AFUNDA = ReadPic(graf -> w, "afunda.xpm", graf -> AFUNDA);
  graf -> tiro_AGUA = ReadPic(graf -> w, "tiro_agua.xpm", graf -> AGUA);
  graf -> mar2 = ReadPic(graf -> w, "oceano.xpm", graf -> APAGA);

InitKBD(graf -> w);
  WShow(graf -> w); /*inicializar o grafico*/
  SetMask(graf -> w, graf -> BAIXO);
  PutPic(graf -> w, graf -> barco_BAIXO, 0 , 0, 30, 30, (y - 1) * 30, 0);

  WCor(graf -> w, WNamedColor("gold"));
  WPrint(graf -> w, 10, (graf -> m) * 30 + 10, "Inicio do jogo");

  return graf;
}

void finalizar_graf (grafico* graf){
  CloseGraph();
  free(graf);
}

void save_file (char* filename){
    FILE *arq;
    int i = 0, j = 0;
    char ext[] = ".txt";

    printf("Digite seu nickname: ");
    scanf("%s", filename);

    while (filename[i] != '\0') /*localiza o fim do nome*/
           i++;
    /*coloca a extensao.pgm ao final do nome*/
    do {
        filename[i] = ext[j];
        j++;
        i++;
    }while (ext[j - 1] != '\0');

    arq = fopen (filename , "w"); /*zerar arquivo*/
    fprintf (arq, " ");
    fclose(arq);
}

/*alocar memoria para matriz*/
char** AlocaMatriz(int m, int n){
  int i;
  char **M;
  M = (char**) malloc(m * sizeof (char*)); /*aloca vetor de apontadores*/
  if (M == NULL)
    exit(1); /*se houver falta de memoria*/
  for (i = 0; i < m; i++){
    M[i] = (char*) malloc(n * sizeof (char)); /*aloca as linhas da matriz*/
    if (M[i] == NULL)
      exit(1);
  }
  return M; /*retorna o apontador da matriz alocada*/
}

/*libera memoria usada para a matriz*/
void LiberaMatriz(char** M, int m){
  int i;
  for (i = 0; i < m; i++)
    free(M[i]);
  free(M);
}

/*ler dados no arquivo*/
void LeDados(FILE *arq, char** M, int m, int n){
  int i, j;
  char verif;

  for (i = 0; i < m; i ++){
    while (getc (arq) != '\n'){} /*consumir 'lixo'*/
    verif = getc (arq); /*leitura de M[i][0]*/

    for (j = 0; j < n && verif != '|'; j ++){
      M[i][j] = verif;
      verif = getc (arq);
    }
  }
}

/*gravar dados no arquivo*/
void GravaDados(FILE *arq, char** M, int m, int n){
  int i, j;
  for (i = 0; i < m; i ++){
    for (j = 0; j < n; j ++)
      putc (M[i][j], arq);
    fprintf (arq, "|\n"); /*imprimir validador de final de linha e quebra de pg*/
  }
}

/*abrir arquivo*/
char** leia_mapa(int *m, int *n){
  FILE *arq = NULL;
  char **M;
  char filename[100];

  printf ("Digite o nome do arquivo de entrada: ");
  while(arq == NULL){
    scanf ("%s", filename);
    arq = fopen (filename , "r");
    if( arq == NULL) /*verifica se  arquivo é valido*/
      printf ("Arquivo %s nao encontrado\nDigite novamente o nome do arquivo: ", filename);
  }
  /*ler o cabecalho do arquivo*/
  fscanf (arq, "%d %d\n", m, n); /*guardar m e n*/
  M = AlocaMatriz (*m, *n);
  printf ("Arquivo %s sendo carregado...\n", filename);
  LeDados (arq, M, *m, *n); /*transferir para a matriz os dados do arquivo*/
  printf ("Arquivo %s carregado com sucesso.\n", filename);
  fclose(arq); /*fechar o arquivo*/
  return M;
}
/*escrever dados no arquivo*/
void escreva_mapa_arquivo(char filename[], char** M, int m, int n){
  FILE *arq;

  arq = fopen (filename , "a"); /*abrir modo gravacao*/
  fprintf (arq, "%d %d |\n", m, n); /*gravar o cabecalho*/
  GravaDados(arq, M, m, n);
  fclose(arq);
}
/*imprime dados na tela*/
void escreva_mapa_tela(char** M, int m, int n){
  int i, j;

  printf("   |");
  for (j = 1; j <= n; j ++) /*imprime num colunas*/
    printf("%2d ", j);
  printf(" |\n___|");
  for (j = 1; j <= n; j ++) /*imprime borda*/
    printf("___");
  printf("_|\n");

  for (i = 0; i < m; i ++){
    printf ("%2d |", (i + 1));  /*imprime num linhas*/
    for (j = 0; j < n; j ++)
      if (M[i][j] == '.' || M[i][j] == 'S' || M[i][j] == 'D' ||
      M[i][j] == 'C' || M[i][j] == 'P' || M[i][j] == 'H'){
    printf (" - ");
      }
      else
    printf (" %c ", M[i][j]);
    printf(" |\n");
  }
  printf ("___|");
  for (j = 1; j <= n; j ++) /*imprime borda*/
    printf("___");
  printf("_|\n\n\n\n\n\n\n\n\n\n\n\n");
}

void atualiza_mapa (char filename[], char** M, int m, int n){
  escreva_mapa_arquivo(filename, M, m, n);
  escreva_mapa_tela(M, m, n);
}

int sorteia (int k){
  return ((int)(1.0 + (rand() / (RAND_MAX + 1.0)) * k));
}
void coordenadas_tiro (int* x, int* y, int m, int n){
  int num_rand;

  num_rand = sorteia (m * n) - 1;
  *x = num_rand / n + 1;
  *y = num_rand % n + 1;
}

char identifica_alvo_atingido (grafico* graf, char filename[], char** M, int x, int y){
  FILE *arq;
  arq = fopen (filename , "a");

  char alvo;
  printf("Tiro atingiu a linha %d coluna %d ", x, y);
  fprintf(arq, "Tiro atingiu a linha %d coluna %d ", x, y);

  alvo = M[x - 1][y - 1];

  if (alvo == 'S' || alvo == 'D' || alvo == 'C' || alvo == 'P' || alvo == 'H' || alvo == 'B'){
    SetMask(graf -> w, graf -> EXPLOSAO);
    PutPic(graf -> w, graf -> _EXPLOSAO, 0 , 0, 30, 30, (y- 1) * 30,  (x - 1) * 30);
  }
  else {
    SetMask(graf -> w, graf -> AGUA);
    PutPic(graf -> w, graf -> tiro_AGUA, 0 , 0, 30, 30, (y- 1) * 30,  (x - 1) * 30);
  }
  usleep(500000);
  WCor(graf -> w, WNamedColor("gold"));

  switch (alvo){
  case 'S' :
    M[x - 1][y - 1] = 'x';
    printf("acertando um submarino\n\n");
    fprintf(arq, "acertando um submarino\n\n");
    WPrint(graf -> w, 0, graf -> m * 30 + 10, "Tiro atingiu um submarino");
    break;

  case 'D' :
    M[x - 1][y - 1] = 'x';
    printf("acertando um destroyer\n\n");
    fprintf(arq, "acertando um destroyer\n\n");
    WPrint(graf -> w, 0, graf -> m * 30 + 10, "Tiro atingiu um destroyer");
    break;

  case 'C' :
    M[x - 1][y - 1] = 'x';
    printf("acertando um cruzador\n\n");
    fprintf(arq, "acertando um cruzador\n\n");
    WPrint(graf -> w, 0, graf -> m * 30 + 10, "Tiro atingiu um cruzador");
    break;

  case 'P' :
    M[x - 1][y - 1] = 'x';
    printf("acertando um porta-aviao\n\n");
    fprintf(arq, "acertando um porta-aviao\n\n");
     WPrint(graf -> w,  0, graf -> m * 30 + 10, "Tiro atingiu um porta-aviao");
    break;

  case 'H' :
    M[x - 1][y - 1] = 'x';
    printf("acertando um hidro-aviao\n\n");
    fprintf(arq, "acertando um hidro-aviao\n\n");
    WPrint(graf -> w, 0, graf -> m * 30 + 10, "Tiro atingiu um hidro-aviao");
    break;

  case '.' :
    M[x - 1][y - 1] = '=';
    printf("acertando a agua\n\n");
    fprintf(arq, "acertando a agua\n\n");
     WPrint(graf -> w,  0, graf -> m * 30 + 10,"Tiro atingiu a agua");
    break;

  case 'T' :
    M[x - 1][y - 1] = '+';
    printf("acertando um local onde o barco esteve\n\n");
    fprintf(arq,"acertando um local onde o barco esteve\n\n");
    WPrint(graf -> w,  0, graf -> m * 30 + 10, "Tiro atingiu um lugar onde o barco esteve");
    break;

  case 'B' :
    M[x - 1][y - 1] = '!';
    printf("acertando o barco\n");
    fprintf(arq, "acertando o barco\n");
    WPrint(graf -> w,  0, graf -> m * 30 + 10,"Tiro atingiu o barco");
    break;

  default:
    printf("atingindo regiao ja atingida\n\n");
    fprintf(arq, "atingindo regiao ja atingida\n\n");
    WPrint(graf -> w,  0, graf -> m * 30 + 10, "Tiro atingiu um regiao ja atingida");
  }

  fclose(arq);
  return alvo;
}
/*corre matriz e afundas as embarcacoes*/
void afundador (grafico* graf, char filename[], char** M, int m, int n, int x, int y, char alvo){
  int i, j;
  M[x-1][y-1]='*';

  PutPic(graf -> w, graf -> mar, (y - 1) * 30, (x - 1) * 30, 30, 30, (y - 1) * 30, (x - 1) * 30);
  SetMask(graf -> w, graf -> AFUNDA);
  PutPic(graf -> w, graf -> _AFUNDA, 0 , 0, 30, 30, (y - 1) * 30,  (x - 1) * 30);

  usleep(20000);
  for(i=-1;i<=1;i++){
    for(j=-1;j<=1;j++){
      /*Limites da matriz*/
      if(x + i > 0 && x + i <= m && y + j > 0 && y + j <= n){
    /*base da recursao(eh alvo)*/
    if(M[(x-1)+i][(y-1)+j] == alvo){
      afundador (graf, filename,M,m,n,x+i,y+j,alvo);
    }
      }
    }
  }
}

/*Afunda o destroyer*/
void afunda_destroyer (grafico* graf, char filename[], char** M, int m, int n, int x, int y, char alvo){
  afundador (graf,filename,M, m, n, x, y, alvo);
}

/*Afunda o cruzador*/
void afunda_cruzador (grafico* graf, char filename[], char** M, int m, int n, int x, int y, char alvo){
  afundador (graf, filename,M, m, n, x, y, alvo);
}
/*Afunda o porta-aviao*/
void afunda_porta_aviao (grafico* graf, char filename[], char** M, int m, int n, int x, int y, char alvo){
  afundador (graf, filename,M, m, n, x, y, alvo);
}

/*afunda o hidro-aviao*/
void afunda_hidro_aviao (grafico* graf, char filename[], char** M, int m, int n, int x, int y, char alvo){
  afundador (graf, filename,M, m, n, x, y, alvo);
}
/*switch para verifcar o tipo de embarcacao*/
void afunda_embarcacao (grafico* graf, char filename[], char** M, int m, int n, int x, int y, char alvo){
  switch (alvo){
  case 'S' :
    break;

  case 'D' :
    afunda_destroyer(graf, filename, M, m, n, x, y, alvo);
    break;

  case 'C' :
    afunda_cruzador (graf, filename ,M ,m ,n ,x ,y ,alvo);
    break;
  case 'P' :
    afunda_porta_aviao (graf, filename,M ,m ,n ,x ,y ,alvo);
    break;

  case 'H' :
    afunda_hidro_aviao (graf, filename ,M ,m ,n ,x ,y ,alvo);
    break;
  }
}
/*diparador de tiros*/
int dispara_tiros(grafico* graf, char filename[],char** M, int m, int n){
  int x, y, cont;
  char alvo;
  FILE *arq;
  arq = fopen (filename , "a");

  for (cont = 0; cont < 3; cont++){
    coordenadas_tiro(&x, &y, m, n);
    alvo = identifica_alvo_atingido (graf, filename, M, x, y);
    atualiza_mapa(filename, M, m, n);
    afunda_embarcacao (graf, filename,M, m, n, x, y, alvo);
    if(alvo=='P'|| alvo == 'D'|| alvo == 'C' || alvo =='H'){
      atualiza_mapa(filename, M, m, n);
    }
    if (alvo == 'B'){
      printf("O barco afundou\n\n");
      fprintf(arq, "O barco afundou\n\n");
      return 0;
    }
    sleep(1);
  }
  fclose(arq);
    return 1;
}
/*posiciona o barco a cada jogada*/
void posiciona_barco (char filename[], char** M, int* xBarco, int* yBarco, int m, int n){
  int y;
  char digito;
  FILE *arq;
  arq = fopen (filename , "a");

  while (1){
    y = 0;
    digito = '0';
    printf("\nEscolha uma posicao incial (1 a %d) para o barco: ", n);
    fprintf(arq, "\nEscolha uma posicao incial (1 a %d) para o barco: ", n);
    while (digito != '\n'){
      if (digito < '0' || digito > '9'){
    while (getc(stdin)!= '\n'){}
    digito = '0';
    printf("\nEste nao eh um valor valido para posicao. Digite novamente: ");
      }
      y = y * 10 + (digito - 48);
      digito = getc (stdin);
    }
    if (y < 0 || y > n)
      printf("%d nao eh uma posicao permitida\n\n", y);
    else if (M[0][y - 1] != '.'){
      printf("Esta posicao esta ocupada. Escolha outra posicao\n\n");
      fprintf(arq, "Esta posicao esta ocupada. Escolha outra posicao\n\n");
    }
    else {
      M[0][y - 1] = 'B';
      *xBarco = 1;
      *yBarco = y;
      break;
    }
  }

  atualiza_mapa(filename, M, m, n);
  fclose(arq);
}

char mov_valido (grafico* graf){
  char mov = 'a';
  int m;

  while(1){
    m = (int) WGetKey(graf -> w); printf ("%d", m);
    if (m == 40 || m == 114) /*para a dir*/
      mov = 'd';
    else if (m == 26 || m == 113) /*para a esq*/
      mov = 'e';
    else if (m == 56 || m == 116) /*para baixo*/
      mov = 'b';
    else if (m == 54 || m == 111) /*para cima*/
      mov = 'c';
    if (mov >= 'b' || mov <= 'e')
      return mov;
    printf("\nDigite um movimento valido (b), (c), (d) ou (e): ");
  }
}
/*movimenta o barco*/
int rema_barco (grafico* graf, char filename[], char** M, int* xBarco, int* yBarco, int m, int n){
  char mov;
  int tentativa = 3, xNew, yNew ; /*para testar nova posicao*/
  FILE *arq;
  arq = fopen (filename , "a");

  while (1){
    mov = mov_valido(graf); /*recebe movimento valido*/
    xNew = *xBarco;
    yNew = *yBarco;

    if (mov == 'c')
      xNew--;
    else if (mov == 'b')
      xNew++;
    else if (mov == 'e')
      yNew--;
    else if (mov == 'd')
      yNew++;

    if ((xNew == 0) || (yNew == 0) || (yNew == (n + 1))){
      printf("O barco atingiu a margem\n\n");
      fprintf(arq, "O barco atingiu a margem\n\n");
      atualiza_mapa(filename, M, m, n);

      tentativa--;
      if (tentativa == 0){
    printf("Voce esgotou suas tentativas\n\n");
    fprintf(arq, "Voce esgotou suas tentativas\n\n");
    atualiza_mapa(filename, M, m, n);
    return 0;
      }
      printf("Voce tem mais %d tentativas\n\n",  tentativa);
      fprintf(arq, "Voce tem mais %d tentativas\n\n",  tentativa);
      atualiza_mapa(filename, M, m, n);
      continue;
    }

    /*esta bloqueada a passagem*/
    else if (M[xNew - 1][yNew - 1] == 'S' || M[xNew - 1][yNew - 1] == 'D' || M[xNew - 1][yNew - 1] == 'C' ||
         M[xNew - 1][yNew - 1] == 'P' || M[xNew - 1][yNew - 1] == 'H') {
      tentativa--;
      if (tentativa == 0){
    printf("Voce esgotou suas tentativas\n\n");
    fprintf(arq, "Voce esgotou suas tentativas\n\n");
    atualiza_mapa(filename, M, m, n);
    return 0;
      }
      printf("O barco atingiu uma embarcacao. Voce tem mais %d tentativas\n\n",  tentativa);
      fprintf(arq, "O barco atingiu uma embarcacao. Voce tem mais %d tentativas\n\n",  tentativa);
      atualiza_mapa(filename, M, m, n);
      continue;
    }
    else if (xNew == m){
      printf("Parabens, voce chegou ao destino\n\n");
      fprintf(arq, "Parabens, voce chegou ao destino\n\n");
      M[*xBarco - 1][*yBarco - 1] = 'T';
      *xBarco = xNew;
      *yBarco = yNew;
      M[*xBarco - 1][*yBarco - 1] = 'B';
      atualiza_mapa(filename, M, m, n);
      return 0;
    }

    else break;
  }
  M[*xBarco - 1][*yBarco - 1] = 'T';
  SetMask(graf -> w, graf -> APAGA);
  PutPic(graf -> w, graf -> mar2, (*yBarco - 1) * 30, (*xBarco - 1) * 30, 30, 30, (*yBarco - 1) * 30, (*xBarco - 1) * 30);

  SetMask(graf -> w, graf -> RASTRO);
  PutPic(graf -> w, graf -> barco_RASTRO,0 , 0, 30, 30, (*yBarco - 1) * 30,  (*xBarco - 1) * 30);

  if (xNew > *xBarco){ /*para baixo*/
    SetMask(graf -> w, graf -> BAIXO);
    PutPic(graf -> w, graf -> barco_BAIXO,0 , 0, 30, 30, (yNew - 1) * 30,  (xNew - 1) * 30);
  }
  else if (xNew < *xBarco){ /*para cima*/
    SetMask(graf -> w, graf -> CIMA);
    PutPic(graf -> w, graf -> barco_CIMA,0 , 0, 30, 30, (yNew - 1) * 30,  (xNew - 1) * 30);
  }
  else if (yNew > *yBarco){ /*para dir*/
    SetMask(graf -> w, graf -> DIR);
    PutPic(graf -> w, graf -> barco_DIR,0 , 0, 30, 30, (yNew - 1) * 30,  (xNew - 1) * 30);
  }
  else if (yNew < *yBarco){ /*para esq*/
    SetMask(graf -> w, graf -> ESQ);
    PutPic(graf -> w, graf -> barco_ESQ,0 , 0, 30, 30, (yNew - 1) * 30,  (xNew - 1) * 30);
  }

  *xBarco = xNew;
  *yBarco = yNew;
  M[*xBarco - 1][*yBarco - 1] = 'B';

  atualiza_mapa(filename, M, m, n);
  fclose(arq);
  return 1;
}
