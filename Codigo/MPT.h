#ifndef MPT_H
#define MPT_H

int verificarExistenciaArquivo();
int escolherDiretorio(char *caminho,int tamanho);
int salvarArquivo();
int excluirTarefas(int *tarefas,int tamanho);
int editarTarefas(int *tarefas,int tamanho);
int listarTarefas();
int cadastrarTarefas(int quantidadeTarefas);

#endif