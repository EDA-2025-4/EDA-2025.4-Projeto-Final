#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN_NOME 100
#define MAX_LEN_CPF 20
#define MAX_LEN_EMAIL 100
#define MAX_LEN_NASC 20
#define MAX_LEN_TEL 30

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
Cliente *editar_cliente_cpf(Cliente *clientes);
Cliente *remover_cliente_cpf(Cliente *clientes, char cpf_cliente[]);

Produto *cadatrar_produto(Produto *estoque);
void listar_produto(const Produto *estoque);
Produto *buscar_produto_codigo(Produto *estoque, int codigo_produto);
Produto *editar_produto_codigo(Produto *estoque);
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
void buscar_cliente(Cliente *clientes);
void buscar_produto(Produto *estoque);

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
      produtos = menu_produto(produtos);
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
    scanf("%d", &opcao_menu);
    while (getchar() != '\n')
      ;

    switch (opcao_menu) {
    case 1:
      clientes = cadastrar_cliente(clientes);
      break;

    case 2:
      listar_cliente(clientes);
      break;

    case 3: {
      buscar_cliente(clientes);
    } break;

    case 4:
      editar_cliente_cpf(clientes);
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
  Cliente *novo = (Cliente *)calloc(1, sizeof(Cliente));
  if (novo == NULL) {
    printf("ERRO! MEMORIA INSUFICIENTE!\n");
    printf("\nSelecione a teclar ENTER para voltar ao menu\n");
    getchar();
    return clientes;
  }

  printf("\n-----CADASTRAR CLIENTE-----\n");
  printf("Insira seu Nome e Sobrenome: ");
  fgets(novo->nome, MAX_LEN_NOME, stdin);
  novo->nome[strcspn(novo->nome, "\n")] = '\0';

  printf("Insira seu CPF (xxx.xxx.xxx-xx): ");
  fgets(novo->cpf, MAX_LEN_CPF, stdin);
  novo->cpf[strcspn(novo->cpf, "\n")] = '\0';

  if (buscar_cliente_cpf(clientes, novo->cpf) != NULL) {
    printf("\nCliente ja Cadastrado");
    printf("\nSelecione a teclar ENTER para voltar ao menu");
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

    printf("\n");
    cliente_lista = cliente_lista->prox;
  }
  printf("Selecione a tecla ENTER para voltar ao menu");
  getchar();
  return;
}

void buscar_cliente(Cliente *clientes) {
  char cpf_busca[MAX_LEN_CPF];
  printf("-----Buscar Cliente-----");
  printf("\nP.S: Caso queira retornar ao menu digite 0\n");
  printf("\nDigite o CPF do Cliente (xxx.xxx.xxx-xx): ");
  fgets(cpf_busca, MAX_LEN_CPF, stdin);
  cpf_busca[strcspn(cpf_busca, "\n")] = '\0';

  if (strcmp(cpf_busca, "0") == 0) {
    return;
  }

  Cliente *encontrado = buscar_cliente_cpf(clientes, cpf_busca);
  if (encontrado != NULL) {
    printf("-----Informacoes Cliente-----\n");
    printf("Nome: %s\n", encontrado->nome);
    printf("CPF: %s\n", encontrado->cpf);
    printf("Data de Nascimento: %s\n", encontrado->data_nascimento);
    printf("Telefone: %s\n", encontrado->telefone);
    printf("Email: %s\n", encontrado->email);
  } else {
    printf("CPF NAO ENCONTRADO!");
  }
  printf("\n");
  printf("\nSelecione ENTER para voltar ao menu");
  getchar();

  return;
}

Cliente *buscar_cliente_cpf(Cliente *clientes, char cpf_cliente[]) {
  Cliente *buscar_cliente = clientes;
  while (buscar_cliente != NULL) {
    int comp = strcmp(buscar_cliente->cpf, cpf_cliente);
    if (comp == 0) {
      return buscar_cliente;
    }
    buscar_cliente = buscar_cliente->prox;
  }

  return NULL;
}
Cliente *editar_cliente_cpf(Cliente *clientes) {
  char cpf_cliente[MAX_LEN_CPF];
  printf("P.S: Caso queira retornar ao menu digite 0\n");
  printf("\nDigite o CPF do Cliente (xxx.xxx.xxx-xx): ");
  fgets(cpf_cliente, MAX_LEN_CPF, stdin);
  cpf_cliente[strcspn(cpf_cliente, "\n")] = '\0';
  if (strcmp(cpf_cliente, "0") == 0) {
    return clientes;
  }

  Cliente *encontrado = buscar_cliente_cpf(clientes, cpf_cliente);

  int opcao_menu;
  if (encontrado != NULL) {
    do {
      printf("\n------Escolha Uma Opcao-----\n");
      printf("1 - Editar Nome\n");
      printf("2 - Editar CPF\n");
      printf("3 - Editar Data de Nascimento\n");
      printf("4 - Telefone\n");
      printf("5 - Email\n");
      printf("0 - Voltar ao Menu de Clientes\n");
      printf("Escolha uma Opcao: \n");
      scanf("%d", &opcao_menu);
      while (getchar() != '\n')
        ;
      switch (opcao_menu) {
      case 1:
        printf("Edite o Nome: ");
        fgets(encontrado->nome, MAX_LEN_NOME, stdin);
        encontrado->nome[strcspn(encontrado->nome, "\n")] = '\0';
        break;

      case 2:
        printf("Edite o CPF: ");
        fgets(encontrado->cpf, MAX_LEN_NOME, stdin);
        encontrado->cpf[strcspn(encontrado->cpf, "\n")] = '\0';
        break;

      case 3:
        printf("Edite a Data de Nascimento: ");
        fgets(encontrado->data_nascimento, MAX_LEN_NOME, stdin);

        encontrado
            ->data_nascimento[strcspn(encontrado->data_nascimento, "\n")] =
            '\0';
        break;

      case 4:
        printf("Edite o Telefone: ");
        fgets(encontrado->telefone, MAX_LEN_NOME, stdin);
        encontrado->telefone[strcspn(encontrado->telefone, "\n")] = '\0';
        break;

      case 5:
        printf("Edite o Email: ");
        fgets(encontrado->email, MAX_LEN_NOME, stdin);
        encontrado->email[strcspn(encontrado->email, "\n")] = '\0';
        break;

      case 0:
        break;

      default:
        printf("\nOpcao Invalida\n");
        printf("\n");
      }

    } while (opcao_menu != 0);

    printf("Cliente Editado com Sucesso!");
  } else {
    printf("CPF Nao Encontrado!");
  }

  return clientes;
}

Produto *menu_produto(Produto *estoque) {
  int opc_menu;
  do {
    printf("\n-----Gerenciamento de Produtos-----\n");
    printf("1 - Cadastrar Produto\n");
    printf("2 - Listar Produtos");
    printf("3 - Buscar Produtos");
    printf("4 - Editar Produto");
    printf("5 - Remover Produto");
    printf("0 - Voltar ao Menu Principal");
    scanf("%d", &opc_menu);
    while (getchar() != '\n')
      ;

    switch (opc_menu) {
    case 1:
      // estoque = cadatrar_produto(estoque);
      break;
    case 2:
      // listar_produto(estoque);
      break;
    case 3:
      // buscar_produto(estoque);
      break;
    case 4:
      // editar_produto_codigo(estoque);
      break;
    case 5:
      break;
    case 0:
      break;

    default:
      printf("OPCAO INVALIDA!");
      printf("\n");
      break;
    }
  } while (opc_menu != 0);
  return estoque;
}
