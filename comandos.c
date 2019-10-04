int operacao_ct(char **args)
{
    int flag = 0;
    char *nome_tabela = (char *)malloc(sizeof(char) * strlen(args[1])); //aloca memória no arquivo
    strcpy(nome_tabela, args[1]);

    if (checar_arquivo_existente(nome_tabela)) //verifica se a tabela já existe
    {
        printf("A tabela %s ja existe.\n\n", args[1]);
        return EXIT_FAILURE; //Executa o comando de encerramento
    }

    FILE *tabela; //variavel tabela do tipo arquivo

    if ((tabela = fopen(adicionar_diretorio(nome_tabela, 1), "w")) == NULL)
    {
        printf("Erro na criacao do arquivo da tabela.\nTente novamente\n");
        return flag;
    }
    //abrir tabela a partir do nome dela para escrita

    free(nome_tabela); //liberar memória alocada no arquivo

    int i = 2;
    while (args[i] != NULL) //verificação do tipo de registro válido
    {
        if (strcmp(args[i], "INT") == 0 || strcmp(args[i] , "int") == 0)
        {
            flag = 1;
            fprintf(tabela, "INT:%s|", args[i + 1]);
        }
        else if (strcmp(args[i], "FLT") == 0)
        {
            flag = 1;
            fprintf(tabela, "FLT:%s|", args[i + 1]);
        }
        else if (strcmp(args[i], "STR") == 0)
        {
            flag = 1;
            fprintf(tabela, "STR:%s|", args[i + 1]);
        }
        else if (strcmp(args[i], "BIN") == 0)
        {
            flag = 1;
            fprintf(tabela, "BIN:%s|", args[i + 1]);
        }

        if (!flag)
            printf("Nao foi digitado um tipo de registro valido!\n\n");
        i++;
    }

    printf("Tabela criada!\nNome da tabela: %s.\n\n", args[1]);

    fprintf(tabela, "#\n");
    printf("\n");

    fclose(tabela);
    return flag;
}

int operacao_rt(char **args) //apaga o arquivo relativo da tabela e remove seus metadados da base
{
    char *nome_tabela = (char *)malloc(sizeof(char) * strlen(args[1]));
    strcpy(nome_tabela, args[1]);

    if (checar_arquivo_existente(args[1])) //verifica se existe a tabela, se existe apaga, senão existe mostra uma mensagem
    {
        remove(adicionar_diretorio(nome_tabela, 1)); //remove a tabela do diretorio
        printf("Tabela %s removida.\n\n", args[1]);
    }
    else
        printf("A tabela %s nao existe.\n\n", args[1]);

    free(nome_tabela);
    return 0;
}

int operacao_at(char **args) //apresenta um resumos dos metadados da tabela indicada (arquivos, campos e índices)
{
    char *nome_tabela = (char *)malloc(sizeof(char) * strlen(args[1]));
    strcpy(nome_tabela, args[1]);

    FILE *tabela;

    if ((tabela = fopen(adicionar_diretorio(nome_tabela, 1), "r")) == NULL) //função para abrir tabela
    {
        printf("Erro ao abrir o arquivo da tabela %s.\nTente novamente.\n", args[1]);
        return 0;
    }

    char *linha = (char *)malloc(sizeof(char) * 150); //aloca espaço para resumo dos metadados
    fgets(linha, 150, tabela);

    char **dados = separar_string(linha); //chama funcao para separar a string por espaço, :, ; e |
    int i = 0;

    printf("Resumo da tabela '%s':\n", nome_tabela);
    printf("Registros:\n");

    while (dados[i] != NULL && strcmp(dados[i], "\n") != 0)
    {
        if (i % 2 == 0)
            printf("-Tipo %s, nome: '%s'.\n", dados[i], dados[i + 1]);
        i++;
    }

    fclose(tabela);
    free(nome_tabela);
    free(linha);
    return 0;
}

int operacao_lt(char **args) //lista o nome de todas as tabelas existentes na base
{
    DIR *dir;  //diretorio
    struct dirent *lsdir;
    char *token;
    int cont = 0;

    if(numero_tabelas()==0){  //Se o diretório estiver vazio
        printf("Nao existem tabelas na base de dados.\n");
        return 0;
    }

    dir = opendir("./Data/"); //abrir diretorio

    printf("Tabelas existentes na base:\n");
    while ((lsdir = readdir(dir)) != NULL){ //Readdir = Lê os campos do manipulador do diretório
                                            //Os nomes de arquivos são retornados na ordem informada pelo sistema de arquivos.
        if (cont >= 2){  //Retira as 2 primeiras impressões "nulas" do diretório
            token = strtok(lsdir->d_name, ".");
            printf("-Tabela %d: %s\n", cont -1 , token); //lista as tabelas existentes no diretorio
        }
        cont++;
    }

    printf("\n\n");

    closedir(dir);
    return 0;
}

int operacao_ir(char **args) //insere o registro na tabela, usando a politica de inserção adequada
{
    char *nome_tabela = (char *)malloc(sizeof(char) * strlen(args[1]));
    strcpy(nome_tabela, args[1]);
    //Realiza a cópia do conteúdo de uma variável a outra
    FILE *tabela;
    FILE *aux;
    char *linha = (char *)malloc(sizeof(char) * 150);

    if ((aux = fopen(adicionar_diretorio(nome_tabela, 1), "r")) == NULL)
    {
        printf("Erro ao abrir o arquivo da tabela %s.\nTente novamente.\n", args[1]);
        return 0;
    }

    fgets(linha, 150, aux);
    //Lê do fluxo para a cadeia de caracteres string até a quantidade de caracteres (tamanho - 1) ser lida
    char **dados = separar_string(linha);
    int i = 0;
    int j = 2;
    while (dados[i] != NULL && strcmp(dados[i], "\n") != 0)
    {
        if (strcmp(dados[i], "INT") == 0)
        {
            if (verifica_int(args[j]) == 1)
            {
                printf("Argumento invalido em campo INT\n");
                return 0;
            }
        }
        else if (strcmp(dados[i], "FLT") == 0)
        {
            if (verifica_flt(args[j]) == 1)
            {
                printf("Argumento invalido em campo FLOAT\n");
                return 0;
            }
        }
        else if (strcmp(dados[i], "STR") == 0)
        {
            if (verifica_str(args[j]) == 1)
            {
                printf("Nao use '#' ou '|'\n");
                return 0;
            }
        }
        else if (strcmp(dados[i], "BIN") == 0)
        {
            if (verifica_str(args[j]) == 1)
            {
                printf("Nao use '#' ou '|'\n");
                return 0;
            }
            if (checar_arquivo_existente(args[j]) == 0)
            {
              printf("Arquivo BIN nao existe, um sera criado (vazio)\nCaso voce queira usar um arquivo especifico, coloque-o na pasta data");
              FILE *arquivo; //variavel tabela do tipo arquivo

              if ((arquivo = fopen(adicionar_diretorio(args[j], 1), "wb")) == NULL)
              {
                  printf("Erro na criacao do arquivo binario");
                  return 0;
              }
              fclose(arquivo);
              free(tabela);
              return 0;
            }
        }
        i = i + 2;
        j++;
    }

    fclose(aux);
    if ((tabela = fopen(adicionar_diretorio(nome_tabela, 1), "a")) == NULL)
    {
        printf("Erro ao abrir o arquivo da tabela %s.\nTente novamente.\n", args[1]);
        return 0;
    }

    i = 2;
    while (args[i] != NULL)
    {
        fprintf(tabela, "%s|", args[i]);
        i++;
    }
    fprintf(tabela, "%s\n", "#");

    fclose(tabela);
    free(nome_tabela);
    free(dados);
    free(linha);
    return 0;
}
int operacao_brN(char **args) //Busca na tabela TODOS os registros que satisfaçam a busca
{
    char *nome_tabela = (char *)malloc(sizeof(char) * strlen(args[2]));
    strcpy(nome_tabela, args[2]);
    //Realiza a cópia do conteúdo de uma variável a outra

    FILE *tabela;

    if ((tabela = fopen(adicionar_diretorio(nome_tabela, 1), "r")) == NULL)
    {
        printf("Erro ao abrir o arquivo da tabela %s.\nTente novamente.\n", args[2]);
        return 0;
    }

    char *linha = (char *)malloc(sizeof(char) * 150);
    fgets(linha, 150, tabela);
    //Lê do fluxo para a cadeia de caracteres string até a quantidade de caracteres (tamanho - 1) ser lida
    char **dados = separar_string(linha);
    int i = 1, flag = 0;

    char *nome_arquivo = (char *)malloc(sizeof(char) * strlen(nome_tabela));
    strcpy(nome_arquivo, nome_tabela); //Realiza a cópia do conteúdo de uma variável a outra

    strcat(nome_arquivo, "_Busca"); //Concatenar strings

    while (dados[i] != NULL && strcmp(dados[i], "\n") != 0) //Comparar strings
    {
        if (strcmp(args[3], dados[i]) == 0) //Comparar strings
        {
            flag = 1;
            if (checar_arquivo_existente(nome_arquivo)) //checar se o arquivo da tabela ja existe no diretorio
                remove(adicionar_diretorio(nome_arquivo, 1));
        }
        i = i + 2;
    }

    if (!flag)
        printf("Não existe o campo %s nesta tabela, tente novamente!\n\n", args[3]);

    for(i=0;i<strlen(*dados);i++){
        free(dados[i]);
    }
    free(dados);

    flag = 0;

    while (fgets(linha, 150, tabela) != NULL)
    { //Enquanto não chegou no fim do arquivo
        char *linha_achada = (char *)malloc(sizeof(char) * 150);
        strcpy(linha_achada, linha);
        char **dados = separar_busca(linha);
        i = 0;
        while (dados[i] != NULL && strcmp(dados[i], "#") != 0)
        { //Enquanto não chegou no fim da linha
            if (strcmp(args[4], dados[i]) == 0)
            {
                flag = 1;
                FILE *tabela2;
                if ((tabela2 = fopen(adicionar_diretorio(nome_arquivo, 1), "a")) == NULL)
                {
                    printf("Erro na criacao do arquivo da tabela.\nTente novamente\n\n");
                    return 0;
                }
                else
                {
                    fprintf(tabela2, "%s", linha_achada);
                }
                fclose(tabela2);
                free(linha_achada);
            }
            i++;
        }
        for(i=0;i<strlen(*dados);i++){
            free(dados[i]);
    }
    
    free(dados);
    }
    if (flag == 0)
    {
        printf("Nao foi encontrado nenhum dado referente a pesquisa.\n\n");
    }

    fclose(tabela);
    free(nome_arquivo);
    free(nome_tabela);
    free(linha);
    return 0;
}
int operacao_brU(char **args) //Busca na tabela pelo primeiro registro que satisfaça a busca
{
    char *nome_tabela = (char *)malloc(sizeof(char) * strlen(args[2]));
    strcpy(nome_tabela, args[2]);

    FILE *tabela;

    if ((tabela = fopen(adicionar_diretorio(nome_tabela, 1), "r")) == NULL)
    {
        printf("Erro ao abrir o arquivo da tabela %s.\nTente novamente.\n", args[2]);
        return 0;
    }

    char *linha = (char *)malloc(sizeof(char) * 150);
    fgets(linha, 150, tabela);
    char **dados = separar_string(linha);
    int i = 1, flag = 0;

    char *nome_arquivo = (char *)malloc(sizeof(char) * strlen(nome_tabela));
    strcpy(nome_arquivo, nome_tabela);
    strcat(nome_arquivo, "_Busca");

    while (dados[i] != NULL && strcmp(dados[i], "\n") != 0)
    {
        if (strcmp(args[3], dados[i]) == 0)
        {
            flag = 1;
            if (checar_arquivo_existente(nome_arquivo))
                remove(adicionar_diretorio(nome_arquivo, 1));
        }
        i = i + 2;
    }

    if (!flag)
        printf("Não existe o campo %s nesta tabela, tente novamente!\n\n", args[2]);

    free(dados);
    flag = 0;

    while ((fgets(linha, 150, tabela) != NULL) && (flag == 0))
    { //Enquanto não chegou no fim do arquivo
        char *linha_achada = (char *)malloc(sizeof(char) * 150);
        strcpy(linha_achada, linha);
        char **dados = separar_busca(linha);
        i = 0;
        while (dados[i] != NULL && strcmp(dados[i], "#") != 0)
        { //Enquanto não chegou no fim da linha
            if (strcmp(args[4], dados[i]) == 0)
            {
                flag = 1;
                FILE *tabela2;
                if ((tabela2 = fopen(adicionar_diretorio(nome_arquivo, 1), "a")) == NULL)
                {
                    return 0;
                }
                else
                {
                    fprintf(tabela2, "%s", linha_achada);
                }
                fclose(tabela2);
                free(linha_achada);
            }
            i++;
        }
    }
    if (flag == 0)
    {
        printf("Nao foi encontrado nenhum dado referente a pesquisa.\n\n");
    }

    fclose(tabela);
    free(nome_arquivo);
    //free(dados);
    free(nome_tabela);
    free(linha);
    return 0;
}
int operacao_ar(char **args) //Apresenta na tabela os valores dos registros retornados pela ultima busca
{
    char *nome_tabela = (char *)malloc(sizeof(char) * strlen(args[1]));
    strcpy(nome_tabela, args[1]);
    strcat(nome_tabela, "_Busca");

    FILE *tabela;

    if ((tabela = fopen(adicionar_diretorio(nome_tabela, 1), "r")) == NULL)
    {
        printf("Erro ao abrir o arquivo da tabela %s.\nTente novamente.\n\n", args[1]);
        return 0;
    }

    char *linha = (char *)malloc(sizeof(char) * 150);
    int i = 0;

    printf("Resultado(s) da(s) ultima busca: \n");

    while (fgets(linha, 150, tabela) != NULL)
    {
        char **dados = separar_busca(linha);
        i = 0;
        printf("Registro %d: ", i+1);
        while (dados[i] != NULL && strcmp(dados[i], "#\n") != 0)
        {
            printf("%s|", dados[i]);
            i++;
        }
        free(dados);
    }

    printf("\n");

    fclose(tabela);
    free(nome_tabela);
    free(linha);
    return 0;
}
int operacao_rr(char **args)
{
    FILE *tabela_busca;
    char *nome_tabela_busca;

    nome_tabela_busca = malloc(sizeof(char) * (strlen(args[1]) + 10));
    strcpy(nome_tabela_busca, args[1]); //Copiar strings
    strcat(nome_tabela_busca, "_Busca");//Concatenar strings

    if ((tabela_busca = fopen(adicionar_diretorio(nome_tabela_busca, 1), "r")) == NULL) //abrir tabela para leitura
    {
        printf("Erro ao abrir o arquivo da tabela %s.\nTente novamente.\n\n", args[1]);
        return 0;
    }

    char linha_busca[150];
    char linha_dados[150];
    char *token;
    char *nome_tabela_dados;
    FILE *tabela_dados;

    nome_tabela_dados = malloc(sizeof(char) * strlen(args[1]));
    strcpy(nome_tabela_dados, args[1]); //copiar strings
    
    if ((tabela_dados = fopen(adicionar_diretorio(nome_tabela_dados, 1), "r+")) == NULL) //abrir tabela para leitura e escrita no fim do arquivo
    {
        printf("Erro ao abrir o arquivo da tabela %s.\nTente novamente.\n\n", args[1]);
        return 0;
    }
    int linha_atual;
    
    while(fgets(linha_busca, 150, tabela_busca) != NULL)
        linha_atual = 0; //ftell = Retorna o valor atual da posição no arquivo
        while(fgets(linha_dados, 150, tabela_dados) != NULL){
            //token = strtok(linha_dados, "\n"); fgets já pega uma linha inteira
            //printf("comparando %s == %s\n", linha_busca, linha_dados);
            if(strcmp(linha_busca, linha_dados) == 0){
                int retorna = ftell (tabela_dados);  //salva o final da linha
                fseek(tabela_dados, linha_atual, SEEK_SET);
                int tam = retorna-linha_atual-1;
                fprintf(tabela_dados, "@%d@", tam);
                fseek (tabela_dados, retorna-3, SEEK_SET); //retorna pro final da linha 
            }
            linha_atual = ftell (tabela_dados); //ftell = Retorna o valor atual da posição no arquivo

        }
            

    fclose(tabela_dados);
    fclose(tabela_busca);
    free(nome_tabela_busca);
    free(nome_tabela_dados);
    return 0;
}

int operacao_ciA(char **args)
{
    printf("Cria um indice estruturado como arvore de multiplos caminhos para a tabela,\n ");
    printf("usando chave como chave de busca, atualizando os metadados.\n\n");
    return 0;
}
int operacao_ciH(char **args)
{
    printf("Cria um indice usando hashing para a tabela, usando chave como chave de busca, atualizando os metadados.\n\n");
    return 0;
}
int operacao_ri(char **args)
{
    printf("Remove o indice relativo a chave, atualizando os metadados e apagando as estruturas envolvidas.\n\n");
    return 0;
}
int operacao_gi(char **args)
{
    printf("Gera novamente o indice de tabela referente a chave, partindo do zero.\n\n");
    return 0;
}
int operacao_eb(char **args)
{
    printf("Encerra a interpretacao e a execucao do programa.\n\n");
    return 0;
}
int operacao_arquivo(char **args)
{
    FILE *arq;
    char *nome_arquivo = args[1];
    char linha[150];
    char *resultado;
    char **argumentos;
    int flag = 0;

    // Abre o arquivo de comandos
    arq = fopen(nome_arquivo, "rt");
    if (arq == NULL) // Se houve erro na abertura
    {
        printf("Problemas na abertura do arquivo '%s'. Tente novamente.\n\n", nome_arquivo);
        return flag;
    }

    while (!feof(arq))
    {
        // Lê uma linha (inclusive com o '\n')
        resultado = remover_espacos_duplos(strtok(fgets(linha, 150, arq), "\n")); // o 'fgets' lê até 150 caracteres ou até o '\n'
        if (resultado)
        {
            if (strcmp(resultado, "eb") == 0 || strcmp(resultado, "EB") == 0)
            {
                exit(0);
            }
            argumentos = separar_string(linha); //Gerador da lista de comandos
            interpretador(argumentos);    //Interpretador dos comandos
        }
    }

    fclose(arq);
    return flag;
}
