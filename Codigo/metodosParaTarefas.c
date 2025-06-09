#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <shlobj.h>
#include "MPT.h"
#include "MPE.h"
#include "MPS.h"

int contarTarefas(){

   FILE *arq;
   arq = fopen("Lista de tarefas.txt","r");

   if(arq == NULL){
      return -1;
   }

   int contarTarefas = 0;
   char linha[300];
   while(fgets(linha,sizeof(linha),arq) != NULL){
      contarTarefas++;
   }

   fclose(arq);

   return contarTarefas;

}

//Função para verificar se a lista de tarefas original já foi criada e se está vazia
int verificarExistenciaArquivo(){
   //Ponteiro para o arquivo
   FILE *arq = NULL;

   //Tenta abrir o arquivo da lista de tarefas
   arq = fopen("Lista de tarefas.txt","r");
   
   //Vetor para verificar se o arquivo está vazio caso exista
   char linha[301];

   //Verifica se o arquivo existe
   if(arq == NULL){
      mudarCor(4);
      printf("Erro: A lista de tarefas não existe ainda.\n");
      mudarCor(7);

      //Erro
      return -1;
   }

   //Verifica se o arquivo está vazio
   if(fgets(linha,sizeof(linha),arq) == NULL){
      mudarCor(4);
      printf("Erro: A lista está vazia.\n");
      mudarCor(7);

      //Erro
      return -1;
   }

   //Fecha o arquivo
   fclose(arq);

   //Sucesso
   return 0;
}

//Função para abrir um janela de escolha de diretório para o usuário e salvar esse diretório
int escolherDiretorio(char *caminho,int tamanho){

   //Configura a janela de seleção de pasta
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

         //Copia o caminho selecionado para o parâmetro "caminho"
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
      strcpy(nomeArquivo," ");
      
      while(estaVazia(nomeArquivo)){
         fflush(stdin);
         printf("Escolha um nome para o arquivo (Sem a extensão): ");
         fgets(nomeArquivo, sizeof(nomeArquivo), stdin);
         if(estaVazia(nomeArquivo)){
            mudarCor(4);
            printf("O nome deve conter caracteres\n");
            mudarCor(7);
         }
      }

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
      int ordemTarefas = 1;
      while (fgets(linha, sizeof(linha), origem)) {
         fprintf(destino,"Tarefa %d: %s",ordemTarefas,linha);
         ordemTarefas++;
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
   system("pause");
   return 0;
}

//Função para deletar linhas do arquivo original
int excluirTarefas(int tarefa){

   //Ponteiro para o arquivo original
   FILE *arq = NULL;

   //Ponteiro para o arquivo que se tornará o original
   FILE *clonearq = NULL;
   
   //Abre a lista de tarefas original
   arq = fopen("Lista de tarefas.txt","r");

   //Cria um arquivo para clonar a lista original com as alterações
   clonearq = fopen("clone.txt","w");

   //Verifica se o arquivo original existe e se o clone foi criado com sucesso
   if(arq == NULL || clonearq == NULL){
      mudarCor(4);
      printf("Erro ao abrir lista de tarefas\n");
      mudarCor(7);

      //Deleta o clone em caso de falha
      remove("clone.txt");

      return -1;
   }

   //Vetor Para armazenar a linha que está sendo clonada
   char linha[100];

   //Loop para deletar linhas que para quando o arquivo original acaba
   //Variável "conferirLinha" para saber se o loop já chegou na linha que deve ser excluída
   for(int conferirTarefa = 1;fgets(linha,sizeof(linha),arq) != NULL;conferirTarefa++){

      //Copia a linha do arquivo original no clone se a linha for diferente da linha que deve ser deletada e ignora caso a linha 
      //caso ela deva ser deletada
      if(conferirTarefa != tarefa){
         fprintf(clonearq,linha);
      }
   }

   //Fecha os arquivos
   fclose(arq);
   fclose(clonearq);

   //Deleta a lista original
   remove("Lista de tarefas.txt");

   //Renomeia clone com as alterações da lista original para o nome da lista original
   rename("clone.txt","Lista de tarefas.txt");

   mudarCor(10);
   printf("Tarefa excluída com sucesso!\n");
   mudarCor(7);

   return 0;
}

int editarTarefas(int tarefa){
   //Ponteiro para o arquivo original
   FILE *arq = NULL;

   //Ponteiro para o arquiv clone do original
   FILE *clonearq = NULL;
   //Abrir o arquivo original
   arq = fopen("Lista de tarefas.txt","r");

   //Cria um arquivo clone
   clonearq = fopen("clone.txt","w");

   //Verificar se o arquivo original existe e se o clone foi criado com sucesso
   if(arq == NULL || clonearq == NULL){
      mudarCor(4);
      printf("Erro ao abrir lista de tarefas\n");
      mudarCor(7);

      //Deleta o clone em caso de falha
      remove("clone.txt");

      return -1;
   }

   //Armazena a linha que está sendo clonada ou editada
   char linha[100];

   //Loop para deletar linhas que para quando o arquivo original acaba
   //Variável "conferirLinha" para saber se o loop já chegou na linha que deve ser editada
   for(int conferirLinha = 1;fgets(linha,sizeof(linha),arq) != NULL;conferirLinha++){

      //Confere se a linha deve ser clonada ou editada
      if(conferirLinha != tarefa){
         fprintf(clonearq,linha);
      }
      else{

         //Reseta a linha armazenada para entrar no loop a seguir
         strcpy(linha," ");

         //Garante que o usuário não insira uma linha em branco no arquivo
         while(estaVazia(linha)){
            printf("Digite a nova tarefa: ");

            //Limpa o buffer do teclado
            fflush(stdin);

            //Lê a edição que deve ser feita
            fgets(linha,sizeof(linha),stdin);

            if(!estaVazia(linha)){

               fprintf(clonearq,linha);
            }
            else{
               //Mensagem de erro caso o usuário digite uma linha em branco
               mudarCor(4);
               printf("A edição deve conter caracteres\n");
               mudarCor(7);
            }
         }
      }
   }

   //Fecha os arquivos
   fclose(arq);
   fclose(clonearq);

   //Deleta a lista original
   remove("Lista de tarefas.txt");

   //Renomeia o clone com as alterações da lista original para o nome da lista original
   rename("clone.txt","Lista de tarefas.txt");

   mudarCor(10);
   printf("Tarefa editada com sucesso!\n");
   mudarCor(7);

   return 0;
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

   //Vetor para armazenar a linha do arquivo
   char linha[100];

   //Loop para mostrar linha a linha do arquivo com numeração
   for(int i = 1;fgets(linha,sizeof(linha),arq) != NULL;i++){
      printf("%d. %s",i,linha);
   }

   //Fecha o arquivo
   fclose(arq);

   return 0;
}

int cadastrarTarefas(){
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

   //Vetor de char para armazenar uma string escolhida pelo usuário
   char *tarefa = NULL;

   //Variável que armazena a capacidade de memória da string, inicializada em zero para se adaptar ao tamnho da string digitada
   size_t capacidade = 0;
   
   while(tarefa == NULL || estaVazia(tarefa)){
      printf("Escreva uma tarefa: ");

      //limpa o buffer do teclado
      fflush(stdin);

      //Lê o input do usuário e armazena na variável "tarefa"
      getline(&tarefa,&capacidade,stdin);

      //Verifica se tem algo escrito no input
      if(!estaVazia(tarefa)){

         //Copia o input para o arquivo original
         fprintf(arq,tarefa);
         
      }
      else{
         mudarCor(4);
         printf("A tarefa deve conter caracteres\n");
         mudarCor(7);
      }
   }
   //Fecha o arquivo
   fclose(arq);
   
   return 0;
   
}