#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

char* LCS(char *lcs, char *string1, char *string2, int tam1, int tam2){

    //Se os tamanhos n�o batem, saia da fun��o:
    if(tam1 != strlen(string1) || tam2 != strlen(string2)){
        return 0;
    }

    // Calcula o tamanho da maior subsequencia comum

    int i,j=0;

    //Matriz que conter� os valores necess�rios para encontrar a LCS:
    int matriz[tam1+1][tam2+1];

    //Para cada linha e para cada coluna:
    for(i=0; i<tam1+1; i++){
        for(j=0; j<tam2+1; j++){
            //Se o termo est� na primeira linha ou primeira coluna, ele � 0:
            if(i==0 || j==0){
                matriz[i][j] = 0;
            //Se os termos da string s�o iguais, some um ao valor na diagonal superior esquerda:
            }else if(string1[i-1] == string2[j-1]){
                matriz[i][j] = matriz[i-1][j-1] + 1;
            //Sen�o, esse termo � o valor m�ximo entre aquele que est� acima e o que est� � esquerda dele:
            }else{
                if(matriz[i-1][j]> matriz[i][j-1]){
                    matriz[i][j] = matriz[i-1][j];
                }else{
                    matriz[i][j] = matriz[i][j-1];
                }
            }
        }
    }

    /*for(i=0; i<tam1+1; i++){
        for(j=0; j<tam2+1; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }*/

    int index = matriz[i][j];
    lcs = (char*) calloc(index,sizeof(char));

    while(i>0 && j>0){
        if(string1[i-1]==string2[j-1]){
            lcs[index-1] = string1[i-1];
            i--;
            j--;
        }else{
            if(matriz[i-1][j]> matriz[i][j-1]){
                i--;
            }else{
                j--;
            }
        }
    }

    return *lcs;
}

int main(){

    //Cadeias de DNA:
    char dna1[10],dna2[10];
    char *comum;

    //Recebendo a primeira:
    printf("Digite a primeira sequ�ncia de DNA:\n");
    scanf("%s", dna1);

    //Recebendo a segunda:
    printf("Digite a segunda sequ�ncia de DNA:\n");
    scanf("%s", dna2);

    //Aplicando a fun��o LCS e dizendo qual � a LCS entre as duas cadeias:
    printf("A maior subsequencia em comum entre essas duas cadeias de DNA e': %s",LCS(comum[0],dna1[0],dna2[0],10,10));

    return 0;
}
