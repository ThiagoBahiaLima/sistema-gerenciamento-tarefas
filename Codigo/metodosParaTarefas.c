#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <shlobj.h>
#include "MPT.h"
#include "MPV.h"
#include "MPE.h"

int verificarExistenciaArquivo(){
   FILE *arq = NULL;

   arq = fopen("Lista de tarefas.txt","r");
   
   char linha[301];

   if(arq == NULL){
      mudarCor(4);
      printf("Erro: A lista de tarefas não existe ainda.\n");
      mudarCor(7);
      return -1;
   }
   if(fgets(linha,sizeof(linha),arq) == NULL){
      mudarCor(7);
      printf("Erro: A lista está vazia.\n");
      mudarCor(7);
      return -1;
   }
   fclose(arq);
   return 0;
}

//Função para abrir um janela de escolha de diretório para o usuário e salvar esse diretório
int escolherDiretorio(char *caminho,int tamanho){

   //Configura a ajnela de seleção de pasta
   BROWSEINFO bi = { 0 };

   //Ponteiro para armazenar o identificador da pasta escolhida
   LPITEMIDLIST pidl;

   //Buffer temporário para armazenar o caminho selecionado
   TCHAR buffer[MAX_PATH];

   //Título da janela de seleção
   bi.lpszTitle = "Escolha uma pasta para salvar:";

   //Flags para retornar apenas diretórios do sistema de arquivos e usar estilo moderno de janela
   bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;

   //Abre a janela para o usuário escolher o diretório
   pidl = SHBrowseForFolder(&bi);

   //Verifica se o usuário selecionou algum diretório
   if(pidl != NULL) {

      //Converte o id do diretório para um caminho legível
      if(SHGetPathFromIDList(pidl,buffer)) {

         //Copia o caminho selecionado para o parÂmetro "caminho"
         strncpy(caminho,buffer,tamanho);

         //Garante que a string termina com /0
         caminho[tamanho-1] = '\0';

         //Libera a memória alocada pelo Windows para o ID do diretório
         CoTaskMemFree(pidl);
         return 0;
      }
      //Libera a memória alocada pelo Windows para o ID do diretório mesmo que a converção do id do diretório falhe
      CoTaskMemFree(pidl);
   }
   return -1;
}

int salvarArquivo(){

   //Vetor para armazenar diretório selecionado
   char diretorio[300];

   //Salva o caminho na variável "diretório" e verifica se um diretório válido foi selecionado
   if (escolherDiretorio(diretorio, sizeof(diretorio)) == 0){
      printf("Você escolheu: %s\n\n", diretorio);

      //Escolha do nome do arquivo
      char nomeArquivo[100];
      fflush(stdin);
      printf("Escolha um nome para o arquivo(Sem a extensão): ");
      fgets(nomeArquivo, sizeof(nomeArquivo), stdin);

      //Retirar a quebra de linha do final no nome escolhido e adicionar um \0 no lugar 
      nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';
      
      //Vetor para concatenar o caminho do diretório com o nome do arquivo a ser salvo
      char caminhoCompleto[400];

      //Salva o caminho completo na variável "caminhoCompleto"
      snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s\\%s.txt", diretorio, nomeArquivo);

      //Tenta abrir o arquivo original gerado pelo programa
      FILE *origem = fopen("Lista de tarefas.txt", "r");

      //Verifica se o arquivo original existe
      if (origem == NULL){
         mudarCor(4);
         printf("Erro: não existe nenhuma lista de tarefas para salvar.\n");
         mudarCor(7);
         system("pause");
         return -1;
      }

      //Cria um arquivo no diretório escolhido pelo usuário para clonar o arquivo original
      FILE *destino = fopen(caminhoCompleto, "w");

      //Verifica se o arquivo foi criado com sucesso
      if (destino == NULL) {
         mudarCor(4);
         printf("Erro ao criar o arquivo no diretório selecionado.\n");
         mudarCor(7);

         //Fecha o arquivo original
         fclose(origem);
         system("pause");
         return -1;
      }

      //Copia linha por linha do arquivo original no arquivo criado no diretório selecionado
      char linha[256];
      while (fgets(linha, sizeof(linha), origem)) {
         fputs(linha, destino);
      }

      //Fecha os arquivos
      fclose(origem);
      fclose(destino);
      mudarCor(10);
      printf("Arquivo salvo com sucesso em: %s\n", caminhoCompleto);
      mudarCor(7);
   } 
   else{
      mudarCor(4);
      printf("Nenhum diretório selecionado.\n");
      mudarCor(7);
   }
   return 0;
}

int excluirTarefas(int *tarefas,int tamanho){
   FILE *arq = NULL;
   FILE *clonearq = NULL;
   
   arq = fopen("Lista de tarefas.txt","r");
   clonearq = fopen("clone.txt","w");

   if(arq == NULL || clonearq == NULL){
      mudarCor(4);
      printf("Erro ao abrir lista de tarefas\n");
      mudarCor(7);
      remove("clone.txt");
      return -1;
   }
   char linha[100];
   int indice = 0;
   int excluidos = 0;
   for(int conferirTarefa = 1;fgets(linha,sizeof(linha),arq);conferirTarefa++){
      if(indice == tamanho || conferirTarefa != tarefas[indice]){
         fprintf(clonearq,linha);
      }
      else{
         excluidos++;
         indice++;
      }
   }

   fclose(arq);
   fclose(clonearq);

   remove("Lista de tarefas.txt");
   rename("clone.txt","Lista de tarefas.txt");

   return excluidos;
}

int editarTarefas(int *tarefas,int tamanho){
   //Ponteiro para o arquivo
   FILE *arq = NULL;
   FILE *clonearq = NULL;
   //Abrir o arquivo
   arq = fopen("Lista de tarefas.txt","r");
   clonearq = fopen("clone.txt","w");
   //Verificar se arquivo foi aberto com êxito
   if(arq == NULL || clonearq == NULL){
      mudarCor(4);
      printf("Erro ao abrir lista de tarefas\n");
      mudarCor(7);
      remove("clone.txt");
      return -1;
   }
   int indice = 0;
   int editados = 0;
   char linha[100];
   for(int conferirLinha = 1;fgets(linha,sizeof(linha),arq) != NULL;conferirLinha++){
      if(indice == tamanho || conferirLinha != tarefas[indice]){
         fprintf(clonearq,linha);
      }
      else{
         strcpy(linha," ");
         while(isspace(linha[0])){
            printf("Digite como quer editar a tarefa %d: ",tarefas[indice]);
            fflush(stdin);
            fgets(linha,sizeof(linha),stdin);
            if(!isspace(linha[0])){
               fprintf(clonearq,linha);
               editados++;
               indice++;
            }
            else{
               mudarCor(4);
               printf("A edição deve conter caracteres\n");
               mudarCor(7);
            }
         }
      }
   }
   fclose(arq);
   fclose(clonearq);

   remove("Lista de tarefas.txt");
   rename("clone.txt","Lista de tarefas.txt");

   return editados;
}

int listarTarefas(){
   //Ponteiro para o arquivo
   FILE *arq = NULL;
   //Abrir o arquivo
   arq = fopen("Lista de tarefas.txt","r");
   //Verificar se arquivo foi aberto com êxito
   if(arq == NULL){
      mudarCor(4);
      printf("Erro ao abrir lista de tarefas\n");
      mudarCor(7);
      return -1;
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
   FILE *arq = NULL;
   //Abrir o arquivo
   arq = fopen("Lista de tarefas.txt","a");
   //Verificar se arquivo foi aberto com êxito
   if(arq == NULL){
      mudarCor(4);
      printf("Erro ao abrir lista de tarefas\n");
      mudarCor(7);
      return -1;
   }
   char *tarefa = NULL;
   size_t capacidade = 0;
   int contar = 0;
   while(contar < quantidadeTarefas){
      printf("Digite uma tarefa: ");
      fflush(stdin);
      getline(&tarefa,&capacidade,stdin);
      if(!isspace(tarefa[0])){
         fprintf(arq,tarefa);
         contar++;
      }
      else{
         mudarCor(4);
         printf("A tarefa deve conter caracteres\n");
         mudarCor(7);
      }
   }
   //Fecha o arquivo
   fclose(arq);
   return contar;
   
}