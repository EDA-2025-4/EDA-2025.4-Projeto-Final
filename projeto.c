#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN_NOME 100
#define MAX_LEN_CPF 20
#define MAX_LEN_EMAIL 100
#define MAX_LEN_NASC 20
#define MAX_LEN_TEL 20

typedef struct cliente Cliente;
typedef struct produto Produto;
typedef struct carrinho Carrinho;

struct cliente {
  char nome[MAX_LEN_NOME];
  char cpf[MAX_LEN_CPF];
  char telefone[MAX_LEN_TEL];
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
    while (getchar() != '\n')
      ;
    switch (opcao_menu) {
    case 1:
      printf("\nMenu Cliente\n");
      printf("\n");
      // clientes = menu_cliente(clientes);
      break;

    case 2:
      printf("\nMenu Produto\n");
      printf("\n");
      // produtos = menu_produto(produtos);
      break;

    case 3:
      if (clientes == NULL || produtos == NULL) {
        printf("\nProdutos e/ou Clientes Nao Disponiveis\n");
        printf("\n");
      } else {
        // modo_compra(clientes, produtos);
      }
      break;

    case 0:
      break;

    default:
      printf("\nOpcao Invalida\n");
      printf("\n");
      break;
    }
  } while (opcao_menu != 0);
  return 0;
}

Cliente *cadastrar_cliente(Cliente *clientes) {
  Cliente *novo = (Cliente *)malloc(sizeof(Cliente));
  if (novo == NULL) {
    printf("ERRO! MEMORIA INSUFICIENTE!\n");
    printf("\nSelecione a teclar ENTER para voltar ao menu\n");
    getchar();
    return clientes;
  }

  printf("\n-----CADASTRAR CLIENTE-----");
  printf("Insira seu Nome: ");
  fgets(novo->nome, MAX_LEN_NOME, stdin);
  novo->nome[strcspn(novo->nome, "\n")] = '\0';

  printf("Insira seu CPF (xxx.xxx.xxx-xx): \n");
  fgets(novo->cpf, MAX_LEN_CPF, stdin);
  novo->cpf[strcspn(novo->cpf, "\n")] = '\0';

  if (buscar_cliente_cpf(clientes, novo->cpf) != NULL) {
    printf("\nCliente ja Cadastrado");
    printf("\nSelecione a teclar ENTER para voltar ao menu\n");
    free(novo);
    return clientes;
  }

  printf("Insira sua data de nascimento (DD/MM/YYYY): ");
  fgets(novo->data_nascimento, MAX_LEN_NASC, stdin);
  novo->data_nascimento[strcspn(novo->data_nascimento, "\n")] = '\0';

  printf("Insira seu telefone (DDD)XXXX-XXXX: ");
  fgets(novo->telefone, MAX_LEN_TEL, stdin);

  novo->telefone[strcspn(novo->telefone, "\n")] = '\0';
  printf("Insira seu email: ");
  fgets(novo->email, MAX_LEN_EMAIL, stdin);
  novo->email[strcspn(novo->email, "\n")] = '\0';

  novo->meu_carrinho = NULL;
  novo->prox = clientes;

  printf("Cliente Cadastrado!\n");
  return novo;
}
