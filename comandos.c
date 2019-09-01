int interpretador(char **comandos, int flag);
int (*comandos_funcoes[])(char **);

int operacao_ct(char **args)
{
    int flag = 0;
    char *nome_tabela = (char *)malloc(sizeof(char) * strlen(args[1]));
    strcpy(nome_tabela, args[1]);

    if (checar_arquivo_existente(nome_tabela))
    {
        printf("A tabela %s ja existe.\n\n", args[1]);
        return (*comandos_funcoes[15])(args);
    }

    FILE *tabela;

    if ((tabela = fopen(adicionar_diretorio(nome_tabela, 1), "w")) == NULL)
    {
        printf("Erro na criacao do arquivo da tabela.\nTente novamente\n");
        return flag;
    }

    free(nome_tabela);

    printf("Tabela criada!\nNome da tabela: %s.\n\n", args[1]);

    int i = 2;
    while (args[i] != NULL)
    {
        if (strcmp(args[i], "INT") == 0)
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

    fprintf(tabela, "\n");
    printf("\n");

    fclose(tabela);
    return flag;
}

int operacao_rt(char **args)
{
    char *nome_tabela = (char *)malloc(sizeof(char) * strlen(args[1]));
    strcpy(nome_tabela, args[1]);

    if (checar_arquivo_existente(args[1]))
    {
        remove(adicionar_diretorio(nome_tabela, 1));
        printf("Tabela %s removida.\n\n", args[1]);
    }
    else
        printf("A tabela %s nao existe.\n\n", args[1]);

    free(nome_tabela);
    return 0;
}

int operacao_at(char **args)
{
    char *nome_tabela = (char *)malloc(sizeof(char) * strlen(args[1]));
    strcpy(nome_tabela, args[1]);

    FILE *tabela;

    if ((tabela = fopen(adicionar_diretorio(nome_tabela, 1), "r")) == NULL)
    {
        printf("Erro ao abrir o arquivo da tabela %s.\nTente novamente.\n", args[1]);
        return 0;
    }

    char *linha = (char *)malloc(sizeof(char) * 150);
    fgets(linha, 150, tabela);

    char **dados = separar_string(linha);
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

int operacao_lt(char **args)
{
    DIR *dir;
    struct dirent *lsdir;
    char *token;
    int cont = 0;

    dir = opendir("./Data/");

    printf("Tabelas existentes na base:\n");
    while ((lsdir = readdir(dir)) != NULL)
    {
        if (cont >= 2)
        {
            token = strtok(lsdir->d_name, ".");
            printf("-Tabela %d: %s\n", cont + 1, token);
        }
        cont++;
    }

    printf("\n\n");

    closedir(dir);
    return 0;
}
int operacao_ir(char **args)
{
    printf("Insere o registro no arquivo de tabela, usando a politica de insercao adequada.\n\n");
    return 0;
}
int operacao_brN(char **args)
{
    printf("Busca em tabela todos os registros que satisfacam o criterio de busca.\n\n");
    return 0;
}
int operacao_brU(char **args)
{
    printf("Busca em tabela o primeiro registro que satisfaca o criterio de busca.\n\n");
    return 0;
}
int operacao_ar(char **args)
{
    printf("Apresenta na tabela o valor dos registros retornados pela ultima busca.\n\n");
    return 0;
}
int operacao_rr(char **args)
{
    printf("Remove, segundo a politica de remocao da tabela, todos os registros da ultima busca realiza.\n\n");
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
    printf("Encerra a interpretação e termina a execução do programa.\n\n");
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
        resultado = remover_espacos_duplos(fgets(linha, 150, arq)); // o 'fgets' lê até 150 caracteres ou até o '\n'
        if (resultado)
        {
            if (strcmp(resultado, "EB") == 0)
            {
                return (*comandos_funcoes[15])(argumentos);
                break;
            }
            argumentos = separar_string(linha); //Gerador da lista de comandos
            interpretador(argumentos, flag);    //Interpretador dos comandos
        }
    }

    fclose(arq);
    return flag;
}