//-cálculo da LCS entre dois arquivos de texto-

#include "funcoes.h"

int 
count_lines(FILE* fp)
{
    // Auxiliará na contagem de linhas
    int teste = 0;
    
    // Linhas do arquivo
    int linhas = 0;

    // Contando as linhas
    while(teste != EOF)
        {
            teste = fgetc(fp);
            if (teste == '\n'){
                linhas++;
            }
        }
    
    //Voltando o ponteiro do arquivo ao início.
    rewind(fp);

    return linhas;
}

int* 
count_characters(FILE* arquivo,int linhas)
{
    // Auxiliará na contagem das letras.
    int teste;

    // Conterá o número de letras em cada linha.
    int *letras;

    // Alocando o tamanho do vetor(número de linhas).
    letras = (int*) calloc(linhas, sizeof(int));

    // Contando as letras em cada linha
    for(int i = 0; i < linhas ; i++)
        {
            teste = 0;
            while(1)
                {
                teste = fgetc(arquivo);
                letras[i]++;
                if(teste == '\n')
                    {
                        break;
                    }
                }
        }

    //Voltando o ponteiro do arquivo ao início.
    rewind(arquivo);

    return letras;
}

char** 
alloc_matrix(arquivo arq1)
{
   
    char** strings = (char**) malloc((arq1.linhas) * sizeof(char*));

    for(int i = 0; i < arq1.linhas; i++)
        {
            strings[i] = (char*) malloc((arq1.letras[i] + 1) * sizeof(char));
        }

    return strings;
}

void
read_file(char** strings, FILE* fp, int linhas, int* letras)
{
    //Voltando o ponteiro do arquivo ao início.
    rewind(fp);

    //Inserindo cada linha em uma posição do vetor de strings.
    for(int i = 0; i < linhas; i++)
        {
            fgets(strings[i], letras[i] + 1, fp);
        }
}

int** 
lcs_matrix(arquivo arq1, arquivo arq2, char** strings1, char** strings2)
{
    // Matriz do algoritmo LCS.
    int **matriz = (int**) malloc((arq1.linhas + 1) * sizeof(int*));

    // Preenchimento dessa matriz:
    for(int i = 0; i < arq1.linhas + 1; i++)
        {
            matriz[i] = (int*) malloc((arq2.linhas + 1) * sizeof(int));
        }

    for(int i = 0; i < arq1.linhas + 1; i++)
        {
        for(int j = 0; j < arq2.linhas + 1; j++)
            {
                if(i == 0 || j == 0)
                    matriz[i][j] = 0;
                else if(strcmp(strings1[i - 1], strings2[j - 1]) == 0)
                    matriz[i][j] = matriz[i-1][j-1] + 1;
                else
                    {
                        if(matriz[i - 1][j] > matriz[i][j - 1])
                            matriz[i][j] = matriz[i - 1][j];
                        else
                            {
                                matriz[i][j] = matriz[i][j - 1];
                    }
                }
            }
        }

    return matriz;
}

//
char** 
get_lcs(arquivo arq1, arquivo arq2, char** strings1,
        char** strings2, int* linhas_lcs, int** matriz_lcs)
{
    /* i e j serão índices do último elemento da matriz do algoritmo LCS.  */
    int i = arq1.linhas, j = arq2.linhas;
    
    // Tamanho(número de linhas) da LCS:
    *linhas_lcs = matriz_lcs[i][j];
    
    // Ajudará no preenchimento da LCS.
    int auxiliar = *linhas_lcs;

    /* Alocação dinâmica do espaço necessário à LCS e preenchimento da mesma
    por meio da matriz de inteiros do algoritmo LCS.  */

    char** lcs = (char**) malloc((*linhas_lcs) * sizeof(char*));

    while(i > 0 && j > 0 && auxiliar > 0)
        {
            if(strcmp(strings1[i - 1], strings2[j - 1]) == 0 )
                {
                    lcs[auxiliar - 1] = (char*) malloc((arq1.letras[i - 1] + 1) * sizeof(char));
                    lcs[auxiliar - 1] = strings1[i - 1];
                    i--;
                    j--;
                    auxiliar--;
            }else if(matriz_lcs[i - 1][j] > matriz_lcs[i][j - 1])
                {
                i--;
            }else
                {
                    j--;
                }
        }

    // Liberação da memória da matriz de inteiros do algoritmo LCS.
    for(int k = 0; k < arq1.linhas; k++)
        {
            free(matriz_lcs[k]);
        }

    free(matriz_lcs);

    matriz_lcs = NULL;

    return lcs;
}

void 
free_mat(char** strings, int linhas)
{
    
    //Liberação das colunas:
    for(int i = 0; i < linhas; i++)
        {
            free(strings[i]);
        }

    //Liberação das linhas:
    free(strings);

    strings = NULL;
}

int 
main(int argc, char *argv[])
{

    /* Conterão o ponteiro, o número de linhas e de letras em cada linha
    dos dois arquivos que serão passados na linha de comando.  */
    arquivo arquivo1, arquivo2;

    /* strings1 e strings2 carregarão, em cada posição do vetor, o texto
    de cada linha do primeiro e do segundo arquivo, respectivamente.
    lcs conterá, da mesma maneira, a maior subsequência em comum entre os dois arquivos. */
    char **strings1, **strings2, **lcs; 
    
    /* Número de linhas do lcs, número de letras em cada linha
    do lcs e a matriz do algoritmo LCS, respectivamente.  */
    int linhas_lcs, *letras_lcs, **matriz_lcs;
    
    // Mensagem de erro em caso de entrada inválida na linha de comando.
    if(argc > 3)
        {
            printf("ERRO! Entrada inválida(entre com, no máximo, 2 arquivos).");
            return 1;
        }

    // Abertura dos dois arquivos passados na linha de comando.
    arquivo1.fp = fopen(argv[1], "r"); 
    arquivo2.fp = fopen(argv[2], "r");

    // Mensagem de erro caso a abertura fracasse.  
    if(arquivo1.fp == NULL || arquivo2.fp == NULL)
        {
            printf("ERRO NA ABERTURA DOS ARQUIVOS!");
            return 1;
        }

    // Contando as linhas de cada arquivo.
    arquivo1.linhas = count_lines(arquivo1.fp);
    arquivo2.linhas = count_lines(arquivo2.fp);

    // Contando as letras em cada linha do arquivo.
    arquivo1.letras = count_characters(arquivo1.fp, arquivo1.linhas);
    arquivo2.letras = count_characters(arquivo2.fp, arquivo2.linhas);

    // Alocando dinamicamente o espaço necessário ao texto de cada arquivo nas matrizes.
    strings1 = alloc_matrix(arquivo1);
    strings2 = alloc_matrix(arquivo2);

    // Armazenando o texto dos arquivos nos vetores de string(strings1 e strings2).
    read_file(strings1, arquivo1.fp, arquivo1.linhas, arquivo1.letras);
    read_file(strings2, arquivo2.fp, arquivo2.linhas, arquivo2.letras);

    // Fechando os arquivos, pois não serão mais necessários.
    fclose(arquivo1.fp);
    fclose(arquivo2.fp);

    // Calculando a matriz do algoritmo LCS.
    matriz_lcs = lcs_matrix(arquivo1, arquivo2, strings1, strings2);

    // Obtendo a LCS entre os dois arquivos.
    lcs = get_lcs(arquivo1, arquivo2, strings1, strings2, &linhas_lcs, matriz_lcs);

    // Imprimindo a LCS na saída padrão.
    for (int k = 0; k < linhas_lcs; k++)
        {
            printf("%s", lcs[k]);
        }

    // Liberando a memória das matrizes utilizadas.
    free_mat(strings1, arquivo1.linhas);
    free_mat(strings2, arquivo2.linhas);
    free_mat(lcs, linhas_lcs);

    return 0;
}
