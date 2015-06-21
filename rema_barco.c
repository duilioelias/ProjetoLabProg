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
