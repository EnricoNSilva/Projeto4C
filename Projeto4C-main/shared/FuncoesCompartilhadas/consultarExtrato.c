#include "../opcoes.h"

void consultarExtrato(const char *cpf) {
  int continuar = 1; // Controla o loop
  while (continuar) {
    FILE *arquivo = fopen("Projeto2C-main/shared/extrato.txt", "r");
    if (arquivo == NULL) {
      printf("Nenhuma transação registrada ainda.\n");
      return;
    }

    printf("\n=== EXTRATO BANCÁRIO ===\n");
    printf("CPF: %s\n\n", cpf);
    printf("DATA/HORA          | OPERAÇÃO       | VALOR    | DETALHES\n");
    printf("-----------------------------------------------------------\n");

    char linha[256];
    int encontradas = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
      char dataHora[20], cpfArquivo[15], operacao[20], detalhes[100];
      float valor;

      // Formato ajustado para ler detalhes
      if (sscanf(linha, "%19[^|] | %14[^|] | %19[^|] | %f | %99[^\n]", dataHora,
                 cpfArquivo, operacao, &valor, detalhes) == 5) {

        // Remover espaços do CPF (como antes)
        char *trimmedCpf = cpfArquivo;
        while (*trimmedCpf == ' ')
          trimmedCpf++;
        size_t len = strlen(trimmedCpf);
        while (len > 0 && trimmedCpf[len - 1] == ' ') {
          trimmedCpf[len - 1] = '\0';
          len--;
        }

        if (strcmp(trimmedCpf, cpf) == 0) {
          printf("%s | %-15s | R$ %7.2f | %s\n", dataHora, operacao, valor,
                 detalhes);
          encontradas++;
        }
      }
    }

    if (encontradas == 0) {
      printf("Nenhuma transação encontrada para este CPF.\n");
    }

    // Pergunta se deseja continuar
    printf("Digite qualquer valor numérico diferente de 1 para voltar ao menu:\n");

    int opcao;
    scanf("%d", &opcao);

    if (opcao != 1) {
      continuar = 0; // Sai do loop
    }

    system("clear");

    fclose(arquivo);
  }
}