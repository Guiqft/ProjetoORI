#include "utils.h"

//Função que transforma uma string em maiuscula e a retorna
char *maiuscula(char *string)
{
    char *copia = (char *) malloc(sizeof(char) * (int) strlen(string));
    strcpy(copia, string);

    for (int i = 0; i < (int) strlen(string); i++)
        if ((string[i] >= 97) && (string[i] <= 122))
            copia[i] = string[i] - 32;

    return copia;
}
//Função que verifica se é inteiro
int verifica_int(char *string)
{
    for (int i = 0; i < (int) strlen(string); i++)
    {
        if ((string[i] < 48) || (string[i] > 57))
            return 1;
    }
    return 0;
}
//Função que verifica se é float
int verifica_flt(char *string)
{
    int j = 0;
    for (int i = 0; i < (int) strlen(string); i++)
    {
        if ((string[i] < 48) || (string[i] > 57))
        {
            if (string[i] != 46)
                return 1;
            else
                j++;
        }
        if (j > 1)
            return 1;
    }
    return 0;
}
//Função que verifica se é uma string
int verifica_str(char *string)
{
    for (int i = 0; i < (int) strlen(string); i++)
    {
        if (string[i] == 35 || string[i] == 124)
            return 1;
    }
    return 0;
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

//Função para separar os comandos da string lida
//Os separadores são: ' ', ';', ':' e '|'
char **separar_string(char *linha)
{
    int posicao = 0;
    char **lista = malloc(150 * sizeof(char *));
    char *token;
    int cont = 0;
    
    token = strtok(linha, " ;:|");
    //divide uma string em strings menores (tokens), com cada token sendo delimitado por
    //uma caracter definida
    while (token != NULL)
    {
        lista[posicao] = token;
        posicao++;
        if (cont < 2)
            token = strtok(NULL, " ;:|");
        else
            token = strtok(NULL, ";:|");
        cont++;
    }
    lista[posicao] = NULL;

    //organizar_lista(lista); //transforma todos os comandos em maiusculo para comparação
    //no interpretador

    return lista;
}

char **separar_busca(char *linha)
{
    int posicao = 0;
    char **lista = malloc(150 * sizeof(char *));
    char *token;
    int cont = 0;

    token = strtok(linha, ";:|");
    //divide uma string em strings menores (tokens), com cada token sendo delimitado por
    //uma caracter definida (;,:,|)
    while (token != NULL)
    {
        lista[posicao] = token;
        posicao++;
        token = strtok(NULL, ";:|");
        cont++;
    }
    lista[posicao] = NULL;

    //organizar_lista(lista);

    return lista;
}

//Função para concatenar o diretório das tabelas em uma string com o nome da tabela
//Se o seletor for 1, adiciona o "./data/" no começo e o .txt no fim
//Se o seletor for 0, adiciona apenas o .txt no fim
char *adicionar_diretorio(char *nome_tabela, int seletor)
{
    char *nome_arquivo = (char *)malloc(sizeof(char) * ((int) strlen(nome_tabela) + 10));
    strcpy(nome_arquivo, nome_tabela);
    strcat(nome_arquivo, ".txt");

    if (seletor)
    {
        char *diretorio_arquivos = (char *)malloc(sizeof(char) * ((int) strlen(nome_arquivo + 10)));
        strcpy(diretorio_arquivos, "./data/");
        strcat(diretorio_arquivos, nome_arquivo);
        return diretorio_arquivos;
    }
    return nome_arquivo;
}

//Função para checar se o arquivo da tabela ja existe no diretorio './data/'
//Retorna 0 se a tabela não existir e 1 se existir
int checar_arquivo_existente(char *nome_tabela)
{
    DIR *dir;
    struct dirent *lsdir;

    dir = opendir("./data/");

    while ((lsdir = readdir(dir)) != NULL)
        if (strcmp(maiuscula(lsdir->d_name), maiuscula(adicionar_diretorio(nome_tabela, 0))) == 0)
            return 1;

    closedir(dir);
    return 0;
}

//Função para contagem do número de tabelas no diretório './data/'
int numero_tabelas(){
    DIR *dir;
    struct dirent *lsdir;
    int cont = -2; //Retira as 2 "contagens nulas" do inicio do diretório

    dir = opendir("./data/");

    while ((lsdir = readdir(dir)) != NULL)
        cont ++;

    closedir(dir);
    return cont;
}

//Recebe uma lista de strings e retorna uma string só com todas concatenadas
//A string retornada terá o formato xxx:xxxx|xxx:xxxx|#
char* juntar_string(char **string_dividida){
    char *string;
    int cont = 0, tamanho_atual = 0;

    tamanho_atual = (int) strlen(string_dividida[0]) + 1;
    string = (char *) malloc (sizeof(char) * tamanho_atual);

    while(strcmp(string_dividida[cont++], "\n") != 0){
        tamanho_atual += (int) strlen(string_dividida[cont]) + 1;
        string  = (char *) realloc(string, sizeof(char) * tamanho_atual);

        strcat(string, string_dividida[cont]);
        if(cont % 2 == 0)
            strcat(string, ":");
        else strcat(string,"|");
    }
    strcat(string,"#");
    
    return string;
}
