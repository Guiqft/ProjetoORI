//Bibliotecas e arquivos externos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "utils.c"
#include "shell.c"
#include "comandos.c"

//Protótipos
void loop_comandos();
int checar_arquivo_existente(char *nome_tabela);
int interpretador(char **comandos);
char *leitura_linha();
char *remover_espacos_duplos(char str[]);
char *maiuscula(char *string);
char *adicionar_diretorio(char *nome_tabela, int seletor);
int numero_tabelas();
char **separar_string(char *linha);
char **separar_busca(char *linha);
char **organizar_lista(char **lista);


//Função principal
int main(int argc, char *argv[ ])
{
    if (argc == 2){ //Se o nome de um arquivo de comandos foi inserido logo após ./main no terminal
                    //O nome do arquivo está armazenado em argv[1]
        char *fim;
        fim = strtok(argv[1],".");
        fim = strtok(NULL, "\n");
        if(!strcmp(fim,"txt")){ //Checa se é um arquivo .txt
                                //Se for, roda o comandos do arquivo
            FILE *arq;
            char linha[150];
            char *resultado;
            char **argumentos;

            // Abre o arquivo de comandos
            arq = fopen(strcat(argv[1],".txt"), "rt");

            if (arq == NULL) // Se houve erro na abertura
            {
                printf("Problemas na abertura do arquivo '%s'. Tente novamente.\n\n", argv[1]);
                return 0;
            }

            while (!feof(arq))
            {
                // Lê uma linha (inclusive com o '\n', que é removido com strtok)
                resultado = remover_espacos_duplos(strtok(fgets(linha, 150, arq), "\n")); // o 'fgets' lê até 150 caracteres ou até o '\n'
                if (resultado)
                    if (strcmp(resultado, "eb") == 0 || strcmp(resultado, "EB") == 0)
                        exit(0);    //Se for o comando de sair, fecha o shell
                    argumentos = separar_string(linha); //Gerador da lista de comandos
                    interpretador(argumentos);    //Interpretador dos comandos
            }
            fclose(arq);
        }
    }else{  //Caso o argumento no terminal não seja o nome de um arquivo, roda o loop de comandos
        loop_comandos();
    }

    //system ("pause"); //Para windows
    return 0;
}
