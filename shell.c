//Definições
#define MAX 1000 //Tamanho maximo para alocação de vetores

//Lista com o nome de todos os comandos
char *comandos_nomes[] = {"ARQUIVO", "CT", "RT", "AT", "LT", "IR", "BRN", "BRU", "AR", "RR", "CIA", "CIH", "GI", "RI", "EB"};

//Função para contagem do número de comandos
int comandos_quantidade() { return sizeof(comandos_nomes) / sizeof(char *); }

//Lista com endereços para os nomes das funções que os comandos executam
int (*comandos_funcoes[15])(char **) = {&operacao_arquivo, &operacao_ct, &operacao_rt, &operacao_at, &operacao_lt, &operacao_ir, &operacao_brN, &operacao_brU, &operacao_ar, &operacao_rr, &operacao_ciA, &operacao_ciH, &operacao_gi, &operacao_ri, &operacao_eb};

//Função para ler a string de comandos
char *leitura_linha()
{
    char *entrada = (char *)malloc(sizeof(char) * MAX); //Alocação do vetor
    int count_espaco = 0;

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
            entrada[i] = maiuscula(c); //Transforma o caractere em maiusculo e copia para o vetor
        }
    }

    free(entrada);
    return entrada;
}

int interpretador(char **comandos)
{
    int i, j;
    int flag = 0;

    if (comandos[0] == NULL)
    {
        return flag;
    }

    for (i = 0; i < comandos_quantidade(); i++)
    {
        if (strcmp(comandos[i], "BR") == 0)
        {
            if (strcmp(comandos[1], "N") == 0)
                return (*comandos_funcoes[5])(comandos);
            else if (strcmp(comandos[1], "U") == 0)
                return (*comandos_funcoes[6])(comandos);
        }
        if (strcmp(comandos[i], "CI") == 0)
        {
            if (strcmp(comandos[1], "A") == 0)
                return (*comandos_funcoes[9])(comandos);
            else if (strcmp(comandos[1], "H") == 0)
                return (*comandos_funcoes[10])(comandos);
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
            printf("Erro de sintaxe! Digite novamente.");
            return flag;
        }
    }
    return 0;
}