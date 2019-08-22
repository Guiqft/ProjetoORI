//Definições
#define MAX 1000 //Tamanho maximo para alocação de vetores

//Lista com o nome de todos os comandos
char *comandos_nomes[] = {"CT", "RT", "AT", "LT", "RI", "BRN", "BRU", "AR", "RR", "CIA", "CIH", "GI"};

//Função para contagem do número de comandos
int comandos_quantidade() { return sizeof(comandos_nomes) / sizeof(char *); }

//Lista com endereços para os nomes das funções que os comandos executam
int (*comandos_funcoes[12])(char **) = {&operacao_ct, &operacao_rt, &operacao_at, &operacao_lt, &operacao_ri, &operacao_brN, &operacao_brU, &operacao_ar, &operacao_rr, &operacao_ciA, &operacao_ciH, &operacao_gi};

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
            entrada[i] = maiuscula(c); //Transforma o caractere em maiusculo e copia para o vetor
        }
    }

    free(entrada);
    return entrada;
}

int interpretador(char **comandos)
{
    int i;

    if (comandos[0] == NULL)
    {
        return 0;
    }

    for (i = 0; i < comandos_quantidade(); i++)
    {
        if (strcmp(comandos[i], comandos_nomes[i]) == 0)
        {
            return (*comandos_funcoes[i])(comandos);
        }
        else
        {
            printf("Erro de sintaxe! Digite novamente.");
            return 0;
        }
    }
    return 0;
}