#include "../shared/opcoes.h"

// Structs globais (herdadas do original)
struct dados usuario;
struct moedas moedas;

// Exibe menu de opções e lê escolha
void menuUsuario() {
  char *alternativa[9] = {
    "Consultar Saldo",
    "Saque",
    "Deposito",
    "Extrato",
    "Comprar Criptomoeda",
    "Vender Criptomoeda",
    "Atualizar Cotacao",
    "Sair",
  };
  printf("--------------| Menu de opcoes |-----------------\n\n");
  for (int l = 0; l < 8; l++) {
    printf("%d . %-3s \n", l + 1, alternativa[l]);
  }
  printf("Escolha: ");
}

// Trata cada opção do usuário
int alternativaUsuario(int num, char *cpf) {
  char senha[100];
  switch (num) {
    case 1:
      printf("Digite sua senha para consultar o saldo: ");
      scanf("%s", senha);
      if (verificarSenha(cpf, senha)) {
        saldo(cpf);
      } else {
        printf("Senha incorreta.\n");
      }
      break;

    case 2:
      printf("Digite sua senha para efetuar o saque: ");
      scanf("%s", senha);
      if (verificarSenha(cpf, senha)) {
        saque(cpf);
      } else {
        printf("Senha incorreta.\n");
      }
      break;

    case 3:
      printf("Digite sua senha para efetuar o deposito: ");
      scanf("%s", senha);
      if (verificarSenha(cpf, senha)) {
        deposito(cpf, &moedas);
      } else {
        printf("Senha incorreta.\n");
      }
      break;

    case 4:
      consultarExtrato(cpf);
      break;

    case 5:
      printf("Digite sua senha para comprar criptomoeda: ");
      scanf("%s", senha);
      if (verificarSenha(cpf, senha)) {
        comprarCripto(cpf, &moedas);
      } else {
        printf("Senha incorreta.\n");
      }
      break;

    case 6:
      printf("Digite sua senha para vender criptomoeda: ");
      scanf("%s", senha);
      if (verificarSenha(cpf, senha)) {
        venderCripto(cpf, &moedas);
      } else {
        printf("Senha incorreta.\n");
      }
      break;

    case 7:
      printf("Digite sua senha para atualizar cotacoes: ");
      scanf("%s", senha);
      if (verificarSenha(cpf, senha)) {
        atualizarcotacao();
      } else {
        printf("Senha incorreta.\n");
      }
      break;

    case 8:
      printf("Saindo...\n");
      exit(0);

    default:
      printf("Opcao invalida.\n");
      break;
  }
  return 0;
}

// Login retorna CPF válido alocado
char* realizarLoginUsuario() {
  char *cpf = malloc(15);
  char senha[100];

  while (1) {
    printf("----------------| Login Usuario |-------------------\n\n");
    printf("Digite o CPF do usuario: ");
    scanf("%s", cpf);
    printf("Digite sua senha: ");
    scanf("%s", senha);

    if (verificarSenha(cpf, senha)) {
      printf("\nLogin realizado com sucesso!\n");
      return cpf;
    } else {
      printf("\nCredenciais incorretas. Tente novamente.\n\n");
    }
  }
  return NULL;
}

int main() {
  setlocale(LC_ALL, "");

  // 1) Login de usuário
  char *cpfUsuario = realizarLoginUsuario();

  // 2) Loop principal do usuário
  while (1) {
    menuUsuario();
    int entrada;
    scanf("%d", &entrada);
    alternativaUsuario(entrada, cpfUsuario);
  }

  free(cpfUsuario);
  return 0;
}