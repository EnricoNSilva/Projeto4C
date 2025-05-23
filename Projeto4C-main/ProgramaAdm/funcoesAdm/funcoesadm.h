#ifndef funcoesadm
#define funcoesadm

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

char** cadastrarMoedas();
char** adicionarMoedas(char** moedas);
char** removerMoedas();
char** obterSaldoUsu();
int verificarSenhaAdmin(char *usuario, char *senha);


#endif