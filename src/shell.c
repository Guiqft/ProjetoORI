#include "shell.h"
#include "comandos.h"
#include "utils.h"

//Lista com o nome de todos os comandos
char *comandos_nomes_maiusculos[] = {"ARQUIVO", "CT", "RT", "AT", "LT", "IR", "BRN", "BRU", "AR", "RR", "CIA", "CIH", "GI", "RI", "EB"};
char *comandos_nomes[] = {"arquivo", "ct", "rt", "at", "lt", "ir", "brn", "bru", "ar", "rr", "cia", "cih", "gi", "ri", "eb"};
//Função para contagem do número de comandos
int comandos_quantidade() { return sizeof(comandos_nomes) / sizeof(char *); }

//Lista com endereços para os nomes das funções que os comandos executam
int (*comandos_funcoes[15])(char **) = {&operacao_arquivo, &operacao_ct, &operacao_rt, &operacao_at, &operacao_lt, &operacao_ir, &operacao_brN, &operacao_brU, &operacao_ar, &operacao_rr, &operacao_ciA, &operacao_ciH, &operacao_gi, &operacao_ri, &operacao_eb};

//Função para ler a string de comandos
char *leitura_linha()
{
    char *entrada = malloc(sizeof(char));
    int i = 0, j = 2;

    while ((entrada[i] = getchar()) != '\n')
    {
        entrada = realloc(entrada, sizeof(char)*(i+2));
        i++;
        j++;
    }

    entrada[i] = '\0';
    return entrada;
}

int interpretador(char **comandos)
{
    int i, j;
    int flag = 0;

    if (comandos[0] == NULL)
        return EXIT_FAILURE;
    else if (strcmp(comandos[0],"eb") == 0 || strcmp(comandos[0],"EB") == 0)
        exit(0);

    for (i = 0; i < comandos_quantidade(); i++)
    {
        if (strcmp(comandos[0], "BR") == 0 || strcmp(comandos[0], "br") == 0)
        {
            if (strcmp(comandos[1], "N") == 0 || strcmp(comandos[1], "n") == 0)
            {
                flag = 1;
                return (*comandos_funcoes[6])(comandos);
            }

            else if (strcmp(comandos[1], "U") == 0 || strcmp(comandos[1], "u") == 0)
            {
                flag = 1;
                return (*comandos_funcoes[7])(comandos);
            }
        }
        if (strcmp(comandos[i], "CI") == 0 || strcmp(comandos[i], "ci") == 0)
        {
            if (strcmp(comandos[1], "A") == 0 || strcmp(comandos[1], "a") == 0)
            {
                flag = 1;
                return (*comandos_funcoes[10])(comandos);
            }
            else if (strcmp(comandos[1], "H") == 0 || strcmp(comandos[1], "h") == 0)
            {
                flag = 1;
                return (*comandos_funcoes[11])(comandos);
            }
        }

        for (j = 0; j < comandos_quantidade(); j++)
        {
            if (strcmp(comandos[i], comandos_nomes[j]) == 0 || strcmp(comandos[i], comandos_nomes_maiusculos[j]) == 0)
            {
                flag = 1;
                return (*comandos_funcoes[j])(comandos);
            }
        }

        if (!flag)
        {
            printf("Erro de sintaxe! Digite novamente.\n\n");
            return flag;
        }
    }
}

//Função base para leitura dos comandos de forma contínua
void loop_comandos()
{
    char *linha;       //Entrada do usuário
    char **argumentos; //Lista dos comandos a serem executados
    int i = 0;         //Marcador de posição

    printf("> ");
    while(linha = remover_espacos_duplos(leitura_linha())){         //Recebe a entrada e retira espacos em excesso
        if (strcmp(linha, "eb") == 0 || strcmp(linha, "EB") == 0)   //Se o usuário digitar "eb", fecha o shell
            exit(0);
        argumentos = separar_string(linha); //Gerador da lista de comandos
        interpretador(argumentos);          //Interpretador dos comandos
        free(argumentos);

        printf("\n> ");
    };
}
