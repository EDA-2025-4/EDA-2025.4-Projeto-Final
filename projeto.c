#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
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
  char nome_produto[MAX_LEN_NOME];
  float preco_produto;
  int quantidade_produto;

  Carrinho *prox;
};

Cliente *cadastrar_cliente(Cliente *clientes);
void listar_cliente(const Cliente *clientes);
Cliente *buscar_cliente_cpf(Cliente *clientes, char cpf_cliente[]);
Cliente *editar_cliente_cpf(Cliente *clientes, char cpf_cliente[]);
Cliente *remover_cliente_cpf(Cliente *clientes, char cpf_cliente[]);

Produto *cadatrar_produto(Produto *estoque);
void listar_produto(const Produto *estoque);
Produto *buscar_produto_codigo(Produto *estoque, int codigo_produto);
Produto *editar_produto_codigo(Produto *estoque, int codigo_produto);
Produto *remover_produto_codigo(Produto *estoque, int codigo_produto);

Carrinho *incluir_produto(Carrinho *carrinho_cliente, Produto *estoque,
                          int codigo_produto_carrinho,
                          int quantidade_produtos_carrinho);
void listar_produtos_carrinho(const Carrinho *carrinho_cliente,
                              char cpf_cliente_carrinho[]);
Carrinho *remover_carrinho(Carrinho *carrinho_cliente, int codigo_produto,
                           char cpf_cliente_carrinho[]);

Cliente *menu_cliente(Cliente *clientes);
Produto *menu_produto(Produto *estoque);
void modo_compra(Cliente *clientes, Produto *estoque);

int main(void) {
  Cliente *clientes = NULL;
  Produto *produtos = NULL;
  int opcao_menu;

  do {
    printf("-----Menu Principal-----\n");
    printf("1 - Gerenciamento de Cliente\n");
    printf("2 - Gerenciamento de Produtos\n");
    printf("3 - Modo de Compra\n");
    printf("0 - Sair\n");
    printf("Escolha uma Opcao: ");
    scanf("%d", &opcao_menu);
    switch (opcao_menu) {
    case 1:
      clientes = menu_cliente(clientes);
      break;

    case 2:
      produtos = menu_produto(produtos);
      break;

    case 3:
      if (clientes == NULL || produtos == NULL) {
        printf("Produtos e/ou Clientes Nao Disponiveis\n");
      } else {
        modo_compra(clientes, produtos);
      }
      break;

    default:
      printf("Opcao Invalida");
      break;
    }
	}while (opcao_menu != 0);
return 0;
}
