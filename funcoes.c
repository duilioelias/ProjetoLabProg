#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*imprime dados na tela*/
void escreva_mapa_tela(char** M, int m, int n){
    int i, j;
    for (i = 0; i < m; i ++){
        for (j = 0; j < n; j ++)
            printf ("%c", M[i][j]);
        printf ("|%d\n", (i + 1)); /*imprime coord y*/
        }
    for (j = 0; j < n; j ++){ /*imprime regua - coord x*/
        if ((j + 1) % 5 == 0)
            printf("*");
        else printf("|");
    }
    printf ("\n\n");
}

void save_file (char* filename){
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

}

/*alocar memoria para matriz*/
char** AlocaMatriz(int m, int n){
  int i;
  char *    *M;
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
/*gravar arquivo*/
void escreva_mapa_arquivo(char filename[], char** M, int m, int n){
    FILE *arq;
    arq = fopen (filename , "w"); /*abrir modo gravacao*/
    fprintf (arq, "%d %d\n", n, m); /*gravar o cabecalho*/
    GravaDados(arq, M, m, n);
    fclose(arq);
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
    *y = num_rand % n + 1;
    *x = num_rand / n + 1;
}

char identifica_alvo_atingido (char filename[], char** M, int x, int y){
    char alvo;
    printf("Tiro atingiu coordenadas (%d, %d) ", x, y);
    alvo = M[x - 1][y - 1];
    
    switch (alvo){
        case 'S' :
            M[x - 1][y - 1] = 'x';
            printf("acertando um submarino\n");
            break;
        
        case 'D' :
            M[x - 1][y - 1] = 'x';
            printf("acertando um destroyer\n");
                break;

        case 'C' :
            M[x - 1][y - 1] = 'x';
            printf("acertando um cruzador\n");
            break;
        
        case 'P' :
            M[x - 1][y - 1] = 'x';
            printf("acertando um porta-aviao\n");
            break;
        
        case 'H' :
            M[x - 1][y - 1] = 'x';
            printf("acertando um hidro-aviao\n");
            break;
        
        case '.' :
            M[x - 1][y - 1] = '=';
            printf("acertando a agua\n");
            break;
        
        case 'T' :
            M[x - 1][y - 1] = '+';
            printf("acertando um local onde o barco esteve\n");
            break;

        case 'B' :
            M[x - 1][y - 1] = '!';
            printf("acertando o barco\n");
            break;
        
        default:
            printf("\n");
    }
}


void dispara_tiros(char filename[],char** M, int m, int n){
    int x, y, cont;
    char alvo;

    for (cont = 0; cont < 3; cont++){
        coordenadas_tiro(&x, &y, m, n);
        alvo = identifica_alvo_atingido (filename, M, x, y);
        atualiza_mapa(filename, M, m, n);
    }
}



void posiciona_barco (char filename[], char** M, int* xBarco, int* yBarco, int m, int n){
    int x;
    do{
        printf("Escolha uma posicao incial (1 a %d) para o barco: ", n);
        scanf("%d", &x);
        if (x < 0 || x > n)
            printf("posicao nao permitida\n");
        else if (M[0][x - 1] != '.')
            printf("Esta posicao esta ocupada. Escolha outra posicao\n");
        else {
            M[0][x - 1] = 'B';

            break;
        }
    } while (1);

    atualiza_mapa(filename, M, m, n);
}
