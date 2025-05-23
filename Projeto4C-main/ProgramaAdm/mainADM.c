#include "../shared/opcoes.h"
#include "funcoesAdm/funcoesadm.h"



// Exibe menu de administrador
void menuAdm() {
  printf("----------------| Menu Administrador |-------------------\n\n");
  printf("[1] Cadastro de novos investidores.\n");
  printf("[2] Cadastro de novas criptomoedas.\n");
  printf("[3] Remover investidor.\n");
  printf("[4] Remover criptomoeda.\n");
  printf("[5] Consultar extrato de investidor.\n");
  printf("[6] Consultar saldos de investidor.\n");
  printf("[7] Atualizar cotacao de criptomoedas.\n");
  printf("[8] Sair.\n");
  printf("Escolha: ");
}

// Opções de administrador
void adminOpcoes(int numero, char *cpfAdmin) {
  (void)cpfAdmin; 
  switch (numero) {
    case 1: cadastrarInvestidor(); break;
    case 2: cadastrarMoedas();     break;
    case 3: removerInvestidor();   break;
    case 4: removerMoedas();       break;
    case 5: consultarExtratoAdmin(); break;
    case 6: obterSaldoUsu();         break;
    case 7: atualizarcotacao();      break;
    case 8:
      printf("Saindo...\n");
      exit(0);
    default:
      printf("Opcao invalida.\n");
  }
}

// Login do administrador retorna CPF alocado
char* realizarLoginAdmin() {
  char *cpfAdmin = malloc(15);
  char senha[100];

  while (1) {
    printf("--------------| Login Administrador |-----------------\n");
    printf("Digite o CPF do administrador: ");
    scanf("%s", cpfAdmin);
    printf("Digite sua senha: ");
    scanf("%s", senha);

    if (verificarSenhaAdmin(cpfAdmin, senha)) {
      printf("Login realizado com sucesso!\n");
      return cpfAdmin;
    } else {
      printf("Credenciais incorretas. Tente novamente.\n");
    }
  }
  return NULL;
}

int main() {
  setlocale(LC_ALL, "");

  // 1) Login de administrador
  char *cpfAdm = realizarLoginAdmin();

  // 2) Loop principal do admin
  while (1) {
    menuAdm();
    int escolha;
    scanf("%d", &escolha);
    adminOpcoes(escolha, cpfAdm);
  }

  free(cpfAdm);
  return 0;
}
