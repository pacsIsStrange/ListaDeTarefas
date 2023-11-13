#include "lib.h"
#include <stdio.h>
#include <string.h>

int main() {
  ListaDeTarefas lt;

  char strArquivo[] = "ListaDeTarefas.bin";
  int codAux, opcao;

  codAux = carregar(&lt, strArquivo);
  if (codAux != 0) {
    printf("Erro: não foi possível carregar a lista de tarefas\n");
    lt.qtd = 0;
  }

  do { // LOOP PARA EXIBIÇÃO CONTÍNUA DO MENU ATÉ QUE O USUÁRIO DECIDA SAIR
    exibeMenu();
    scanf("%d", &opcao); 
    if(opcao == 0){
      
    } else if (opcao == 1){
      codAux = criaTarefa(&lt);
      if (codAux == 1){printf("Erro: limite de tarefas atingido.\n'");}
    } else if (opcao == 2){
      codAux = deletaTarefa(&lt);
      if (codAux == 1){printf("Erro: nao existem tarefas para deletar.\n");}
    } else if (opcao == 3){
      codAux = listaTarefas(&lt);
      if (codAux == 1){printf("Erro: nao existem tarefas para listar.\n");}
    } else if (opcao == 4){
      codAux = alterarTarefa(&lt);
      if (codAux == 1){printf("Erro: nao existem tarefas para alterar.\n");}
    } else if (opcao == 5){
      codAux = filtrarTarefas(&lt);
      if (codAux == 1){printf("Erro: nao existem tarefas para filtrar.\n");}
    } else if (opcao == 6){
      codAux = exportarTarefas(&lt);
      if (codAux == 1){printf("Erro: nao existem tarefas para exportar.\n");}
      else if (codAux == 2){printf("Erro: não foi possível gerar o arquivo 'exportacao.txt'.\n");}
    }
    
  } while (opcao != 0); // ESTABELECE A CONDIÇÃO PARA PARAR A EXIBIÇÃO DO MENU

  codAux = salvar(&lt, strArquivo);
  if (codAux != 0){
    printf("Erro: não foi possível salvar as alteracoes da lista de tarefas no arquivo");
  }

}
