#include "lib.h"
#include <stdio.h>
#include <string.h>

int salvar(ListaDeTarefas *lt, char *strArquivo) {
  FILE *f = fopen(strArquivo, "wb");
  if (f == NULL) {
    return 1;
  }
  fwrite(lt, sizeof(ListaDeTarefas), 1, f);
  fclose(f);
  return 0;
}
int carregar(ListaDeTarefas *lt, char *strArquivo) {
  FILE *f = fopen(strArquivo, "rb");
  if (f == NULL) {
    return 1;
  }
  fread(lt, sizeof(ListaDeTarefas), 1, f);
  fclose(f);
  return 0;
}
int criaTarefa(ListaDeTarefas *lt) {
  if (lt->qtd >= TOTAL_TAREFAS) {
    return 1;
  }
  Tarefa *t = &lt->tarefas[lt->qtd];

  do {
    printf("\nESCOLHA A CATEGORIA DA TAREFA:\n");
    printf(
        "1. Trabalho\n2. Estudos\n3. Familia/Amigos\n4. Pessoal\n5. Outros\n");
    scanf("%d", &t->categoria);
    if (t->categoria < 1 || t->categoria > 5) {
      printf("Erro: valor inválido, digite um numero entre 1 a 5\n");
    }
  } while (t->categoria < 1 || t->categoria > 5);
  do {
    printf("\nDIGITE A PRIORIDADE DA TAREFA (0 - Mais importante // 10 - menos "
           "importante):\n");
    scanf("%d", &t->prioridade);
    if (t->prioridade < 0 || t->prioridade > 10) {
      printf("Erro: valor inválido, digite um numero entre 0 e 10\n");
    }
  } while (t->prioridade < 0 || t->prioridade > 10);

  printf("DIGITE A DESCRICAO DA TAREFA:\n");
  scanf("%s[\n]", t->descricao);

  t->estado = 0;

  lt->qtd++;

  return 0;
}
int listaTarefas(ListaDeTarefas *lt) {
  if (lt->qtd == 0) {
    return 1;
  }

  for (int i = 0; i < lt->qtd; i++) {
    Tarefa *t = &lt->tarefas[i];

    printf("\n--- TAREFA %d ---\n", i);
    if (t->categoria == 1) {
      printf("CATEGORIA: Trabalho\n");
    } else if (t->categoria == 2) {
      printf("CATEGORIA: Estudos\n");
    } else if (t->categoria == 3) {
      printf("CATEGORIA: Familia/Amigos\n");
    } else if (t->categoria == 4) {
      printf("CATEGORIA: Pessoal\n");
    } else if (t->categoria == 5) {
      printf("CATEGORIA: Outros\n");
    } else {
      printf("!!!CATEGORIA INVALIDA.\n");
    }
    printf("PRIORIDADE: %d\n", t->prioridade);
    printf("DESCRICAO: %s\n", t->descricao);
    if (t->estado == 0) {
      printf("ESTADO: Nao iniciado\n");
    } else if (t->estado == 1) {
      printf("ESTADO: Em andamento\n");
    } else if (t->estado == 2) {
      printf("ESTADO: Concluido\n");
    } else {
      printf("!!!ESTADO INVALIDO.\n");
    }
  }
  return 0;
}
int deletaTarefa(ListaDeTarefas *lt) {
  if (lt->qtd == 0) {
    return 1;
  }
  int boolUsuario; // VARIÁVEL BOOLEANA QUE VAI DIZER SE O USUÁRIO JÁ SABE A
                   // POSIÇÃO DA TAREFA QUE ELE DESEJA DELETAR NA LISTA
  int posTarefa;
  printf("VOCE JA SABE EM QUE POSICAO ESTA A TAREFA QUE DESEJA DELETAR? (1 = "
         "SIM // 0 = NÃO)\n");
  scanf("%d", &boolUsuario);
  if (boolUsuario == 0) {
    listaTarefas(lt);
    printf(
        "\nA PARTIR DA LISTA, DIGITE O NUMERO DA TAREFA QUE DESEJA DELETAR:\n");
    scanf("%d", &posTarefa);
  } else if (boolUsuario == 1) {
    printf("DIGITE A POSICAO DA TAREFA QUE DESEJA DELETAR:\n");
    scanf("%d", &posTarefa);
  }
  for (; posTarefa < lt->qtd - 1; posTarefa++) {
    strcpy(lt->tarefas[posTarefa].descricao,
           lt->tarefas[posTarefa + 1].descricao);
    lt->tarefas[posTarefa].categoria = lt->tarefas[posTarefa + 1].categoria;
    lt->tarefas[posTarefa].estado = lt->tarefas[posTarefa + 1].estado;
    lt->tarefas[posTarefa].prioridade = lt->tarefas[posTarefa + 1].prioridade;
  }
  lt->qtd--;
  return 0;
}
int alterarTarefa(ListaDeTarefas *lt) {
  if (lt->qtd == 0) {
    return 1;
  }
  int boolUsuario; // VARIÁVEL BOOLEANA QUE VAI DIZER SE O USUÁRIO JÁ SABE A
                   // POSIÇÃO DA TAREFA QUE ELE DESEJA DELETAR NA LISTA
  int posTarefa;
  printf("VOCE JA SABE EM QUE POSICAO ESTA A TAREFA QUE DESEJA DELETAR? (1 = "
         "SIM // 0 = NÃO)\n");
  scanf("%d", &boolUsuario);
  if (boolUsuario == 0) {
    listaTarefas(lt);
    printf(
        "\nA PARTIR DA LISTA, DIGITE O NUMERO DA TAREFA QUE DESEJA DELETAR:\n");
    scanf("%d", &posTarefa);
  } else if (boolUsuario == 1) {
    printf("DIGITE A POSICAO DA TAREFA QUE DESEJA DELETAR:\n");
    scanf("%d", &posTarefa);
  }
  int opcao; // VARIÁVEL PARA ARMAZENAR QUAL CAMPO O USUÁRIO ESCOLHEU ALTERAR
  printf("\nESCOLHA O CAMPO QUE DESEJA ALTERAR:\n");
  do {
    printf("1. Categoria\n2. Prioridade\n3. Descricao\n4. Estado\n");
    scanf("%d", &opcao);
    if (opcao < 1 || opcao > 4) {
      printf("Opcao invalida, digite um numero de 1 a 4.\n");
    }
  } while (opcao < 1 || opcao > 4);
  if (opcao == 1) {
    printf("\nESCOLHA A NOVA CATEGORIA DA TAREFA:\n1. Trabalho\n2. Estudos\n3. "
           "Familia/Amigos\n4. Pessoal\n5. Outros\n");
    scanf("%d", &lt->tarefas[posTarefa].categoria);
  } else if (opcao == 2) {
    printf("\nDIGITE A NOVA PRIORIDADE DA TAREFA (0 - Mais importante // 10 - "
           "menos importante):\n");
    scanf("%d", &lt->tarefas[posTarefa].prioridade);
  } else if (opcao == 3) {
    char auxDesc[300];
    printf("\nDIGITE A NOVA DESCRICAO DA TAREFA:\n");
    scanf("%s", auxDesc);
    strcpy(lt->tarefas[posTarefa].descricao, auxDesc);
  } else if (opcao == 4) {
    printf("\nESCOLHA O NOVO ESTADO DA TAREFA\n");
    printf("0. Nao iniciado\n1. Em andamento\n2. Concluido\n");
    scanf("%d", &lt->tarefas[posTarefa].estado);
  } else {
    printf("Erro: opcao invalida.\n");
  }
  return 0;
}
int filtrarTarefas(ListaDeTarefas *lt) {
  if (lt->qtd == 0) {
    return 1;
  }
  int opcao;
  printf("ESCOLHA O FILTRO QUE DESEJA APLICAR:\n");
  do {
    printf(
        "1. Prioridade\n2. Estado\n3. Categoria\n4. Prioridade + Categoria\n");
    scanf("%d", &opcao);
    if (opcao < 1 || opcao > 4) {
      printf("Opcao invalida, digite um numero de 1 a 4.\n");
    }
  } while (opcao < 1 || opcao > 4);
  if (opcao == 1) {
    int auxPri; // VARIÁVEL PARA ARMAZENAR A PRIORIDADE ESCOLHIDA PELO USUIÁRIO
    printf("\nDIGITE A PRIORIDADE QUE DESEJA VER (0 - Mais importante // 10 - "
           "menos importante):\n");
    scanf("%d", &auxPri);
    for (int i = 0; i < lt->qtd; i++) {
      Tarefa *t = &lt->tarefas[i];
      if (t->prioridade == auxPri) {
        printf("\n--- TAREFA %d ---\n", i);
        if (t->categoria == 1) {
          printf("CATEGORIA: Trabalho\n");
        } else if (t->categoria == 2) {
          printf("CATEGORIA: Estudos\n");
        } else if (t->categoria == 3) {
          printf("CATEGORIA: Familia/Amigos\n");
        } else if (t->categoria == 4) {
          printf("CATEGORIA: Pessoal\n");
        } else if (t->categoria == 5) {
          printf("CATEGORIA: Outros\n");
        } else {
          printf("!!!CATEGORIA INVALIDA.\n");
        }
        printf("PRIORIDADE: %d\n", t->prioridade);
        printf("DESCRICAO: %s\n", t->descricao);
        if (t->estado == 0) {
          printf("ESTADO: Nao iniciado\n");
        } else if (t->estado == 1) {
          printf("ESTADO: Em andamento\n");
        } else if (t->estado == 2) {
          printf("ESTADO: Concluído\n");
        } else {
          printf("!!!ESTADO INVALIDO.\n");
        }
      }
    }
  } else if (opcao == 2) {
    int auxEst; // VARIÁVEL PARA ARMAZENAR O ESTADO ESCOLHIDA PELO USUIÁRIO
    do {
      printf("\nESCOLHA O ESTADO QUE DESEJA VER:\n");
      printf("0. Nao iniciado\n1. Em andamento\n2. Concluido\n");
      scanf("%d", &auxEst);
      if (auxEst < 0 || auxEst > 2) {
        printf("Opcao invalida, digite um numero entre 0 e 2\n");
      }
    } while (auxEst < 0 || auxEst > 2);
    for (int i = 0; i < lt->qtd; i++) {
      Tarefa *t = &lt->tarefas[i];
      if (t->estado == auxEst) {
        printf("\n--- TAREFA %d ---\n", i);
        if (t->categoria == 1) {
          printf("CATEGORIA: Trabalho\n");
        } else if (t->categoria == 2) {
          printf("CATEGORIA: Estudos\n");
        } else if (t->categoria == 3) {
          printf("CATEGORIA: Familia/Amigos\n");
        } else if (t->categoria == 4) {
          printf("CATEGORIA: Pessoal\n");
        } else if (t->categoria == 5) {
          printf("CATEGORIA: Outros\n");
        } else {
          printf("!!!CATEGORIA INVALIDA.\n");
        }
        printf("PRIORIDADE: %d\n", t->prioridade);
        printf("DESCRICAO: %s\n", t->descricao);
        if (t->estado == 0) {
          printf("ESTADO: Nao iniciado\n");
        } else if (t->estado == 1) {
          printf("ESTADO: Em andamento\n");
        } else if (t->estado == 2) {
          printf("ESTADO: Concluído\n");
        } else {
          printf("!!!ESTADO INVALIDO.\n");
        }
      }
    }
  } else if (opcao == 3) {
    int auxCat;
    do {
      printf("ESCOLHA A CATEGORIA QUE DESEJA VER:\n");
      printf("1. Trabalho\n2. Estudos\n3. Familia/Amigos\n4. Pessoal\n5. "
             "Outros\n");
      scanf("%d", &auxCat);
      if (auxCat < 1 || auxCat > 5) {
        printf("Opcao invalida, digite um numero entre 1 e 5\n");
      }
    } while (auxCat < 1 || auxCat > 5);
    for (int i = 0; i <= 10;
         i++) { // A VARIÁVEL 'i' SERÁ UTILIZADA PARA ITERAR SOBRE AS POSSÍVEIS
                // PRIORIDADES DAS TAREFAR (DE 0 A 10)
      for (int auxPos = 0; auxPos < lt->qtd; auxPos++) {
        Tarefa *t = &lt->tarefas[auxPos];
        if (t->categoria == auxCat && t->prioridade == i) {
          printf("\n--- TAREFA %d ---\n", i);
          if (t->categoria == 1) {
            printf("CATEGORIA: Trabalho\n");
          } else if (t->categoria == 2) {
            printf("CATEGORIA: Estudos\n");
          } else if (t->categoria == 3) {
            printf("CATEGORIA: Familia/Amigos\n");
          } else if (t->categoria == 4) {
            printf("CATEGORIA: Pessoal\n");
          } else if (t->categoria == 5) {
            printf("CATEGORIA: Outros\n");
          } else {
            printf("!!!CATEGORIA INVALIDA.\n");
          }
          printf("PRIORIDADE: %d\n", t->prioridade);
          printf("DESCRICAO: %s\n", t->descricao);
          if (t->estado == 0) {
            printf("ESTADO: Nao iniciado\n");
          } else if (t->estado == 1) {
            printf("ESTADO: Em andamento\n");
          } else if (t->estado == 2) {
            printf("ESTADO: Concluído\n");
          } else {
            printf("!!!ESTADO INVALIDO.\n");
          }
        }
      }
    }
  } else if (opcao == 4) {
  }
  return 0;
}
int exportarTarefas(ListaDeTarefas *lt) {
  if (lt->qtd == 0) {
    return 1;
  }
  FILE *f = fopen("exportacao.txt", "w");
  if (f == NULL) {
    return 2;
  }
  int opcao;
  int auxPrioridade;
  int auxCategoria;
  int auxBoolPrioridade;
  int auxBoolCategoria;
  do {
    printf("ESCOLHA QUAL FILTRO DESEJA APLICAR NA EXPORTACAO DAS TAREFAS:\n");
    printf("1. Prioridade\n2. Categoria\n3. Prioridade + Categoria\n");
    scanf("%d", &opcao);
    if (opcao < 1 || opcao > 3) {
      printf("Opcao invalida, digite um numero entre 1 e 3.\n");
    }
  } while (opcao < 1 || opcao > 3);
  if (opcao == 1 || opcao == 3) {
    do {
      printf("DIGITE A PRIORIDADE DAS TAREFAS QUE DESEJA EXPORTAR (0 a 10):\n");
      scanf("%d", &auxPrioridade);
      if (auxPrioridade < 0 || auxPrioridade > 10) {
        printf("Opcao invalida, digite um número entre 0 e 10.\n");
      }
    } while (auxPrioridade < 0 || auxPrioridade > 10);
  }
  if (opcao == 2 || opcao == 3) {
    do {
      printf("\nESCOLHA A CATEGORIA DA TAREFA:\n");
      printf("1. Trabalho\n2. Estudos\n3. Familia/Amigos\n4. Pessoal\n5. "
             "Outros\n");
      scanf("%d", &auxCategoria);
      if (auxCategoria < 1 || auxCategoria > 5) {
        printf("Opcao invalida, digite um numero entre 1 e 5\n");
      }
    } while (auxCategoria < 1 || auxCategoria > 5);
  }
  for (int i = 0; i < lt->qtd; i++) {
    Tarefa *t = &lt->tarefas[i];
    if (opcao == 1) {
      auxBoolCategoria = 1;
      auxBoolPrioridade = 0;
      if (t->prioridade == auxPrioridade) {
        auxBoolPrioridade = 1;
      }
    } else if (opcao == 2) {
      auxBoolCategoria = 0;
      auxBoolPrioridade = 1;
      if (t->categoria == auxCategoria) {
        auxBoolCategoria = 1;
      }
    } else if (opcao == 3) {
      auxBoolCategoria = 0;
      auxBoolPrioridade = 0;
      if (t->prioridade == auxPrioridade) {
        auxBoolPrioridade = 1;
      }
      if (t->categoria == auxCategoria) {
        auxBoolCategoria = 1;
      }
    }
    if (auxBoolCategoria && auxBoolPrioridade) {
      fprintf(f, "PRIORIDADE: %d  ", t->prioridade);
      if (t->categoria == 1) {
        fprintf(f, "CATEGORIA: Trabalho  ");
      } else if (t->categoria == 2) {
        fprintf(f, "CATEGORIA: Estudos  ");
      } else if (t->categoria == 3) {
        fprintf(f, "CATEGORIA: Familia/Amigos  ");
      } else if (t->categoria == 4) {
        fprintf(f, "CATEGORIA: Pessoal  ");
      } else if (t->categoria == 5) {
        fprintf(f, "CATEGORIA: Outros  ");
      }
      if (t->estado == 0) {
        fprintf(f, "ESTADO: Nao iniciado  ");
      } else if (t->estado == 1) {
        fprintf(f, "ESTADO: Em andamento");
      } else if (t->estado == 2) {
        fprintf(f, "ESTADO: Concluido");
      }
      fprintf(f, "DESCRICAO: %s\n", t->descricao);
    }
  }
  fclose(f);
  return 0;
  }

  void exibeMenu() {
    printf("\n--- ESCOLHA UMA OPCAO ---\n\n");
    printf("1. Criar nova tarefa\n");
    printf("2. Apagar uma tarefa\n");
    printf("3. Listar tarefas\n");
    printf("4. Atualizar tarefa\n");
    printf("5. Buscar tarefas (Filtro)\n");
    printf("6. Exportar tarefas\n");
    printf("\n0. Sair\n");
  }