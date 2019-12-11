# Interpretador de comandos na linguagem C

Esse é um trabalho de caráter avaliativo proposto na disciplina de Organização e Recuperação da Informação, ministrada por Jander Moreira.
Esta disciplina faz parte da grade curricular dos cursos de Ciência de Computação e Engenharia de Computação da Universidade Federal de São Carlos (UFSCar).

## Iniciando

Para utilizar o interpretador, basta executar o arquivo "sgbd"
A lista dos comandos disponíveis se encontra logo abaixo.

## Comandos

| Comando | Descrição |
| :----- | :--------- |
|  **CT** *tabela campos* | Cria um arquivo vazio associado ao nome *tabela* com os campos definidos. |
| **RT** *tabela* | Apaga o arquivo relativo a tabela e remove seus metadados da base. |
| **AT** *tabela* | Apresenta um resumo dos metadados da *tabela* indicada. |
| **LT**  | Lista o nome de todas as tabelas existentes na base. |
| **IR** *tabela* | Insere o registro no arquivo de tabela. |
| **BR** **N** *tabela* *busca* | Busca em *tabela* todos os registros que satisfaçam o critério *busca*. |
| **BR** **U** *tabela* *busca* | Busca em *tabela* pelo primeiro registro que satisfaça o critério *busca*. |
| **AR** *tabela* | Apresenta na tela os valores dos registros retornados pela última busca. |
| **RR** *tabela* | Remove todos os registros da última busca realizada. |
| **CI** **A** *tabela* *chave* | Cria um indice estruturado como arvore de multiplos caminhos para a tabela usando *chave* como chave de busca. |
| **CI** **H** *tabela* *chave* | Cria um indice usando *hashing* para a tabela, usando *chave* como chave de busca. |
| **RI** *tabela* *chave* | Remove o indice relativo a *chave*. |
| **GI** *tabela* *chave* | Gera novamente o indice de *tabela* referente à *chave*. |

Exemplos de comandos:

```
CT CLIENTES INT:CODIGO;STR:NOME;BIN:CERTIF
IR CLIENTES 10;JOSE DA SILVA;jose_cert.crt
IR CLIENTES 20;JOSE DE SOUZA;souza.crt
IR CLIENTES 30;JOAO PASCOAL;jp.crt
IR CLIENTES 40;LUIS BERTOLO;lb_novo.crt
IR CLIENTES 50;JOAO PASCOAL;jp2.crt
```
  
## Autores

Grupo A2:

* **Gabriel Fernandes Roza** - RA: 760688	
* **Guilherme Oliveira** - RA: 759041
* **Jhonattan Vieira dos Santos** - RA: 563234
* **Roger Sigolo Junior** - RA: 728340
* **Victoria de Martini de Souza** - RA: 759378	

Lista dos [colaboradores](https://github.com/Guiqft/ProjetoORI/contributors) deste projeto.
