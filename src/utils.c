#include "utils.h"
#define BUFF_SIZE 2000



//Função que transforma uma string em maiuscula e a retorna
char *maiuscula(char *string)
{
    char *copia = (char *) malloc(sizeof(char) * ((int) strlen(string)+1));
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
    char **lista = (char**) malloc(BUFF_SIZE * sizeof(char *));
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

    return lista;
}

char **separar_busca(char *linha)
{
    int posicao = 0;
    char **lista = malloc(BUFF_SIZE * sizeof(char *));
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
//Se o seletor for 0, adiciona apenas o .txt no fim
//Se o seletor for 1, adiciona o "./data/" no começo e o .txt no fim
char *adicionar_diretorio(char *nome_tabela, int seletor)
{
    char *nome_arquivo = malloc(sizeof(char) * BUFF_SIZE);
    strcpy(nome_arquivo, nome_tabela);
    strcat(nome_arquivo, ".txt");

    if (seletor)
    {
        char *diretorio_arquivos = malloc(sizeof(char) * BUFF_SIZE);
        strcpy(diretorio_arquivos, "./data/");
        strcat(diretorio_arquivos, nome_arquivo);

        free(nome_arquivo);
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
    char *aux;
    if(strstr(nome_tabela,"index_files")!=NULL){
        dir = opendir("./data/index_files/");
        aux = strtok(nome_tabela,"/");
        aux = strtok(NULL,".");
        nome_tabela = aux;
    }else{
        dir = opendir("./data/");
    }

    while ((lsdir = readdir(dir)) != NULL){
        aux = maiuscula(lsdir->d_name); //aux == NOME_DOS_ARQUIVOS.TXT do diretório em ./data/
        char *aux2 = adicionar_diretorio(nome_tabela, 0); //aux2 == nomedatabela.txt 
        char *aux3 = maiuscula(aux2);   //NOMEDATABELA.TXT
        if (strcmp(aux, aux3) == 0){//compara NOME_DOS_ARQUIVOS.TXT com NOMEDATABELA.TXT
                                    //os nomes estão em maiusculos para casos em que tenha nomes com maiuscula e minusculas misturadas
            free(aux);
            free(aux2);
            free(aux3);
            return 1;
        }
        free(aux);
        free(aux2);
        free(aux3);
    }

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

//função que verifica se uma tabela está indexada ou não
//a função retorna:
//- 0 se não estiver indexada
//- 1 se estiver indexada por arvore
//- 2 se estiver indexada por hash
int verifica_index(char *nome_tabela){
    FILE *index_file;

    char diretorio[BUFF_SIZE];
    strcpy(diretorio, "./data/");
    strcat(diretorio, nome_tabela);
    strcat(diretorio, ".txt");

    index_file = fopen(diretorio, "r");

    char linha[BUFF_SIZE];
    fgets(linha, BUFF_SIZE, index_file);

    fclose(index_file);
    
    if(strstr(linha, "TRE:"))
        return 1;
    else if (strstr(linha, "HSH:"))
        return 2;
    else
        return 0;
}

char *replace_str(char *str, char *orig, char *rep)
{
  static char buffer[4096];
  char *p;

  if(!(p = strstr(str, orig)))  // Is 'orig' even in 'str'?
    return str;

  strncpy(buffer, str, p-str); // Copy characters from 'str' start to 'orig' st$
  buffer[p-str] = '\0';

  sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));

  return buffer;
}
