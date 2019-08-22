#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_DELIMIT " " //Separador da string com os comandos
#define MAX 100           //Tamanho maximo para alocação de vetores

int lsh_help(char **args);

char *comandos_nomes[] = {"help"};

int (*comandos_funcoes[])(char **) = {&lsh_help};

int comandos_quantidade() { return sizeof(comandos_nomes) / sizeof(char *); }

//Função para ler a string de comandos
char *leitura_linha()
{
    char *entrada = (char *)malloc(sizeof(char) * MAX); //Alocação do vetor

    for (int i = 0; i < MAX; i++)
    {

        if (i == MAX)
        {
            entrada = realloc(entrada, strlen(entrada) * 2); //Se ultrapassar o tamanho, realoca memória
        }

        char c = getc(stdin); //Leitura do caractere atual

        if (c == EOF || c == '\n') //Checa se a string acabou
        {
            entrada[i] = '\0'; //Se acabou, coloca \0 no fim
            return entrada;
        }
        else
        {
            entrada[i] = c; //Copia o caracter atual para o vetor
        }
    }
    free(entrada);
    return entrada;
}

//Função para separar os comandos da string lida
char **divisao_linha(char *linha)
{
    int posicao = 0;
    char **comandos = malloc(MAX * sizeof(char *)); //Matriz para armazenar cada comando em uma linha
    char *token;                                    //Token para dividir a string

    token = strtok(linha, TOKEN_DELIMIT); //Divide a primeira parte da string
    while (token != NULL)
    {
        comandos[posicao] = token; //Copia o token atual para a linha da matriz
        posicao++;

        if (posicao >= MAX) //Se ultrapassar o tamanho máximo da matriz
        {
            MAX *= 2;
            comandos = realloc(comandos, MAX * sizeof(char *)); //Realoca memória na matriz

            if (!comandos)
            {
                fprintf(stderr, "ERRO: falha na alocacao\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, TOKEN_DELIMIT); //Divide as partes subsequentes da string
    }
    comandos[posicao] = NULL; //Coloca NULL na ultima linha depois dos comandos

    return comandos;
}

void loop_comandos()
{
    char *linha;
    char **argumentos;
    int status;

    do
    {
        printf("> ");
        linha = leitura_linha();
        argumentos = divisao_linha(linha);
        status = interpretador(argumentos);
    } while (strcmp(linha, "sair") != 0);

    //status = lsh_excute(args);

    free(linha);
    free(argumentos);
}
int interpretador(char **comandos)
{
    int i, j;

    if (comandos[0] == NULL)
    {
        return 0;
    }

    for (i = 0; i < comandos_quantidade(); i++)
    {
        for (j = 0; i < comandos_quantidade(); j++)
        {
            if (strcmp(comandos[i], comandos_nomes[j]) == 0)
            {
                return (*comandos_funcoes[j])(comandos);
            }
        }
    }
    return 1;
}

int lsh_help(char **args)
{
    int i;
    printf("Stephen Brennan's LSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");
    printf("Use the man command for information on other programs.\n");
    return 1;
}

int main()
{
    loop_comandos();
    return 0;
}
