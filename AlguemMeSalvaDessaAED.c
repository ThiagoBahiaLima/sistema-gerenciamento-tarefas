#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int excluirTarefa(int tarefa){
   FILE *arq;
   FILE *clonearq;
   
   arq = fopen("Lista de tarefas.txt","r");
   clonearq = fopen("clone.txt","w");

   if(arq == NULL || clonearq == NULL){
      printf("Erro ao abrir lista de tarefas\n");
      return 0;
   }
   char linha[100];
   for(int conferirTarefa = 1;fgets(linha,sizeof(linha),arq);conferirTarefa++){
      if(conferirTarefa != tarefa){
         fprintf(clonearq,linha);
      }
   }

   fclose(arq);
   fclose(clonearq);

   remove("Lista de tarefas.txt");
   rename("clone.txt","Lista de tarefas.txt");

   return 0;
}

int editarTarefa(int tarefa){
   //Ponteiro para o arquivo
   FILE *arq;
   FILE *clonearq;
   //Abrir o arquivo
   arq = fopen("Lista de tarefas.txt","r");
   clonearq = fopen("clone.txt","w");
   //Verificar se arquivo foi aberto com êxito
   if(arq == NULL || clonearq == NULL){
      printf("Erro ao abrir lista de tarefas\n");
      return 0;
   }
   char linha[100];
   for(int conferirLinha = 1;fgets(linha,sizeof(linha),arq) != NULL;conferirLinha++){
      if(conferirLinha != tarefa){
         fprintf(clonearq,linha);
      }
      else{
         printf("Digite como quer editar essa tarefa: ");
         fflush(stdin);
         fgets(linha,sizeof(linha),stdin);
         fprintf(clonearq,linha);
      }
   }
   fclose(arq);
   fclose(clonearq);

   remove("Lista de tarefas.txt");
   rename("clone.txt","Lista de tarefas.txt");

   return 0;
}

int listarTarefas(){
   //Ponteiro para o arquivo
   FILE *arq;
   //Abrir o arquivo
   arq = fopen("Lista de tarefas.txt","r");
   //Verificar se arquivo foi aberto com êxito
   if(arq == NULL){
      printf("Erro ao abrir lista de tarefas\n");
      return 0;
   }
   char linha[100];
   for(int i = 1;fgets(linha,sizeof(linha),arq) != NULL;i++){
      printf("%d. %s",i,linha);
   }
   fclose(arq);
   return 0;
}

int cadastrarTarefas(int quantidadeTarefas){
   //Ponteiro para o arquivo
   FILE *arq;
   //Abrir o arquivo
   arq = fopen("Lista de tarefas.txt","a");
   //Verificar se arquivo foi aberto com êxito
   if(arq == NULL){
      printf("Erro ao abrir lista de tarefas\n");
      return 0;
   }
   char *tarefa = NULL;
   size_t capacidade = 0;
   for(int i = 0;i < quantidadeTarefas;i++){
      printf("Digite uma tarefa: ");
      fflush(stdin);
      getline(&tarefa,&capacidade,stdin);
      fprintf(arq,tarefa);
   }
   //Fecha o arquivo
   fclose(arq);
   return 0;
   
}

int main(){

   int escolha = 0;
   while(escolha != 6){
      printf("=== Sistema de Gerenciamento de Tarefas ===\n");
      printf("1. Cadastrar tarefa\n");
      printf("2. Listar tarefas\n");
      printf("3. Editar tarefa\n");
      printf("4. Excluir tarefa\n");
      printf("5. Salvar lista em um arquivo .txt\n"); //Ainda não está feito
      printf("6. Sair\n");
      printf("\nEscolha uma opção: ");
      //Seleciona uma opção
      scanf("%d",&escolha);

      switch(escolha){
         case 1: printf("Escolha quantas tarefas quer cadastrar: ");
         int quantidade = 0;
         scanf("%d",&quantidade);
         cadastrarTarefas(quantidade);
         printf("Tarefas cadastradas com sucesso!\n");
         system("pause");
         break;
         case 2: listarTarefas();
         system("pause");
         break;
         case 3: listarTarefas();
         printf("Escolha uma tarefa para editar: ");
         int tarefa = 0;
         scanf("%d",&tarefa);
         editarTarefa(tarefa);
         printf("Tarefa editada com sucesso\n");
         system("pause");
         break;
         case 4: listarTarefas();
         printf("Escolha uma tarefa para excluir: ");
         int TAREFA = 0;
         scanf("%d",&TAREFA);
         excluirTarefa(TAREFA);
         printf("Tarefa excluida com sucesso\n");
         system("pause");
         break;
         case 5:
         break;
         case 6:printf("Encerrando programa...\n");
         break;
         default:printf("Escolha inválida\n");
         break;
      }
   }

   return 0;
}