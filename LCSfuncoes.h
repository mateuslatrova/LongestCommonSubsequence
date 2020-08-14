#ifndef FUNCOES
#define FUNCOES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Struct que contém o ponteiro de um arquivo, o número de 
linhas e o número de letras em cada linha do arquivo.  */
typedef struct
{
    FILE* fp;
    int linhas;
    int* letras;
}
arquivo;

/* Recebe o ponteiro de um arquivo aberto e retorna um valor
inteiro que é número de linhas desse arquivo.  */
int count_lines(FILE*);

/* Recebe o ponteiro de um arquivo aberto e o seu número de linhas.
Retorna um vetor de inteiros em que cada posição conterá 
o número de letras da respectiva linha do arquivo.  */ 
int* count_characters(FILE*, int);

/* Aloca a matriz de chars onde serão armazenadas strings,
sendo que cada string representa uma linha do arquivo.
Retorna o ponteiro para essa matriz, agora, com espaço alocado.  */
char** alloc_matrix(arquivo);

/* Recebe um vetor de strings, o ponteiro para um arquivo aberto
(que será lido), o número de linhas e de letras em cada linha desse
arquivo. O texto de cada linha do arquivo será armazenado na respectiva
posição do vetor de strings. */
void read_file(char**, FILE*, int, int*);

/* Recebe dois structs arquivo e os vetores de strings que contém
o texto desses arquivos. Calcula, a partir dos dados dessas strings,
a matriz do algoritmo LCS e retorna o ponteiro para essa matriz.  */
int** lcs_matrix(arquivo, arquivo, char**, char**);

/* Recebe os mesmos argumentos da função anterior, além de um ponteiro 
para inteiro que conterá o endereço da variável com o tamanho(número de
linhas) da LCS e da matriz do  algoritmo LCS. Por meio dessa matriz, 
calculamos qual é a LCS entre os dois arquivos, a qual é retornada.  */
char** get_lcs(arquivo, arquivo,char**, char**, int*, int**);

/* Recebe uma matriz de char e o seu número de linhas. 
Libera a memória usada em uma matriz de chars.  */
void free_mat(char**, int);

#endif 
