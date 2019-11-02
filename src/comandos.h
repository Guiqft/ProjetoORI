#ifndef COMANDOS
#define COMANDOS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <dirent.h>
#include "utils.h"
#include "shell.h"
#include "external/cranbtree.h" //Retirado de: https://github.com/abdullahemad12/Cranberry-Btree

int operacao_ct(char **args);
int operacao_rt(char **args);
int operacao_at(char **args);
int operacao_lt(char **args);
int operacao_ir(char **args);
int operacao_brN(char **args);
int operacao_brU(char **args);
int operacao_ar(char **args);
int operacao_rr(char **args);
int operacao_ciA(char **args);
int operacao_ciH(char **args);
int operacao_ri(char **args);
int operacao_gi(char **args);
int operacao_eb(char **args);
int operacao_arquivo(char **args);

#endif /* COMANDOS */