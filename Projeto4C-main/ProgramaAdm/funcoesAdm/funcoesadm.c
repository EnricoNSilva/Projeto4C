#include "../../shared/opcoes.h"

char** adicionarMoedas(char** moedas){
  // Abre o arquivo para escrita (sobrescreve o existente)
  FILE *cotacoes = fopen("Projeto2C-main/shared/cotacoes.txt", "w");
  if(cotacoes == NULL){
    printf("Erro ao abrir o arquivo.\n");
    return NULL;
  }
 else{
    printf("Buscando moedas...");
    // Percorre até 20 tokens (10 pares nome/valor)
    for(int i = 0; i < 20; i++){
      // Se o ponteiro não for NULL e não estiver marcado "NULL"
      if(moedas[i] != NULL && strcmp(moedas[i], "NULL") != 0){
       printf("Alterando moedas...\n");
        if(i%2 == 0){
        // Índices pares armazenam o nome da moeda
         fprintf(cotacoes, "%s,", moedas[i]);
        }
       else{
         // Índices ímpares armazenam o valor (string), converte para inteiro
         fprintf(cotacoes, "%d\n", atoi(moedas[i]));
        }
     }
   }

  }

  printf("Alteração concluída!\n");
  fclose(cotacoes);
  return 0;
}


char** cadastrarMoedas(){
  FILE *cotacoes = fopen("Projeto2C-main/shared/cotacoes.txt", "r");
  if(cotacoes == NULL){
    printf("Erro ao abrir o arquivo.\n");
    return NULL;
  }
  // Armazena até 10 pares nome/valor
  static char* valores[20];
  int cotas=0;
  char buffer[255];
  
  // Lê linha a linha e separa tokens por vírgula ou nova linha
  while(fgets(buffer, sizeof(buffer), cotacoes)){
    char *delimitador = strtok(buffer, ",\n");
    while(delimitador != NULL){
      valores[cotas] = strdup(delimitador); // Cópia do token
      delimitador = strtok(NULL, ",\n");
      cotas++;
    }
    free(delimitador);
  }
  // Exibe as moedas já cadastradas (apenas nomes)
  printf("----------| Acesso as moedas cotadas |----------------\n");
  for(int i = 0; i < cotas; i++){
    if(i%2 == 0){
      printf("%s\n", valores[i]);
    }
  }
  printf("------------------| Cadastro Moeda |------------------\n");
  // Aloca buffers para entrada do usuário
  char *nova_moeda = malloc(20 * sizeof(char));
  char *valor_moeda = malloc(20 * sizeof(char));
  while(1){
    printf("Digite o nome da nova moeda para cadastrar: \n");
    scanf("%s", nova_moeda);
    printf("Digite o valor da cotacao da nova moeda para cadastrar: \n");
    scanf("%s", valor_moeda);
    // Conta quantos tokens já existem
    int qtd_valores = 0;
    for(int l=0;l<20;l++){
      if(valores[l] != NULL){
        qtd_valores++;
      }
    }
    // Verifica se a moeda já existe
    int permissao;
    for(int l = 0; l< qtd_valores; l++){
      if(l%2 == 0){
        if(strcmp(valores[l], nova_moeda) == 0){
        permissao = 1;
        }
        else{
          permissao = 0;
        }
      }
      
    }

    if(permissao == 1){
      printf("moeda ja cadastrada.\n");
    }
    else if(permissao == 0){
      // Adiciona nos próximos índices vazios
      printf("quantidade de moedas: %d\n", qtd_valores/2);
  
      valores[qtd_valores] = malloc(20 * sizeof(char));
      valores[qtd_valores+1] = malloc(20 * sizeof(char));
      
      strcpy(valores[qtd_valores], nova_moeda);
      strcpy(valores[qtd_valores+1], valor_moeda);
      free(nova_moeda);
      free(valor_moeda);
      // Exibe nova lista de nomes
      printf("----------| Acesso as novas moedas cotadas |----------------\n");
      for(int i = 0; i <= qtd_valores; i++){
        if(i%2 == 0){
          printf("%s\n", valores[i]);
        }
      }
      printf("-------------------------------------------------------\n");
      // Regrava arquivo com todas as moedas
      adicionarMoedas(valores);
      break;
    }
    
  }
  return valores; // retorna a lista atualizada
  fclose(cotacoes);
}

char** removerMoedas(){
  FILE *cotacoes = fopen("Projeto2C-main/shared/cotacoes.txt", "r");
  if(cotacoes == NULL){
    printf("Erro ao abrir o arquivo.\n");
    return NULL;
  }

  static char* valores[20];
  int cotas=0;

  char buffer[255];
  while(fgets(buffer, sizeof(buffer), cotacoes)){
    char *delimitador = strtok(buffer, ",\n");
    while(delimitador != NULL){
      valores[cotas] = strdup(delimitador);
      delimitador = strtok(NULL, ",\n");
      cotas++;
    }
    free(delimitador);
  }
  // Exibe nomes disponíveis
  printf("-----------------| Acesso para remover moedas |-----------------\n");
  for(int i = 0; i < cotas; i++){
    if(i%2 == 0){
      printf("%s\n", valores[i]);
    }
  }

  printf("-------------------------------------------------------\n");
  
    printf("------------------| Remocao de Moeda |------------------\n");
    char *moeda_remover = malloc(20 * sizeof(char));
    printf("Digite o nome da nova moeda para remover: \n");
    scanf("%19s", moeda_remover); // lê nome a remover

    int found = 0;
    for(int l=0; l< cotas;l += 2){
      if (strcmp(valores[l], moeda_remover) == 0) {
        // Marca nome e valor como NULL
        strcpy(valores[l],   "NULL");
        strcpy(valores[l+1],   "NULL");
        // regrava sem prints de clear
        adicionarMoedas(valores);  // regrava sem o par removido
        printf("Moeda '%s' removida com sucesso.\n", moeda_remover);
        found = 1;
        break;
      }
    }
    if (!found) {
      printf("Moeda '%s' não encontrada.\n", moeda_remover);
    }
    free(moeda_remover);
    fclose(cotacoes);
    return valores;
  }
  

char** obterSaldoUsu(){
  FILE *informacoesUsu = fopen("Projeto2C-main/shared/informacoesUsu.txt", "r");
  if(informacoesUsu == NULL){
    printf("Erro ao abrir o arquivo.\n");
    return NULL;
  }
  
  char* cpf = malloc(15 * sizeof(char));
  static char *moedasCadastradas[10];
  
  printf("-----------| Acesso para obter saldos de investidores |--------\n");
  printf("Digite o CPF do usuario que deseja consultar o seu saldo:\n");
  scanf("%s", cpf);
  // importarInfo retorna array de dados do usuário
  char** dadosUsu = {importarInfo(cpf)};
  
  if(!dadosUsu){
      printf("CPF não encontrado.\n");
      return NULL;
    }
  // Procura CPF nos dados (índice até 10)
  for(int procurarCPF=0;procurarCPF<10;procurarCPF++){
    if(strcmp(dadosUsu[procurarCPF], cpf) == 0){
      // Lê cotacoes para cálculo de saldos
      FILE *cotacoes = fopen("Projeto2C-main/shared/cotacoes.txt", "r");
      if(cotacoes == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
      }

      int cotas=0;

      char buffer[255];
      while(fgets(buffer, sizeof(buffer), cotacoes)){
        char *delimitador = strtok(buffer, ",\n");
        while(delimitador != NULL){
          moedasCadastradas[cotas] = strdup(delimitador);
          delimitador = strtok(NULL, ",\n");
          cotas++;
        }
        free(delimitador);
      }
      fclose(cotacoes);
    
      int qtd_valores = 0;
      for(int l=0;l<20;l++){
        if(moedasCadastradas[l] != NULL){
          qtd_valores++;
        }
      }

      char* nome_moedas[10];
      float valor[10];

      for(int adicionarmoedas=0;adicionarmoedas<5;adicionarmoedas++){
        if(adicionarmoedas%2==0){
          nome_moedas[adicionarmoedas] = moedasCadastradas[adicionarmoedas];
        }
      }
      // Sincroniza valores de moedas com dados do usuário
        int sincronizar=3;

        for(int valoresMoedas=0;valoresMoedas<6;valoresMoedas++){
          valor[valoresMoedas] = atof(dadosUsu[sincronizar]);
          sincronizar>=6?sincronizar=sincronizar:sincronizar++;
        }
       // Exibe saldos
      printf("-------------------------------------------------------\n");
      printf("CPF encontrado.\n");
      printf("saldo em reais: %s\n", dadosUsu[3]);
      
      for(int exibirSaldos=0;exibirSaldos<3;exibirSaldos++){
        printf("saldo em %s: %.2f\n", exibirSaldos%2==0?nome_moedas[exibirSaldos]:nome_moedas[exibirSaldos+3], valor[exibirSaldos+1]>0?valor[exibirSaldos+1]:0.00);
      }
      break; 
    }
  }
  return NULL;
}