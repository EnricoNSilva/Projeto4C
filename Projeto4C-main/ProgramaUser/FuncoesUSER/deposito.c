#include "../../shared/opcoes.h"

void deposito(char *usuario, struct moedas *informacoes){
  // Primeiro obtém os dados do usuário
  char **dados = importarInfo(usuario);
  if (!dados) {
      printf("Usuário não encontrado.\n");
      return;
  }

  // Converte o saldo para float
  float saldoAtual = atof(dados[3]);

  // Mostra o saldo disponível
  printf("\nSaldo disponível: R$ %.2f\n", saldoAtual);

  // Pede o valor do deposito
  printf("Digite o quantia para depósito (ou digite 0 para cancelar): ");

  float valordeposito;
  while (1) {
      if (scanf("%f", &valordeposito) != 1) {
          // Limpa o buffer de entrada em caso de erro
          while (getchar() != '\n');
          printf("Valor inválido, digite um número: ");
          continue;
      }

      if (valordeposito == 0) {
          printf("Voltando ao menu.\n");
          sleep(2);
          return;
      }

      if (valordeposito <= 0) {
          printf("Valor deve ser positivo, digite novamente: ");
          continue;
      }

      break; // Valor válido
  }

  // Processa o deposito
  float novoSaldo = saldoAtual + valordeposito;
  if (editaArquivo(usuario, "saldo", novoSaldo)) {
      registrarTransacao(usuario, "DEPOSITO", valordeposito, "N/A");
      printf("\nDeposito efetuado com sucesso!\n");
      printf("Valor depositado: R$ %.2f\n", valordeposito);
      printf("Novo saldo: R$ %.2f\n", novoSaldo);
      informacoes->saldo_reais = novoSaldo;
  } else {
      printf("Erro ao atualizar saldo.\n");
  }

  sleep(3); // Pausa para leitura
}