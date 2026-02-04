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
Cliente *remover_cliente_cpf(Cliente *clientes);

Produto *cadastrar_produto(Produto *estoque);
void listar_produto(const Produto *estoque);
Produto *buscar_produto_codigo(Produto *estoque, int codigo_produto);
void buscar_produto(Produto *estoque);
Produto *editar_produto_codigo(Produto *estoque);
Produto *remover_produto_codigo(Produto *estoque);
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
      printf("\n--OPCAO INVALIDA\n");
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
      clientes = remover_cliente_cpf(clientes);
      break;

    case 0:
      break;

    default:
      printf("\n--OPCAO INVALIDA--\n");
      printf("\n");
    }

  } while (opcao_menu != 0);

  return clientes;
}

Cliente *cadastrar_cliente(Cliente *clientes) {
  Cliente *novo = (Cliente *)calloc(1, sizeof(Cliente));
  if (novo == NULL) {
    printf("ERRO! MEMORIA INSUFICIENTE!\n");
    printf("\nSelecione a teclar ENTER para voltar ao MENU\n");
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
    printf("\n!!!Cliente Ja Cadastrado!!!\n");
    printf("\nSelecione a teclar ENTER para voltar ao MENU");
    free(novo);
    return clientes;
  }

  printf("Insira sua Data de Nascimento (DD/MM/YYYY): ");
  fgets(novo->data_nascimento, MAX_LEN_NASC, stdin);
  novo->data_nascimento[strcspn(novo->data_nascimento, "\n")] = '\0';

  printf("Insira seu Telefone (DDD)XXXX-XXXX: ");
  fgets(novo->telefone, MAX_LEN_TEL, stdin);

  novo->telefone[strcspn(novo->telefone, "\n")] = '\0';
  printf("Insira seu Email: ");
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
    printf("\n--SEM REGISTRO DE CLIENTES\n--");
    printf("Selecione a tecla ENTER para voltar ao MENU");
    getchar();
    return;
  }
  printf("\n-----CLIENTES CADASTRADOS-----\n");
  while (cliente_lista != NULL) {
    printf("Nome: %s\n", cliente_lista->nome);
    printf("CPF: %s\n", cliente_lista->cpf);
    printf("Data de Nascimento: %s\n", cliente_lista->data_nascimento);
    printf("Telefone: %s\n", cliente_lista->telefone);
    printf("Email: %s\n", cliente_lista->email);

    printf("\n");
    cliente_lista = cliente_lista->prox;
  }
  printf("--Selecione a tecla ENTER para voltar ao MENU--");
  getchar();
  return;
}

void buscar_cliente(Cliente *clientes) {
  char cpf_busca[MAX_LEN_CPF];
  printf("-----BUSCAR CLIENTE-----\n");
  printf("P.S: Caso queira retornar ao MENU digite 0\n");
  printf("Digite o CPF do Cliente (xxx.xxx.xxx-xx): ");
  fgets(cpf_busca, MAX_LEN_CPF, stdin);
  cpf_busca[strcspn(cpf_busca, "\n")] = '\0';

  if (strcmp(cpf_busca, "0") == 0) {
    return;
  }

  Cliente *encontrado = buscar_cliente_cpf(clientes, cpf_busca);
  if (encontrado != NULL) {
    printf("\n-----INFORMACOES CLIENTE-----\n");
    printf("Nome: %s\n", encontrado->nome);
    printf("CPF: %s\n", encontrado->cpf);
    printf("Data de Nascimento: %s\n", encontrado->data_nascimento);
    printf("Telefone: %s\n", encontrado->telefone);
    printf("Email: %s", encontrado->email);
  } else {
    printf("CPF NAO ENCONTRADO!");
  }
  printf("\n");
  printf("\nSelecione ENTER para voltar ao MENU");
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
  printf("P.S: Caso queira retornar ao MENU digite 0\n");
  printf("Digite o CPF do Cliente (xxx.xxx.xxx-xx): ");
  fgets(cpf_cliente, MAX_LEN_CPF, stdin);
  cpf_cliente[strcspn(cpf_cliente, "\n")] = '\0';
  if (strcmp(cpf_cliente, "0") == 0) {
    return clientes;
  }

  Cliente *encontrado = buscar_cliente_cpf(clientes, cpf_cliente);

  int opcao_menu;
  if (encontrado != NULL) {
    do {
      printf("\n------MENU DE EDICOES-----\n");
      printf("1 - Editar Nome\n");
      printf("2 - Editar CPF\n");
      printf("3 - Editar Data de Nascimento\n");
      printf("4 - Telefone\n");
      printf("5 - Email\n");
      printf("0 - Voltar ao MENU de Clientes\n");
      printf("Escolha uma Opcao: ");
      scanf("%d", &opcao_menu);
      while (getchar() != '\n')
        ;
      switch (opcao_menu) {
      case 1:
        printf("Edite o Nome: ");
        fgets(encontrado->nome, MAX_LEN_NOME, stdin);
        encontrado->nome[strcspn(encontrado->nome, "\n")] = '\0';
        printf("\n---Nome Editado Com sucesso---\n");
        break;

      case 2:
        printf("Edite o CPF: ");
        fgets(encontrado->cpf, MAX_LEN_NOME, stdin);
        encontrado->cpf[strcspn(encontrado->cpf, "\n")] = '\0';
        printf("\n---CPF Editado Com sucesso---\n");
        break;

      case 3:
        printf("Edite a Data de Nascimento: ");
        fgets(encontrado->data_nascimento, MAX_LEN_NOME, stdin);
        encontrado
            ->data_nascimento[strcspn(encontrado->data_nascimento, "\n")] =
            '\0';
        printf("\n---Data de Nascimento Editada Com sucesso---\n");
        break;

      case 4:
        printf("Edite o Telefone: ");
        fgets(encontrado->telefone, MAX_LEN_NOME, stdin);
        encontrado->telefone[strcspn(encontrado->telefone, "\n")] = '\0';
        printf("\n---Telefone Editado Com sucesso---\n");
        break;

      case 5:
        printf("Edite o Email: ");
        fgets(encontrado->email, MAX_LEN_NOME, stdin);
        encontrado->email[strcspn(encontrado->email, "\n")] = '\0';
        printf("\n---Email Editado Com sucesso---\n");
        break;

      case 0:
        break;

      default:
        printf("\nOpcao Invalida\n");
        printf("\n");
      }

    } while (opcao_menu != 0);

    printf("----CLIENTE EDITADO(A) COM SUCESSO!----");
  } else {
    printf("CPF Nao Encontrado!");
  }

  return clientes;
}

Cliente *remover_cliente_cpf(Cliente *clientes) {
  Cliente *atual = clientes;
  Cliente *anterior = NULL;
  char cpf_remover[MAX_LEN_CPF];

  printf("\n-----REMOVER CLIENTE-----\n");
  printf("Digite o CPF do Cliente (xxx.xxx.xxx-xx) ou 0 para cancelar: ");
  fgets(cpf_remover, MAX_LEN_CPF, stdin);
  cpf_remover[strcspn(cpf_remover, "\n")] = '\0';

  if (strcmp(cpf_remover, "0") == 0) {
    return clientes;
  }

  while (atual != NULL && strcmp(atual->cpf, cpf_remover) != 0) {
    anterior = atual;
    atual = atual->prox;
  }

  if (atual == NULL) {
    printf("\nCPF NAO ENCONTRADO!");
    printf("\nSelecione ENTER para voltar ao MENU");
    getchar();
    return clientes;
  }

  if (atual->meu_carrinho != NULL) {
    Carrinho *c_atual = atual->meu_carrinho;
    while (c_atual != NULL) {
      Carrinho *c_temp = c_atual;
      c_atual = c_atual->prox;
      free(c_temp);
    }
  }

  if (anterior == NULL) {
    clientes = atual->prox;
  } else {
    anterior->prox = atual->prox;
  }

  free(atual);

  printf("\nCliente Removido com Sucesso!");
  printf("\nSelecione ENTER para continuar");
  getchar();

  return clientes;
}

Produto *menu_produto(Produto *estoque) {
  int opc_menu;
  do {
    printf("\n-----Gerenciamento de Produtos-----\n");
    printf("1 - Cadastrar Produto\n");
    printf("2 - Listar Produtos\n");
    printf("3 - Buscar Produtos\n");
    printf("4 - Editar Produto\n");
    printf("5 - Remover Produto\n");
    printf("0 - Voltar ao Menu Principal\n");
    scanf("%d", &opc_menu);
    while (getchar() != '\n')
      ;

    switch (opc_menu) {
    case 1:
      // estoque = cadastrar_produto(estoque);
      break;
    case 2:
      listar_produto(estoque);
      break;
    case 3:
      buscar_produto(estoque);
      break;
    case 4:
      estoque = editar_produto_codigo(estoque);
      break;
    case 5:
      estoque = remover_produto_codigo(estoque);
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

Produto *cadastrar_produto(Produto *estoque) {
  Produto *novo = (Produto *)calloc(1, sizeof(Produto));
  if (novo == NULL) {
    printf("ERRO! MEMORIA INSUFICIENTE!\n");
    getchar();
    return estoque;
  }

  printf("\n-----CADASTRAR PRODUTO-----\n");
  printf("Insira o Codigo do Produto: ");
  scanf("%d", &novo->codigo);
  while (getchar() != '\n')
    ;

  if (buscar_produto_codigo(estoque, novo->codigo) != NULL) {
    printf("\n!!!Codigo de Produto Ja Cadastrado!!!\n");
    printf("\nSelecione ENTER para voltar ao MENU");
    getchar();
    free(novo);
    return estoque;
  }

  printf("Insira o Nome do Produto: ");
  fgets(novo->nome_prod, MAX_LEN_NOME, stdin);
  novo->nome_prod[strcspn(novo->nome_prod, "\n")] = '\0';

  printf("Insira o Preco: ");
  scanf("%f", &novo->preco);

  printf("Insira a Quantidade em Estoque: ");
  scanf("%d", &novo->quantidade);
  while (getchar() != '\n')
    ;

  novo->prox = estoque;

  printf("\nProduto Cadastrado com Sucesso!\n");
  printf("Selecione ENTER para continuar");
  getchar();

  return novo;
}

Produto *buscar_produto_codigo(Produto *estoque, int codigo_produto) {
  Produto *atual = estoque;
  while (atual != NULL) {
    if (atual->codigo == codigo_produto) {
      return atual;
    }
    atual = atual->prox;
  }
  return NULL;
}

void buscar_produto(Produto *estoque) {
  int cod_busca;
  printf("\n-----BUSCAR PRODUTO-----\n");
  printf("Digite o Codigo do Produto (ou 0 para voltar): ");

  if (scanf("%d", &cod_busca) != 1) {
    while (getchar() != '\n')
      ;
    return;
  }
  while (getchar() != '\n')
    ;

  if (cod_busca == 0)
    return;

  Produto *encontrado = buscar_produto_codigo(estoque, cod_busca);

  if (encontrado != NULL) {
    printf("\n-----INFORMACOES PRODUTO-----\n");
    printf("Codigo: %d\n", encontrado->codigo);
    printf("Nome: %s\n", encontrado->nome_prod);
    printf("Preco: R$ %.2f\n", encontrado->preco);
    printf("Quantidade: %d\n", encontrado->quantidade);
  } else {
    printf("\nCODIGO NAO ENCONTRADO!");
  }
  printf("\nSelecione ENTER para voltar ao MENU");
  getchar();
}

void listar_produto(const Produto *estoque) {
  const Produto *atual = estoque;
  if (atual == NULL) {
    printf("\n--SEM REGISTRO DE PRODUTOS--\n");
    printf("Selecione ENTER para voltar");
    getchar();
    return;
  }
  printf("\n-----PRODUTOS EM ESTOQUE-----\n");
  printf("%-5s | %-20s | %-10s | %-5s\n", "COD", "NOME", "PRECO", "QTD");
  while (atual != NULL) {
    printf("%-5d | %-20.20s | R$ %-7.2f | %-5d\n", atual->codigo,
           atual->nome_prod, atual->preco, atual->quantidade);
    atual = atual->prox;
  }
  printf("\nSelecione ENTER para voltar");
  getchar();
}

Produto *editar_produto_codigo(Produto *estoque) {
  int cod_busca;
  printf("\n-----EDITAR PRODUTO-----\n");
  printf("Digite o Codigo do Produto que deseja editar: ");
  scanf("%d", &cod_busca);
  while (getchar() != '\n')
    ; // Limpa buffer

  Produto *encontrado = buscar_produto_codigo(estoque, cod_busca);

  if (encontrado != NULL) {
    int opc_edit;
    do {
      printf("\n--- Editando: %s ---\n", encontrado->nome_prod);
      printf("1 - Editar Nome\n");
      printf("2 - Editar Preco\n");
      printf("3 - Editar Quantidade em Estoque\n");
      printf("0 - Finalizar Edicao\n");
      printf("Escolha: ");
      scanf("%d", &opc_edit);
      while (getchar() != '\n')
        ;

      switch (opc_edit) {
      case 1:
        printf("Novo Nome: ");
        fgets(encontrado->nome_prod, MAX_LEN_NOME, stdin);
        encontrado->nome_prod[strcspn(encontrado->nome_prod, "\n")] = '\0';
        break;
      case 2:
        printf("Novo Preco: ");
        scanf("%f", &encontrado->preco);
        while (getchar() != '\n')
          ;
        break;
      case 3:
        printf("Nova Quantidade: ");
        scanf("%d", &encontrado->quantidade);
        while (getchar() != '\n')
          ;
        break;
      case 0:
        break;
      default:
        printf("Opcao Invalida!\n");
      }
    } while (opc_edit != 0);
    printf("\nProduto atualizado com sucesso!\n");
  } else {
    printf("\nCODIGO %d NAO ENCONTRADO!\n", cod_busca);
  }

  printf("\nPressione ENTER para voltar ao menu...");
  getchar();
  return estoque;
}

Produto *remover_produto_codigo(Produto *estoque) {
  int cod_remover;
  Produto *atual = estoque;
  Produto *anterior = NULL;

  printf("\n-----REMOVER PRODUTO-----\n");
  printf(
      "Digite o Codigo do Produto que deseja remover (ou 0 para cancelar): ");
  scanf("%d", &cod_remover);
  while (getchar() != '\n')
    ;

  if (cod_remover == 0)
    return estoque;

  while (atual != NULL && atual->codigo != cod_remover) {
    anterior = atual;
    atual = atual->prox;
  }

  if (atual == NULL) {
    printf("\nCODIGO %d NAO ENCONTRADO!", cod_remover);
    printf("\nPressione ENTER para voltar...");
    getchar();
    return estoque;
  }

  if (anterior == NULL) {
    estoque = atual->prox;
  } else {

    anterior->prox = atual->prox;
  }

  free(atual);
  printf("\nProduto removido com sucesso!");
  printf("\nPressione ENTER para continuar...");
  getchar();

  return estoque;
}
