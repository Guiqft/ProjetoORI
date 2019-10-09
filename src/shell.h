#ifndef SHELL
#define SHELL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <dirent.h>


int comandos_quantidade();
int (*comandos_funcoes[15])(char **);
char *leitura_linha();
int interpretador(char **comandos);
void loop_comandos();

#endif /* SHELL */