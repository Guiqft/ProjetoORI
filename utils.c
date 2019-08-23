//Definições
#define MAX 1000 //Tamanho maximo para alocação de vetores

char maiuscula(char c)
{

    {
        if ((c >= 97) && (c <= 132))

            c = c - 32;
    }
    return c;
}

char *remover_espacos_duplos(char str[])
{
    int j = 1;
    for (int i = 1; str[i]; i++)
    {
        if (str[i] != ' ' || (str[i - 1] != ' '))
        {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';

    return str;
}

//Função para separar os comandos da string lida
char **separar_string(char *linha)
{
    int posicao = 0;
    char **lista = malloc(MAX * sizeof(char *));
    char *token;

    token = strtok(linha, " ;:");
    while (token != NULL)
    {
        lista[posicao] = token;
        posicao++;

        token = strtok(NULL, " ;:");
    }
    lista[posicao] = NULL;

    return lista;
}