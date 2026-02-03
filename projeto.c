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
      clientes = menu_cliente(clientes);
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

Cliente *menu_cliente(Cliente *clientes) {
  int opcao_menu;
  do {
    printf("\n-----Gerenciamento De Clientes------\n");
    printf("1 - Cadastrar Cliente\n");
    printf("2 - Listar Clientes\n");
    printf("3 - Buscar Cliente\n");
    printf("4 - Editar Cliente\n");
    printf("5 - Remover Cliente\n");
    printf("0 - Voltar ao Menu Principal\n");
    printf("Escolha uma Opcao: ");
    scanf(" %d", &opcao_menu);

    switch (opcao_menu) {
    case 1:
      clientes = cadastrar_cliente(clientes);
      break;

    case 2:
      listar_cliente(clientes);
      break;

    case 3:
      break;

    case 4:
      break;

    case 5:
      break;

    case 0:
      break;

    default:
      printf("\nOpcao Invalida\n");
      printf("\n");
    }

  } while (opcao_menu != 0);

  return clientes;
}

Cliente *cadastrar_cliente(Cliente *clientes) {
  Cliente *novo = (Cliente *)malloc(sizeof(Cliente));
  if (novo == NULL) {
    printf("ERRO! MEMORIA INSUFICIENTE!\n");
    printf("\nSelecione a teclar ENTER para voltar ao menu\n");
    getchar();
    return clientes;
  }

  printf("\n-----CADASTRAR CLIENTE-----\n");
  printf("Insira seu Nome: \n");
  fgets(novo->nome, MAX_LEN_NOME, stdin);
  novo->nome[strcspn(novo->nome, "\n")] = '\0';

  printf("\nInsira seu CPF (xxx.xxx.xxx-xx): \n");
  fgets(novo->cpf, MAX_LEN_CPF, stdin);
  novo->cpf[strcspn(novo->cpf, "\n")] = '\0';

  if (buscar_cliente_cpf(clientes, novo->cpf) != NULL) {
    printf("\nCliente ja Cadastrado");
    printf("\nSelecione a teclar ENTER para voltar ao menu\n");
    free(novo);
    return clientes;
  }

  printf("\nInsira sua data de nascimento (DD/MM/YYYY): \n");
  fgets(novo->data_nascimento, MAX_LEN_NASC, stdin);
  novo->data_nascimento[strcspn(novo->data_nascimento, "\n")] = '\0';

  printf("\nInsira seu telefone (DDD)XXXX-XXXX: \n");
  fgets(novo->telefone, MAX_LEN_TEL, stdin);

  novo->telefone[strcspn(novo->telefone, "\n")] = '\0';
  printf("\nInsira seu email: \n");
  fgets(novo->email, MAX_LEN_EMAIL, stdin);
  novo->email[strcspn(novo->email, "\n")] = '\0';

  novo->meu_carrinho = NULL;
  novo->prox = clientes;

  printf("\nCliente Cadastrado!\n");
  return novo;
}

void listar_cliente(const Cliente *clientes) {
  const Cliente *cliente_lista = clientes;

  if (cliente_lista == NULL) {
    printf("\nSEM REGISTRO DE CLIENTES\n");
    printf("Selecione a tecla ENTER para voltar ao menu");
    getchar();
    return;
  }
  printf("-----LISTA DE CLIENTES-----\n");
  while (cliente_lista != NULL) {
    printf("Nome: %s\n", cliente_lista->nome);
    printf("CPF: %s\n", cliente_lista->cpf);
    printf("Data de Nascimento: %s\n", cliente_lista->data_nascimento);
    printf("Telefone: %s\n", cliente_lista->telefone);
    printf("Email: %s\n", cliente_lista->email);

    cliente_lista = cliente_lista->prox;
  }
  printf("Selecione a tecla ENTER para voltar ao menu");
  getchar();
  return;
}

Cliente *buscar_cliente_cpf(Cliente *clientes, char cpf_cliente[]) {}
