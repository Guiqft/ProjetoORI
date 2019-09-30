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
int main()
{
    loop_comandos();

    system ("pause");
    return 0;
}
