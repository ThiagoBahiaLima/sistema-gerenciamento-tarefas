#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <shlobj.h>
#include "MPT.h"
#include "MPV.h"

int verificarExistenciaArquivo(){
   FILE *arq = NULL;

   arq = fopen("Lista de tarefas.txt","r");
   
   char linha[301];

   if(arq == NULL){
      printf("Erro: A lista de tarefas não existe ainda.\n");
      return -1;
   }
   if(fgets(linha,sizeof(linha),arq) == NULL){
      printf("Erro: A lista está vazia.\n");
      return -1;
   }
   fclose(arq);
   return 0;
}

int escolherDiretorio(char *caminho,int tamanho){
   BROWSEINFO bi = { 0 };
   LPITEMIDLIST pidl;
   TCHAR buffer[MAX_PATH];
   bi.lpszTitle = "Escolha uma pasta para salvar:";
   bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;

   pidl = SHBrowseForFolder(&bi);

   if(pidl != NULL) {
      if(SHGetPathFromIDList(pidl,buffer)) {
         strncpy(caminho,buffer,tamanho);
         caminho[tamanho-1] = '\0';
         CoTaskMemFree(pidl);
         return 0;
      }
      CoTaskMemFree(pidl);
   }
   return -1;
}

int salvarArquivo(){
   char diretorio[300];
   if (escolherDiretorio(diretorio, sizeof(diretorio)) == 0){
      printf("Você escolheu: %s\n", diretorio);
      
      char caminhoCompleto[350];
      snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s\\Lista de tarefas.txt", diretorio);

      FILE *origem = fopen("Lista de tarefas.txt", "r");
      if (origem == NULL){
         printf("Erro: não existe nenhuma lista de tarefas para salvar.\n");
         system("pause");
         return -1;
      }

      FILE *destino = fopen(caminhoCompleto, "w");
      if (destino == NULL) {
            printf("Erro ao criar o arquivo no diretório selecionado.\n");
            fclose(origem);
            system("pause");
            return -1;
      }

      char linha[256];
      while (fgets(linha, sizeof(linha), origem)) {
         fputs(linha, destino);
      }

      fclose(origem);
      fclose(destino);
      printf("Arquivo salvo com sucesso em: %s\n", caminhoCompleto);
   } 
   else{
      printf("Nenhum diretório selecionado.\n");
   }
   return 0;
}

int excluirTarefas(int *tarefas,int tamanho){
   FILE *arq = NULL;
   FILE *clonearq = NULL;
   
   arq = fopen("Lista de tarefas.txt","r");
   clonearq = fopen("clone.txt","w");

   if(arq == NULL || clonearq == NULL){
      printf("Erro ao abrir lista de tarefas\n");
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
      printf("Erro ao abrir lista de tarefas\n");
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
               printf("A edição deve conter caracteres\n");
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
      printf("Erro ao abrir lista de tarefas\n");
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
      printf("Erro ao abrir lista de tarefas\n");
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
         printf("A tarefa deve conter caracteres\n");
      }
   }
   //Fecha o arquivo
   fclose(arq);
   return contar;
   
}