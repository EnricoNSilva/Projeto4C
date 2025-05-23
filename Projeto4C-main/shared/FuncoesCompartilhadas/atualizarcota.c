#include "../opcoes.h"

char **obterCotacoes(){
  static char *valores[20];   // até 10 moedas (nome+valor)
  int cotas = 0;

  FILE *cotacoes = fopen("Projeto2C-main/shared/cotacoes.txt", "r");
  if (!cotacoes) {
    printf("Erro ao abrir o arquivo.\n");
    return NULL;
  }

  char buffer[255];
  while (fgets(buffer, sizeof(buffer), cotacoes) && cotas < 20) {
    // separa "nome,valor\n"
    char *token = strtok(buffer, ",\n");
    while (token != NULL && cotas < 20) {
      valores[cotas++] = strdup(token);
      token = strtok(NULL, ",\n");
    }
  }

  fclose(cotacoes);
  return valores;
}

int atualizarcotacao(){
  // 2) atribuição direta, sem chaves extras nem inicialização estranha
  char **cotacoes = obterCotacoes();
  if (!cotacoes) return 0;

  FILE *fout = fopen("Projeto2C-main/shared/cotacoes.txt", "w");
  if (!fout) {
    printf("Erro ao abrir o arquivo para escrita.\n");
    return 0;
  }

  printf("----------| Acesso as novas cotações |----------------\n");

  // consideramos sempre 5 moedas (10 tokens)
  for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
      // nome
      fprintf(fout, "%s,", cotacoes[i]);
    } else {
      // valor antigo
      printf("cotação da moeda %s anteriormente: %s\n",
             cotacoes[i - 1], cotacoes[i]);

      // gera variação entre -3% e +3%
      float variador;
      if (rand() % 2 == 0) {
        variador = -((rand() % 3 + 1) / 100.0f);
      } else {
        variador = ((rand() % 3 + 1) / 100.0f);
      }

      printf("variacao da moeda: %.2f ponto percentual\n",
             variador * 100);

      int antigo = atoi(cotacoes[i]);
      int novo   = antigo + (int)(antigo * variador);
      if (novo < 0) novo = 0;

      fprintf(fout, "%d\n", novo);
    }
  }

  printf("-------------------------------------------------------\n");
  fclose(fout);
  return 1;
}
