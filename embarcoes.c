#include <stdio.h>
#include <stdlib.h>


struct pent{
	int rot, inv;
	char penta;
};

typedef struct pent piece;

/***************************************************** Índice de funções *******************************************************/
/*******************************************************************************************************************************/
int ** criaSubmarino (int ** mat);
int ** criaDestroy (int ** mat);
int ** criaL (int ** mat);
int ** criaN (int ** mat);
int ** criaP (int ** mat);


int ** bornMatriz(int A, int B);
void killMattriz(int ** m, int lin);
void fiatMatrix (int **mat, int a, int b);
int InsertWall (int ** mat, int lin, int col, int posx, int posy);
int SumElem (int **mat, int lin, int col);
int ** invertePeca (int ** mat, int linha, int col);
int ** RodaPeca (int ** mat, int lin, int col);

void AllowSubmarino (int ** mat, int lin, int col, piece * pilha, int * pospilha, int tamx, int tamy);
void AllowDestroy (int ** mat, int lin, int col, piece * pilha, int * pospilha, int tamx, int tamy);
void AllowL (int ** mat, int lin, int col, piece * pilha, int * pospilha, int tamx, int tamy);
void AllowN (int ** mat, int lin, int col, piece * pilha, int * pospilha, int tamx, int tamy);
void AllowP (int ** mat, int lin, int col, piece * pilha, int * pospilha, int tamx, int tamy);


void InsertPiece (int ** mat, int * pilha);
void RemovePiece (int ** mat, int * pilha);
void ResolveTabuleiro (int ** mat, int lin, int col);
/*********************************************************************************************************************************/
/*********************************************************************************************************************************/

/***************************************************** Definição das peças *******************************************************/  
/*Nessa parte do código que vai até a linha 201 eu estou definindo as peças em suas configurações iniciais. Em se criando funções
para gerar cada uma das peças, eu pretendo economizar memória, pois cada peça será acessada no momento em que se faz necessária   */
/**********************************************************************************************************************************/

int ** criaSubmarino (int ** mat){
	mat[0][0]=0;
	mat[0][1]=2;							//	0	2	2
	mat[0][2]=2;							//	2	2	0
	mat[1][0]=2;							//	0	2	0
	mat[1][1]=2;
	mat[1][2]=0;
	mat[2][0]=0;
	mat[2][1]=2;
	mat[2][2]=0;
	return mat;
}

int ** criaDestroy (int **mat){
	mat[0][0]=3;							//	3
	mat[1][0]=3;							//	3
	mat[2][0]=3;							//	3
	mat[3][0]=3;							//	3
	mat[4][0]=3;							//	3
	return mat;
}

int ** criaL (int **	mat){
	mat[0][0]=4;
	mat[0][1]=0;							//	4	0
	mat[1][0]=4;							//	4	0
	mat[1][1]=0;							//	4	0
	mat[2][0]=4;							//	4	4
	mat[2][1]=0;
	mat[3][0]=4;
	mat[3][1]=4;
	return mat;	
}

int ** criaN (int **	mat){
	mat[0][0]=0;
	mat[0][1]=5;							//	0	5
	mat[1][0]=5;							//	5	5
	mat[1][1]=5;							//	5	0
	mat[2][0]=5;							//	5	0
	mat[2][1]=0;
	mat[3][0]=5;
	mat[3][1]=0;
	return mat;
}

int ** criaP (int **	mat){
	mat[0][0]=0;
	mat[0][1]=6;						//	0	6
	mat[1][0]=6;						//	6   6
	mat[1][1]=6;						//  6   6
	mat[2][0]=6;
	mat[2][1]=6;
	return mat;
}


/******************************************************* Montando o Tabuleuro *****************************************************/
/**********************************************************************************************************************************/

int ** bornMatriz (int A, int B) { 
/* Função q cria Matriz tamanho A x B do tipo int */
	int ** mat;
	int i;
	mat = (int **)calloc(A, sizeof(int *));
	if (mat == NULL)
		printf("ERRO na alocação da função bornMatrizInt\n");
	for (i=0; i<A; i++) {
		mat[i] = (int *)calloc(B, sizeof(int));
		if (mat[i] == NULL)
			printf("ERRO na alocação -- loop for\n");
	}
	return mat;
}

void killMattriz  (int **m, int lin){
/*Libera a Matriz Tabuleiro*/
	int i;
	for (i=0;i<lin; i++){
		free (m[i]);
	}
	free (m);
}

void fiatMatrix (int **mat, int a, int b){
/*Imprime a matriz tabuleiro ao final da exeução se uma soloção é encontrada*/
	int i,j;
	char ** aux;
	aux=(char **)malloc(a*sizeof(char *));
	if (aux==NULL) printf("Problema na grande alocação\n");
	for (i=0;i<a;i++){
		aux[i]=(char *)malloc(b*sizeof(char));
		if (aux[i]=NULL) printf("Problema na pequena alocação\n");
	}
	for (i=0;i<a;i++){
		for (j=0;j<b;j++){
			if (mat[i][j]==0) aux [i][j]='_';
			if (mat[i][j]==1) aux [i][j]='*';
			if (mat[i][j]==2) aux [i][j]='F';
			if (mat[i][j]==3) aux [i][j]='I';
			if (mat[i][j]==4) aux [i][j]='L';
			if (mat[i][j]==5) aux [i][j]='N';
			if (mat[i][j]==6) aux [i][j]='P';
			if (mat[i][j]==7) aux [i][j]='T';
			if (mat[i][j]==8) aux [i][j]='U';
			if (mat[i][j]==9) aux [i][j]='V';
			if (mat[i][j]==10) aux [i][j]='W';
			if (mat[i][j]==11) aux [i][j]='X';
			if (mat[i][j]==12) aux [i][j]='Y';
			if (mat[i][j]==13) aux [i][j]='Z';
		}
	}
	for (i=0; i<a; i++){
		for (j=0;j<b;j++)
			printf("%c\t", aux[i][j]);
		printf("\n");
	}
	for (i=0;i<a;i++)
		free (aux[i]);
	free (aux);
}

int InsertWall (int ** mat, int lin, int col, int posx, int posy){
/*Se a matriz dada pelo usuário tiver mais de 60 espaços livres, essa função será chamada para incluir barreiras que diminuirão a quantidade de espaços livres*/
	int ok=0;
	if (posx<lin && posy<col){
		if (mat [posx][posy]==0)
		ok=1;
	}
	return ok;
}

int SumElem (int **mat, int lin, int col){
/*Essa função conta a quanttidade de espaços ocupados, seja por barreiras ou peças na matriz Tabuleiro*/
	int i, j, soma=0;
	for (i=0; i<lin; i++)
		for (j=0; j<col; j++)
			soma=soma+ mat[i][j];
	return soma;
}

/************************************************** Resolvendo o Tabuleiro ********************************************************/
/**********************************************************************************************************************************/

int ** invertePeca (int ** mat, int linha, int col){
/*Essa função inverte as peças*/
	int i, j;
	int ** aux;
	aux=malloc(3*sizeof(int));
	if(aux==NULL) printf("Erro na 1a alocação\n");
	for (i=0;i<3;i++){
		aux[i]=malloc(3*sizeof(int));
		if(aux[i]==NULL) printf("Erro na alocação a nivel FOR\n");
	}	
	for (i=0;i<linha;i++){
		for (j=0;j<col;j++){
			aux[i][j]=mat[linha-(i+1)][j];
		}
	}
	for (i=0;i<linha;i++){
		for (j=0;j<col;j++){
			mat[i][j]=aux[i][j];
		}
	}
	for (i=0;i<3;i++)
		free(aux[i]);
	free(aux);	
	return mat;
}

int ** RodaPeca (int ** mat, int lin, int col){
/*Essa função ajuda na rotação das peças*/
	int i,j;
	int ** aux;

    aux=malloc(col*sizeof(int *));
	
    if(aux==NULL) printf("Erro na 1a alocação\n");
    
	for (i=0;i<col;i++){
		aux[i]=malloc(lin*sizeof(int));
		if(aux[i]==NULL) printf("Erro na alocação a nivel FOR\n");
	}
	
    for (i=0;i<lin;i++){
		for (j=0;j<col;j++){
			aux[col-(j+1)][i]=mat[i][j];
		}
	}
	return aux;
}

/******************** Nessa parte do código, eu inseri as linhas responsáveis por conferir e inserir as peças *********************/
/**********************************************************************************************************************************/


void AllowDestroy (int ** mat, int lin, int col, piece * pilha, int * pospilha, int tamx, int tamy){
/*Função que verifica se a peça I pode ser colocado no tabuleiro*/
	int ok=1, i;
	int ** aux;
	aux = criaDestroy(aux);
	for (i=0;i<5 && ok;i++){
		if (lin+i>tamy) ok=0;
		else	if (mat[lin+i][col]!=0)	
			ok=0;
	}
	if (ok){
		for (i=0;i<5;i++){
			mat[lin+i][col]=aux[i][0];
		}
		pilha[*pospilha].penta='I';
		pilha[*pospilha].rot=0;
		pilha[*pospilha].inv=0;
		pospilha++;
	}
	else	aux=RodaPeca(aux, 5, 1);
	ok=1;
	for (i=0;i<5 && ok;i++){
		if (col+i>tamx) ok=0;
		else	if (mat[lin][col+i]!=0)	
			ok=0;
	}
	if (ok){
		for (i=0;i<5;i++){
			mat[lin][col]=aux[0][i];
		}
		pilha[*pospilha].penta='I';
		pilha[*pospilha].rot=1;
		pilha[*pospilha].inv=0;
		pospilha++;
	}
}

void AllowSubmarino (int ** mat, int lin, int col, piece * pilha, int * pospilha, int tamx, int tamy){
/*Função que verifica se a peça F pode ser colocado no tabuleiro*/
	int ok, rotF=0, i, j, inverte=0;
	int ** aux;
	aux=criaSubmarino(aux);
	while (inverte<2){
		while (rotF<4){
			ok=1;
			for (i=0; i<3 && ok ; i++){
				for (j=0;j<3;j++){
					if (lin+i>tamy || col+j>tamx) ok=0;
						if (aux[i][j]==2 && ok){
							if (mat[lin+i][col+j]!=0)
								ok=0;
						}
					}
				}
			if (ok==0){
				rotF++;
				aux=RodaPeca(aux, 3, 3);
			}
		}
		rotF=0; //reinicializando rotF para poder tentar outra posição apos a inversao
		inverte++;
		if(inverte!=2) ok=1; 
		invertePeca(aux, 3, 3);
	}
	if(ok){
		pilha[*pospilha].penta='F';
		pilha[*pospilha].rot=rotF;
		pilha[*pospilha].inv=inverte;
		pospilha++;
		for (i=0;i<3;i++){
			for (j=0;j<3;j++){
				if (aux[i][j]==2)
					mat[lin+i][col+j]=aux[i][j];
			}
		}
	}
}

void AllowL (int ** mat, int lin, int col, piece * pilha, int * pospilha, int tamx, int tamy){
/*Função que verifica se a peça L pode ser colocado no tabuleiro*/
	int ok, rotL=0, i, j, inverte=0;
	int ** aux;
	aux=criaL(aux);
	while(inverte<2){
		while(rotL<4){
			ok=1;
			if (rotL%2==0){
				for (i=0;i<4;i++){
					for (j=0;j<2 && ok;j++){
						if (lin+i>tamy || col+j>tamx) ok=0;
						else if (aux[i][j]==4)
							if (mat[lin+i][col+j]!=0) ok=0;
					}
				}
					if (ok==0){
						aux=RodaPeca(aux, 4, 2);
						rotL++;
					}	
			}
			else{
				for (i=0;i<2;i++){
					for (j=0;j<4;j++){
						if (lin+i>tamy || col+j>tamx) ok=0;
						else if (aux[i][j]==4)
							if (mat[lin+i][col+j]!=0) ok=0;
					}
				}
				if (ok==0){
					aux=RodaPeca(aux, 2, 4);
					rotL++;
				}
			}
		}
		if (ok==0){
			inverte++;
			if (inverte!=2){
				aux=criaL(aux);
				aux=invertePeca(aux, 4, 2);
			}
		}
	}
	if(ok){
		pilha[*pospilha].penta='L';
		pilha[*pospilha].rot=rotL;
		pilha[*pospilha].inv=inverte;
		pospilha++;
		if (rotL%2){
			for (i=0;i<4;i++){
				for (j=0;j<2;j++){
					if (aux[i][j]==4)
						mat[lin+i][col+j]=aux[i][j];
				}
			}
		}
		else{
			for (i=0;i<2;i++){
				for (j=0;j<4;j++){
					if (aux[i][j]==4)
						mat[lin+i][col+j]=aux[i][j];
				}
			}
		}
	}		
}

void AllowN (int ** mat, int lin, int col, piece * pilha, int * pospilha, int tamx, int tamy){
/*Função que verifica se a peça N pode ser colocado no tabuleiro*/
	int ok, rotN=0, i, j, inverte=0;
	int ** aux;
	aux=criaN(aux);
	while(inverte<2){
		while(rotN<4){
			ok=1;
			if (rotN%2==0){
				for (i=0;i<4;i++){
					for (j=0;j<2 && ok;j++){
						if (lin+i>tamy || col+j>tamx) ok=0;
						else if (aux[i][j]==5)
							if (mat[lin+i][col+j]!=0) ok=0;
					}
				}
					if (ok==0){
						aux=RodaPeca(aux, 4, 2);
						rotN++;
					}	
			}
			else{
				for (i=0;i<2;i++){
					for (j=0;j<4;j++){
						if (lin+i>tamy || col+j>tamx) ok=0;
						else if (aux[i][j]==5)
							if (mat[lin+i][col+j]!=0) ok=0;
					}
				}
				if (ok==0){
					aux=RodaPeca(aux, 2, 4);
					rotN++;
				}
			}
		}
		if (ok==0){
			inverte++;
			if (inverte!=2){
				aux=criaN(aux);
				aux=invertePeca(aux, 4, 2);
			}
		}
	}
	if(ok){
		pilha[*pospilha].penta='N';
		pilha[*pospilha].rot=rotN;
		pilha[*pospilha].inv=inverte;
		pospilha++;
		if (rotN%2){
			for (i=0;i<4;i++){
				for (j=0;j<2;j++){
					if (aux[i][j]==5)
						mat[lin+i][col+j]=aux[i][j];
				}
			}
		}
		else{
			for (i=0;i<2;i++){
				for (j=0;j<4;j++){
					if (aux[i][j]==5)
						mat[lin+i][col+j]=aux[i][j];
				}
			}
		}
	}		
}

void AllowP (int ** mat, int lin, int col, piece * pilha, int * pospilha, int tamx, int tamy){
/*Função que verifica se a peça P pode ser colocado no tabuleiro*/
	int ok, rotP=0, i, j, inverte=0;
	int ** aux;
	aux=criaP(aux);
	while(inverte<2){
		while(rotP<4){
			ok=1;
			if (rotP%2==0){
				for (i=0;i<3;i++){
					for (j=0;j<2 && ok;j++){
						if (lin+i>tamy || col+j>tamx) ok=0;
						else if (aux[i][j]==6)
							if (mat[lin+i][col+j]!=0) ok=0;
					}
				}
					if (ok==0){
						aux=RodaPeca(aux, 3, 2);
						rotP++;
					}	
			}
			else{
				for (i=0;i<2;i++){
					for (j=0;j<3;j++){
						if (lin+i>tamy || col+j>tamx) ok=0;
						else if (aux[i][j]==6)
							if (mat[lin+i][col+j]!=0) ok=0;
					}
				}
				if (ok==0){
					aux=RodaPeca(aux, 2, 3);
					rotP++;
				}
			}
		}
		if (ok==0){
			inverte++;
			if (inverte!=2){
				aux=criaP(aux);
				aux=invertePeca(aux, 3, 2);
			}
		}
	}
	if(ok){
		pilha[*pospilha].penta='P';
		pilha[*pospilha].rot=rotP;
		pilha[*pospilha].inv=inverte;
		pospilha++;
		if (rotP%2){
			for (i=0;i<3;i++){
				for (j=0;j<2;j++){
					if (aux[i][j]==6)
						mat[lin+i][col+j]=aux[i][j];
				}
			}
		}
		else{
			for (i=0;i<2;i++){
				for (j=0;j<3;j++){
					if (aux[i][j]==6)
						mat[lin+i][col+j]=aux[i][j];
				}
			}
		}
	}		
}

/**********************************************************************************************************************************/
/**********************************************************************************************************************************/

void RemovePiece (int ** mat, int * pilha){}


int main (){
	int i, aux, a, b, posx, posy;
	int ** matriz;
	scanf ("%d %d", &a, &b);
	matriz = bornMatriz (a, b);
	aux=a*b-60;
	i=SumElem(matriz, a, b);
	printf("%d \t %d \n", aux, i);
	if (aux<0) aux=0;
	while (i<aux){
		printf("Digite as coordenadas (x,y) dos pontos onde nao hevera peças:\n");
		scanf ("%d %d", &posx, &posy);
		if(InsertWall (matriz, a, b, posx, posy)==1)
			matriz[posx][posy]=1;
		i=SumElem(matriz, a, b);
	}
	//ResolveTabuleiro(matriz, a, b);
	fiatMatrix (matriz, a,b);
	killMattriz (matriz, a);
	return 0;
}