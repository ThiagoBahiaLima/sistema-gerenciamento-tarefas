#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <shlobj.h>
#include "MPT.h"
#include "MPV.h"
#include "MPE.h"

int main(){

   //Comando para aceitar acentos e o caracter "ç"
   system("chcp 65001");

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

            //seletor de quantas tarefas serão cadastradas inicializado com número negativo para entrar no loop a seguir
            int quantidade = -1;

            //Leitura de quantas tarefas serão cadastradas, com verificador de leitura para letras e números negativos 
            while(verificarLeitura != 1 || quantidade < 0){
               printf("Escolha quantas tarefas quer cadastrar: ");

               //Verificador de leitura recebe o valor deixado pelo scanf após uma leitura bem-sucedida ou falha
               verificarLeitura = scanf("%d",&quantidade);

               //verificar se foi digitado um inteiro ao fazer uma escolha 
               if(verificarLeitura != 1){
                  mudarCor(4);
                  printf("Evite caracteres que não sejam números\n");
                  mudarCor(7);

                  //consumir quaisquer possíveis letras digitadas no lugar da escolha
                  while(getchar() != '\n');
               }
               else{
                  
                  //Verificar se o número digitado é uma quantidade válida de tarefas a cadastrar 
                  if(quantidade < 0){
                     mudarCor(4);
                     printf("Insira um número natural\n");
                     mudarCor(7);
                  }
               }
            }
            //resetar o verificador de leitura para a próxima leitura
            verificarLeitura = 0;

            //Verifica se há tarefas a serem cadastradas
            if(quantidade != 0){

               //Chamada de função para cadastrar tarefas
               cadastrarTarefas(quantidade);
               mudarCor(10);
               printf("Tarefas cadastradas com sucesso!\n");
               mudarCor(7);
            }
            else{
               mudarCor(14);
               printf("Ok, nenhuma tarefa será cadastrada!\n");
               mudarCor(7);
            }

            //Pausa o programa
            system("pause");
            break;
         case 2: 

            //Verifica se a lista de tarefas já foi criada e se não está vazia
            if(verificarExistenciaArquivo() == 0){

               //Chamada de função para visualizar as tarefas que já foram cadastradas
               listarTarefas();
            }

            //Pausa
            system("pause");
            break;
         case 3: 

            //Verifica se a lista de tarefas já foi criada e se não está vazia
            if(verificarExistenciaArquivo() == 0){
               printf("Escolha quantas tarefas quer editar: ");

               //seletor de quantas tarefas serão editadas inicializada com número negativo para entarar no loop a seguir
               int quantidade2 = -1;

               //Leitura de quantidade de tarefas a serem editadas, com verificador de letras e de números negativos
               while(quantidade2 < 0 || verificarLeitura != 1){

                  //Verificador de leitura recebe o valor deixado pelo scanf após uma leitura bem-sucedida ou falha
                  verificarLeitura = scanf("%d",&quantidade2);

                  //verifica se houve falha na leitura
                  if(verificarLeitura != 1){
                     mudarCor(4);
                     printf("Evite caracteres que não sejam números\nEscolha uma quantidade válida: ");
                     mudarCor(7);

                     //consumir quaisquer possíveis letras digitadas no lugar da escolha
                     while(getchar() != '\n');
                  }
                  else{  //Se a leitura foi bem sucedida, verificar se a quantidade de tarefas é válida
                     if(quantidade2 < 0){
                        mudarCor(4);
                        printf("Escolha uma quantidade valida: ");
                        mudarCor(7);
                     }
                  }
               }
               //resetar o verificador de leitura para a próxima leitura
               verificarLeitura = 0;

               //Verifica se há tarefas a serem editadas
               if(quantidade2 != 0){

                  //Vetor para armazenar as tarefas a serem editadas
                  int tarefas[quantidade2];

                  //Verifica se a lista de tarefas existe e lista as tarefas caso exista
                  if(listarTarefas() != -1){

                     //loop para escolher quais tarefas serão editadas
                     for(int i = 0;i < quantidade2;i++){

                        //inicialização da posição do vetor para retirar lixo e entrar no loop a seguir
                        tarefas[i] = 0;

                        //Leitura de quais tarefas serão editadas com verificador de letras e números negativos
                        while(tarefas[i] <= 0 || verificarLeitura != 1){
                           printf("Digite o numero da tarefa que quer editar: ");

                           //Verificador de leitura recebe o valor deixado pelo scanf após uma leitura bem-sucedida ou falha
                           verificarLeitura = scanf("%d",&tarefas[i]);

                           //verifica se houve falha na leitura
                           if(verificarLeitura != 1){
                              mudarCor(4);
                              printf("Evite caracteres que não sejam números\n");
                              mudarCor(7);

                              //consumir quaisquer possíveis letras digitadas no lugar da escolha
                              while(getchar() != '\n');
                           }
                           else{

                              //Verifica se o número da tarefa é possível
                              if(tarefas[i] <= 0){
                                 mudarCor(4);
                                 printf("Insira um valor natural não nulo\n");
                                 mudarCor(7);
                              }
                           }
                        }
                        //resetar o verificador de leitura para a próxima leitura
                        verificarLeitura = 0;
                     }

                     //Ordena quais tarefas serão editadas em ordem crescente
                     ordenarVetor(tarefas,quantidade2);

                     //Edita e verifica se todas as tarefas escolhidas foram editadas com sucesso
                     if(editarTarefas(tarefas,quantidade2) == quantidade2){
                        mudarCor(10);
                        printf("Todas as tarefas editadas com sucesso!\n");
                        mudarCor(7);
                     }
                     else{
                        mudarCor(12);
                        printf("Nem toda tarefa pôde ser editada ou algumas tarefas não existem\n");
                        mudarCor(7);
                     }
                  }
               }
               else{
                  mudarCor(14);
                  printf("Ok, nenhuma tarefa será editada!\n");
                  mudarCor(7);
               }
            }

            //Pausa
            system("pause");
            break;
         case 4: 

            //Verifica se a lista de tarefas já foi criada e se não está vazia
            if(verificarExistenciaArquivo() == 0){
               printf("Escolha quantas tarefas quer excluir: ");

               //Seletor de quantidade de tarefas a serem excluídas inicializado com número negativo para entrar no loop a seguir
               int quantidade3 = -1;

               //Leitura de quantas tarefas serão excluídas, com verificador de letras e números negativos
               while(quantidade3 < 0 || verificarLeitura != 1){

                  //Verificador de leitura recebe o valor deixado pelo scanf após uma leitura bem-sucedida ou falha
                  verificarLeitura = scanf("%d",&quantidade3);

                  //verifica se houve falha na leitura
                  if(verificarLeitura != 1){
                     mudarCor(4);
                     printf("Evite caracteres que não sejam números\nEscolha uma quantidade válida: ");
                     mudarCor(7);

                     //consumir quaisquer possíveis letras digitadas no lugar da escolha
                     while(getchar() != '\n');
                  }
                  else{  //Se a leitura for bem-sucedida, verifica se a quantidade de itens a serem excluídos é válida
                     if(quantidade3 < 0){
                        mudarCor(4);
                        printf("Escolha uma quantidade valida: ");
                        mudarCor(7);
                     }
                  }
               }
               //resetar o verificador de leitura para a próxima leitura
               verificarLeitura = 0;

               //Verifica se há itens a serem excluídos
               if(quantidade3 != 0){

                  //Verifica se o arquivo de texto existe e lista as tarefas
                  if(listarTarefas() != -1){

                     //Vetor para armazenar quais tarefas serão excluídas
                     int tarefas[quantidade3];

                     //Loop para escolher quais tarefas serão excluídas
                     for(int i = 0;i < quantidade3;i++){

                        //Tarefa inicializada em 0 para entrar no loop a seguir
                        tarefas[i] = 0;
                        while(tarefas[i] <= 0 || verificarLeitura != 1){
                           printf("Digite o número da tarefa que quer excluir: ");

                           //Verificador de leitura recebe o valor deixado pelo scanf após uma leitura bem-sucedida ou falha
                           verificarLeitura = scanf("%d",&tarefas[i]);

                           //verifica se houve falha na leitura
                           if(verificarLeitura != 1){
                              mudarCor(4);
                              printf("Evite caracteres que não sejam números\n");
                              mudarCor(7);

                              //consumir quaisquer possíveis letras digitadas no lugar da escolha
                              while(getchar() != '\n');
                           }
                           else{
                              if(tarefas[i] <= 0){
                                 mudarCor(4);
                                 printf("Insira um valor natural não nulo\n");
                                 mudarCor(7);
                              }
                           }
                        }
                        //resetar o verificador de leitura para a próxima leitura
                        verificarLeitura = 0;
                     }

                     //Ordena as tarefas a serem excluídas em ordem crescente
                     ordenarVetor(tarefas,quantidade3);

                     //Exclue as tarefas escolhidas e verifica se toda tarefa escolhida foi excluída
                     if(excluirTarefas(tarefas,quantidade3) == quantidade3){
                        mudarCor(10);
                        printf("Tarefas excluídas com sucesso!\n");
                        mudarCor(7);
                     }
                     else{
                        mudarCor(12);
                        printf("Nem toda tarefa pôde ser excluída ou algumas tarefas não existem\n");
                        mudarCor(7);
                     }
                  }
               }
               else{
                  mudarCor(14);
                  printf("Ok, nenhuma tarefa será excluída!\n");
                  mudarCor(7);
               }
            }

            //Pausa
            system("pause");
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

            //Pausa
            system("pause");
            break;
      }
   }

   return 0;
}