#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <shlobj.h>
#include "MPT.h"
#include "MPE.h"
#include "MPS.h"

int main(){

   //Comando para aceitar acentos e o caractere "ç"
   system("chcp 65001");
   system("cls");

   //Verificador de que os scanfs realizaram as leituras com sucesso,
   //ou seja, se o input esperado foi digitado
   int verificarLeitura = 0;

   //variável de seleção de escolha
   int escolha = 0;

   //Loop para realizar escolhas até que o usuário queira sair
   while(escolha != 6){
      
      //interface inicial
      mudarCor(11);
      printf("=== Sistema de Gerenciamento de Tarefas ===\n");
      printf("1. Cadastrar tarefas\n");
      printf("2. Listar tarefas\n");
      printf("3. Editar tarefas\n");
      printf("4. Excluir tarefas\n");
      printf("5. Salvar lista em um arquivo .txt\n"); 
      printf("6. Sair\n");
      mudarCor(7);
      
      //Leitura de escolha com verificador de leitura bem sucedida
      while(verificarLeitura != 1){
         printf("\nEscolha uma opção: ");
         
         //Verificador de leitura recebe o valor deixado pelo scanf após uma leitura bem-sucedida ou falha
         verificarLeitura = scanf("%d",&escolha);
         
         //verificar se foi digitado um inteiro ao fazer uma escolha 
         if(verificarLeitura != 1){
            mudarCor(4);
            printf("Evite caracteres que não sejam números\n");
            mudarCor(7);
            
            //consumir quaisquer possíveis letras digitadas no lugar da escolha
            while(getchar() != '\n');
         }
      }
      //resetar o verificador de leitura para a próxima leitura
      verificarLeitura = 0;

      //Verificador de qual escolha for selecionada
      switch(escolha){
         case 1: printf("\n"); //O case não pode iniciar com declaração de variável

            //Variável para verificar se o usuário quer continuar a execução da escolha
            int continuar = 1;

            while(continuar == 1){

               //Função para cadastrar tarefas
               cadastrarTarefas();
               
               mudarCor(10);
               printf("Tarefa cadastrada com sucesso!\n\n");
               mudarCor(7);

               printf("Tarefas cadastradas até agora:\n");
               listarTarefas();

               printf("\nDeseja cadastrar mais tarefas? (1 = sim/0 = não)\n");
               while(verificarLeitura != 1 || continuar != 1 && continuar != 0){
               
                  //Verificador de leitura recebe o valor deixado pelo scanf após uma leitura bem-sucedida ou falha
                  verificarLeitura = scanf("%d",&continuar);
                  
                  //verificar se foi digitado um inteiro ao fazer uma escolha 
                  if(verificarLeitura != 1){
                     mudarCor(4);
                     printf("Evite caracteres que não sejam números\nFaça uma escolha válida: ");
                     mudarCor(7);
                     
                     //consumir quaisquer possíveis letras digitadas no lugar da escolha
                     while(getchar() != '\n');
                  }
                  else{
                     if(continuar != 1 && continuar != 0){
                        mudarCor(4);
                        printf("Faça uma escolha válida: ");
                        mudarCor(7);
                     }
                  }
               }
               //resetar o verificador de leitura para a próxima leitura
               verificarLeitura = 0;
            }

            printf("Cadastro de tarefas encerrado...\n");

            Sleep(1000);
            break;
         case 2: 

            //Verifica se a lista de tarefas já foi criada e se não está vazia
            if(verificarExistenciaArquivo() == 0){

               //Chamada de função para visualizar as tarefas que já foram cadastradas
               listarTarefas();
            }

            Sleep(1000);
            break;
         case 3: 

            //Verifica se a lista de tarefas já foi criada e se não está vazia
            if(verificarExistenciaArquivo() == 0){
               //Variável para verificar se o usuário quer continuar a execução da escolha
               int CONTINUAR = 1;

               //Variável para saber quantas tarefas existem
               int tarefas = contarTarefas();
               
               while(CONTINUAR == 1){

                  //Variável para saber qual tarefa será alterada
                  int tarefa = 0;

                  printf("Tarefas atuais:\n");
                  listarTarefas();
                  printf("Escolha qual tarefa quer editar: ");
                  while(tarefa <= 0 || verificarLeitura != 1 || tarefa > tarefas){

                     //Verificador de leitura recebe o valor deixado pelo scanf após uma leitura bem-sucedida ou falha
                     verificarLeitura = scanf("%d",&tarefa);

                     //verifica se houve falha na leitura
                     if(verificarLeitura != 1){
                        mudarCor(4);
                        printf("Evite caracteres que não sejam números\nFaça uma escolha válida: ");
                        mudarCor(7);

                        //consumir quaisquer possíveis letras digitadas no lugar da escolha
                        while(getchar() != '\n');
                     }
                     else{
                        if(tarefa <= 0 || tarefa > tarefas){
                           mudarCor(4);
                           printf("Faça uma escolha válida: ");
                           mudarCor(7);
                        }
                     }
                  }
                  verificarLeitura = 0;
                  editarTarefas(tarefa);
                  printf("\n");
                  printf("Deseja editar mais tarefas? (1 = sim/0 = não)\n");
                  while(verificarLeitura != 1 || CONTINUAR != 1 && CONTINUAR != 0){
                  
                     //Verificador de leitura recebe o valor deixado pelo scanf após uma leitura bem-sucedida ou falha
                     verificarLeitura = scanf("%d",&CONTINUAR);
                     
                     //verificar se foi digitado um inteiro ao fazer uma escolha 
                     if(verificarLeitura != 1){
                        mudarCor(4);
                        printf("Evite caracteres que não sejam números\nFaça uma escolha válida: ");
                        mudarCor(7);
                        
                        //consumir quaisquer possíveis letras digitadas no lugar da escolha
                        while(getchar() != '\n');
                     }
                     else{
                        if(CONTINUAR != 1 && CONTINUAR != 0){
                           mudarCor(4);
                           printf("Faça uma escolha válida: ");
                           mudarCor(7);
                        }
                     }
                  }
                  verificarLeitura = 0;
               }
            }

            printf("Encerrando edição de tarefas...\n");

            Sleep(1000);
            break;
         case 4: 

            //Verifica se a lista de tarefas já foi criada e se não está vazia
            if(verificarExistenciaArquivo() == 0){
               
               //Variável para verificar se o usuário quer continuar a execução da escolha
               int CONTINUAR = 1;

               //Variável para saber quantas tarefas existem
               int tarefas = contarTarefas();
               
               while(CONTINUAR == 1 && tarefas != 0){

                  //Variável para saber qual tarefa será alterada
                  int tarefa = 0;

                  printf("Tarefas atuais:\n");
                  listarTarefas();
                  printf("Escolha qual tarefa quer excluir: ");
                  while(tarefa <= 0 || verificarLeitura != 1 || tarefa > tarefas){

                     //Verificador de leitura recebe o valor deixado pelo scanf após uma leitura bem-sucedida ou falha
                     verificarLeitura = scanf("%d",&tarefa);

                     //verifica se houve falha na leitura
                     if(verificarLeitura != 1){
                        mudarCor(4);
                        printf("Evite caracteres que não sejam números\nFaça uma escolha válida: ");
                        mudarCor(7);

                        //consumir quaisquer possíveis letras digitadas no lugar da escolha
                        while(getchar() != '\n');
                     }
                     else{
                        if(tarefa <= 0 || tarefa > tarefas){
                           mudarCor(4);
                           printf("Faça uma escolha válida: ");
                           mudarCor(7);
                        }
                     }
                  }
                  verificarLeitura = 0;
                  excluirTarefas(tarefa);

                  //Atualizar quantas tarefas existem após exclusão
                  tarefas = contarTarefas();

                  printf("\n");
                  if(tarefas != 0){
                     printf("Deseja excluir mais tarefas? (1 = sim/0 = não)\n");
                     while(verificarLeitura != 1 || CONTINUAR != 1 && CONTINUAR != 0){
                     
                        //Verificador de leitura recebe o valor deixado pelo scanf após uma leitura bem-sucedida ou falha
                        verificarLeitura = scanf("%d",&CONTINUAR);
                        
                        //verificar se foi digitado um inteiro ao fazer uma escolha 
                        if(verificarLeitura != 1){
                           mudarCor(4);
                           printf("Evite caracteres que não sejam números\nFaça uma escolha válida: ");
                           mudarCor(7);
                           
                           //consumir quaisquer possíveis letras digitadas no lugar da escolha
                           while(getchar() != '\n');
                        }
                        else{
                           if(CONTINUAR != 1 && CONTINUAR != 0){
                              mudarCor(4);
                              printf("Faça uma escolha válida: ");
                              mudarCor(7);
                           }
                        }
                     }
                  }
                  verificarLeitura = 0;
               }
               if(tarefas == 0){
                  mudarCor(14);
                  printf("Não há mais tarefas na lista\n");
                  mudarCor(7);
               }
            }

            printf("Encerrando exclusão de tarefas...\n");
            
            Sleep(1000);
            break;
         case 5:

            //Verifica se a lista de tarefas já foi criada e se não está vazia
            if(verificarExistenciaArquivo() == 0){

               //Função para salvar o arquivo no diretório que o usuário escolher
               salvarArquivo();
            }
            break;
         case 6:printf("Encerrando programa...\n");

            //Delay de 1 segundo
            Sleep(1000);
            break;
         default:
            mudarCor(4);
            printf("Escolha inválida\n");
            mudarCor(7);

            Sleep(1000);
            break;
      }
   }

   return 0;
}