//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.c"
#include "comandos.c"
#include "shell.c"

//Função principal
int main()
{
    char *linha;       //Entrada do usuário
    char **argumentos; //Lista dos comandos a serem executados

    while (1) //Loop infinito até que seja cancelado pelo usuário
    {
        printf("> ");
        linha = remover_espacos(leitura_linha()); //Recebe a entrada e retira espacos em excesso
        if (strcmp(linha, "sair") == 0)
            break;
        argumentos = divisao_linha(linha); //Gerador da lista de comandos
        interpretador(argumentos);         //Interpertador dos comandos
    }

    free(linha);
    free(argumentos);
    return 0;
}
