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
            printf("Não foi digitado um tipo de registro válido!\n");

        i++;
    }
    return 0;
}

int operacao_rt(char **args)
{
    printf("tabela criada");
    return 0;
}
int operacao_at(char **args)
{
    printf("tabela criada");
    return 0;
}
int operacao_lt(char **args)
{
    printf("tabela criada");
    return 0;
}
int operacao_ri(char **args)
{
    printf("tabela criada");
    return 0;
}
int operacao_brN(char **args)
{
    printf("tabela criada");
    return 0;
}
int operacao_brU(char **args)
{
    printf("tabela criada");
    return 0;
}
int operacao_ar(char **args)
{
    printf("tabela criada");
    return 0;
}
int operacao_rr(char **args)
{
    printf("tabela criada");
    return 0;
}
int operacao_ciA(char **args)
{
    printf("tabela criada");
    return 0;
}
int operacao_ciH(char **args)
{
    printf("tabela criada");
    return 0;
}
int operacao_gi(char **args)
{
    printf("tabela criada");
    return 0;
}