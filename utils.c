//Definições
#define MAX 100 //Tamanho maximo para alocação de vetores

char maiuscula(char c)
{

    {

        if ((c >= 65) && (c <= 90))

            c = c + 32;

        else if ((c >= 97) && (c <= 132))

            c = c - 32;
    }
    return c;
}

char *remover_espacos(char str[])
{ //remover espaços do meio
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

char **separar_entrada(char *string, int tam)
{
    char **comandos = malloc(tam * sizeof(char *));
    char *token;
    int posicao = 0;

    token = strtok(string, ";");
    while (token != NULL)
    {
        comandos[posicao] = token;
        posicao++;

        token = strtok(NULL, " ");
    }
    comandos[posicao] = NULL;

    free(comandos);
    return comandos;
}