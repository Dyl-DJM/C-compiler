#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "make_anonymous.h"



unsigned int id_etiquette = 0;



void main_asm(FILE * file){

    fprintf(file, "\n_start : \n\n\tmov r12, 0\n\tmov r13, 0\n\tmov r14, 0\n\tmov r15, 0\n\tmov rbx, 0\n");

    
}


/*Write the end of a NASM file into 'file'*/
void end_asm(FILE * file){
    fprintf(file, "\n\n\tmov rax, 60\n\tmov rdi, 0\n\tsyscall");
}


/*Write the substraction of a NASM file into 'file'*/
void soustraction_asm(FILE * file, int val_one, int val_two){
    fprintf(file, "\n\n\tmov r12, %d\n\tmov r13, %d\n\tmov rbx, r12\n\tsub rbx, r13\n\tcall show_registers", val_one, val_two);
}


/*Write the addition of a NASM file into 'file'*/
void addition_asm(FILE * file, int val_one, int val_two){
    fprintf(file, "\n\n\tmov r12, %d\n\tmov r13, %d\n\tmov rbx, r13\n\tadd rbx, r12\n\tcall show_registers", val_one, val_two);
}


/*Write the substraction of a NASM file into 'file'*/
void multiplication_asm(FILE * file, int val_one, int val_two){
    fprintf(file, "\n\n\tmov r12, %d\n\tmov r13, %d\n\tmov rbx, r13\n\timul rbx, r12\n\tcall show_registers", val_one, val_two);
}















/*Explore the abstract tree given ('tree')*/
void parcours_arbre_abstrait(FILE * file, Node * tree){

    if(tree == NULL){
        return;
    }

    




    //printf("%s", StringFromLabel[tree->label]);


    /*Déclaration de fonction*/
    if(strcmp(StringFromLabel[tree->label], "identificateur : ") == 0){

        if(strcmp(tree->value.val, "main") == 0){

            fprintf(file, "\n_start :\n");

        }else{

            fprintf(file, "\n%s :\n", tree->value.val);
        }
    }


    /*Appel de fonction*/
    if(strcmp(StringFromLabel[tree->label], "fonction : ") == 0){

            if(strcmp(tree->value.val, "putchar") == 0){

                fprintf(file, "\tmov dil, byte[%s]\n", tree->firstChild->firstChild->value.val);
            }

            fprintf(file, "\tcall %s\n", tree->value.val);
    }


     /*Appel de fonction*/
    if(strcmp(StringFromLabel[tree->label], "return") == 0){

            fprintf(file, "\tmov rax, 60\n\tmov rdi, %d\n\tsyscall\n", tree->firstChild->value.entier);
    }



    /*Affectations*/
    if(strcmp(StringFromLabel[tree->label], "=") == 0){

            fprintf(file, "\tmov byte[%s], '%c'\n", tree->firstChild->value.val, tree->firstChild->nextSibling->value.caractere);
    }



    /*if*/
    if(strcmp(StringFromLabel[tree->label], "if") == 0){

            fprintf(file, "\tif_%d : \n", id_etiquette);

            if(strcmp(StringFromLabel[tree->firstChild->label], "comparateur : ") == 0){

                    //mettre conditions selon comparateur
            }else{

                switch(tree->firstChild->show){
                    case 0:{
                        fprintf(file, "\t\tcmp %d, 0\n", tree->firstChild->value.entier);
                        break;
                    }

                    case 1:{
                        fprintf(file, "\t\tcmp %d, 0\n", tree->firstChild->value.caractere);
                        break;
                    }
                }


                fprintf(file, "\t\tje else\n");


            }


            fprintf(file, "\telse_%d : \n", id_etiquette);

                    

               
            /*tree  = tree->nextSibling;*/
            id_etiquette ++;

    }




  

    switch(tree->show){
        case 0:{
            //printf("%d", tree->value.entier);
            break;
        }

        case 1:{
            //printf("%c", tree->value.caractere);
            break;
        }

        case 2:{
            //printf("%s", tree->value.val);
            break;
        }
    }




    for (Node *child = tree->firstChild; child != NULL; child = child->nextSibling) {
        parcours_arbre_abstrait(file, child);
    }

}




/*Write the getchar function in a NASM file*/
void print_getchar(FILE * file){


    fprintf(file, "\n\ngetchar : \n\n\tsub rsp, 8\n\tmov rax, 0\n\tmov rdi, 0\n\tmov rsi, rsp\n\tmov rdx, 1\n\tsyscall\n\tpop rax\n\tret\n\n");


}



/*Write the putchar function in a NASM file*/
void print_putchar(FILE * file){


    fprintf(file, "\n\nputchar : \n\n\tpush rdi\n\tmov rax, 1\n\tmov rdi, 1\n\tmov rsi, rsp\n\tmov rdx, 1\n\tsyscall\n\tpop rax\n\tret\n\n");


}




/*Write the getchar function in a NASM file*/
void print_getint(FILE * file){


    fprintf(file, "\n\ngetint : \n\n\tsub rsp, 8\n\tmov rax, 0\n\tmov rdi, 0\n\tmov rsi, rsp\n\tmov rdx, 4\n\tsyscall\n\tpop rax\n\tret\n\n");


}



/*Write the putchar function in a NASM file*/
void print_putint(FILE * file){


    fprintf(file, "\n\nputint : \n\n\tpush rdi\n\tmov rax, 1\n\tmov rdi, 1\n\tmov rsi, rsp\n\tmov rdx, 4\n\tsyscall\n\tpop rax\n\tret\n\n");


}


















/* affiche une liste chainée de variable*/
void allocate_var(FILE * file, variable var, int code){

    variable *tmp;

    /* cas où cet emplacement n'a pas été utilisé*/

    if(var.used < 2){

        return;

    }

    tmp = &var;

    while(tmp != NULL) {

        //printf("var : type : ");
        show_type(tmp->type);
        //printf("  \n");
        //printf("var : nom : %s \n",tmp->nom);
        //printf("var : ligne : %d \n", tmp->line);
       


        if(tmp->type == MY_INT){
            fprintf(file, "\t%s : resd 1\n\n", tmp->nom);
        }

        if(tmp->type == MY_CHAR){
            fprintf(file, "\t%s : resb 1\n\n", tmp->nom);
        }


         tmp = tmp->suivant; 
    }

}








/* affiche la table des symboles*/
void parcours_tab(FILE * file, Tab_symb tab_symb){

    int i;
    int j;
    
    /*on affiche les variables et leurs types pour chaque fonction que l'on possède*/
   for(i = 0; i< tab_symb.nb_fonc;i++){
        
        //printf("fonc, nom : %s \n", tab_symb.tab_fonc[i][FONCTION].nom);
        for(j = 1; j<NB_VAR; j++){
          allocate_var(file, tab_symb.tab_fonc[i][j], j);
        }
    }
}






/*Write the beginning of a NASM file into 'file'*/
void introduction_asm(FILE * file, Tab_symb tab){
    fprintf(file, "global _start\nextern show_registers\n\n");  


    fprintf(file, "section .bss\n\n");

    parcours_tab(file, tab);
    

    fprintf(file, "\nsection .text\n\n");

    print_getchar(file);
    print_putchar(file);
    print_getint(file);
    print_putint(file);
}




/*Creates a new path for the filename*/
char * newPath(const char * path){

    unsigned int i;

    char * buff;


    buff = (char *) malloc(sizeof(char) * (strlen(path) + 5));

    i = 0;

    while(i < strlen(path)){

        

        if(path[i] == '.'){

            buff[i] = '\0';

        }else{

            buff[i] = path[i];
        }

        i ++;

    }

    strcat(buff, ".nasm");

    return buff;

}









int ecriture_fichier(Node * tree, char * path, Tab_symb tab){

	FILE * file;

    char * var1;


	/*This creates a new file where we'd write nasm instructions*/
    if (path == NULL){

        file = fopen("./bin/_anonymous.asm", "w");
        if(file == NULL)
            exit(EXIT_FAILURE);

    }else{

        var1 = newPath(path);
        file = fopen(var1, "w");
       
    }
	


    /*Write the beginning of the nasm file*/
	introduction_asm(file, tab);

    

    //main_asm(file);

    parcours_arbre_abstrait(file, tree);  /*This function needs a tree to work*/


    /*-------- Operations checks (Only for tests) --------*/
    /*soustraction_asm(file, 1, 2);
    addition_asm(file, 1, 2);
    multiplication_asm(file, 1, 2);*/

    //end_asm(file);

   


	fclose(file);



    switch(fork()){

        case 0 : {
            if(path == NULL)
                execlp("nasm", "nasm", "-f", "elf64", "-o", "obj/anonymous.o", "bin/_anonymous.asm", (char *) NULL);
            else
                 execlp("nasm", "nasm", "-f", "elf64", "-o", "obj/anonymous.o", var1, (char *) NULL);



            break;

        }

        default : {

            int waitpid;

            wait(&waitpid);

            switch(fork()){

                case 0 : {

                    execlp("gcc", "gcc", "-o", "bin/a.out", "obj/anonymous.o", "-nostartfiles", "-no-pie", (char *) NULL);
                    break;

                }

                default : {

                    break;
                }
            }

            break;
        }
    }

	return 0;
}

/*


nasm -f elf64 -o anonymous.o _anonymous.asm
nasm -f elf64 -o utils.o utils.asm
gcc -o a.out anonymous.o -nostartfiles -no-pie
*/