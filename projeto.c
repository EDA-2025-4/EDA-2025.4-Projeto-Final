#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN_NOME 100
#define MAX_LEN_CPF 20
#define MAX_LEN_EMAIL 100
#define MAX_LEN_NASC 20

typedef struct cliente Cliente;
typedef struct produto Produto;
typedef struct carrinho Carrinho;

struct cliente {
  char nome[MAX_LEN_NOME];
  char cpf[MAX_LEN_CPF];
  char email[MAX_LEN_EMAIL];
  char data_nascimento[MAX_LEN_NASC];

	Carrinho *meu_carrinho;
	Cliente *prox;
};


struct produto {
  int codigo;
  char nome_prod[MAX_LEN_NOME];
  float preco;
  int quantidade;

	Produto *prox;
};

struct carrinho {
	int cod_unico;
	char nome_produto [MAX_LEN_NOME];
	float preco_produto;
	int quantidade_produto;

	Carrinho *prox;
};
