#ifndef MPT_H
#define MPT_H

int contarTarefas();
int verificarExistenciaArquivo();
int escolherDiretorio(char *caminho,int tamanho);
int salvarArquivo();
int excluirTarefas(int tarefa);
int editarTarefas(int tarefa);
int listarTarefas();
int cadastrarTarefas();

#endif