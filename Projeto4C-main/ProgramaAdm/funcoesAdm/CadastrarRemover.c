#include "../../shared/opcoes.h"
// Esse arquivo cadastra e remove investidores
void cadastrarInvestidor() {
    char nome[100];
    char cpf[15];
    char senha[20];

    printf("-- Cadastro de Novo Investidor --\n");
    printf("Nome: ");
    scanf(" %99[^\n]", nome);
    printf("CPF (11 dígitos): ");
    scanf(" %14s", cpf);
    printf("Senha: ");
    scanf(" %19s", senha);

    // 1) verifica se CPF já existe
    FILE *leitura = fopen("Projeto2C-main/shared/informacoesUsu.txt", "r");
    if (leitura) {
        char linha[256], existente[15];
        while (fgets(linha, sizeof linha, leitura)) {
            sscanf(linha, "%14[^,]", existente);
            if (strcmp(existente, cpf) == 0) {
                printf("Erro: CPF %s já cadastrado.\n", cpf);
                fclose(leitura);
                return;
            }
        }
        fclose(leitura);
    }
    // 2) se chegou aqui, CPF é único -> adiciona novo investidor
    FILE *fp = fopen("Projeto2C-main/shared/informacoesUsu.txt", "a");
    if (!fp) {
        perror("Erro ao abrir arquivo de dados");
        return;
    }
    fprintf(fp, "%s,%s,%s,0.00,0,0,0\n",
            cpf, senha,
            nome);
    fclose(fp);

    printf("Investidor %s cadastrado com sucesso!\n", nome);
}

void removerInvestidor() {
  char cpfBusca[15];
  char linha[256];
  char confirm;
  int encontrado = 0;

  printf("-- Remover Investidor --\n");
  printf("CPF do investidor: ");
  scanf(" %14s", cpfBusca);

  /* Ler todas as linhas e armazenar menos a do CPF informado */
  FILE *fp = fopen("Projeto2C-main/shared/informacoesUsu.txt", "r");
  if (!fp) {
      perror("Erro ao abrir arquivo de dados");
      return;
  }
  char **linhas = NULL;
  size_t count = 0;

  while (fgets(linha, sizeof(linha), fp)) {
      char tmp[15];
      /* copia CPF da linha */
      sscanf(linha, "%14[^,]", tmp);
      if (strcmp(tmp, cpfBusca) == 0) {
          printf("Investidor encontrado: %s", linha);
          encontrado = 1;
          printf("Confirma exclusão (s/n)? ");
          scanf(" %c", &confirm);
          if (confirm == 's' || confirm == 'S') {
              /* pula esta linha, não adiciona ao buffer */
              continue;
          } else {
              /* mantém a linha existente */
          }
      }
      /* mantem linha no buffer */
      linhas = realloc(linhas, (count + 1) * sizeof(char*));
      linhas[count] = strdup(linha);
      count++;
  }
  fclose(fp);

  if (!encontrado) {
      printf("CPF não encontrado. Nenhuma alteração realizada.\n");
      /* limpa memória */
      for (size_t i = 0; i < count; i++) free(linhas[i]);
      free(linhas);
      return;
  }

  /* Grava de volta as linhas mantidas */
  fp = fopen("Projeto2C-main/shared/informacoesUsu.txt", "w");
  if (!fp) {
      perror("Erro ao abrir arquivo para escrita");
      for (size_t i = 0; i < count; i++) free(linhas[i]);
      free(linhas);
      return;
  }
  for (size_t i = 0; i < count; i++) {
      fputs(linhas[i], fp);
      free(linhas[i]);
  }
  free(linhas);
  fclose(fp);

  printf("Operação concluída.\n");
}
