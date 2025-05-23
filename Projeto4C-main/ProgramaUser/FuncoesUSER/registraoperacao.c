#include "../../shared/opcoes.h"

void registrarTransacao(const char *cpf, const char *operacao, float valor, const char *detalhes) {
  FILE *arquivo = fopen("Projeto2C-main/shared/extrato.txt", "a"); // Modo append para adicionar ao final
  if (arquivo == NULL) {
    printf("Erro ao abrir arquivo de extrato.\n");
    return;
  }

  // Obter data e hora atual
  time_t now;
  time(&now);
  struct tm *local = localtime(&now);
  char dataHora[50];
  strftime(dataHora, sizeof(dataHora), "%d/%m/%Y %H:%M:%S", local);

  // Escrever no arquivo
  fprintf(arquivo, "%s | %s | %s | %.2f | %s\n", dataHora, cpf, operacao, valor, detalhes);

  fclose(arquivo);

  // Manter apenas as últimas 100 transações
  void manterUltimasTransacoes();
}

void manterUltimasTransacoes() {
  FILE *arquivo = fopen("Projeto2C-main/shared/extrato.txt", "r");
  if (arquivo == NULL)
    return;

  char linhas[100][256]; // Armazenar até 100 linhas
  int count = 0;

  // Ler todas as linhas
  while (fgets(linhas[count], sizeof(linhas[count]), arquivo) && count < 100) {
    count++;
  }
  fclose(arquivo);

  // Reabrir o arquivo para escrita (sobrescrever)
  arquivo = fopen("Projeto2C-main/shared/extrato.txt", "w");
  if (arquivo == NULL)
    return;

  // Escrever apenas as últimas 100 linhas
  int inicio = (count >= 100) ? count - 100 : 0;
  for (int i = inicio; i < count; i++) {
    fprintf(arquivo, "%s", linhas[i]);
  }
  fclose(arquivo);
}