#include "../../shared/opcoes.h"

int editaArquivo(char *identificadorUsuario, char *campo, float novoValor) {
  const char *nomeArquivo = "Projeto2C-main/shared/informacoesUsu.txt";
  const char *nomeArquivoTemporario = "Projeto2C-main/shared/temp_informacoesUsu.txt";

  FILE *arquivoOriginal =
      fopen(nomeArquivo, "r"); // Abre o arquivo original para leitura
  FILE *arquivoTemporario = fopen(
      nomeArquivoTemporario, "w"); // Abre o arquivo temporário para escrita
  if (!arquivoOriginal || !arquivoTemporario) {
    printf("Erro ao manipular arquivos.\n");
    return 0; // erro
  }

  char linha[256];
  int usuarioEncontrado = 0; // Verificação se o usuario foi encontrado

  while (fgets(linha, sizeof(linha), arquivoOriginal)) {
    size_t comprimento = strlen(linha);
    // Remove o caractere de nova linha do final da linha, se existir
    if (comprimento > 0 && linha[comprimento - 1] == '\n') {
      linha[comprimento - 1] = '\0';
    }

    char usuarioNaLinha[256];
    sscanf(linha, "%[^,],",
           usuarioNaLinha); // Pega o identificador do usuário da linha

    if (strcmp(usuarioNaLinha, identificadorUsuario) == 0) {
      char cpf[15], senha[100], nome[100], bitcoin[20], ethereum[20], ripple[20];
      float saldo;
      bitcoin[0] = ethereum[0] = ripple[0] = nome[0] = '\0'; // limpar buffers antes
      if (sscanf(linha,
                 "%14[^,],%19[^,],%99[^,],%f,%19[^,],%19[^,],%19[^\n]",
                 cpf, senha, nome, &saldo,
                 bitcoin, ethereum, ripple
                 ) != 7) {
          // erro de parsing: linha mal-formatada
      }
      if (strcmp(campo, "saldo") == 0) {
        fprintf(arquivoTemporario, "%s,%s,%s,%.2f,%s,%s,%s\n", cpf, senha,nome,
                novoValor, bitcoin, ethereum, ripple);
      } else if (strcmp(campo, "bitcoin") == 0) {
        fprintf(arquivoTemporario, "%s,%s,%s,%.2f,%.2f,%s,%s\n", cpf, senha,nome, saldo,
                novoValor, ethereum, ripple);
      } else if (strcmp(campo, "ethereum") == 0) {
        fprintf(arquivoTemporario, "%s,%s,%s,%.2f,%s,%.2f,%s\n", cpf, senha, nome, saldo,
                bitcoin, novoValor, ripple);
      } else if (strcmp(campo, "ripple") == 0) {
        fprintf(arquivoTemporario, "%s,%s,%s,%.2f,%s,%s,%.2f\n", cpf, senha,nome, saldo,
                bitcoin, ethereum, novoValor);
      }

      usuarioEncontrado = 1;
    } else {
      fprintf(arquivoTemporario, "%s\n", linha);
    }
  }
  // Fecha os arquivos
  fclose(arquivoOriginal);
  fclose(arquivoTemporario);

  if (!usuarioEncontrado) {
    remove(nomeArquivoTemporario);
    printf("Usuario nao encontrado.\n");
    return 0; // Indica falha
  }

  remove(nomeArquivo);
  rename(nomeArquivoTemporario, nomeArquivo);

  return 1; // Indica sucesso
}