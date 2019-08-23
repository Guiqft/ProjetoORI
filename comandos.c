int interpretador(char **comandos);

int operacao_ct(char **args)
{
    char *nome_tabela = args[1];
    printf("Tabela criada!\nNome da tabela: %s\n\n", nome_tabela);

    printf("Registros:\n");
    int i = 2, flag = 0;
    while (args[i] != NULL)
    {
        if (strcmp(args[i], "INT") == 0)
        {
            printf("Tipo INT. Nome: %s\n", args[i + 1]);
            flag = 1;
        }
        else if (strcmp(args[i], "FLT") == 0)
        {
            printf("Tipo FLT. Nome: %s\n", args[i + 1]);
            flag = 1;
        }
        else if (strcmp(args[i], "STR") == 0)
        {
            printf("Tipo STR. Nome: %s\n", args[i + 1]);
            flag = 1;
        }
        else if (strcmp(args[i], "BIN") == 0)
        {
            printf("Tipo BIN. Nome: %s\n", args[i + 1]);
            flag = 1;
        }

        if (!flag)
            printf("Não foi digitado um tipo de registro válido!\n\n");
        i++;
    }
    printf("\n");
    return 0;
}

int operacao_rt(char **args)
{
    printf("Tabela %s removida.\n\n", args[1]);
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
int operacao_arquivo(char **args)
{
    FILE *arq;
    char *nome_arquivo;
    char linha[MAX];
    char *resultado;
    char **argumentos;

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
            if (strcmp(resultado, "sair") == 0)
                break;
            argumentos = separar_string(linha); //Gerador da lista de comandos
            interpretador(argumentos);          //Interpretador dos comandos
        }
    }

    fclose(arq);
    return 0;
}