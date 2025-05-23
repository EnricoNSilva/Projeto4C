#include "../opcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxLinha   256
#define MaxCampos  10

/**
 * importarInfo:
 *   Procura uma linha em `shared/informacoesUsu.txt` cujo CPF (primeiro campo 
 *   antes da vírgula) seja igual a usuarioProcurado, e retorna um array estático
 *   de strings com os campos dessa linha (até MaxCampos).
 * 
 *   Retorna NULL se não encontrar ou em caso de erro de arquivo.
 */
char** importarInfo(char* usuarioProcurado) {
    FILE *arquivoUsu = fopen("Projeto2C-main/shared/informacoesUsu.txt", "r");
    if (arquivoUsu == NULL) {
        perror("Erro ao abrir Projeto2C-main/shared/informacoesUsu.txt");
        return NULL;
    }

    static char* informacoes[MaxCampos];
    char linha[MaxLinha];

    while (fgets(linha, sizeof(linha), arquivoUsu)) {
        // Faz uma cópia, pois strtok modifica a string
        char *tempLinha = strdup(linha);
        char *cpf = strtok(tempLinha, ",\n");

        if (cpf && strcmp(cpf, usuarioProcurado) == 0) {
            // Preenche o array retornável
            int i = 0;
            informacoes[i++] = strdup(cpf);

            char *token;
            while ((token = strtok(NULL, ",\n")) != NULL && i < MaxCampos) {
                informacoes[i++] = strdup(token);
            }
            // Se houver menos campos que MaxCampos, opcionalmente zerar o resto:
            for (; i < MaxCampos; i++) {
                informacoes[i] = NULL;
            }

            free(tempLinha);
            fclose(arquivoUsu);
            return informacoes;
        }

        free(tempLinha);
    }

    // Fecha e indica não encontrado
    fclose(arquivoUsu);
    return NULL;
}

/**
 * adminInfo:
 *   Mesma lógica, mas para o arquivo de administradores em `shared/informacoesAdm.txt`.
 */
char** adminInfo(char* AdminProcurado) {
    FILE *arquivoAdm = fopen("Projeto2C-main/shared/informacoesAdm.txt", "r");
    if (arquivoAdm == NULL) {
        perror("Erro ao abrir Projeto2C-main/shared/informacoesAdm.txt");
        return NULL;
    }

    static char* admInfo[MaxCampos];
    char linha[MaxLinha];

    while (fgets(linha, sizeof(linha), arquivoAdm)) {
        char *tempLinha = strdup(linha);
        char *cpf = strtok(tempLinha, ",\n");

        if (cpf && strcmp(cpf, AdminProcurado) == 0) {
            int i = 0;
            admInfo[i++] = strdup(cpf);

            char *token;
            while ((token = strtok(NULL, ",\n")) != NULL && i < MaxCampos) {
                admInfo[i++] = strdup(token);
            }
            for (; i < MaxCampos; i++) {
                admInfo[i] = NULL;
            }

            free(tempLinha);
            fclose(arquivoAdm);
            return admInfo;
        }

        free(tempLinha);
    }

    fclose(arquivoAdm);
    return NULL;
}
