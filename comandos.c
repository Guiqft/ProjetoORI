int interpretador(char **comandos, int flag);
int (*comandos_funcoes[])(char **);

int operacao_ct(char **args)
{
    int flag = 0;
    char *nome_tabela = (char *)malloc(sizeof(char) * strlen(args[1]));
    strcpy(nome_tabela, args[1]);

    if (!checar_arquivo_existente(nome_tabela))
        return (*comandos_funcoes[15])(args);

    FILE *tabela;
    char diretorio_arquivos[100] = "./Data/";

    strcat(nome_tabela, ".txt");
    strcat(diretorio_arquivos, nome_tabela);

    if ((tabela = fopen(diretorio_arquivos, "w")) == NULL)
    {
        printf("Erro na criacao do arquivo da tabela.\nTente novamente\n");
        return flag;
    }

    printf("Tabela criada!\nNome da tabela: %s\n\n", args[1]);
    printf("Registros:\n");

    int i = 2;
    while (args[i] != NULL)
    {
        if (strcmp(args[i], "INT") == 0)
        {
            printf("Tipo INT. Nome: %s\n", args[i + 1]);
            flag = 1;

            fprintf(tabela, "INT:%s|", args[i + 1]);
        }
        else if (strcmp(args[i], "FLT") == 0)
        {
            printf("Tipo FLT. Nome: %s\n", args[i + 1]);
            flag = 1;

            fprintf(tabela, "FLT:%s|", args[i + 1]);
        }
        else if (strcmp(args[i], "STR") == 0)
        {
            printf("Tipo STR. Nome: %s\n", args[i + 1]);
            flag = 1;

            fprintf(tabela, "STR:%s|", args[i + 1]);
        }
        else if (strcmp(args[i], "BIN") == 0)
        {
            printf("Tipo BIN. Nome: %s\n", args[i + 1]);
            flag = 1;

            fprintf(tabela, "BIN:%s|", args[i + 1]);
        }

        if (!flag)
            printf("Não foi digitado um tipo de registro válido!\n\n");
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
    strcat(nome_tabela, ".txt");

    char *diretorio_arquivos = (char *)malloc(sizeof(char) * (strlen(nome_tabela) + 8));
    strcpy(diretorio_arquivos, "./Data/");
    strcat(diretorio_arquivos, nome_tabela);

    if (!checar_arquivo_existente)
    {
        remove(diretorio_arquivos);
        printf("Tabela %s removida.\n\n", args[1]);
    }
    else
        printf("A tabela %s nao existe.\n\n");

    free(nome_tabela);
    free(diretorio_arquivos);
    return 0;
}

int operacao_at(char **args)
{
    printf("Apresenta um resumo da tabela %s.\n\n ", args[1]);
    return 0;
}
int operacao_lt(char **args)
{
    printf("Lista o nome de todas as tabelas existentes na base.\n\n");
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
    char *nome_arquivo;
    char linha[MAX];
    char *resultado;
    char **argumentos;
    int flag;

    nome_arquivo = strlwr(args[1]); //passa o nome do arquivo para minusculo

    // Abre um arquivo TEXTO para LEITURA
    arq = fopen(nome_arquivo, "rt");
    if (arq == NULL) // Se houve erro na abertura
    {
        printf("Problemas na abertura do arquivo '%s'. Tente novamente.\n\n", nome_arquivo);
        return 0;
    }

    while (!feof(arq))
    {
        // Lê uma linha (inclusive com o '\n')
        resultado = remover_espacos_duplos(fgets(linha, MAX, arq)); // o 'fgets' lê até MAX caracteres ou até o '\n'
        if (resultado)                                              // Se foi possível ler
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
    return 0;
}