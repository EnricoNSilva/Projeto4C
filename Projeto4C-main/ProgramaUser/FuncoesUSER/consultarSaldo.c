#include "../../shared/opcoes.h"

void saldo(char *usuario) {
    char **dadosUsuario = importarInfo(usuario);
    if (!dadosUsuario) {
        printf("Usuário não encontrado.\n");
        sleep(2);
        return;
    }

    float saldoReais = atof(dadosUsuario[3]);
    float bitcoinAtual = atof(dadosUsuario[4]);
    float ethereumAtual = atof(dadosUsuario[5]);
    float rippleAtual = atof(dadosUsuario[6]);

    FILE *arquivoCotacoes = fopen("Projeto2C-main/shared/cotacoes.txt", "r");
    if (!arquivoCotacoes) {
        printf("Erro ao abrir arquivo de cotações.\n");
        sleep(2);
        return;
    }

    printf("\n------| Saldo atual do usuário |------\n");
    printf("Saldo em Reais: R$ %.2f\n", saldoReais);
    printf("--------------------------------------\n");

    char linha[256];
    char criptomoedas[10][20];
    float cotacoes[10];
    int numCripto = 0;

    while (fgets(linha, sizeof(linha), arquivoCotacoes) && numCripto < 5) {
        sscanf(linha, "%[^,],%f", criptomoedas[numCripto], &cotacoes[numCripto]);

        float saldoCripto;
        if (strcmp(criptomoedas[numCripto], "bitcoin") == 0)
            saldoCripto = bitcoinAtual;
        else if (strcmp(criptomoedas[numCripto], "ethereum") == 0)
            saldoCripto = ethereumAtual;
        else if (strcmp(criptomoedas[numCripto], "ripple") == 0)
            saldoCripto = rippleAtual;
        else
            saldoCripto = 0.00;

        printf("%s: %.8f (Cotação: R$ %.2f)\n", criptomoedas[numCripto],
               saldoCripto, cotacoes[numCripto]);

        numCripto++;
    }

    fclose(arquivoCotacoes);
    printf("--------------------------------------\n");
    sleep(3);
}
