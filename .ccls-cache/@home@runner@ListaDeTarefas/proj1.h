#ifndef PROJETO_BIBLIOTECA_H
#define PROJETO_BIBLIOTECA_H

struct lista{ // DEFINIÇÃO DA STRUCT DA LISTA DE TAREFAS
        int prioridade; //VARIÁVEL QUE VAI ARMAZENAR A PRIORIDADE DA TAREFA (NÚMERO INTEIRO).
        char categoria[300]; //  ARRAY DE CARACTERES QUE VAI ARMAZENAR A CATEGORIA DA TAREFA
        char descricao[100]; // ARRAY DE CARACTERES QUE VAI ARMAZENAR A DESCRIÇÃO DA TAREFA
};

void criaTarefa(struct lista *lt);
void listaTarefas(int tam, struct lista *lt);
int tamanho(struct lista *lt);
void salvar(int tam, struct lista *lt);
void deletaTarefa(int *tam, struct lista *lt, int posTarefa);

#endif
