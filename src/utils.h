#ifndef UTILS
#define UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <dirent.h>
#include "external/cranbtree.h" //Retirado de: https://github.com/abdullahemad12/Cranberry-Btree

char *maiuscula(char *string);
char *remover_espacos_duplos(char str[]);
int verifica_int(char *string);
int verifica_flt(char *string);
int verifica_str(char *string);
char **organizar_lista(char **lista);
char **separar_string(char *linha);
char **separar_busca(char *linha);
char *adicionar_diretorio(char *nome_tabela, int seletor);
int checar_arquivo_existente(char *nome_tabela);
int numero_tabelas();
char* juntar_string(char **string_dividida);
int verificaIndex(char *nome_tabela);
cranbtree_t* mount_tree(FILE* tree_file);

#endif /* UTILS */