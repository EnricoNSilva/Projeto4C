#include "../../shared/opcoes.h"

// Função para verificar a senha do usuário
int verificarSenha(char *usuario, char *senha) {
  char **dadosUsuario = importarInfo(usuario);
  if (dadosUsuario != NULL) {
    if (strcmp(senha, dadosUsuario[1]) == 0) {
      return 1; // Senha correta
    }
  }
  return 0; // Senha incorreta ou usuário não encontrado
}

