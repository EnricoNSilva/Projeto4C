#include "../../shared/opcoes.h"

void saque(char *usuario) {
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

    // Pede o valor do saque
    printf("Digite o quantia do saque (ou digite 0 para cancelar): ");

    float valorRetirada;
    while (1) {
        if (scanf("%f", &valorRetirada) != 1) {
            // Limpa o buffer de entrada em caso de erro
            while (getchar() != '\n');
            printf("Valor inválido, digite um número: ");
            continue;
        }

        if (valorRetirada == 0) {
            printf("Voltando ao menu.\n");
            sleep(2);
            return;
        }

        if (valorRetirada <= 0) {
            printf("Valor deve ser positivo, digite novamente: ");
            continue;
        }

        if (valorRetirada > saldoAtual) {
            printf("Saldo insuficiente :( , Saldo atual: R$ %.2f\nDigite um valor menor: ", saldoAtual);
            continue;
        }

        break; // Valor válido
    }

    // Processa o saque
    float novoSaldo = saldoAtual - valorRetirada;
    if (editaArquivo(usuario, "saldo", novoSaldo)) {
        registrarTransacao(usuario, "SAQUE", valorRetirada, "N/A");
        printf("\nSaque efetuado com sucesso!\n");
        printf("Valor sacado: R$ %.2f\n", valorRetirada);
        printf("Novo saldo: R$ %.2f\n", novoSaldo);
    } else {
        printf("Erro ao atualizar saldo.\n");
    }

    sleep(3); // Pausa para leitura
}