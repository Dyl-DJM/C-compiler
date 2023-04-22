#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/* copie source vers file*/

int copie_file(char ** file, char *source){

  if(*file == NULL){
    *file = malloc(sizeof(char)*10);
    strcpy(*file, source);
  }

  printf(" Le contenu de file : %s \n\n" ,*file);

  return 1;


}

int main(void){

    char * file;

    file = NULL;

    copie_file(&file, "aaaaa");

    if(file !=  NULL)
        printf(" le contenu de file %s \n\n" ,file);


    return 0;
}