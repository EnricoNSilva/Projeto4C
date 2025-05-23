#include "../../shared/opcoes.h"

void comprarCripto(char *usuario, struct moedas *informacoes) {
  int continuar = 1;
  while (continuar) {
    // Obtém os dados do usuário primeiro para mostrar os saldos
    char **dadosUsuario = importarInfo(usuario);
    if (!dadosUsuario) {
      printf("Usuário não encontrado.\n");
      sleep(2);
      return;
    }

    float saldoAtual = atof(dadosUsuario[3]);
    float bitcoinAtual = atof(dadosUsuario[4]);
    float ethereumAtual = atof(dadosUsuario[5]);
    float rippleAtual = atof(dadosUsuario[6]);

    FILE *arquivoCotacoes = fopen("Projeto2C-main/shared/cotacoes.txt", "r");
    if (!arquivoCotacoes) {
      printf("Falha em tentar abrir o arquivo.\n");
      sleep(2);
      return;
    }

    char linha[256];
    char criptomoedas[10][20];
    float cotacoes[10];
    int numCriptomoedas = 0;

    printf("Criptomoedas disponíveis para compra:\n");
    while (fgets(linha, sizeof(linha), arquivoCotacoes)&& numCriptomoedas < 5) {
      sscanf(linha, "%[^,],%f", criptomoedas[numCriptomoedas],
             &cotacoes[numCriptomoedas]);

      //printf("%s", criptomoedas[numCriptomoedas]);

      // Mostra saldo junto com a cotação
      float saldoCripto;
      if (strcmp(criptomoedas[numCriptomoedas], "bitcoin") == 0)
        saldoCripto = bitcoinAtual;
      else if (strcmp(criptomoedas[numCriptomoedas], "ethereum") == 0)
        saldoCripto = ethereumAtual;
      else if (strcmp(criptomoedas[numCriptomoedas], "ripple") == 0)
        saldoCripto = rippleAtual;
      else
        saldoCripto = 0.00;

      printf("%d. %s (Cotação: R$ %.2f | Quantidade em carteira: %.8f)\n", numCriptomoedas + 1,
             criptomoedas[numCriptomoedas], cotacoes[numCriptomoedas],
             saldoCripto);
      numCriptomoedas++;
    }
    
    fclose(arquivoCotacoes);

    // Validação da escolha da criptomoeda
    int escolhaCripto;
    char input[10];
    int valido = 0;

    while (!valido) {
      printf(
          "\nEscolha o número da criptomoeda (ou pressione 0 para cancelar): ");
      fgets(input, sizeof(input), stdin);

      // Verifica se é número válido
      if (sscanf(input, "%d", &escolhaCripto) != 1) {
        printf("Entrada inválida, digite um número.\n");
        continue;
      }

      if (escolhaCripto == 0) {
        printf("Voltando ao menu.\n");
        sleep(1);
        return;
      }

      if (escolhaCripto < 1 || escolhaCripto > numCriptomoedas) {
        printf("Opção inválida, escolha um valor entre 1 e %d.\n",
               numCriptomoedas);
        continue;
      }

      valido = 1;
    }

    char *criptoEscolhida = criptomoedas[escolhaCripto-1];
    float saldoDisponivel;

    if (strcmp(criptoEscolhida, "bitcoin") == 0)
      saldoDisponivel = bitcoinAtual;
    else if (strcmp(criptoEscolhida, "ethereum") == 0)
      saldoDisponivel = ethereumAtual;
    else
      saldoDisponivel = rippleAtual;

    printf("Seu saldo atual em %s: %.8f\n", criptoEscolhida, saldoDisponivel);

    // Validação da quantidade
    float quantidade;
    valido = 0;

    while (!valido) {
      printf("Digite a quantidade que deseja comprar (ou 0 para cancelar):");
      fgets(input, sizeof(input), stdin);

      if (sscanf(input, "%f", &quantidade) != 1) {
        printf("Valor inválido, digite um número.\n");
        continue;
      }

      if (quantidade == 0) {
        printf("Operação cancelada.\n");
        sleep(1);
        return;
      }

      if (quantidade <= 0) {
        printf("A quantidade precisa ser positiva.\n");
        continue;
      }

      valido = 1;
    }

    // Processa a compra
    float cotacaoEscolhida = cotacoes[escolhaCripto - 1];
    float valorBruto = quantidade * cotacaoEscolhida;

    // Aplica taxa
    float taxa = (strcmp(criptoEscolhida, "bitcoin") == 0)    ? 0.02
                 : (strcmp(criptoEscolhida, "ethereum") == 0) ? 0.01
                                                              : 0.01;
    float valorLiquido = valorBruto * (1 - taxa);

    // Atualiza saldos
    if (strcmp(criptoEscolhida, "bitcoin") == 0) {
      editaArquivo(usuario, "bitcoin", bitcoinAtual + quantidade);
      informacoes->valor[0] = bitcoinAtual + quantidade;
    } else if (strcmp(criptoEscolhida, "ethereum") == 0) {
      editaArquivo(usuario, "ethereum", ethereumAtual + quantidade);
      informacoes->valor[1] = ethereumAtual + quantidade;
    } else if(strcmp(criptoEscolhida, "ripple") == 0){
      editaArquivo(usuario, "ripple", rippleAtual + quantidade);
      informacoes->valor[2] = rippleAtual + quantidade;
    }

    editaArquivo(usuario, "saldo", saldoAtual - valorLiquido);

    // Registra a transação
    char detalhes[100];
    snprintf(detalhes, sizeof(detalhes),
             "COMPRA_%s (QTD: %.8f, COTAÇÃO: R$ %.2f)", criptoEscolhida,
             quantidade, cotacaoEscolhida);
    registrarTransacao(usuario, "COMPRA_CRIPTO", valorLiquido, detalhes);

    // Mostra resumo
    printf("\n=== COMPRA REALIZADA COM SUCESSO ===\n");
    printf("Criptomoeda: %s\n", criptoEscolhida);
    printf("Quantidade: %.8f\n", quantidade);
    printf("Valor bruto: R$ %.2f\n", valorBruto);
    printf("Taxa: R$ %.2f (%.0f%%)\n", valorBruto * taxa, taxa * 100);
    printf("Valor líquido creditado: R$ %.2f\n", valorLiquido);
    printf("Novo saldo: R$ %.2f\n", saldoAtual + valorLiquido);

    // Pergunta se deseja continuar
    printf("\nDeseja comprar outra criptomoeda? (1-Sim / 0-Não): ");
    fgets(input, sizeof(input), stdin);
    continuar = (atoi(input) == 1);

    system("clear");
  }
}
