#define TOTAL_TAREFAS 100

typedef struct {
  int prioridade;
  char descricao[300];
  int categoria;
  int estado;
} Tarefa;

typedef struct {
  Tarefa tarefas[TOTAL_TAREFAS];
  int qtd;
} ListaDeTarefas;

int salvar(ListaDeTarefas *lt, char *strArquivo);
int carregar(ListaDeTarefas *lt, char *strArquivo);
int criaTarefa(ListaDeTarefas *lt);
int listaTarefas(ListaDeTarefas *lt);
int deletaTarefa(ListaDeTarefas *lt);
int alterarTarefa(ListaDeTarefas *lt);
int filtrarTarefas(ListaDeTarefas *lt);
int exportarTarefas(ListaDeTarefas *lt);

void exibeMenu();