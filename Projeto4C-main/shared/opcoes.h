#ifndef opcoes
#define opcoes

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

struct dados{
  char* nome;
  int cpf;
  int senhas;
  int qtd_moedas;
};

struct moedas {
  char *nome_moeda[10];
  float valor[10];
  int total_moedas;
  int cpf_moedas;
  float saldo_reais;
};

int atualizarcotacao();
void deposito(char *usuario, struct moedas *informacoes);
void comprarCripto(char *cpf, struct moedas *informacoes);
void saldo(char *usuario);
void venderCripto(char *usuario, struct moedas *informacoes);
char **importarInfo(char *usuarioProcurado);
int editaArquivo(char *identificadorUsuario, char *campo, float novoValor);
void saque(char *usuario);
int verificarSenha(char *usuario, char *senha);
int verificarSenhaAdmin(char *usuario, char *senha);
int alternativa(int num, char *cpf);
void registrarTransacao(const char *cpf, const char *operacao, float valor, const char *detalhes);
void consultarExtrato(const char *cpf);
char** adminInfo(char *AdminProcurado);
void consultarExtratoAdmin();
void cadastrarInvestidor();
void removerInvestidor();

#endif