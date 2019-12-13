#include "comandos.h"
#define BUFF_SIZE 2000


int operacao_ct(char **args)
{
    int flag = 0;
    char nome_tabela[BUFF_SIZE];
    strcpy(nome_tabela, args[1]);

    if (checar_arquivo_existente(nome_tabela)) //verifica se a tabela já existe
    {
        printf("A tabela %s ja existe.\n\n", args[2]);
        return EXIT_FAILURE; //Executa o comando de encerramento
    }

    FILE *tabela;

    if ((tabela = fopen(adicionar_diretorio(nome_tabela, 1), "w")) == NULL)
    {
        printf("Erro na criacao do arquivo da tabela.\nTente novamente\n");
        return flag;
    }
    //abrir tabela a partir do nome dela para escrita

    int i = 2;
    while (args[i] != NULL) //verificação do tipo de registro válido
    {
        if (strcmp(args[i], "INT") == 0 || strcmp(args[i] , "int") == 0)
        {
            flag = 1;
            fprintf(tabela, "INT:%s|", args[i + 1]);
        }
        else if (strcmp(args[i], "FLT") == 0 || strcmp(args[i] , "flt") == 0)
        {
            flag = 1;
            fprintf(tabela, "FLT:%s|", args[i + 1]);
        }
        else if (strcmp(args[i], "STR") == 0 || strcmp(args[i] , "str") == 0 ) 
        {
            flag = 1;
            fprintf(tabela, "STR:%s|", args[i + 1]);
        }
        else if (strcmp(args[i], "BIN") == 0 || strcmp(args[i] , "bin") == 0 )
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
    char nome_tabela[BUFF_SIZE];
    strcpy(nome_tabela, args[1]);

    DIR *data_dir;

    struct dirent *lsdir;

    data_dir = opendir("./data/");

    char nome_arquivo[BUFF_SIZE];

    strcpy(nome_arquivo, "./data/");
    while((lsdir = readdir(data_dir)) != NULL){
        if(strstr(lsdir->d_name, nome_tabela))
            strcat(nome_arquivo, lsdir->d_name);
            remove(nome_arquivo);

            strcpy(nome_arquivo, "./data/");
        // if(strstr(lsdir->d_name, nome_tabela))
        //     remove(lsdir->d_name);
    }
    closedir(data_dir);

    data_dir = opendir("./data/index_files/");

    strcpy(nome_arquivo, "./data/index_files/");
    while((lsdir = readdir(data_dir)) != NULL){
        if(strstr(lsdir->d_name, nome_tabela))
            strcat(nome_arquivo, lsdir->d_name);
            remove(nome_arquivo);

            strcpy(nome_arquivo, "./data/index_files/");
    }

    return 0;
}

int operacao_at(char **args) //apresenta um resumos dos metadados da tabela indicada (arquivos, campos e índices)
{
    char nome_tabela[BUFF_SIZE];
    strcpy(nome_tabela, args[1]);

    FILE *tabela;

    if ((tabela = fopen(adicionar_diretorio(nome_tabela, 1), "r")) == NULL) //função para abrir tabela
    {
        printf("Erro ao abrir o arquivo da tabela %s.\nTente novamente.\n", args[1]);
        return 0;
    }

    char linha[BUFF_SIZE]; //aloca espaço para resumo dos metadados
    fgets(linha, BUFF_SIZE, tabela);

    char **dados = separar_string(linha); //chama funcao para separar a string por espaço, :, ; e |
    
    int i = 0;
    
    printf("Resumo da tabela '%s':\n", nome_tabela);
    printf("Campos:\n");

    while (dados[i] != NULL && strcmp(dados[i], "#\n") != 0)
    {
        if(strstr(dados[i], "TRE") != NULL){             
                printf("-Tipo 'INT', nome: '%s', indexacao: '%s'.\n", dados[i+1], "arvore");
        }
        else if(strstr(dados[i], "HSH") != NULL){            
                printf("-Tipo 'INT', nome: '%s', indexacao: '%s'.\n", dados[i+1], "hash");
        }
        else
            printf("-Tipo %s, nome: '%s'.\n", dados[i], dados[i + 1]);
        i+=2;
    }

    fclose(tabela);
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

    dir = opendir("./data/"); //abrir diretorio

    printf("Tabelas existentes na base:\n");
    while ((lsdir = readdir(dir)) != NULL){ //Readdir = Lê os campos do manipulador do diretório
                                            //Os nomes de arquivos são retornados na ordem informada pelo sistema de arquivos.
        token = strtok(lsdir->d_name, ".");
        if(token != NULL)
            printf("-Tabela %d: %s\n", cont -1 , token); //lista as tabelas existentes no diretorio
        cont++;
    }

    printf("\n\n");

    closedir(dir);
    return 0;
}

int operacao_ir(char **args) //insere o registro na tabela, usando a politica de inserção adequada
{
    char nome_tabela[BUFF_SIZE];
    strcpy(nome_tabela, args[1]); //Realiza a cópia do conteúdo de uma variável a outra

    if(verifica_index(nome_tabela) != 0){
        printf("A funcao IR contempla indexacao.");
    }
    else{
        FILE *tabela;
        char linha[BUFF_SIZE];

        if ((tabela = fopen(adicionar_diretorio(nome_tabela, 1), "r+")) == NULL)
        {
            printf("Erro ao abrir o arquivo da tabela %s.\nTente novamente.\n", args[1]);
            return 0;
        }

        fgets(linha, BUFF_SIZE, tabela); //pega a linha do cabeçalho da tabela
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
                    free(dados);
                    return 0;
                }
            }
            else if (strcmp(dados[i], "FLT") == 0)
            {
                if (verifica_flt(args[j]) == 1)
                {
                    printf("Argumento invalido em campo FLOAT\n");
                    free(dados);
                    return 0;
                }
            }
            else if (strcmp(dados[i], "STR") == 0)
            {
                if (verifica_str(args[j]) == 1)
                {
                    printf("Nao use '#' ou '|'\n");                    
                    free(dados);
                    return 0;
                }
            }
            else if (strcmp(dados[i], "BIN") == 0)
            {
                if (checar_arquivo_existente(args[j]) == 0)
                {
                    printf("Arquivo BIN nao existe, um sera criado (vazio)\nCaso voce queira usar um arquivo especifico, coloque-o na pasta ./data/");
                    FILE *arquivo; //variavel tabela do tipo arquivo
                    arquivo = fopen(adicionar_diretorio(args[j], 1), "rb");
                    fclose(arquivo);
                }
            }
            i+=2;
            j++;
        }
        fclose(tabela);

        tabela = fopen(adicionar_diretorio(nome_tabela, 1), "r+");

        char nome_tabela_reuso[BUFF_SIZE];
        strcpy(nome_tabela_reuso, nome_tabela);
        strcat(nome_tabela_reuso, "_reuso");

        int tamanho_entrada = 0;
        i = 2;
        while (args[i] != NULL)
            tamanho_entrada += ((int) strlen(args[i++]) + 1);

        int flag = 0;

        if(checar_arquivo_existente(nome_tabela_reuso)){
            FILE* tabela_reuso;
            tabela_reuso = fopen(adicionar_diretorio(nome_tabela_reuso, 1), "r+");

            char linha_reuso[BUFF_SIZE];

            int posicao_usada = 0;
            int pos_menor = 0;
            int menor_tamanho = 1000;

            while(fgets(linha_reuso, BUFF_SIZE, tabela_reuso) != NULL){
                if(linha_reuso[0] != '@'){
                    char copy[BUFF_SIZE];
                    strcpy(copy, linha_reuso);

                    char* token  =  strtok(linha_reuso, "|");
                    int pos = atoi(token);
                    token = strtok(NULL, "|");
                    int tam_dispo = atoi(token);

                    if((tam_dispo < menor_tamanho) && (tam_dispo >= (tamanho_entrada + 2))){
                        menor_tamanho = tam_dispo;
                        pos_menor = pos;
                        posicao_usada = ftell(tabela_reuso) - strlen(copy);
                    }
                }
            }

            if(menor_tamanho != 1000)   //1000 é o padrão. Se nada menor que ele foi achado, 
                                        //não há posições na tabela de reúso que caiba o registro atual
                flag = 1;

            if(flag){
                fseek(tabela_reuso, posicao_usada, SEEK_SET);
                fprintf(tabela_reuso, "@");
                fclose(tabela_reuso);

                fseek(tabela, pos_menor, SEEK_SET);
            }
        }
        
        i = 2;
        while (args[i] != NULL)
            fprintf(tabela, "%s|", args[i++]);
        (flag) ? fprintf(tabela, "#\n@") : fprintf(tabela, "#\n");
        

        fclose(tabela);
        free(dados);
    }

    return 0;
}
int operacao_brN(char **args) //Busca na tabela TODOS os registros que satisfaçam a busca
{
    int flag = 0;
    char *nome_tabela = args[2];

    char nome_arquivo_busca[BUFF_SIZE];
    strcpy(nome_arquivo_busca, nome_tabela);
    strcat(nome_arquivo_busca, "_busca");

    FILE *tabela;

    if ((tabela = fopen(adicionar_diretorio(nome_tabela, 1), "r")) == NULL)
    {
        printf("Erro ao abrir o arquivo da tabela %s.\nTente novamente.\n", args[2]);
        return 0;
    }

    if(verifica_index(nome_tabela) == 1){ //se a tabela conter indexacao tipo arvore
        // bTree *tree = btCreate(100);
        
        // char diretorio[BUFF_SIZE];
        // strcpy(diretorio, "./data/index_files/");
        // strcat(diretorio, nome_tabela);
        // strcat(diretorio, "_index_tree.dat");
        // //nesse momento, diretorio == "./data/index_files/nometabela_index_tree.dat"

        // FILE *fp;
        // fp = fopen(diretorio, "rb");

        // element record;
        // record.key = atoi(args[4]);

        // btNode read_node = disk_read(0, tree->order, fp);

        // int found = btSearch(read_node, tree->order, record, fp);

        // printf("chave: %d, data: %d\n", record.key, found);
        // //int achado = *found;

        // //if(cbt_errno(index_tree)==0) //Se não ocorreram erros, considera como encontrado
        // //    flag = 1;
        
        // // char * nome_arquivo_busca = adicionar_diretorio(nome_tabela, 1);
        // // tabela = fopen(nome_arquivo_busca, "r+");

        // // char linha[BUFF_SIZE];
        // // fseek(tabela, *found, SEEK_SET); //seta o ponteiro para a posição do registro encontrado
        // // fgets(linha, BUFF_SIZE, tabela);

        // // char *token = strtok(linha, "#\n");
        // // fprintf(tabela_busca, "%s#\n", token); //grava o registro encontrado no arquivo de busca
        // // free(nome_arquivo_busca);
        
        // // //cbt_destroy(index_tree, NULL);
        // fclose(fp);
    }

    else if(verifica_index(nome_tabela)==2){ //se a tabela conter indexacao tipo hash
        printf("hash\n");
        return 0;
    }

    else{
        char linha[BUFF_SIZE];
        fgets(linha, BUFF_SIZE, tabela);
        
        char **dados = separar_string(linha);
        
        int i = 1;

        while (dados[i] != NULL && strcmp(dados[i], "\n") != 0){
            if(strcmp(args[3], dados[i]) == 0){ //significa que achou um campo com o msm nome procurado
                //remover o arquivo de busca anterior
                remove(adicionar_diretorio(nome_arquivo_busca, 1));
                
                flag = 1;
                break;
            }
        
            i += 2;
        }
        
        if (!flag){
            printf("Não existe o campo %s nesta tabela, tente novamente!\n\n", args[3]);
            return 0;
        }
            
        free(dados);
        flag = 0;

        while (fgets(linha, BUFF_SIZE, tabela) != NULL)
        { //Enquanto não chegou no fim do arquivo
            char register_line[BUFF_SIZE];
            strcpy(register_line, linha);

            dados = separar_busca(linha);

            i = 0;

            FILE *tabela_busca;

            while (dados[i] != NULL && strcmp(dados[i], "#") != 0){ //Enquanto não chegou no fim da linha
                if (strcmp(args[4], dados[i]) == 0)
                {   
                    if(!flag)
                        tabela_busca = fopen(adicionar_diretorio(nome_arquivo_busca, 1), "w");
                    else
                        tabela_busca = fopen(adicionar_diretorio(nome_arquivo_busca, 1), "a");

                    fprintf(tabela_busca, "%ld|%ld|#\n", ftell(tabela) - strlen(register_line), strlen(register_line));

                    fclose(tabela_busca);

                    flag = 1;
                }
                i++;
            }
        }
    }

    if (flag == 0)
    {
        printf("Nao foi encontrado nenhum dado referente a pesquisa.\n\n");
    }   


    fclose(tabela);
    return 0;
}
int operacao_brU(char **args) //Busca na tabela pelo primeiro registro que satisfaça a busca
{
    int flag = 0;
    char *nome_tabela = args[2];

    char nome_arquivo_busca[BUFF_SIZE];
    strcpy(nome_arquivo_busca, nome_tabela);
    strcat(nome_arquivo_busca, "_busca");

    FILE *tabela;

    if ((tabela = fopen(adicionar_diretorio(nome_tabela, 1), "r")) == NULL)
    {
        printf("Erro ao abrir o arquivo da tabela %s.\nTente novamente.\n", args[2]);
        return 0;
    }

    if(verifica_index(nome_tabela) == 1){ //se a tabela conter indexacao tipo arvore
        // bTree *tree = btCreate(100);
        
        // char diretorio[BUFF_SIZE];
        // strcpy(diretorio, "./data/index_files/");
        // strcat(diretorio, nome_tabela);
        // strcat(diretorio, "_index_tree.dat");
        // //nesse momento, diretorio == "./data/index_files/nometabela_index_tree.dat"

        // FILE *fp;
        // fp = fopen(diretorio, "rb");

        // element record;
        // record.key = atoi(args[4]);

        // btNode read_node = disk_read(0, tree->order, fp);

        // int found = btSearch(read_node, tree->order, record, fp);

        // printf("chave: %d, data: %d\n", record.key, found);
        // //int achado = *found;

        // //if(cbt_errno(index_tree)==0) //Se não ocorreram erros, considera como encontrado
        // //    flag = 1;
        
        // // char * nome_arquivo_busca = adicionar_diretorio(nome_tabela, 1);
        // // tabela = fopen(nome_arquivo_busca, "r+");

        // // char linha[BUFF_SIZE];
        // // fseek(tabela, *found, SEEK_SET); //seta o ponteiro para a posição do registro encontrado
        // // fgets(linha, BUFF_SIZE, tabela);

        // // char *token = strtok(linha, "#\n");
        // // fprintf(tabela_busca, "%s#\n", token); //grava o registro encontrado no arquivo de busca
        // // free(nome_arquivo_busca);
        
        // // //cbt_destroy(index_tree, NULL);
        // fclose(fp);
    }

    else if(verifica_index(nome_tabela)==2){ //se a tabela conter indexacao tipo hash
        printf("hash\n");
        return 0;
    }

    else{
        char linha[BUFF_SIZE];
        fgets(linha, BUFF_SIZE, tabela);
        
        char **dados = separar_string(linha);
        
        int i = 1;

        while (dados[i] != NULL && strcmp(dados[i], "\n") != 0){
            if(strcmp(args[3], dados[i]) == 0){ //significa que achou um campo com o msm nome procurado
                //remover o arquivo de busca anterior
                remove(adicionar_diretorio(nome_arquivo_busca, 1));
                
                flag = 1;
                break;
            }
        
            i += 2;
        }
        
        if (!flag){
            printf("Não existe o campo %s nesta tabela, tente novamente!\n\n", args[3]);
            return 0;
        }
            
        free(dados);
        flag = 0;

        while ((fgets(linha, BUFF_SIZE, tabela) != NULL) && (flag == 0))
        { //Enquanto não chegou no fim do arquivo
            if(linha[0] != '@'){ //só cogitará registros válidos
                char register_line[BUFF_SIZE];
                strcpy(register_line, linha);

                dados = separar_busca(linha);

                i = 0;

                FILE *tabela_busca;

                while (dados[i] != NULL && strcmp(dados[i], "#") != 0){ //Enquanto não chegou no fim da linha
                    if (strcmp(args[4], dados[i]) == 0)
                    {   
                        tabela_busca = fopen(adicionar_diretorio(nome_arquivo_busca, 1), "w");

                        fprintf(tabela_busca, "%ld|%ld|#\n", ftell(tabela) - strlen(register_line), strlen(register_line));

                        fclose(tabela_busca);

                        flag = 1;
                    }
                    i++;
                }
            }
        }
    }

    if (flag == 0)
    {
        printf("Nao foi encontrado nenhum dado referente a pesquisa.\n\n");
    }   


    fclose(tabela);
    return 0;
}

int operacao_ar(char **args) //Apresenta na tabela os valores dos registros retornados pela ultima busca
{
    char nome_tabela[BUFF_SIZE];
    strcpy(nome_tabela, args[1]);

    char nome_tabela_busca[BUFF_SIZE];
    strcpy(nome_tabela_busca, args[1]);
    strcat(nome_tabela_busca, "_busca");

    FILE *tabela_dados;
    FILE *tabela_busca;

    if ((tabela_dados = fopen(adicionar_diretorio(nome_tabela, 1), "r")) == NULL)
    {
        printf("Erro ao abrir o arquivo da tabela %s.\nTente novamente.\n\n", nome_tabela);
        return 0;
    }
    if ((tabela_busca = fopen(adicionar_diretorio(nome_tabela_busca, 1), "r")) == NULL)
    {
        printf("Erro ao abrir o arquivo da tabela %s.\nTente novamente.\n\n", nome_tabela_busca);
        return 0;
    }

    char linha[BUFF_SIZE];
    int i = 0, j=0;

    printf("Resultado(s) da(s) ultima busca: \n");

    while (fgets(linha, BUFF_SIZE, tabela_busca) != NULL)
    {
        char* token = strtok(linha, "|");
        int pos = atoi(token);
        token = strtok(NULL, "|");
        int tam = atoi(token);

        fseek(tabela_dados, pos, SEEK_SET);
        
        char resultado[tam];
        fgets(resultado, tam, tabela_dados);

        printf("Registro %d: %s\n", i+1, resultado);

        i++;
    }

    printf("\n");

    fclose(tabela_dados);
    fclose(tabela_busca);
    return 0;
}

int operacao_rr(char **args)
{
    char nome_tabela[BUFF_SIZE];
    strcpy(nome_tabela, args[1]);

    char nome_tabela_busca[BUFF_SIZE];
    strcpy(nome_tabela_busca, args[1]);
    strcat(nome_tabela_busca, "_busca");

    char nome_tabela_reuso[BUFF_SIZE];
    strcpy(nome_tabela_reuso, args[1]);
    strcat(nome_tabela_reuso, "_reuso");

    FILE *tabela_dados;
    FILE *tabela_busca;
    FILE *tabela_reuso;

    if ((tabela_dados = fopen(adicionar_diretorio(nome_tabela, 1), "r+")) == NULL)
    {
        printf("Erro ao abrir o arquivo da tabela %s.\nTente novamente.\n\n", nome_tabela);
        return 0;
    }
    if ((tabela_busca = fopen(adicionar_diretorio(nome_tabela_busca, 1), "r")) == NULL)
    {
        printf("Erro ao abrir o arquivo da tabela %s.\nTente novamente.\n\n", nome_tabela_busca);
        return 0;
    }
    if ((tabela_reuso = fopen(adicionar_diretorio(nome_tabela_reuso, 1), "a+")) == NULL)
    {
        printf("Erro ao abrir o arquivo da tabela %s.\nTente novamente.\n\n", nome_tabela_reuso);
        return 0;
    }

    char linha_busca[BUFF_SIZE];
    char linha_dados[BUFF_SIZE];

    while(fgets(linha_busca, BUFF_SIZE, tabela_busca) != NULL){
        char *token = strtok(linha_busca, "|");
        int pos = atoi(token);
        token = strtok(NULL, "|");
        int tam = atoi(token);

        fseek(tabela_dados, pos, SEEK_SET);
        fprintf(tabela_dados, "@");
        fprintf(tabela_reuso, "%d|%d|#\n", pos, tam);
    }

    // char **auxiliar = (char**)malloc(sizeof(char*)*4);
    // auxiliar[0] = "GI";
    // auxiliar[1] = nome_tabela;

    // if(verifica_index(nome_tabela)==1)
    //     auxiliar[2] = "arvore";
    // else if (verifica_index(nome_tabela)==2)
    //     auxiliar[2] = "hash";
    
    // operacao_gi(auxiliar);
    
    fclose(tabela_reuso);
    fclose(tabela_dados);
    fclose(tabela_busca);
    return 0;
}

int operacao_ciA(char **args)
{
    if(!strlen(args[2])){ //se o usuário digitou apenas "ci a"
        printf("Digite o nome da tabela que deseja indexar.\n");
        return EXIT_FAILURE;
    }
    if(!strlen(args[3])){ //se o usuário digitou apenas "ci a nome_tabela"
        printf("Digite o nome do campo que deseja indexar.\n");
        return EXIT_FAILURE;
    }

    char* nome_tabela = args[2];
    char* nome_campo = args[3];

    FILE* tabela_registros;

    tabela_registros = fopen(adicionar_diretorio(nome_tabela, 1), "r+");
    if(tabela_registros != NULL){
        char linha[BUFF_SIZE];
        fgets(linha, BUFF_SIZE, tabela_registros);

        char confirmacao[BUFF_SIZE];
        strcpy(confirmacao, "TRE:");
        strcat(confirmacao, nome_campo); //confirmacao == "TRE:nomecampo"

        if(strstr(linha, confirmacao)){
            printf("A tabela '%s' ja apresenta o campo '%s' indexado por arvore.\n", nome_tabela, nome_campo);
            return 0;
        }
        else if(!strstr(linha, replace_str(confirmacao, "TRE:", "INT:"))){
            printf("O campo não existe ou não eh do tipo INT\n");
            return EXIT_FAILURE;
        }
        else{
            char new_line[BUFF_SIZE];
            strcpy(new_line, "INT:");
            strcat(new_line, nome_campo);

            long int before = ftell(tabela_registros);

            fseek(tabela_registros, 0, SEEK_SET);
            fprintf(tabela_registros, "%s", replace_str(linha, new_line, confirmacao));
    
            int i = 0;
            char** linha_separada;

            int *keys = malloc(sizeof(int));
            long int *adresses = malloc(sizeof(long int));

            
            char diretorio[BUFF_SIZE];
            strcpy(diretorio, "./data/index_files/");
            strcat(diretorio, nome_tabela);
            strcat(diretorio, "_index_tree.dat");

            FILE *fp;
            fp = fopen(diretorio, "wb+");


            int chave = 0;
            int tamanho = 0;
            long int pos = 0;

            element record;

            bTree* tree = btCreate(100); //order 100;

            while(fgets(linha, BUFF_SIZE, tabela_registros) != NULL){
                tamanho = strlen(linha);
                pos = ftell(tabela_registros);

                linha_separada = separar_string(linha);
                chave = atoi(linha_separada[0]);

                record.key = chave;
                record.data = pos - tamanho;

                btInsert(tree, record, fp);
            }

            free(linha_separada);
            fclose(fp);
        }
    }

    fclose(tabela_registros);
    return 0;
}

int operacao_ciH(char **args)
{   
    printf("Necessario implementar uma biblioteca de hash em disco\n");
    return 0;
}

int operacao_ri(char **args)
{   
    if(!strlen(args[1])){ //se o usuário digitou apenas "ri"
        printf("Digite o nome da tabela que deseja remover o indice.\n");
        return EXIT_FAILURE;
    }
    if(strlen(args[2]) == 0){ //se o usuário digitou apenas "ri nome_tabela"
        printf("Digite o nome da chave que deseja remover o indice.\n");
        return EXIT_FAILURE;
    }

    char* nome_tabela = args[1];

    char diretorio[BUFF_SIZE];
    strcpy(diretorio, "./data/index_files/");
    strcat(diretorio, args[1]);
    strcat(diretorio, "_index_tree.dat");

    if(remove(diretorio) != 0)
        printf("Nao foi possivel apagar o indice, verifique os dados\n");

    FILE* tabela;
    tabela = fopen(adicionar_diretorio(nome_tabela, 1), "r+");

    char linha[BUFF_SIZE];

    fgets(linha, BUFF_SIZE, tabela);
    char* replace = replace_str(linha, "TRE:", "INT:");
    //replace = replace_str(linha, "HSH:", "INT:");
    
    fseek(tabela, 0, SEEK_SET);

    fprintf(tabela, "%s", replace);

    fclose(tabela);
    return 0;
}

int operacao_gi(char **args)
{   
    if(!strlen(args[1])){ //se o usuário digitou apenas "ri"
        printf("Digite o nome da tabela que deseja gerar o indice.\n");
        return EXIT_FAILURE;
    }
    if(!strlen(args[2])){ //se o usuário digitou apenas "ri nome_tabela"
        printf("Digite o nome da chave que deseja gerar o indice.\n");
        return EXIT_FAILURE;
    }

    char* nome_tabela = args[1];
    char* nome_campo = args[2];

    char **argumentos = malloc(sizeof(char*) * 4);

    argumentos[0] = "ci";
    argumentos[1] = "a";
    argumentos[2] = nome_tabela;
    argumentos[3] = nome_campo;

    //if(tree)
    operacao_ciA(argumentos);
    //if(hash)
    //operacao_ciH(argumentos);

    free(argumentos);

    return 0;

    // if(strcmp(args[2],"arvore")==0)
    //     operacao_ciA(args);
    // else if(strcmp(args[2],"hash")==0)
    //     operacao_ciH(args);
    // return 0;
}

int operacao_eb(char **args)
{
    printf("Sai do programa\n\n");
    return 0;
}

int operacao_arquivo(char **args)
{
    FILE *arq;
    char *nome_arquivo = args[1];
    char linha[BUFF_SIZE];
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
        // Lê uma linha (inclusive com o '\n', que é removido com strtok)
        resultado = remover_espacos_duplos(strtok(fgets(linha, BUFF_SIZE, arq), "\n")); // o 'fgets' lê até BUFF_SIZE caracteres ou até o '\n'
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