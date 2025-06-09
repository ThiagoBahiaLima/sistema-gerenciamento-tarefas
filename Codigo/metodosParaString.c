#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "MPS.h"

int estaVazia(const char *str){
   while(*str){
      if(!isspace((unsigned char)*str)){
         return 0;
      }
      str++;
   }
   return 1;
}