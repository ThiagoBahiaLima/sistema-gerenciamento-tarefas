#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <shlobj.h>
#include "MPT.h"
#include "MPV.h"

int main(){

   int escolha = 0;
   while(escolha != 6){
      //interface inicial
      printf("=== Sistema de Gerenciamento de Tarefas ===\n");
      printf("1. Cadastrar tarefa\n");
      printf("2. Listar tarefas\n");
      printf("3. Editar tarefa\n");
      printf("4. Excluir tarefa\n");
      printf("5. Salvar lista em um arquivo .txt\n"); 
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
         case 3: printf("Escolha quantas tarefas quer editar: ");
            int quantidade2 = -1;
            while(quantidade2 < 0){
               scanf("%d",&quantidade2);
               if(quantidade2 < 0){
                  printf("Escolha uma quantidade valida: ");
               }
            }
            if(quantidade2 != 0){
               int tarefas[quantidade2];
               if(listarTarefas() != -1){
                  for(int i = 0;i < quantidade2;i++){
                     tarefas[i] = 0;
                     while(tarefas[i] <= 0){
                        printf("Digite o numero da tarefa que quer editar: ");
                        scanf("%d",&tarefas[i]);
                        if(tarefas[i] <= 0){
                           printf("Insira um valor natural não nulo\n");
                        }
                     }
                  }
                  ordenarVetor(tarefas,quantidade2);
                  if(editarTarefas(tarefas,quantidade2) == quantidade2){
                     printf("Todas as tarefas editadas com sucesso!\n");
                  }
                  else{
                     printf("Nem toda tarefa pôde ser editada ou algumas tarefas não existem\n");
                  }
               }
            }
            system("pause");
            break;
         case 4: printf("Escolha quantas tarefas quer excluir: ");
            int quantidade3 = -1;
            while(quantidade3 < 0){
               scanf("%d",&quantidade3);
               if(quantidade3 < 0){
                  printf("Escolha uma quantidade valida: ");
               }
            }
            if(quantidade3 != 0){
               if(listarTarefas() != -1){
                  int tarefas[quantidade3];
                  for(int i = 0;i < quantidade3;i++){
                     tarefas[i] = 0;
                     while(tarefas[i] <= 0){
                        printf("Digite o número da tarefa que quer excluir: ");
                        scanf("%d",&tarefas[i]);
                        if(tarefas[i] <= 0){
                           printf("Insira um valor natural não nulo\n");
                        }
                     }
                  }
                  ordenarVetor(tarefas,quantidade3);
                  if(excluirTarefas(tarefas,quantidade3) == quantidade3){
                     printf("Tarefas excluídas com sucesso!\n");
                  }
                  else{
                     printf("Nem toda tarefa pôde ser excluída ou algumas tarefas não existem\n");
                  }
               }
            }
            system("pause");
            break;
         case 5:salvarArquivo();
            break;
         case 6:printf("Encerrando programa...\n");
            Sleep(3000);
            break;
         default:printf("Escolha inválida\n");
            break;
      }
   }

   return 0;
}