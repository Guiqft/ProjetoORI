//Lista com o nome de todos os comandos
char *comandos_nomes[] = {"ARQUIVO", "CT", "RT", "AT", "LT", "IR", "BRN", "BRU", "AR", "RR", "CIA", "CIH", "GI", "RI", "EB"};

//Função para contagem do número de comandos
int comandos_quantidade() { return sizeof(comandos_nomes) / sizeof(char *); }

//Lista com endereços para os nomes das funções que os comandos executam
int (*comandos_funcoes[15])(char **) = {&operacao_arquivo, &operacao_ct, &operacao_rt, &operacao_at, &operacao_lt, &operacao_ir, &operacao_brN, &operacao_brU, &operacao_ar, &operacao_rr, &operacao_ciA, &operacao_ciH, &operacao_gi, &operacao_ri, &operacao_eb};

//Função para ler a string de comandos
char *leitura_linha()
{
    char *entrada = (char *)malloc(sizeof(char)); //Alocação do vetor
    int i = 0, j = 2;

    while ((entrada[i] = getchar()) != '\n')
    {
        entrada = (char *)realloc(entrada, sizeof(char) * j);
        i++;
        j++;
    }

    entrada[i] = '\0';
    return entrada;
}

int interpretador(char **comandos, int flag)
{
    int i, j;
    flag = 0;

    if (comandos[0] == NULL)
        return flag;

    for (i = 0; i < comandos_quantidade(); i++)
    {
        if (strcmp(comandos[0], "BR") == 0)
        {
            if (strcmp(comandos[1], "N") == 0)
            {
                flag = 1;
                return (*comandos_funcoes[6])(comandos);
            }

            else if (strcmp(comandos[1], "U") == 0)
            {
                flag = 1;
                return (*comandos_funcoes[7])(comandos);
            }
        }
        if (strcmp(comandos[i], "CI") == 0)
        {
            if (strcmp(comandos[1], "A") == 0)
            {
                flag = 1;
                return (*comandos_funcoes[9])(comandos);
            }
            else if (strcmp(comandos[1], "H") == 0)
            {
                flag = 1;
                return (*comandos_funcoes[10])(comandos);
            }
        }

        for (j = 0; j < comandos_quantidade(); j++)
        {
            if (strcmp(comandos[i], comandos_nomes[j]) == 0)
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

//Função base para leitura infinita dos comandos
int loop_comandos()
{
    char *linha;       //Entrada do usuário
    char **argumentos; //Lista dos comandos a serem executados
    int flag = 1;

    do
    {
        printf("\n> ");
        linha = remover_espacos_duplos(leitura_linha()); //Recebe a entrada e retira espacos em excesso
        if (strcmp(linha, "EB") == 0)                    //Usuário fecha o terminal
        {
            return (*comandos_funcoes[15])(argumentos);
            break;
        }

        argumentos = separar_string(linha); //Gerador da lista de comandos
        interpretador(argumentos, flag);    //Interpretador dos comandos
    } while (flag);                         //Loop infinito até que seja cancelado pelo usuário

    free(linha);
    free(argumentos);

    return flag;
}
