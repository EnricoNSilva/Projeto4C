#include "../../shared/opcoes.h"

int verificarSenhaAdmin(char *cpfAdmin, char *senha){
  char **dadosAdmin = adminInfo(cpfAdmin);
  if (dadosAdmin != NULL){
    if (strcmp(senha, dadosAdmin[1]) == 0 && strcmp(cpfAdmin, dadosAdmin[0])==0){
      return 1;
    }
  }

  return 0;
}