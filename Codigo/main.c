#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <shlobj.h>
#include "MPT.h"
#include "MPV.h"

int main(){

   system("chcp 65001");
   int verificarLeitura = 0;
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
      
      while(verificarLeitura != 1){
         printf("\nEscolha uma opção: ");
         verificarLeitura = scanf("%d",&escolha);
         if(verificarLeitura != 1){
            printf("Evite caracteres que não sejam números\n");
            while(getchar() != '\n');
         }
      }
      verificarLeitura = 0;

      switch(escolha){
         case 1: printf("\n");
            int quantidade = -1;
            while(verificarLeitura != 1 || quantidade < 0){
               printf("Escolha quantas tarefas quer cadastrar: ");
               verificarLeitura = scanf("%d",&quantidade);
               if(verificarLeitura != 1){
                  printf("Evite caracteres que não sejam números\n");
                  while(getchar() != '\n');
               }
               else{
                  if(quantidade < 0){
                     printf("Insira um número natural\n");
                  }
               }
            }
            verificarLeitura = 0;
            if(quantidade != 0){
               cadastrarTarefas(quantidade);
               printf("Tarefas cadastradas com sucesso!\n");
            }
            else{
               printf("Ok, nenhuma tarefa será cadastrada!\n");
            }
            system("pause");
            break;
         case 2: 
            if(verificarExistenciaArquivo() == 0){
               listarTarefas();
            }
            system("pause");
            break;
         case 3: 
            if(verificarExistenciaArquivo() == 0){
               printf("Escolha quantas tarefas quer editar: ");
               int quantidade2 = -1;
               while(quantidade2 < 0 || verificarLeitura != 1){
                  verificarLeitura = scanf("%d",&quantidade2);
                  if(verificarLeitura != 1){
                     printf("Evite caracteres que não sejam números\nEscolha uma quantidade válida: ");
                     while(getchar() != '\n');
                  }
                  else{
                     if(quantidade2 < 0){
                        printf("Escolha uma quantidade valida: ");
                     }
                  }
               }
               verificarLeitura = 0;
               if(quantidade2 != 0){
                  int tarefas[quantidade2];
                  if(listarTarefas() != -1){
                     for(int i = 0;i < quantidade2;i++){
                        tarefas[i] = 0;
                        while(tarefas[i] <= 0 || verificarLeitura != 1){
                           printf("Digite o numero da tarefa que quer editar: ");
                           verificarLeitura = scanf("%d",&tarefas[i]);
                           if(verificarLeitura != 1){
                              printf("Evite caracteres que não sejam números\n");
                              while(getchar() != '\n');
                           }
                           else{
                              if(tarefas[i] <= 0){
                                 printf("Insira um valor natural não nulo\n");
                              }
                           }
                        }
                        verificarLeitura = 0;
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
               else{
                  printf("Ok, nenhuma tarefa será editada!\n");
               }
            }
            system("pause");
            break;
         case 4: 
            if(verificarExistenciaArquivo() == 0){
               printf("Escolha quantas tarefas quer excluir: ");
               int quantidade3 = -1;
               while(quantidade3 < 0 || verificarLeitura != 1){
                  verificarLeitura = scanf("%d",&quantidade3);
                  if(verificarLeitura != 1){
                     printf("Evite caracteres que não sejam números\nEscolha uma quantidade válida: ");
                     while(getchar() != '\n');
                  }
                  else{
                     if(quantidade3 < 0){
                        printf("Escolha uma quantidade valida: ");
                     }
                  }
               }
               verificarLeitura = 0;
               if(quantidade3 != 0){
                  if(listarTarefas() != -1){
                     int tarefas[quantidade3];
                     for(int i = 0;i < quantidade3;i++){
                        tarefas[i] = 0;
                        while(tarefas[i] <= 0 || verificarLeitura != 1){
                           printf("Digite o número da tarefa que quer excluir: ");
                           verificarLeitura = scanf("%d",&tarefas[i]);
                           if(verificarLeitura != 1){
                              printf("Evite caracteres que não sejam números\n");
                              while(getchar() != '\n');
                           }
                           else{
                              if(tarefas[i] <= 0){
                                 printf("Insira um valor natural não nulo\n");
                              }
                           }
                        }
                        verificarLeitura = 0;
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
               else{
                  printf("Ok, nenhuma tarefa será excluída!\n");
               }
            }
            system("pause");
            break;
         case 5:
            if(verificarExistenciaArquivo() == 0){
               salvarArquivo();
            }
            break;
         case 6:printf("Encerrando programa...\n");
            Sleep(1000);
            break;
         default:printf("Escolha inválida\n");
            break;
      }
   }

   return 0;
}