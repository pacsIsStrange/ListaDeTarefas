#include "lib.h"
#include <stdio.h>
#include <string.h>

int salvar(ListaDeTarefas *lt, char *strArquivo){
  FILE *f = fopen(strArquivo, "wb");
  if (f == NULL){
    return 1;
  }
  fwrite(lt, sizeof(ListaDeTarefas), 1, f);
  fclose(f);
  return 0;
}
int carregar(ListaDeTarefas *lt, char *strArquivo){
  FILE *f = fopen(strArquivo, "rb");
  if (f == NULL){
    return 1;
  }
  fread(lt, sizeof(ListaDeTarefas), 1, f);
  fclose(f);
  return 0;
}
int criaTarefa(ListaDeTarefas *lt){
  if (lt->qtd >= TOTAL_TAREFAS){
    return 1;
  }
  Tarefa *t = &lt->tarefas[lt->qtd];

  do {
    printf("\nESCOLHA A CATEGORIA DA TAREFA:\n1. Trabalho\n2. Estudos\n3. Familia/Amigos\n4. Pessoal\n5. Outros\n");
    scanf("%d", &t->categoria);
    if (t->categoria < 1 || t->categoria > 5){printf("Erro: valor inválido, digite um numero entre 1 a 5\N");}
  } while (t->categoria < 1 || t->categoria > 5);
  do {
  printf("\nDIGITE A PRIORIDADE DA TAREFA (0 - Mais importante // 10 - menos importante):\n");
  scanf("%d", &t->prioridade);
    if (t->prioridade < 0 || t->prioridade > 10){printf("Erro: valor inválido, digite um numero entre 0 e 10\n");}
  } while (t->prioridade < 0 || t->prioridade > 10);

  printf("DIGITE A DESCRICAO DA TAREFA:\n");
  scanf("%s[\n]", t->descricao);

  t->estado = 0;

  lt->qtd++;

  return 0;
}
int listaTarefas(ListaDeTarefas *lt){
  if (lt->qtd == 0){return 1;}

  for (int i = 0; i < lt->qtd; i++){
    Tarefa *t = &lt->tarefas[i];
    
    printf("\n--- TAREFA NUMERO %d ---\n", i);
    switch (t->categoria){
      case (1):
        printf("CATEGORIA: Trabalho\n");
      case (2):
        printf("CATEGORIA: Estudos\n");
      case (3):
        printf("CATEGORIA: Familia/Amigos\n");
      case (4):
        printf("CATEGORIA: Pessoal\n");
      case (5):
        printf("CATEGORIA: Outros\n");
    }
    printf("PRIORIDADE: %d\n", t->prioridade);
    printf("DESCRICAO: %s\n", t->descricao);
    switch(t->estado){
      case (0):
        printf("ESTADO: Não iniciado\n");
      case (1):
        printf("ESTADO: Em andamento\n");
      case (2):
        printf("ESTADO: Concluído\n");
    }
  }
};
int deletaTarefa(ListaDeTarefas *lt){
  int boolUsuario; // VARIÁVEL BOOLEANA QUE VAI DIZER SE O USUÁRIO JÁ SABE A POSIÇÃO DA TAREFA QUE ELE DESEJA DELETAR NA LISTA
  int posTarefa;
  printf("VOCE JA SABE EM QUE POSICAO ESTA A TAREFA QUE DESEJA DELETAR? (1 = SIM // 0 = NÃO)\n");
  scanf("%d", &boolUsuario);
  if (boolUsuario == 0){
    listaTarefas(lt);
    printf("\nA PARTIR DA LISTA, DIGITE O NUMERO DA TAREFA QUE DESEJA DELETAR:\n");
    scanf("%d", &posTarefa);
  }
  else if (boolUsuario == 1){
    printf("DIGITE A POSICAO DA TAREFA QUE DESEJA DELETAR:\n");
    scanf("%d", &posTarefa);
  }
  for (; posTarefa < lt->qtd - 1; posTarefa++){
    strcpy(lt->tarefas[posTarefa].descricao, lt->tarefas[posTarefa + 1].descricao);
    lt->tarefas[posTarefa].categoria = lt->tarefas[posTarefa + 1].categoria;
    lt->tarefas[posTarefa].estado = lt->tarefas[posTarefa + 1].estado;
    lt->tarefas[posTarefa].prioridade = lt->tarefas[posTarefa + 1].prioridade;
  }
}
int alterarTarefa(ListaDeTarefas *lt);
int filtrarTarefas(ListaDeTarefas *lt);
int exportarTarefas(ListaDeTarefas *lt);