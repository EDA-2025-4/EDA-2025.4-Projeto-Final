#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN_NOME 100
#define MAX_LEN_CPF 20
#define MAX_LEN_EMAIL 100
#define MAX_LEN_NASC 20

typedef struct cliente {
	char nome[MAX_LEN_NOME];
	char cpf [MAX_LEN_CPF];
	char email [MAX_LEN_EMAIL];
	char data_nascimento [MAX_LEN_NASC];
}Cliente;

typedef struct produto {
	int codigo;
	char nome_produto [MAX_LEN_NOME];
	float preco;
	int quantidade;
}Produto;
