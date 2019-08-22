#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TOKEN_DELIMIT " "
#define MAX 100

int lsh_help(char **args);

char *comandos_nomes[] = {"help"};

int (*comandos_funcoes[])(char **) = {&lsh_help};

int comandos_quantidade() { return sizeof(comandos_nomes) / sizeof(char *); }

char *leitura_linha()
{
    char *entrada = (char *)malloc(sizeof(char) * MAX);

    for (int i = 0; i < MAX; i++)
    {

        if (i == MAX)
        {
            entrada = realloc(entrada, strlen(entrada) * 2);
        }

        char c = getc(stdin);

        if (c == EOF || c == '\n')
        {
            entrada[i] = '\0';
            return entrada;
        }
        else
        {
            entrada[i] = c;
        }
    }
    free(entrada);
    return entrada;
}
char **divisao_linha(char *linha)
{
    int buf_size = 64, posicao = 0;
    char **comandos = malloc(buf_size * sizeof(char *));
    char *token;

    token = strtok(linha, TOKEN_DELIMIT);
    while (token != NULL)
    {
        comandos[posicao] = token;
        posicao++;

        if (posicao >= buf_size)
        {
            buf_size += 64;
            comandos = realloc(comandos, buf_size * sizeof(char *));

            if (!comandos)
            {
                fprintf(stderr, "ERRO: falha na alocacao\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, TOKEN_DELIMIT);
    }
    comandos[posicao] = NULL;

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
