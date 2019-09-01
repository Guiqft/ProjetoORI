//Definições
#define MAX 1000 //Tamanho maximo para alocação de vetores
char **organizar_lista(char **lista);

//Função que transforma uma string em maiuscula e a retorna
char *maiuscula(char *string)
{
    char *copia = (char *)malloc(sizeof(char) * strlen(string));
    strcpy(copia, string);

    for (int i = 0; i < strlen(string); i++)
        if ((string[i] >= 97) && (string[i] <= 122))
            copia[i] = string[i] - 32;

    return copia;
}

//Função que recebe uma string e a retorna sem espaços duplos
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

    organizar_lista(lista);

    return lista;
}

//Função que transforma os comandos em maiusculos, para comparação no interpretador
char **organizar_lista(char **lista)
{
    int i = 0;
    char c;

    lista[0] = maiuscula(lista[0]);

    if (strcmp(lista[0], "BR") == 0 || strcmp(lista[0], "CI") == 0)
    {
        lista[1] = maiuscula(lista[1]);
    }
    return lista;
}

//Função para checar se o arquivo da tabela ja existe no diretorio './Data/'
//Retorna 1 se a tabela não existir e 0 se existir
int checar_arquivo_existente(char *nome_tabela)
{
    DIR *dir;
    struct dirent *lsdir;

    char *nome_arquivo = (char *)malloc(sizeof(char) * strlen(nome_tabela));
    strcpy(nome_arquivo, nome_tabela);
    strcat(nome_arquivo, ".txt");

    dir = opendir("./Data/");

    while ((lsdir = readdir(dir)) != NULL)
    {
        if (strcmp(maiuscula(lsdir->d_name), maiuscula(nome_arquivo)) == 0)
        {
            free(nome_arquivo);
            return 0;
        }
    }

    closedir(dir);

    free(nome_arquivo);
    return 1;
}