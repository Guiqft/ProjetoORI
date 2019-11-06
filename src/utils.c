#include "utils.h"



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
    char **lista = (char**) malloc(150 * sizeof(char *));
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
//Se o seletor for 0, adiciona apenas o .txt no fim
//Se o seletor for 1, adiciona o "./data/" no começo e o .txt no fim
char *adicionar_diretorio(char *nome_tabela, int seletor)
{
    char *nome_arquivo = (char *)malloc(sizeof(char) * ((int) strlen(nome_tabela) + 15));
    strcpy(nome_arquivo, nome_tabela);
    strcat(nome_arquivo, ".txt");

    if (seletor)
    {
        char *diretorio_arquivos = (char *)malloc(sizeof(char) * ((int) strlen(nome_arquivo)+15));
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
int verificaIndex(char *nome_tabela){
    FILE *index_file;
    char *diretorio;
    diretorio = malloc(sizeof(char) * (strlen(nome_tabela) + 24));
    strcpy(diretorio,"index_files/");
    strcat(diretorio,nome_tabela);
    strcat(diretorio,"_index"); //Nesse momento, diretorio[] = "index_files/nometabela_index_tree"

    char *aux = adicionar_diretorio(diretorio, 1);
    if ((index_file = fopen(aux, "r")) != NULL){ //checar o arquivo de indexacao
        free(diretorio);
        char linha[150];
        fgets(linha,150,index_file);
        if(strstr(linha, "tree") != NULL){
            free(aux);
            return 1;
        }
        else if(strstr(linha,"hash") != NULL){

            free(aux);
            return 2;
        }
    }
    else{
        free(diretorio);
        return 0;
    }
}

//Função que recebe o arquivo estrutural da árvore e retorna um ponteiro para a árvore instanciada
//cranbtree_t* mount_tree(char* nome_tabela){
cranbtree_t * mount_tree(char* nome_tabela){
    char* name_index_file = (char *) malloc(sizeof(char) * ((int) strlen(nome_tabela)+100));
    char aux[13] = "index_files/";
    strcpy(name_index_file, aux);
    strcat(name_index_file, nome_tabela);
    strcat(name_index_file, "_index");

    FILE* tabela;

    if ((tabela = fopen(adicionar_diretorio(name_index_file, 1), "r")) == NULL)
    {
        printf("Erro na abertura do arquivo de indice.\nTente novamente\n\n");
    }

    char linha[150];
    cranbtree_t *tree_index = cbt_create(3); //Cria a arvore permitindo até 3 chaves por nó (é o minimo permitido pela biblioteca)

    fgets(linha, 150, tabela); //pega a linha de cabeçalho e descarta
    while(fgets(linha, 150, tabela) != NULL) {
        int chave = atoi(strtok(linha,"|"));
        int aux = atoi(strtok(NULL, "|"));
        cbt_insert(tree_index, chave, &aux);    //Insere na arvore o registro na arvore com o inteiro como chave
                                                        //e a localização do registro como conteúdo
    }

    printTree(tree_index);
    fclose(tabela);
    return tree_index;
}

//Função que recebe o arquivo estrutural e retorna um ponteiro para a hash instanciada
map_int_t mount_hash(char* nome_tabela){
    char* name_index_file = (char *) malloc(sizeof(char) * ((int) strlen(nome_tabela)+100));
    char p[13] = "index_files/";
    strcpy(name_index_file, p);
    strcat(name_index_file, nome_tabela);
    strcat(name_index_file, "_index");

    FILE* tabela;

    char* aux = adicionar_diretorio(name_index_file, 1);
    if ((tabela = fopen(aux, "r")) == NULL)
    {
        printf("Erro na abertura do arquivo de indice.\nTente novamente\n\n");
    }
    free(aux);

    char linha[150];
    map_int_t m;
    map_init(&m);

    fgets(linha, 150, tabela); //pega a linha de cabeçalho e descarta
    while(fgets(linha, 150, tabela) != NULL) {
        char *chave = strtok(linha,"|");
        int aux = atoi(strtok(NULL, "|"));
        map_set(&m, chave, aux);    //Insere na arvore o registro na arvore com o inteiro como chave
                                                        //e a localização do registro como conteúdo
    }

    free(name_index_file);
    fclose(tabela);
    return m;
}