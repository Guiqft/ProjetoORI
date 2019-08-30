//Bibliotecas e arquivos externos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.c"
#include "comandos.c"
#include "shell.c"

//Protótipos
int loop_comandos();
char *leitura_linha();
int interpretador(char **comandos, int flag);
char **separar_string(char *linha);
char *remover_espacos_duplos(char str[]);
char maiuscula(char c);

//Função principal
int main()
{
    loop_comandos();
    return 0;
}