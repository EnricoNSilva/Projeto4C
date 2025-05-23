#include "../../shared/opcoes.h"

void consultarExtratoAdmin() {
    char cpfBusca[15];
    printf("-- Extrato de Investidor (Admin) --\n");
    printf("Informe o CPF do investidor: ");
    scanf(" %14s", cpfBusca);
    consultarExtrato(cpfBusca);
}
