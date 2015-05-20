/*******************************************************************************
*	Membros do Grupo:
*	 Nome: Duilio Henrique Haroldo Elias                                        *
*	 Numero USP: 6799722                                                        *
*	 
*	 Nome: Maurício Ozaki                                                       *
*	 Numero USP:7577427                                                        *
*	 
*	 Nome:Ricardo Oliveira                                                      *
*	 Numero USP: 3683165                                                           *
*	 
*	Professor: Alair             					                           *
*	Matéria: Laboratório de Programação I                                      *
*
*											    			                   *
*******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void save_file (char* filename){
    FILE *arq;
    int i = 0, j = 0;
    char ext[] = ".txt";

    printf("Digite o nome do arquivo de saída: ");
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
    /*fprintf (arq, "");*/
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
    fscanf (arq, "%d %d", m, n); /*guardar m e n*/
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
    printf("_|\n\n\n\n\n\n\n");

}

/*Atualiza Matriz que representa o mapa e o arquivo de saida*/
void atualiza_mapa (char filename[], char** M, int m, int n){
    escreva_mapa_arquivo(filename, M, m, n);
    escreva_mapa_tela(M, m, n);
}

/*serteia tiro*/
int sorteia (int k){
        return ((int)(1.0 + (rand() / (RAND_MAX + 1.0)) * k));
}

/*gera as coordenadas do tiro*/
void coordenadas_tiro (int* x, int* y, int m, int n){
    int num_rand;

    num_rand = sorteia (m * n) - 1;
    *x = num_rand / n + 1;
    *y = num_rand % n + 1;
}

/*Identifica alvo atingido*/
char identifica_alvo_atingido (char** M, int x, int y){
    char alvo;
    printf("Tiro atingiu a linha %d coluna %d ", x, y);
    alvo = M[x - 1][y - 1];
    
    switch (alvo){
        case 'S' :
            M[x - 1][y - 1] = 'x';
            printf("acertando um submarino\n\n");
            break;
        
        case 'D' :
            M[x - 1][y - 1] = 'x';
            printf("acertando um destroyer\n\n");
                break;

        case 'C' :
            M[x - 1][y - 1] = 'x';
            printf("acertando um cruzador\n\n");
            break;
        
        case 'P' :
            M[x - 1][y - 1] = 'x';
            printf("acertando um porta-aviao\n\n");
            break;
        
        case 'H' :
            M[x - 1][y - 1] = 'x';
            printf("acertando um hidro-aviao\n\n");
            break;
        
        case '.' :
            M[x - 1][y - 1] = '=';
            printf("acertando a agua\n\n");
            break;
        
        case 'T' :
            M[x - 1][y - 1] = '+';
            printf("acertando um local onde o barco esteve\n\n");
            break;

        case 'B' :
            M[x - 1][y - 1] = '!';
            printf("acertando o barco\n");
            break;
        
        default:
            printf("atingindo regiao ja atingida\n\n");
    }
    return alvo;
}
/*corre matriz e afundas as embarcacoes*/
void afundador (char filename[], char** M, int m, int n, int x, int y, char alvo){
    int i, j;
    M[x-1][y-1]='*';
    for(i=-1;i<=1;i++){
        for(j=-1;j<=1;j++){
            /*Limites da matriz*/
            if(x + i > 0 && x + i <= m && y + j > 0 && y + j <= n){
                /*base da recursao(eh alvo)*/
                if(M[(x-1)+i][(y-1)+j] == alvo){
                    afundador (filename,M,m,n,x+i,y+j,alvo);
                }
                
            }
            
        }
    }
}

/*Afunda o destroyer*/
void afunda_destroyer (char filename[], char** M, int m, int n, int x, int y, char alvo){
    afundador (filename,M, m, n, x, y, alvo);
}

/*Afunda o cruzador*/
void afunda_cruzador (char filename[], char** M, int m, int n, int x, int y, char alvo){
    afundador (filename,M, m, n, x, y, alvo);
}
/*Afunda o porta-aviao*/
void afunda_porta_aviao (char filename[], char** M, int m, int n, int x, int y, char alvo){
    afundador (filename,M, m, n, x, y, alvo);
}

/*afunda o hidro-aviao*/
void afunda_hidro_aviao (char filename[], char** M, int m, int n, int x, int y, char alvo){
    afundador (filename,M, m, n, x, y, alvo);
}
/*swtch para verifcar o tipo de embarcacao*/
void afunda_embarcacao (char filename[], char** M, int m, int n, int x, int y, char alvo){
    switch (alvo){
        case 'S' :
            break;

        case 'D' :
            afunda_destroyer(filename, M, m, n, x, y, alvo);
            break;

        case 'C' :
            afunda_cruzador (filename ,M ,m ,n ,x ,y ,alvo);
            break;
        case 'P' :
            afunda_porta_aviao (filename,M ,m ,n ,x ,y ,alvo);
            break;
        
        case 'H' :
            afunda_hidro_aviao (filename ,M ,m ,n ,x ,y ,alvo);
            break;
    }
}
/*diparador de tiros*/
int dispara_tiros(char filename[],char** M, int m, int n){
    int x, y, cont, time;
    char alvo;

    for (cont = 0; cont < 3; cont++){
        coordenadas_tiro(&x, &y, m, n);
        alvo = identifica_alvo_atingido (M, x, y);
        atualiza_mapa(filename, M, m, n);
        afunda_embarcacao (filename,M, m, n, x, y, alvo);
        if(alvo=='P'|| alvo == 'D'|| alvo == 'C' || alvo == 'P'|| alvo =='H'){
            atualiza_mapa(filename, M, m, n);
        }
        if (alvo == 'B'){
            printf("O barco afundou\n\n");
            return 0;
        }
        for (time = 0; time < 200000000; time++){} /*intervalo de tempo entre os tiros*/
    }
    return 1;
}
/*posiciona o barco a cada jogada*/
void posiciona_barco (char filename[], char** M, int* xBarco, int* yBarco, int m, int n){
    int y;
    char digito;
     fflush(stdin); /*para windows*/
    /*_fpurge(stind) para linux*/

    while (1){
        y = 0;
        digito = '0';
        printf("\nEscolha uma posicao incial (1 a %d) para o barco: ", n);
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
        else if (M[0][y - 1] != '.')
            printf("Esta posicao esta ocupada. Escolha outra posicao\n\n");
        else {
            M[0][y - 1] = 'B';
            *xBarco = 1;
            *yBarco = y;
            break;
        }
    }
    atualiza_mapa(filename, M, m, n);
}

/*verifica se o movimento de entrada é valido*/
char mov_valido (){
    char mov;
    while(1){
      mov = getchar();
        if (mov >= 'B' && mov <= 'E') /*deixar minuscula*/
            mov = mov + 32;
        if (mov >= 'b' && mov <= 'e')
            return mov;
        printf("\nDigite um movimento valido (b), (c), (d) ou (e): ");
    }
}
/*movimenta o barco*/
int rema_barco (char filename[], char** M, int* xBarco, int* yBarco, int m, int n){
    char mov;
    int tentativa = 3, xNew, yNew ; /*para testar nova posicao*/

    while (1){
        mov = mov_valido(); /*recebe movimento valido*/
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
            atualiza_mapa(filename, M, m, n);

                tentativa--;
                if (tentativa == 0){
                    printf("Voce esgotou suas tentativas\n\n");
                    atualiza_mapa(filename, M, m, n);
                    return 0;
                }
            printf("Voce tem mais %d tentativas\n\n",  tentativa);
            atualiza_mapa(filename, M, m, n);
            continue;
        }

        /*esta bloqueada a passagem*/
        else if (M[xNew - 1][yNew - 1] == 'S' || M[xNew - 1][yNew - 1] == 'D' || M[xNew - 1][yNew - 1] == 'C' ||
                                M[xNew - 1][yNew - 1] == 'P' || M[xNew - 1][yNew - 1] == 'H') {
            tentativa--;
            if (tentativa == 0){
                printf("Voce esgotou suas tentativas\n\n");
                atualiza_mapa(filename, M, m, n);
                return 0;
            }
            printf("O barco atingiu uma embarcacao. Voce tem mais %d tentativas\n\n",  tentativa);
            atualiza_mapa(filename, M, m, n);
            continue;
        }
        else if (xNew == m){
            printf("Parabens, voce chegou ao destino\n\n");
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
    *xBarco = xNew;
    *yBarco = yNew;
    M[*xBarco - 1][*yBarco - 1] = 'B';
    atualiza_mapa(filename, M, m, n);
    return 1;
}
