

/*


la gestion des switch. :

-autoriser seulement des constantes pour les cases :

ex :

switch

  case 1: --> autorisé

  case 2:

  case x: --> interdit

  -vérifier que les deux cases possibles ne soient pas identiques :

  ex :

    case 0:

    case -0:

    case -2:

    case -2:

  ---> interdit


  Il faut interdire les cas où on a plusieurs défault qui sont écrit pour le même switch :

  default :
    blabla
  default: 
    blilbli

  --> interdit

  gérer le cas du switch contenant un switch dans lui-même : ce n'est qu'un cas particulier normalement qui est gérér par le cas général à part si il
  est ignoré par l'arbre, dans ce cas relancer sur ce switch la fonction du switch général


*/

  /* intedire à un int d'être affecté à un char,
tester les affectations de résultats de fonction et que les paramètres de fonctions sont valides en tant
que affectation

à résoudre :

-déclencher des Warning dans certains cas : int donné à un char avec la valeur de retour appropriée.
-faire des tests avec une table de symbole de taille ridicule pour voir si la réalloc se passe bien.
-ajouter adresses des variables à la table des symboles.



*/

/* tree.c */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
extern int lineno;       /* from lexer */


int has_semantical_err = 0;

/* table des symboles*/
Tab_symb tab_symb1;

/* 

adresse dans la tab des symboles associée à l'emplacement où va être stocké le prochain élément
c'est tjrs un multiple de 8, on incrémente de 8 en 8 .
On met cette variable ici car sinon ça crée des bugs lors d'un double make.
Le compilateur n'aime pas recompiler deux fois pour les variables globales auxquelles ont fait une affection on dirait dans un .h

*/

int adr_tab = 0; 



/* crée un noeud avec le label "label" et précise la ligne ou a été trouvée l'élément (line)*/
Node *makeNode(label_t label, int line) {
  Node *node = malloc(sizeof(Node));
  if (!node) {
    printf("Run out of memory\n");
    exit(1);
  }
  node->label = label;
  node-> firstChild = node->nextSibling = NULL;
  node->line=lineno;

  /*show prend l'ancien rôle de type qui sert à savoir si on doit afficher un caractère, le nom de l'identificateur, un int*/
  node->show = -1;

  return node;
}

void addSibling(Node *node, Node *sibling) {
  Node *curr = node;
  while (curr->nextSibling != NULL) {
    curr = curr->nextSibling;
  }
  curr->nextSibling = sibling;
}

void addChild(Node *parent, Node *child) {
  if (parent->firstChild == NULL) {
    parent->firstChild = child;
  }
  else {
    addSibling(parent->firstChild, child);
  }
}

void deleteTree(Node *node) {
  if (node->firstChild) {
    deleteTree(node->firstChild);
  }
  if (node->nextSibling) {
    deleteTree(node->nextSibling);
  }
  free(node);
}

void printTree(Node *node) {
  static bool rightmost[128]; // tells if node is rightmost sibling
  static int depth = 0;       // depth of current node
  for (int i = 1; i < depth; i++) { // 2502 = vertical line
    printf(rightmost[i] ? "    " : "\u2502   ");
  }
  if (depth > 0) { // 2514 = L form; 2500 = horizontal line; 251c = vertical line and right horiz 
    printf(rightmost[depth] ? "\u2514\u2500\u2500 " : "\u251c\u2500\u2500 ");
  }

   printf("%s", StringFromLabel[node->label]);

  /*ECRIRE LES AUTRES TRUCS CORRESPONDANTS*/

    switch(node->show){
        case 0:{
            printf("%d",node->value.entier);
            break;
        }

        case 1:{
            printf("%c", node->value.caractere);
            break;
        }

        case 2:{
            printf("%s",node->value.val);
            break;
        }
    }

  printf("\n");
  depth++;
  for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
    rightmost[depth] = (child->nextSibling) ? false : true;
    printTree(child);
  }
  depth--;
}


/*Remplit la tab des symboles 'tab' avec les éléments de l'arbre 'node' */
void remplir_tab(Node *node, Tab_symb * tab) {

    Node * child, * child_two;
    Node * child3;
  
    int retour;

  /* variable qui indique si on doit ignorer les ajouts des variables et des arguments jusqu'à la prochaine fonction, car 
  la dernière fonction vue aurait été refusées*/
  int static stop =0 ;

    static int depth = 0;       // depth of current node
    static int init = 0;        //permet d'initialiser une fois la tab des symboles


    /* on initialise une seule fois la tab des symboles*/

    if(init == 0){

      init_tab_symb(tab);
      init = 1;

    }


    if(node != NULL){
      /* cas où on tombe sur une déclaration de fonction (on le sait car elle a le label "identificateur")*/
      if(strcmp(StringFromLabel[node->label], "identificateur : ") == 0 && node->value.val != NULL){
  
        /* on augmente toujours de 1 le nombre de fonction avant d'en ajouter une */
        tab->nb_fonc++;
        /*on ajoute la fonction à la table*/
        /*l'ajout est un échec, probablement pcq c'est un appel de fonction, on diminue le nombre de fonction pour ne pas en ajouter une à tort*/
        /* on initialise retour à -1 par défaut*/
        retour = -1;

        if(strcmp(StringFromLabel[node->firstChild->label], "char") == 0)
          retour = add_varfonc(tab, node->value.val, MY_CHAR, node->line);

        else if(strcmp(StringFromLabel[node->firstChild->label], "int") == 0)
          retour = add_varfonc(tab, node->value.val, MY_INT, node->line);

        else if(strcmp(StringFromLabel[node->firstChild->label], "void") == 0)
          retour = add_varfonc(tab, node->value.val, MY_VOID, node->line);


        /*L'ajout de la fonction a échoué*/
        if(retour == 0 || retour == -1){
          /*printf("échec d e l'ajout de la fonction : %s \n\n " ,node->value.val);*/
          tab->nb_fonc--;

          /* on interdira tous les ajouts qui étaient censés être associés à cette fonction car ils sont tous invalides */
          stop = 1;
          /*printf(" les ajouts sont interdits à cause de : %s \n" ,node->value.val);*/
        }
        else{
          /* on permet à nouveau au user de faire des ajouts*/

          /*printf(" les ajouts sont autorisés à cause de : %s \n" ,node->value.val);*/

          stop = 0;
        }
      }

      /* on ajoute les variables locales et les arguments associés à la fonction ssi elle a été acceptée, 
      sinon on ne fait rien car stop vaut 1, et on passe à la prochaien fonction (DÉBUT) */
      if(stop == 0){

        /*On trouve les paramètres de la fonction précédemment définie*/
        if(strcmp(StringFromLabel[node->label], "PARAMETRES") == 0){
         /* printf(" on tombe bien sur un paramètre mais... \n\n\n");*/
          /*on ajoute le paramètre à la table*/
          child = node->firstChild;
         
          while(child != NULL){

            if( child->value.val != NULL ){
              /*
              printf("Le fils du paramètre est en ligne : %s \n" , child->value.val);

              printf("Le fils du paramètre est en ligne : %d \n" , child->line);*/

              /*printf(" on tombe bien sur un paramètre mais 2222... \n\n\n");*/
              /* pb : en deux 2222 étapes l'ajout*/
              add_param(tab, child->value.val,-1, child->line);

              child_two = child->firstChild;  /*Noeud comportant le type de la variable*/

              if(strcmp(StringFromLabel[child_two->label], "int") == 0)
                add_param(tab, NULL, MY_INT,child->line);

              if(strcmp(StringFromLabel[child_two->label], "char") == 0)
                add_param(tab, NULL, MY_CHAR, child->line);

            }

            child = child->nextSibling;
          }
        }
        

          /*On ajoute les variables locales associées à une fonction */

          if(strcmp(StringFromLabel[node->label], "DECLVARS") == 0 && StringFromLabel[node->label] != NULL){
            /*on ajoute les variables locales à la table en parcourant
            les fils successifs sur l'arbre */

            /* problème : on tombe sur lala par 2 moyen d'où la déclaration multiple*/


            child = node->firstChild;
            while(child != NULL){

                  if( strcmp(StringFromLabel[child->label], "variable : ") == 0 && child->value.val != NULL){
                   /* “ICI 7777”*/
                   /* printf(" la nouvelle var est 111 : %s \n" ,child->value.val);*/
                    /*on ajoute les variables */

                    /*printf(" le fils du paramètre est en ligne : %d \n" , node->line);*/

                    /*on essaye de faire en une fois 
                    
                    add_varfonc(tab,child->value.val,-1, child->line);
                    add_varfonc(tab,NULL,child->type, child->line);*/

                     add_varfonc(tab,child->value.val,child->type, child->line);


                     for(child3 = child->firstChild ; child3 !=NULL; child3 = child3->nextSibling){
                     /* “ICI 7777” --> créé une deuxième analyse de la même variable donc problème mais est indispensable pour les déclarations 
                     de la forme
                     int x, y, z;*/
                    if( strcmp(StringFromLabel[child3->label], "variable : ") == 0 && child3->value.val != NULL){

                   /* printf(" la nouvelle var est 222 : %s \n" ,child3->value.val);*/

                     add_varfonc(tab,child3->value.val,child3->type, child3->line);

                    }
                    /*on essaye de faire en une fois 
                    
                    add_varfonc(tab,child3->value.val,-1, child3->line);
                    add_varfonc(tab,NULL,child3->type, child3->line);*/

                  }












                  }


                  /* pour le cas de déclaration multiples, on parcourt les frères (siblings) pose problème car entraine un double ajout alors que 
                  des variables ne sont pas déclrées deux fois*/

                  

                  
                  
                  
                  

                /* on passe à l'enfant suivant*/
                child = child->nextSibling;

            }

                
          }
      }

       /* on ajoute les variables locales et les arguments associés à la fonction ssi elle a été acceptée, 
      sinon on ne fait rien car stop vaut 1, et on passe à la prochaien fonction (FIN) */
  
      depth++;
      for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
        remplir_tab(child, tab);
      }
      depth--;
    }
}


/* initialise la table des symboles*/
/* renvoie 1 : si tout s'est bien passé et que c'était déjà initialisé : on ne fait rien
0 : en cas d'erreur  
2 : on a initialisé car déjà fait ce tour-ci mais on ne veut pas incrémenter une seconde fois la valeur dans tpcas.y donc on renvoie un nombre spéicilal, ici 2  (à supprimer)
*/
int init_tab_symb(Tab_symb *tab_symb){
  int i,j,k;
  static int init = 0;

  /* si le tableau a déjà été initialisé et qu'on passe pour la prepas été initialisé alors on l'initialise
    cela a lieu une fois normalement*/
  /* (cas 1 : ) le tableau a déjà été initialisé, on fait un return*/
  if(init == 1){

      return 1;

      
  }

  /* (cas 2 :) le tableau n'a pas encore été initialisé, on l'initialise*/
  /* on alloue pour le nombre de fonction estimé au départ*/
  if(((*tab_symb).tab_fonc = (variable**) malloc(sizeof(variable*) * NB_FONC_INIT)) != NULL){

    /* on a 0 fonction au départ
    donc on démarre à 0 pcq */
    tab_symb->nb_fonc = 0;

    /* on a assez d'espace pour nb_fonc_init au début*/

    tab_symb->max = NB_FONC_INIT;
  }
  else{

      printf("erreur lors de l'allocation \n");

      return 0;
  }
  
  /* on alloue pour nb_var éléments dans nb_fonc_init cases, en sachant que la première case sera celle de la fonction*/
  for(j = 0;j<NB_FONC_INIT;j++){

    if((tab_symb->tab_fonc[j] = (variable*) malloc(sizeof(variable) * NB_VAR)) == NULL){

        printf("erreur lors de l'allocation \n");
        return 0;
    }
    
  }
    /* on initalise chaque emplacement en précisant qu'ils ne sont pas utilisés*/
    for(i = 0; i < NB_FONC_INIT ; i++){
        for(k = 0; k < NB_VAR; k++){
            tab_symb->tab_fonc[i][k].used = 0;
            tab_symb->tab_fonc[i][k].suivant = NULL;
            tab_symb->tab_fonc[i][k].nom[0] = '\0';
        }
    }
    /* on initialise le champ dans lequel on pourra enregistrer une variable en cours d'insertion car dans ce cas précis, on a seulement son type*/
    tab_symb->attempt = -1 ; /*(variable*) malloc(sizeof(variable) );*/
    /* pour le prochain appel, on sait que la table a déjà été initialisée mais que aucun appel n'a été fait dans tpcas.y (en d'autres termes qu'on a pas changé de fonction et on ne veut pas
    compter deux fois la même fonction
    */
    init = 1;
    /* on donne tjrs à nb_fonc le nombre de fonction que l'on a avant l'ajout de la fonction.
    Par exemple si la table des symboles contient 1 fonction, sa valeur sera de un, ce qui parait logique, seulement on incrémentera de un juste avant l'ajout de la fonction dans la table 
    et pas après*/
    tab_symb->nb_fonc = 1;

    /* on ajoute les fonctions usuelles issues des librairies*/
    add_usual_fonct(tab_symb);
      
    

    /*on ajoute d'abord le type de la fonction ce sera le type void car ce n'est pas vraiment une fonction mais le fichier qui accepte des variables globales, un fichier n'a pas de type*/

    if(add_fonc(tab_symb,"globale",MY_VOID, LINE_IMPORT) == 0){
      /* cas d'échec*/
      free_tab_symb(tab_symb);
      printf("Erreur : Il y a eu une erreur lors de l'allocation , échec ");
      return 0;
    }
    /* aucun main n'a été détecté à ce stade*/
    tab_symb->main = 0;
    return 1;
}

/* libère un élément de type variable*/
void free_suivant_var(variable * var1){
    variable * tmp;
    /*on commence à partir de la variable 2 car la première n'est pas allouée dynamiquement*/
    var1 = var1->suivant;

    if(var1 == NULL)
      return;
    /* quand le suivant est null, on s'arrête et on gère le dernier cas*/
    while(var1->suivant != NULL){

        tmp = var1->suivant;

        free(var1);

        var1 = tmp;
    }
    /* on libère le dernier cas*/
    free(var1);
}

/* libère la table des symboles*/
void free_tab_symb(Tab_symb *tab_symb){
  int i;
  int j;
  /* cas où la table est déjà vidée : on arrête tout*/
  if(tab_symb->nb_fonc == 0){
    return;
  }
    /* on libère les variables pour le nombre de fonction estimé au final*/
    for(i = 0; i<tab_symb->nb_fonc ;i++){
    /* on analyse chaque variable et ses frères*/
      for(j=0 ;j<NB_VAR;j++){

    /* on appelle la fonction qui libère les suivants de chaque variables*/
        free_suivant_var(&tab_symb->tab_fonc[i][j]);
      }

    }
  /* on libère les sous tableaux de la table des symboles : 1 fonction = un sous tableau (utilisé ou au moins alloué)*/

  for(j = 0;j<tab_symb->max;j++){

    free(tab_symb->tab_fonc[j]);

  }

  /* puis on libère le grand tableau*/

  free(tab_symb->tab_fonc);

  tab_symb->nb_fonc = 0;

  tab_symb->tab_fonc = NULL;
}




/* fonction de réallocation*/
/* renvoie 1 si tout s'est bien passé et 0 sinon*/
int realloue_tab_symb(Tab_symb *tab_symb){
  /* on récupère l'ancienne valeur du max pour pas écraser le contenu stocké par les anciens mallocs*/


  if(tab_symb->tab_fonc == NULL) {

    printf("Impossible d'allouer le tableau est null \n");

    return 0;

  }
  int oldmax = tab_symb->max;

  /* on multiplie par 2 la capacité théorique */
   tab_symb->max*= 2;

   /* garder en mémoire le oldmax pour pas écraser au dessus ?? */

  /* on multiplie par 2 le nombres de fonctions possibles et on realloue "bêtement la deuxième partie */
  if((tab_symb->tab_fonc = (variable ** ) realloc(tab_symb->tab_fonc, (tab_symb->max)*sizeof(variable*))) == NULL){

    printf("erreur lors de l'allocation \n");

    return 0;

  }


  int j;

  /* on réalloue pour de oldmax vers le nouveau max*/
  for(j = oldmax;j<(tab_symb->max);j++){


    if(   (tab_symb->tab_fonc[j] = (variable*) malloc(sizeof(variable) * NB_VAR )   ) == NULL )  {


      /*tab_symb->tab_fonc[j] = (variable*) malloc(sizeof(variable) * NB_VAR)) == NULL)*/

        printf("erreur lors de l'allocation \n");
        return 0;
    }

    
  }

 

  return 1;

}











































/* ajoute une fonction à la table des symboles
renvoie 0 en cas de problème et 1 si tout s'est bien passé*/

int add_fonc(Tab_symb *tab, char *nom_fonc, int type_fonc, int ligne){


  /* indique si une erreur a eu lieu : 
  0 = oui
  1 = non*/

  /* hypothèse crédible : le fait de bloquer l'ajout d'une fonction alors qu'elle possède quand même des arguments et des
  variables crée un bug à posteriori, la solution : ajouter la fonction même si il y a eu un pb puis renvoyer un code d'erreur ou arrêter tout le programme.
  Il ne sera peut-être pas possbile d'arrêter tout le programme si on traverse les fils et qu'on tente automatiquement de les ajouter avant d'avoir vu l'erreur chez le père, donc à tester*/

  /*int ok;*/

  /*printf("entrée dans add_fonc pour : %s \n\n\n", nom_fonc);*/
  if((nom_fonc != NULL) && ( isherefonc(*tab,nom_fonc) ==1  || ishereglobale(*tab,nom_fonc) ==1 ) ) 
  
      {   
          
          /* l'emplacement serait celui qui est déjà dans la tab des symboles essayer la ligne associée à la variable */

              char msg[200];

              /* variable qui enregistre la ligne dans la tab des symboles associées à la variable globale qui est déjà enregistré */

              char l2[10];

              variable var2;

              /* cas où il y a deux fois le même nom pour une variable globale et une fonction */

              if(ishereglobale(*tab,nom_fonc) ==1){
                

                  strcpy(msg, "multiples declarations of the same name for a globale variable and function: ' ");

                  /* on recopie la variable qui était déjà présente dans la tab dans la partie globale pour récupérer sa ligne */

                  deep_copy_var(&var2, search_variable(*tab,nom_fonc,GLOBALE));

                  strcat(msg, nom_fonc);

                  strcat(msg,"  ' ");

                  /*  la ligne dans la tab des symboles associée à la variable qui est déjà enregistré */

                  strcat(msg," | Line : ");

                  sprintf(l2, "%d", var2.line);

                  strcat(msg, l2);

                  strcat(msg, "   AND  ");
                  
                  yyerror2(msg, ligne, 1);


              }

              /* cas où il y a deux fois le même nom pour deux fonctions déclarées à deux endroits différents */

               else if(isherefonc(*tab,nom_fonc) ==1){

                  strcpy(msg, "multiples declarations of the same name for two functions : ' ");

                  /* on recopie la fonction qui était déjà présente dans la tab dans la partie globale pour récupérer sa ligne */

                  deep_copy_var(&var2, search_fonction(*tab,nom_fonc));

                  strcat(msg, nom_fonc);

                  strcat(msg,"  ' ");

                  /*  la ligne dans la tab des symboles associée à la variable qui est déjà enregistré */

                  strcat(msg," | Line : ");

                  sprintf(l2, "%d", var2.line);

                  strcat(msg, l2);

                  strcat(msg, "   AND  ");
                  
                  yyerror2(msg, ligne, 1);

              }
              
              
        
        /* l'utilisateur a déclaré deux fois la même fonction avec un type différent ou le même type : erreur tout s'arrête*/
       return 0;   
  }


  if(nom_fonc == NULL || type_fonc<0){

    /* il manque des informations, on ne fait rien et on renvoie le code d'erreur*/

    return 0;
  }
  

  

      if(tab->nb_fonc+1 >= tab->max){
        if(realloue_tab_symb(tab) == 0){

          printf("erreur lors de la réallocation de la tab des symboles pour une nouvelle fonction \n");

          return 0;

        }

        
      }

  /*printf(" pour la fonction : %s, le type trouvé est : ", nom_fonc);*/

  /* ajouter le type*/
  /* on part du principe que le nom du type ne dépassera pas plus de  200 caractères, ce qui est déjà énorme
   et on le copie */

 

  if((type_fonc > -1) && tab->tab_fonc[tab->nb_fonc-1][MY_FUNCTION].used < 1){

    tab->tab_fonc[tab->nb_fonc-1][0].type = type_fonc; 
    /* on précise que le type a été ajouté*/
    tab->tab_fonc[tab->nb_fonc-1][0].used = 1;
    
  }


   /* ajouter le nom de l'ident*/
  if(nom_fonc != NULL && tab->tab_fonc[tab->nb_fonc-1][MY_FUNCTION].used < 2){

    strcpy(tab->tab_fonc[tab->nb_fonc-1][MY_FUNCTION].nom, nom_fonc);

    /* on précise que l'emplacement est rempli car on a le type et le nom de la variable*/ 

    tab->tab_fonc[tab->nb_fonc-1][MY_FUNCTION].used = 2;

    /* on en profite pour aussi ajouter la ligne où on a trouvé la fonction */

    tab->tab_fonc[tab->nb_fonc-1][MY_FUNCTION].line = ligne;

    /*on pas encore récupéré le type de retour*/

    tab->tab_fonc[tab->nb_fonc-1][MY_FUNCTION].type_rec = -1;

    /*on ajoute l'adresse @*/

    /* pour la fausse fonction globale, il n'y a pas d'adresse à ajouter pour le reste, si*/
    if( ligne != LINE_IMPORT || strcmp(nom_fonc, "globale" ) != 0){
      
        tab->tab_fonc[tab->nb_fonc-1][MY_FUNCTION].adresse = adr_tab;

        /*update pour la prochaine adresse*/

        adr_tab +=8;
      }
  }

  /* pour une fonction le suivant sera toujours NULL*/
  tab->tab_fonc[tab->nb_fonc-1][MY_FUNCTION].suivant = NULL;

  
  return 1;
}
























/* cette fonction crée un hashcode en fonction du nom d'une variable*/
/* elle renvoie une valeur qui correspond au hashcode*/
/* elle renvoie -1 si l'élément donné était une chaine vide*/
int hashcode(char * nom_var){
  if(nom_var == NULL){
    return -1;
  }
    
  int length;
  /* enregiste la somme des caractères en ascii*/
  int somme;
  int i;
  length = strlen(nom_var);
  /* échec, chaine vide*/
  if(length <=0)
    return -1;
  somme = 0;
  for(i = 0;i < length;i++){
    /* on additionne les valeurs ascii des lettres de la variable pour créer un hashcode*/
    somme += nom_var[i];
  }

  /* on renvoie un code qui peut être inclus dans les cases du tableau*/
  /* cas où somme risque d'être trop grand, on n'ajoute pas +2 pour le hashcode*/
  if(somme == NB_VAR-1)
    return somme % NB_VAR;
  /* on commence à ajouter les variables à la case 2 donc 2 + mod valeur : les deux premières cases sont prices par le
  nom de la fonction elle-même, et aussi les variables qui sont chainées, les paramètres de la fonction */
  return (VARIABLES+ somme % NB_VAR);
}


/* 
Cette fonction indique si une variable a déjà été ajouté parmi les variables globales
renvoie 1 si la variable est déjà dedans
et renvoie 0 sinon*/
int ishereglobale(Tab_symb tab_symb , char * nom_var){
  int code;
  variable * tmp;
  code = hashcode(nom_var);
  /* On regarde d'abord au niveau de la table consacrée aux variables globales*/
  tmp = &tab_symb.tab_fonc[GLOBALE][code];

  /* cas où l'emplacement n'est pas utilisé*/
  if(tmp->used < 2){
    return 0;
  }
  /* la variable est là c'est celle en tête de liste*/

    if(strcmp(tmp->nom, nom_var) == 0){
        return 1;
    }

  /* cas où l'emplacement suivant est utilisé mais on ne sait pas si il contient la variable
  car le premier maillon de la chaine ne contient pas ce nom de variable.
  On avance dans la liste chainée.*/

  while(tmp != NULL){
    /* cette variable est présente parmi les globlaes */
    if(strcmp(tmp->nom, nom_var) == 0){
      return 1;
    }
    /* on avance dans la recherche car on ne l'a pas trouvée */
    tmp = tmp->suivant;
  }

    return 0;
}




/* 
Cette fonction indique si cette variable a déjà été ajouté pour cette fonction
renvoie 1 si la variable est déjà dedans
et renvoie 0 sinon
pos = fonction de référence : fonction appelante */
int ishere(Tab_symb tab_symb , char * nom_var, int pos){

  variable * tmp;

  /* enregistre le hashcode*/
  int code;

  
    
  code = hashcode(nom_var);


  /* on commence par regarder les arguments de la fonction, c'est à dire, dans la liste chainée des variables qui sont à la première case associée au numéro de la fonction.
  Par définitioon la fonction "globale" (le fichier) n'a pas d'arguments donc il n'est pas nécessaire d'aller ici */
  if(pos != GLOBALE){
    for(tmp =  &tab_symb.tab_fonc[pos][ARGS]; tmp != NULL;  tmp=tmp->suivant){
      /* si une variable est présente à cet emplacement, on tente de comparer son nom avec celui recherché*/
      if(tmp->used == 2){
        /*printf("l'emplacement en arg de la fonction a été trouvé \n");*/
        if(strcmp(tmp->nom, nom_var) == 0){
            /* la variable a été trouvée, on renvoie 1 pour l'attester*/
            return 1;
        }
      }
    }
  }
  
 
  
  /* finalement on regarde au niveau des variables locales*/
  tmp = &tab_symb.tab_fonc[pos][code];

  /* cas où l'emplacement n'est pas utilisé*/
  if(tmp->used < 2){
    return 0;
  }
 
  /* la variable est déjà là c'est celle en tête de liste*/
    /*printf(" le contenu de tmp : %s " ,tmp->nom);
    printf(" le contenu de nom_var : %s " ,nom_var);*/
    if(strcmp(tmp->nom, nom_var) == 0){
        return 1;
    }

  
  /* cas où l'emplacement suivant n'est pas utilisé*/
  while(tmp != NULL){
    /* cette variable est déjà utilisée car on retrouve son nom on arrête tout */
    if(strcmp(tmp->nom, nom_var) == 0){
      return 1;
    }
    /* on avance dans la recherche*/
    tmp = tmp->suivant;
  }
  
  /* la variable n'a pas été trouvée, on renvoie 0*/
  return 0;
}


/* 
Cette fonction renvoie une variable qui est présente dans la table des symboles avec ses informations
si elle n'est pas présente, elle renvoie une "variable vide"
*/
variable search_variable(Tab_symb tab_symb , char * nom_var, int pos){

  variable * tmp;
  variable tmp2;
  /* enregistre le hashcode*/
  int code;

  
    
  code = hashcode(nom_var);

  tmp2.cat = -1;
  tmp2.line = -1;
  tmp2.type = -1;
  tmp2.nom[0] = '\0';
  tmp2.type_rec = -1;
  tmp2.suivant = NULL;
 

  /* finalement on regarde au niveau des variables locales*/

  tmp = &tab_symb.tab_fonc[pos][code];

  /* cas où l'emplacement n'est pas utilisé*/

  if(tmp->used < 2){

    /* on renvoie une variable vide*/

    return tmp2;

  }

  /* la variable est déjà là c'est celle en tête de liste*/

    if(strcmp(tmp->nom, nom_var) == 0){
        return *tmp;
    }

  /* cas où l'emplacement suivant n'est pas utilisé*/
  while(tmp != NULL){

    /* cette variable est déjà là car on retrouve son nom on arrête tout */

    if(strcmp(tmp->nom, nom_var) == 0){

      return *tmp;

    }
    /* on avance dans la recherche*/
    tmp = tmp->suivant;
  }

  /* la variable n'a pas été trouvée, on renvoie la variable vide*/

  return tmp2;
}
















/* 
Cette fonction indique le type de la varialbe recherchée
pos correspond à l'emplacement de la fonction depuis laquelle on cherche la variable (on cherhera aussi dans les variables globales)*/
int istype(Tab_symb tab_symb , char * nom_var, int pos){
  variable * tmp;
  /* enregistre le hashcode*/
  int code;

   /* cas où on gère le nom de la variable est NULL*/

   /* code d'erreur*/
    if(nom_var == NULL)
        return -1;

   code = hashcode(nom_var);
  

  /* on regarde au niveau des arguments de la fonction pour voir si elle n'est pas dans ses argumetns */

  for(tmp =  &tab_symb.tab_fonc[pos][ARGS]; tmp != NULL;  tmp=tmp->suivant){
    /* si une variable est présente à cet emplacement, on tente de comparer son nom avec celui recherché*/
    if(tmp->used == 2){
      if(strcmp(tmp->nom, nom_var) == 0){
          /* la variable a été trouvée, on renvoie son type*/
          return tmp->type;
      }
    }
  }


  /* on regarde au niveau des variables locales à la fonction si la variable n'est pas dans les globales*/

  tmp = &tab_symb.tab_fonc[pos][code];

  /* cas où l'emplacement est utilisé*/
  if(tmp->used == 2){
  /* la variable est déjà là c'est celle en tête de liste, on renvoie son type*/

    if(strcmp(tmp->nom, nom_var) == 0){
        return tmp->type;
    }

    /* cas où l'emplacement suivant est  utilisé mais que le premier maillon
    de la chaine ne correspond pas au nom del a variable : on parcourt la liste */
    while(tmp != NULL){
      /* cette variable est déjà utilisée car on retrouve son nom. On renvoie son type */
      if(strcmp(tmp->nom, nom_var) == 0){
        return tmp->type;
      }
      /* on avance dans la recherche*/
      tmp = tmp->suivant;
    }
  }

  /* Partie II (Début)*/
  /* On regarde en dernier au niveau de la table consacrée aux variables globales*/

  tmp = &tab_symb.tab_fonc[GLOBALE][code];

  /* cas où l'emplacement est utilisé*/
  if(tmp->used == 2){
    
    /* la variable est déjà là c'est celle en tête de liste,
    on renvoie son type*/
      if(strcmp(tmp->nom, nom_var) == 0){
          return tmp->type;
      }
    /* Une variable partage son hashcode, on cherche dans ses suivants*/
    while(tmp != NULL){
      /* cette variable est présente, on renvoie son type */
      if(strcmp(tmp->nom, nom_var) == 0){
        return tmp->type;
      }
      /* on avance dans la recherche*/
      tmp = tmp->suivant;
    }
  }

  /* Partie II (FIN)*/

    /* la variable n'a pas été trouvée, on renvoie -1*/

  return -1;
}


/* 
Cette fonction indique si l'emplacement d'une fonction dans la tab des symboles.
Elle renvoie -1 si la fonction n'a pas été trouvée.
Sinon elle renvoie l'emplacement où se trouve la fonction  */

int foncpos(Tab_symb tab_symb , char * nom_fonc){
  int i;
   for(i=0;i<tab_symb.nb_fonc;i++){
     /* On cherche dans tous les emplacements associés aux noms de fonctions, sauf celui qui porte sur la fonction appelée globale 
     car ce n'est pas une vraie fonction seulement le nom générique pour désigner tout le fichier*/
     if(i != GLOBALE){
      /* cas où le nom de la fonction a été trouvé parmi les noms des fonctions */
      if(strcmp(tab_symb.tab_fonc[i][0].nom, nom_fonc) == 0){
          /*printf("la fonction %s a été trouvée ! \n", nom_fonc);*/
          return i;
      }
    }
   }
  
  /* la fonction n'a pas été trouvée, on renvoie -1, c'est une erreur*/
  return -1;
}



/* 
Cette fonction indique si cette fonction a déjà été ajoutée pour cette table des symboles
renvoie -1 si la fonction donnée est NULL
renvoie 1 si la fonction est déjà dedans
et renvoie 0 sinon*/
int isherefonc(Tab_symb tab_symb , char * nom_fonc){

  
  
  int i;

  /* code d'erreur*/

  if(nom_fonc == NULL){
    return -1;
  }

  /* on a déjà cet identificateur sous le nom d'une variable globale : code d'erreur 2 */
  
  if( ishere(tab_symb , nom_fonc, GLOBALE) == 1){

      return 2;

  }
  
  


   for(i=0;i<tab_symb.nb_fonc;i++){
    /* cas où le nom de la fonction a été trouvé parmi les noms des fonctions : code d'erreur 1 */
    /*si on est sur l'emplacement associé fichier "globale" alors on ignore cet emplacement d'où le i != GLOBALE*/

    if(i != GLOBALE){

     if(strcmp(tab_symb.tab_fonc[i][0].nom, nom_fonc) == 0){
        return 1;

     }

    }
   }
  
  /* la fonction n'a pas été trouvée, on renvoie 0*/
  return 0;
}

/* fonction qui initialise un tableau de type list_type si nécessaire, c'est à dire si l'argument vaut 1 sinon ne l'initialise pas*/
void init_list_type(List_type * tab){
  /*static int init;*//* on définit une variable qui initialise si nécessaire la list_type*/
  tab->used = 0;
  tab->max = MAX_TYPE_NAME;
}


/* trouve dans la tab des symboles tab, le type des paramètres de la fonction choisie (nom) en respectant leur ordre d'apparition et les ajoute à tablist*/
int find_types_fonc(Tab_symb tab_symb, char * nom,  List_type * tablist){
  /* variable qui contient la position de la fonction dans la tab des symboles*/
  int pos;

  variable var1;
  /* cas d'erreur, le nom de la fonction à chercher est vide*/
  if(nom == NULL)
    return -1;
  /* la fonction, appelée n'a pas été trouvée dans la tab des symboles, code d'erreur*/
  if((pos = foncpos(tab_symb , nom)) == -1){
    printf("la fonction n'a pas été trouvée dans la tab \n");
    return 0;
  }

  /* cas où la fonction n'a pas d'argument, on renvoie 1, aucun argument n'est attendu*/
  if(tab_symb.tab_fonc[pos][ARGS].used < 2)
    return 1;

  /* cas où la fonction a des arguments, on ajoute leur type sauf le dernier d'entre eux*/
  for(var1 = tab_symb.tab_fonc[pos][ARGS]; var1.suivant != NULL; var1 = *(var1.suivant)){
      
      tablist->tab[tablist->used] = var1.type;

      tablist->used++;

      

  }
  /* on gère le dernier argument à part car on s'est arrêté à l'avant-dernier car son suivant valait null*/
   tablist->tab[tablist->used] = var1.type;
   tablist->used++;
  
  return 1;
  
  
}

/* fonction qui compare les types des arguments utilisés pour un appel de fonction et les paramètres attendues par celle-ci.
pb contient l'emplacement qui a posé problème c'est à dire l'emplacement des variables avec le mauvais type*/
int compare_arg_appel(List_type tablist, List_type tablist2, int * pb){
    int i;
    /* cas où le nombre d'argument de la première liste est différent du nombre d'argument de la deuxième liste : code d'erreur -2.
    */
    if(tablist.used != tablist2.used)
      return -2;
    /* pb n'a pas détecté d'erreurs, donc on lui affecte un emplacement du tableau qui n'existe pas*/
    *pb = -1;
    for(i=0; i<tablist.used;i++){
      /* les types enregistrés ne sont pas les mêmes ou du moins pas dans le bon ordre : on arrête tout*/
      if(tablist.tab[i] != tablist2.tab[i]){
        /* on enregistre l' emplacement du tableau qui est problématique dans pb */
        *pb = i;
        /* code d'erreur -1 car les types sont différents */
        return -1;
      }

    }

    return 1;
}



/*

Trouve le type d'une variable dans la table des symboles en fonction de la fonction dans 
laquelle on se situe

renvoie le type trouvé 
si la variable n'est pas dans la table, on renvoie -1

*/


int find_type_var(Tab_symb tab, char * nom_var, int pos){
  int type;
  /* la variable est de type void donc on a pas trouvé*/
  if(strcmp("void", nom_var) == 0)
    return -1;
  /* on vérifie que le nom de la variable existe*/
  if(ishere(tab, nom_var, tab.nb_fonc-1) == 0 && ishereglobale(tab, nom_var) == 0){
  printf("la variable : %s a été appelée alors qu'elle n'existe pas \n", nom_var);
  /* la variable a été utilisé lors de l'appel alors qu'elle n'existe pas*/
    return -1;
  }
  /* on a retrouvé le type de la variable donc on le renvoie*/
  if( (type = istype(tab, nom_var, pos)) != -1){
    return type;
  }
  /* on a pas trouvé le type de la variable, donc elle n'existe pas*/
  return -1;
}


/* réinitialise le tableau de char d'une variable de type Variable*/
void init_tab_attempt(Tab_symb * tab){
    /* -1 signifie que on n'a pas de hashcode que l'on cherche à utiliser*/
    tab->attempt= -1;
}





















/* ajoute une variable à la table des symboles*/
/* elle renvoie 1 si tout s'est bien passé, et 0 sinon*/


int add_var(Tab_symb *tab_symb, char * nom_var,int type_var, int ligne){

  int code;

  variable * var1;

  variable * tmp;
  /* cas où on ajoute un type d'ident*/
  code = tab_symb->attempt;
  /* cas où on ajoute une variable (ou une variable plus autre chose) donc que le nom de var n'est pas vide*/

  if(nom_var != NULL)

    code = hashcode(nom_var);

  /*cas où la variable est déjà dans le tableau on arrête tout*/

  /* on teste cette possibilité si et seulement si le nom de la variable n'est pas null, c'est à dire qu'on essaye d'ajouter un nom de
  variable*/

  if(nom_var != NULL && ishere(*tab_symb , nom_var, tab_symb->nb_fonc-1) == 1){
        /* l'emplacement serait celui qui est déjà dans la tab des symboles essayer la ligne associée à la variable */

        char msg[200];

        /* variable qui enregistre la ligne dans la tab des symboles associées à la variable qui est déjà enregistré */

        char l2[10];

        variable var2;

        strcpy(msg, "multiples declaration of the same variable in the same function: ' ");

        /* on recopie la variable qui était déjà présente dans la tab pour sa ligne */

        deep_copy_var(&var2, search_variable(*tab_symb,nom_var,tab_symb->nb_fonc-1));

        strcat(msg, nom_var);



        strcat(msg,"  ' ");

         /*  la ligne dans la tab des symboles associée à la variable qui est déjà enregistré */

        strcat(msg," | Line : ");

        sprintf(l2, "%d", var2.line);

        strcat(msg, l2);

         strcat(msg, "   AND  ");
        
        yyerror2(msg, ligne, 1);

        /* l'utilisateur a déclaré deux fois la même variable avec un type différent ou le même type : erreur*/

        init_tab_attempt(tab_symb);

        /* on lance code d'erreur */
        return 0;   
  }
  
  /* si le code est négatif cela signifie que la variable était déjà là (et donc que la dernière tentative d'ajout de nom de variable a échouée), on arrête tout */
  if(code == -1){
        /* on ne cherche plus, la variable est déjà là*/
        tab_symb->attempt = -1;
        /* printf("la variable est déjà là \n");*/
        return 1;
  }
  /* cas où on ajoute le nom de la variable. il est possible qu'on ne connaisse jamais son type dans ce cas particulier .
  Premier cas : le premier emplacement associé au code est vide ou on enregistre le type de la variable : pas besoin de chainer.*/
  else if(tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].used  < 2 && ( (type_var != -1 && type_var != MY_NULL && type_var != MY_VOID) || nom_var != NULL)){

    /* on réalise les copies des noms*/
    /* on constate qu'il n'y a pas d'allocation dynamique car on a supposé raisonnablement que 
    les noms ne pouvaient pas dépasser les tailles respectives de 100 et 200 caractères
    si ce nombre est dépassé il faudra envisager un malloc
    */
        
    /* on ajoute le nom de la variable*/
      if(nom_var != NULL){

              /* on précise que le nom a été enregistré*/
              tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].used = 1;
              strcpy(tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].nom, nom_var);
              tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].suivant = NULL;
              /*on ajoute aussi l'emplacement où il faudra enregistrer si on trouve le type*/
              tab_symb->attempt = code;
             /* pas de type de retour récupéré car il n'y en pas pour une variable*/
              tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].type_rec = -1;
              /* on ajoute l'adresse pour cette variable*/
              tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].adresse = adr_tab;

              /*update pour la prochaine adresse*/
    
              adr_tab +=8;

              /*return 1; on essaye de s'en passer*/
      }

      /* on ajoute le type de la variable*/
      if(type != -1){
              tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].type = type_var;
              tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].suivant = NULL;
              /* le type de la variable a été enregistré, on précise que l'ajout est complet*/
              tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].used = 2;
              /* on ajoute aussi la ligne où se trouve la variable*/
              tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].line = ligne;
              /* pas de type de retour récupéré car il n'y en pas pour une variable*/
              tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].type_rec = -1;

              /* on précise que le type a été enregistré, il n'est donc plus nécessaire de faire d'attempt*/

              init_tab_attempt(tab_symb);
              return 1;
      }
    }

  /* cas où l'emplacement est occupé, on cherche un emplacement vide dans la liste chainée*/
  else{

    tmp = tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].suivant;
    /* cas où le premier élément alloué dynamiquement vaut null */
    if(tmp == NULL){
      /* on crée dynamiquement une variable*/
      /*cas d'échec*/
      if((var1 = (variable *) malloc(sizeof(variable))) == NULL){
                printf("échec du malloc \n");
        return 0;
            }
      
      /* on affecte au premier élément de la liste le nouvel élément comme son suivant*/
      tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].suivant = var1;
    }

    /* on parcourt jusqu'à trouver le premier emplacement vide dans liste pour chainer*/   
    else{
      while(tmp->suivant != NULL){

        tmp = tmp->suivant;

      }
      /* cas où le dernier élément du tableau était totalement rempli et qu'on cherche à ajouter une nouvelle variable et non un type*/
      /* on alloue donc pour un nouvel élément*/
      if(tmp->used == 2 && type_var == -1){
        /* on crée dynamiquement une variable*/
        /*cas d'échec*/
        if((var1 = (variable *) malloc(sizeof(variable))) == NULL){
          printf("échec du malloc \n");
          return 0;
        }
        /* on affecte au dernier élément de la liste le nouvel élément comme son suivant*/
        tmp->suivant = var1;
      }
      /*cas où le dernier élément du tableau n'était pas totalement rempli ou qu'on cherche ou à ajouter un type*/
      else{
        var1 = tmp;
      }
    }

    /* on copie les infos du nom de la variable*/
    if(nom_var != NULL){

        strcpy(var1->nom, nom_var);
        /* l'emplacement est en partie utilisé*/
        var1->used=1;
        /* on met les infos du type du pointeur attempt dans un état de recherche*/
        tab_symb->attempt = code;

        /* adresse de la variable */

        var1->adresse = adr_tab;

        /* update pour le prochain ajout */
        adr_tab += 8;
    }

    /* on copie les infos du type de la variable et on les mets dans l'emplacement du tableau*/

    if(type_var != -1){

      var1->type = type_var;
      /* l'emplacement est totalement utilisé*/
      var1->used=2;
      var1->line = ligne;
      /* pas de type de retour récupéré car il n'y en pas pour une variable*/
      var1->type_rec = -1;

      
      /* cas où on a traité le type on ne va plus faire de recherche d'attempt, on remet à -1*/
      init_tab_attempt(tab_symb);
    }

    var1->suivant = NULL;
  }
  return 1;
}





















/* fonction d'ajout général qui va appeler soit la fonction d'ajout d'une fonction soit celle d'une variable suivant les cas
renvoie 0 en cas de problème
renvoie 1 si tout s'est bien passé*/
int add_varfonc(Tab_symb *tab_symb, char * nom_var, int type_var, int ligne){
   

    /* si elle n'a pas encore été initialisée, on initialise la table des symboles*/
    init_tab_symb(tab_symb);

    /* cas où on entre dans une fonction
    On traite donc une fonction */

    if(tab_symb->tab_fonc[(tab_symb->nb_fonc-1)][FONCTION].used < 2){
        /* on remet les attempts à -1 pour éviter la confusion sur l'ajout du type*/
        init_tab_attempt(tab_symb);
        /* on traite une fonction*/
        return add_fonc(tab_symb,nom_var,type_var, ligne);
    }
    /* on traite une variable*/
    return add_var(tab_symb,nom_var,type_var, ligne);
}

/* affiche le type d'une variable ou le type de retour d'une fonction*/
void show_type(int type){
  if(type == MY_CHAR){
    printf("char");
  }

  else if(type == MY_INT){
    printf("int");
  }

  else if(type == MY_VOID){
    printf("VOID");
  }
}

/* affiche la catégorie d'un identificateur*/
void show_categorie(int categorie){
  if(categorie == MY_FUNCTION){
    printf("fonction");
  }

  else if(categorie == MY_VARIABLE){
    printf("variable");
  }

  else if(categorie == MY_PARAMETRE){
    printf("parametre");
  }

  else if(categorie == MY_FILE){
    printf("fichier");
  }
}



/* enregistre le type "type" sous forme de chaine de caractère dans tab*/
void type_to_char(int type, char tab[10]){
  if(type == MY_CHAR){
    strcpy(tab, "char");
  }

  else if(type == MY_INT){
    strcpy(tab, "int");
  }

  else if(type == MY_VOID){
    strcpy(tab, "VOID");
  }
  /*my_none*/
  else {
    strcpy(tab, "UNDEFINED");
  }
}


/* affiche une liste chainée de variable*/
void show_liste_var(variable var, int code){

    variable *tmp;

    /* cas où cet emplacement n'a pas été utilisé*/

    if(var.used < 2){

        return;

    }

    tmp = &var;

    while(tmp != NULL) {

        printf("var : type : ");
        show_type(tmp->type);
        printf("  \n");
        printf("var : nom : %s \n",tmp->nom);
        printf("var : adresse: %d \n",tmp->adresse);
        printf("var : ligne : %d \n", tmp->line);
        tmp = tmp->suivant; 

    }

}








/* affiche la table des symboles*/
void show_tab_symb(Tab_symb tab_symb){

    int i;
    int j;
    
    printf("le nombre de fonction est : %d \n", tab_symb.nb_fonc-1);
    /*on affiche les variables et leurs types pour chaque fonction que l'on possède*/
   for(i = 0; i< tab_symb.nb_fonc;i++){

        /* on affiche pas la fonction "globale" qui n'est pas une vraie fonction*/
        if(i != GLOBALE){
          /* à cause de la fonction globale on doit décrémenter de 1*/
          if(i > GLOBALE)
            printf("nous sommes à la fonction numéro : %d \n" ,i-1);

          else if(i < GLOBALE)
            printf("nous sommes à la fonction numéro : %d \n" ,i);

         

          printf("fonc, type retour : " );
          show_type(tab_symb.tab_fonc[i][FONCTION].type);
          printf("  \n");
          printf("fonc, nom : %s \n", tab_symb.tab_fonc[i][FONCTION].nom);
          printf("fonc, adresse mémoire nasm: %d \n", tab_symb.tab_fonc[i][FONCTION].adresse);

        }
        else
            printf("les variables globales : \n");
        for(j =1;j<NB_VAR;j++){

          /* on précise que l'on va afficher les arguments tant que j vaut 2*/
          
          if(i == GLOBALE){

           /*on fait rien */

          }

          else{

              if(j == ARGS){

                printf("La liste des arguments de la fonction \n");

              }

            /* on précise que l'on va afficher les variables pour tous les j supérieurs à 2*/

              if(j == VARIABLES){

                printf("La liste des variables de la fonction \n");

              }
          }

            
              show_liste_var(tab_symb.tab_fonc[i][j], j);
        }
        

    }
}


























/* ajoute un numéro de type (int/char/none/void) à un noeud sous forme d'entier en fonction du type donné en argument*/
void add_type_node(Node * node, char * type){

  if(strcmp(type,"char") == 0){
    node->type =  MY_CHAR;
  }
  
  else if(strcmp(type, "int") == 0){
    node->type =  MY_INT;
  }

  else if(strcmp(type, "void") == 0) {
    node->type =  MY_VOID;
  }
  else{
    node->type =  MY_NULL;
  }

}
















/* ajoute un argument de la fonction et son type à la table des symboles*/
/* elle renvoie 1 si tout s'est bien passé, et 0 sinon*/
int add_param(Tab_symb *tab_symb, char * nom_var, int type_var, int ligne){
  /* cas à résoudre mais en solution provisoire interdire au programme de donner des arguments à globale.
  Pour une raison qui échappe au développeur globale prend les arguments de toutes les fonctions pour ses propres*/
   if(tab_symb->nb_fonc-1 == GLOBALE){
     return 1;
   }
  int code;

  variable * var1;

  variable * tmp;
  /* cle hashcode sera toujours 1, car on chaine tous les arguments les uns à la suite des autres*/
  code = ARGS;
  
  /*cas où la variable est déjà dans le tableau on arrête tout et on renvoie une erreur*/
  /* on teste cette possibilité si et seulement si le nom de la variable n'est pas null, c'est à dire qu'on essaye d'ajouter un nom de
  variable*/

  if(nom_var != NULL && ishere(*tab_symb , nom_var, tab_symb->nb_fonc-1) == 1){
        char msg[200];
        init_tab_attempt(tab_symb);
        strcpy(msg, "multiples declaration of the same parameter in the prototype: ' ");
        strcat(msg, nom_var);
        strcat(msg,"  ' ");
        yyerror2(msg, ligne, 1);
        return 0;   
  }
  
  /* cas où on ajoute le nom de la variable. il est possible qu'on ne connaisse jamais son type dans ce cas particulier .
  Premier cas : le premier emplacement associé au code est vide ou on enregistre le type de la variable : pas besoin de chainer.*/
  else if(tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].used  < 2 && (type_var != -1|| nom_var != NULL)){

    /* on réalise les copies des noms*/
    /* on constate qu'il n'y a pas d'allocation dynamique car on a supposé raisonnablement que 
    les noms ne pouvaient pas dépasser les tailles respectives de 100 et 200 caractères
    si ce nombre est dépassé il faudra envisager un malloc
    */
        
    /* on ajoute le nom de la variable*/
      if(nom_var != NULL){
              /* on précise que le nom a été enregistré avec 1*/
              tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].used = 1;
              strcpy(tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].nom, nom_var);
              tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].suivant = NULL;
              /* on ajoute aussi la ligne de déclaration de la variable*/
              tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].line = ligne;
              tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].adresse = adr_tab;
              /* adresse mise à jour*/
              adr_tab +=8;
              /*on ajoute aussi l'emplacement où il faudra enregistrer si on trouve le type*/
              tab_symb->attempt = code;
              return 1;
      }

      /* on ajoute le type de la variable*/
      if(type != -1){
              tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].type = type_var;
              tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].suivant = NULL;
              /* le type de la variable a été enregistré, on précise que l'ajout est complet avec "2"*/
              tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].used = 2;
              /* on ajoute aussi la ligne de déclaration de la variable*/
              tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].line = ligne;
              /* on précise que le type a été enregistré, il n'est donc plus nécessaire de faire d'attempt*/
              init_tab_attempt(tab_symb);
              return 1;
      }
    }

  /* cas où l'emplacement est occupé, on cherche un emplacement vide dans la liste chainée*/
  else{

    tmp = tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].suivant;
    /* cas où le premier élément alloué dynamiquement vaut null */
    if(tmp == NULL){
      /* on crée dynamiquement une variable*/
      /*cas d'échec*/
      if((var1 = (variable *) malloc(sizeof(variable))) == NULL){
                printf("échec du malloc \n");
        return 0;
            }
      
      /* on affecte au premier élément de la liste le nouvel élément comme son suivant*/
      tab_symb->tab_fonc[tab_symb->nb_fonc-1][code].suivant = var1;
    }

    /* on parcourt jusqu'à trouver le premier emplacement vide dans liste pour chainer*/   
    else{
      while(tmp->suivant != NULL){

        tmp = tmp->suivant;

      }
      /* cas où le dernier élément du tableau était totalement rempli et qu'on cherche à ajouter une nouvelle variable et non un type*/
      /* on alloue donc pour un nouvel élément*/
      if(tmp->used == 2 && type_var == -1){
        /* on crée dynamiquement une variable*/
        /*cas d'échec*/
        if((var1 = (variable *) malloc(sizeof(variable))) == NULL){
          printf("échec du malloc \n");
          return 0;
        }
        /* on affecte au dernier élément de la liste le nouvel élément comme son suivant*/
        tmp->suivant = var1;
      }
      /*cas où le dernier élément du tableau n'était pas totalement rempli ou qu'on cherche ou à ajouter un type*/
      else{
        var1 = tmp;
      }
    }

    /* on copie les infos du nom de la variable*/
    if(nom_var != NULL){
        strcpy(var1->nom, nom_var);
        /* l'emplacement est en partie utilisé*/
        var1->used=1;
        /* on met les infos du type du pointeur attempt dans un état de recherche*/
        tab_symb->attempt = code;
    }

    /* on copie les infos du type de la variable et on les mets dans l'emplacement du tableau*/
    if(type_var != -1){
      var1->type = type_var;
      /* l'emplacement est totalement utilisé*/
      var1->used=2;
      var1->line=ligne;
      var1->adresse = adr_tab;
      /* on avance 8 pour nasm*/
      adr_tab+=8;
      /* cas où on a traité le type on ne va plus faire de recherche d'attempt, on remet à -1*/
      init_tab_attempt(tab_symb);
    }

    var1->suivant = NULL;
  }
  return 1;
}























/* Ajoute toutes les fonctions prédéfinies demandées : getchar(), ...*/



int add_usual_fonct(Tab_symb * tab_symb){

    int value;
    /* par défaut tout s'est bien passé*/

    value = 1;


    /* ====================   GETCHAR    =========================*/

    

     /* on ajoute ensuite le nom + type de la fonction à la table de symbole*/
    if(add_varfonc(tab_symb, "getchar", MY_CHAR, LINE_IMPORT) == 0){

      value = 0;

    }

   else{

      tab_symb->tab_fonc[tab_symb->nb_fonc-1][MY_FUNCTION].type_rec = MY_CHAR;
      tab_symb->nb_fonc++;

    }
   

     /* ====================   PUTCHAR    =========================*/


    /* on ajoute le type de retour de la fonction */
    if(add_varfonc(tab_symb, "putchar", MY_VOID, LINE_IMPORT) == 0){

      value =  0;
    }


  /*on ajoute ensuite les arguments*/

    else{

      add_param(tab_symb, "c", -1, 0);
      add_param(tab_symb, NULL, MY_CHAR, 0);
       tab_symb->tab_fonc[tab_symb->nb_fonc-1][MY_FUNCTION].type_rec = MY_VOID;
      tab_symb->nb_fonc++;

    }


     /* ====================   GETINT    =========================*/
    

    /* on ajoute  le type de retour de la fonction + le nom de la fonction à la table de symbole*/
    if(add_varfonc(tab_symb, "getint", MY_INT, LINE_IMPORT) == 0){

      value = 0;
      
    }
    
    else{
       tab_symb->tab_fonc[tab_symb->nb_fonc-1][MY_FUNCTION].type_rec = MY_INT;
      tab_symb->nb_fonc++;

    }


     /* ====================   PUTINT    =========================*/

    /* on ajoute ensuite le nom de la fonction + de type de retour à la table de symbole*/
    if(add_varfonc(tab_symb, "putint", MY_VOID, LINE_IMPORT) == 0){

      value = 0;
      
    }

    /* on ajoute les arguments*/

   else{

      add_param(tab_symb, "i", -1, 0);
      add_param(tab_symb, NULL, MY_INT, 0);
      tab_symb->tab_fonc[tab_symb->nb_fonc-1][MY_FUNCTION].type_rec = MY_VOID;
      tab_symb->nb_fonc++;

    }

    return value;
}

/*fonction qui vérifie que la fonction a un main et si oui s'il est au bon endroit
elle renvoie 1 si le main est bien situé.
 elle renvoie 0 si il n'y a pas de main 
elle renvoie -1 si le main est mal situé*/
int has_main(Tab_symb tab){
  int res;

  /* il n'y pas de main du tout*/

  if(( res =  isherefonc(tab, "main")) ==0 ){
    return 0;
  }
  /* il y a un main mais il est mal situé, code d'erreur*/
  
  if(strcmp(tab.tab_fonc[tab.nb_fonc-1][MY_FUNCTION].nom, "main") != 0) {
        return -1;
  }

  /* le main est présent et est bien situé*/
  return res;
}

/* fonction qui renvoie le type de retour d'une fonction
la tab1 est la table dans laquelle on cherche la fonction et nom_fonc et la fonction que l'on cherche
on renvoie -2 si la fonction n'existe pas, -1 si son type de retour est void, et sinon on renvoie le type de retour la fonction*/
int retourne(Tab_symb tab1, char * nom_fonc){
  int i;
  /* si la fonction dont on cherche le type de retour n'existe pas, on renvoie 0*/
  if(isherefonc(tab1, nom_fonc) == 0){
    return -2;
  }
  /* la fonction existe on cherche son type de retour*/

   for(i=0;i<tab1.nb_fonc;i++){
    /* cas où le nom de la fonction a été trouvé parmi les noms des fonctions */
    /*si on est sur l'emplacement associé fichier "globale" alors on ignore cet emplacement d'où le i != GLOBALE*/

      if(i != GLOBALE){

        if(strcmp(tab1.tab_fonc[i][0].nom, nom_fonc) == 0){

          /*le type de retour étant différent de void, il est valide, on le renvoie*/

            if(tab1.tab_fonc[i][0].type != MY_NULL && tab1.tab_fonc[i][0].type != MY_VOID  && tab1.tab_fonc[i][0].type != MY_NONE)
              return tab1.tab_fonc[i][0].type;

            /* le type de retour étant void, on ne peut pas l'affecter à une variable, c'est donc une erreur*/
            else
              return -1;

        }

      }
   }

   return -2;

}

#if 0
/* affiche les liens entre les noeuds (siblings, fils,....)*/
void printLink(Node *node) {

  

  static bool rightmost[128]; // tells if node is rightmost sibling
  static int depth = 0;       // depth of current node
  for (int i = 1; i < depth; i++) { // 2502 = vertical line
    printf(rightmost[i] ? "    " : "\u2502   ");
  }
  if (depth > 0) { // 2514 = L form; 2500 = horizontal line; 251c = vertical line and right horiz 
    printf(rightmost[depth] ? "\u2514\u2500\u2500 " : "\u251c\u2500\u2500 ");
  }

   printf("%s", StringFromLabel[node->label]);

  /*ECRIRE LES AUTRES TRUCS CORRESPONDANTS*/
  printf("\nCatégorie (%s): %d \n", StringFromLabel[node->label], node->show);

    switch(node->show){
        case 0:{
            printf("%d",node->value.entier);
            break;
        }

        case 1:{
            printf("%c", node->value.caractere);
            break;
        }

        case 2:{
            printf("%s",node->value.val);
            break;
        }
    }

  printf("\n");
  depth++;
  for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
    rightmost[depth] = (child->nextSibling) ? false : true;
    printLink(child);
  }
  depth--;

  




}
  #endif




#if 0

/*Fonction qui evalue le type d'une expression (variable, appel fonction, valeurs brutes)*/
int expression_type(Node * node, Tab_symb tab, int pos){

    Node * child;

    child = node->firstChild;

    if(strcmp(StringFromLabel[child->label], "variable : ") == 0){

        return find_type_var(tab, child->value.val);
    }

    if(strcmp(StringFromLabel[child->label], "valeur : ") == 0){

        return MY_INT;
    }

    if(strcmp(StringFromLabel[child->label], "caractère : ") == 0){

        return MY_CHAR;
    }


    if(child->firstChild == NULL){
        return -1;
    }


    /*Appel de fonction*/
    if(strcmp(StringFromLabel[child->firstChild->label], "fonction : ") == 0){

        return retourne(tab, child->firstChild->value.val);
    }



    return -1;
}
#endif



/*Fonction qui evalue le type d'une expression*/
#if 0
int evaluate_expression(Node * node, Tab_symb tab){

    if(node != NULL){

        if(node->firstChild->firstChild == NULL){
            return expression_type(node, tab);
        }



    }

    return 1;
}
#endif






/*

Trouve et verifie la bonne utilisation des returns de la fonction definies par le noeud 'fonction'

0 -> Void

1 -> Int

2 -> Char

fonction : est la fonction appelante où est le programme : cela permet de connaitre les variables autorisées.

pos correspond à la position de la fonction appelante.

fonction -> Noeud associé à la fonction appelante elle-même

node -> noeud actuellement traité

tab_symb -> table des symboles.

ret1-> type structuré qui contient les éléments qui font partie de l'expression qui sera renvoyée.

ret2 -> correspond à la fonction appelante et le type retour associée attendue.

*/


int checkReturnedType(Node * node, Node * fonction, List_args * ret2, List_args * ret1, int pos, Tab_symb tab_symb){
  
  static int trait = 0;

  int check;

  Node * node3;

  Node * node2;

  /* On utilise check pour dire que l'on va 

  vérifier au premier appel. */

  check = 0;

  /* On ne fera ça qu'une seule fois */

  if(trait == 0){

      /* on ajoute la fonction qui est appelante 
      à la liste ret2 : on connait ainsi son nom, sa ligne de définition et son type de retour 
      */
      add_fonclist(fonction, tab_symb, ret2);

      check = 1;

      trait = 1;

  }

  /* on passe ensuite au traitement de la valeur de retour (DEBUT) */

  /* à chaque fois qu'on tomberait sur un élément, il faudrait segmenter en deux : d'une part on chercherait l'opérateur ou une valeur/identificateur suivant qui serait le fils, d'autre part, on chercherait 
l'identficateur/valeur suivante tout court, qui serait le sibling
lorsqu'on tombe sur un ident on se met à chercher seulement son frère qui est en fait le nombre avec lequel il s'applique un opérateur*/


  
  
  if(node != NULL){


    node2 = node->firstChild;

    node3 = node->nextSibling;

    /* on tombe sur une variable, on la copie */
    
    if (strcmp(StringFromLabel[node->label], "variable : ") == 0 ) {   


        variable v5;

        int type1;

        /* on récupère le type de la variable de retour */

        type1 = istype(tab_symb, node->value.val, pos);

        create_variable(node->value.val, type1, node->line, &v5);


        /* manque d'espace pour copier la variable : échec malloc*/

        if(deep_copy_var_tab(ret1, v5) == -1) {

            printf(" échec de la copie errreur !!! \n");

            return 0;
        }
               

        /* on lance un appel récursif sur l'arbre */

        checkReturnedType(node2, fonction, ret2, ret1, pos, tab_symb);
        

        /* on lance un appel récursif sur l'arbre   */

        checkReturnedType(node3, fonction, ret2, ret1, pos, tab_symb);



    }
    
    
    /* on tombe sur un opérateur, on fait seulement un appel récursif */

    else if (strcmp(StringFromLabel[node->label], "operateur : ") == 0 ) {              

        node2 = node->firstChild;

        node3 = node->nextSibling;

        /* on lance un appel récursif sur l'arbre   */

        checkReturnedType(node2, fonction, ret2, ret1, pos, tab_symb);
        

       
        /* on lance un appel récursif sur l'arbre   */

        checkReturnedType(node3, fonction, ret2, ret1, pos, tab_symb);


    }

    /* cas d'une fonction*/

    else if(strcmp(StringFromLabel[node->label], "fonction : ") == 0 && node->value.val != NULL ){

      

        /* on vérifie que la fonction en elle-même respecte la forme du langage C
        checkExpr(curr2, curr, tab); --> Ce n'est plus nécessaire, le programme CheckArbre via passe de lui même via checkexpr sur la fonction qui est en right-value.
        */
        
        /* ensuite on ajoute en particulier la fonction à la liste des éléments de l'expression, pour vérifier que son type de retour colle bien aux aattentes.
        Si la fonction n'existe pas alors elle est de type non-type*/

        add_fonclist(node, tab_symb, ret1);

        return 1;
        
        
      }


      /* cas où on tombe sur un argument, on arrête le parcours*/


      else if(strcmp(StringFromLabel[node->label], "ARGUMENTS") == 0 && node->value.val != NULL ){
        
        
            return 1;

      }


    /* on tombe sur une constante, on crée une variable spéciale pour les constantes et on la copie */

    else {

          variable var1;

          node2 = node->firstChild;

          node3 = node->nextSibling;

         



          

          /* chaine de caractère constitué à partir de la constante */

          char consta[100];
                        
                      if(strcmp(StringFromLabel[node->label], "valeur : ") == 0){

                            /* le problème est lié au nombre qui sont entre parenthèse il crée des stack smashing detected*/

                            /* on copie dans une chaine de caractère le nom de la constante */
                            
                            sprintf(consta,"%d",node->value.entier);

                            create_variable(consta, MY_INT, node->line, &var1);
                            
                            /* on vérifie qu'il n'y pas d'erreur lors de l'ajout de la constante dans le tableau*/
                            
                            if(deep_copy_var_tab(ret1, var1) != 1){

                              printf("erreur lors de la copie d'une constante ");

                              return 0;
                            }
                            
                            

                        }

                        /* cas où on tombe sur des caractères seuls */
                        
                        else if(strcmp(StringFromLabel[node->label],  "caractère : ") == 0){
                              
                              strcpy(consta, &(node->value.caractere));

                              create_variable(consta, MY_CHAR, node->line, &var1);
                              
                              if(deep_copy_var_tab(ret1, var1) != 1){

                                printf("erreur lors de la copie d'une constante ");

                                return 0;
                              }
                        }
                        


          

           


        }


        checkReturnedType(node2, fonction, ret2, ret1, pos, tab_symb);

        /* 
        on lance un appel récursif sur l'arbre sur le frère*/

        checkReturnedType(node3, fonction, ret2, ret1, pos, tab_symb);

    }

    /* On passe ensuite à l'analyse une fois qu'on a récupéré tous les contenus des noeuds grâce aux appels récursifs */
  
    if(check == 1){

      /* on reprépare trait pour le prochain appel en le reinitialisant*/

        trait = 0;

      /* On revoie différentes valeurs selon si tout s'est bien passé ou non*/

        /* Test : A supprimer 
        printf(" les tableaux qu'on analyse contiennent : \n");

        show_list_args(*ret2);

        printf("\n\n\n");
        
        show_list_args(*ret1);*/

        


        return check_returned_value(*ret2, *ret1);
        

        
    
    }
    
    
  

    /* cas par défaut on est dans un traitement récursif, il n'est donc pas pertinent d'anaylser le tableau*/
    
    return 1;
        

  }
  
  


/* Analyse l'arbre, pour vérifier que les actions réalisées dans le fichier .c sont valides.
curr correspond à la fonction appelante, node correspond au noeud sur lequel on est acutellement dans l'arbre 
tab est la tab des symboles


curr correspond au noeud dans lequel le user est actuellement.
Node correspond au noeud de la fonction appelante.


 */

int checkArbre(Node * curr, Node * node, Tab_symb * tab){
 
  /* variable utilisée pour compter les arguments ou déterminer les éléments des left et right value*/
  List_args list;
  List_args list2;
  init_list_args(&list);
  init_list_args(&list2);

  /* valeur de retour : renvoie 1 si tout s'est bien passé par défaut et 0 sinon*/
  static int ok = 1;
  int pos;

  static int depth = 0;       // depth of current node

  /* variable qui indique si on doit ignorer les ajouts des variables et des arguments jusqu'à la prochaine fonction, car 
  la dernière fonction vue aurait été refusées*/
  int static stop = 0 ;

    /* on met à jour la fonction qui est actuellement traité.
    Cela est indispensable pour connaitre les variables qui sont disponibles*/

    /* il faudra gérer les différents cas par différentes sous fonctions :

      -cas d'une affectation.
      -cas d'une expression seule (courte ou composée (opérateurs))
      -cas des switchs ??

    */
    /* fin de parcours*/
    if(node == NULL) {  


      return 1;


    }



      if(strcmp(StringFromLabel[node->label], "identificateur : ") == 0 && node->value.val != NULL ){

      /* le pointeur prend comme info le dernier noeud associé à une déclaration de fonction traité*/

          curr = node;

      /* 
      si la fonction a en réalité été refusée par la table,
      on va ignorer ce qui viendra après.*/

          if(isherefonc(*tab, node->value.val) != 1)
              stop = 1;
          else stop = 0;

          /*printf(" la fonction traitée mtnt est : %s \n" ,curr->value.val);*/
        
      }

      /* si on a pas décidé d'ignorer la dernière fonction croisée (stop != 1), alors on passe
      à l'analyse de son contenu sinon on ignore tout ce qu'on peut voir jusqu'à tomber à nouveau sur une fonction */

      if(stop != 1){
  
        /*On arrive sur une appel de fonction qui est seul */

        if(strcmp(StringFromLabel[node->label], "fonction : ") == 0 && node->value.val != NULL){

          /* noeud actuellement traité*/
          Node * curr2;

          curr2 = node;
          /* on vérifie que l'expression respecte la forme du langage C*/
         
          if(checkExpr(curr2, curr, *tab) == 0){

             /* cas d'erreur */
            ok = 0;
          }
          
        }


          /* cas où on arrive sur une affectation*/
          else if(strcmp(StringFromLabel[node->label], "=") == 0){


            /*printf(" le frrère de == est : %s " node->next);*/
            
            /* noeud actuellement traité*/
            Node * curr2;

            /* on créé d'abord une variable qui correspondra à la valeur gauche*/
            curr2 = node->firstChild;


            /* on vérifie que l'affectation respecte la forme du langage C */
            if(checkAffArbre(curr2, curr, *tab, &list, &list2) == 0){

              /* cas d'erreur*/
              ok = 0;
            }
            
            printf("\n\n\n\n ");
            

          }

          /*On trouve le return*/
          if(strcmp(StringFromLabel[node->label], "return") == 0){
              
              /* noeud actuellement traité*/

              Node * curr2;

              /* récupère la valeur de retour */
              int ret1;




              /* on créé d'abord une variable qui pointera*/

              curr2 = node->firstChild;


              /*on récupère la position de la fonction appelante*/
              
              pos = foncpos(*tab, curr->value.val);

              /* on précise qu'on a trouvé un retour pour la fonction en question*/

              


              
              /* on vérifie que le type de retour respecte la forme du langage C */

              /* s'il y a un problème : on renvoie 0, on arrête tout */

              if((ret1 = checkReturnedType(curr2, curr, &list, &list2, pos, *tab)) == -1 ){

                  /* cas d'erreur*/

                  ok = 0;

                 /* printf(" échec pour trouver le retour pour la fonction : %s ", curr->value.val);*/

              }

              else{

                 /* la fonction récupère le fait qu'ella a eu le type de retour qu'il lui fallait */

                /* printf(" On a trouvé le le retour pour la fonction : %s ", curr->value.val);*/

                  tab->tab_fonc[pos][MY_FUNCTION].type_rec = ret1;
              }
              

              printf("\n\n\n\n ");


            }
        }
      
  
    depth++;
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {


      checkArbre(curr, child, tab);

      
    }
    depth--;

    /* on revoie la variable static ok, cela permet d'analyser tout le code plutôt que de tout stopper à la moindre erreur */
    return ok;

}

/* compte le nombre d'argument d'une fonction dans la table des symboles
 pos correspond à l'emplacement de la fonction dans la tab des symboles 
 elle renfoie le nombre d'arguments si tout se passe bien, et 0 en cas d'erreur.*/

int nb_args(Tab_symb tab, int pos){

  /* variable qui compte le nombre d'argument*/

  int count;

  variable * var1;

  count = 0;

  if(pos < tab.nb_fonc){

    printf(" Erreur Vous cherchez une fonction qui n'est pas présente dans la table des symboles \n");

    return -1;

  }
  
  else{

    /* à chaque fois qu'on trouve une variable on avance*/
    for(var1 = &(tab.tab_fonc[pos][ARGS]) ; var1 != NULL && var1->used == 2 ; var1 = var1->suivant){

      count++;

    }

  }

  return count;
}








/* fonction qui gère la copie profonde d'une variable sauf de son suivant*/

void deep_copy_var(variable * dest, variable source){

  strcpy(dest->nom, source.nom);
  dest->type = source.type;
  dest->used = source.used;
  dest->cat = source.cat;
  dest->line = source.line;
  /* on copie tout sauf le suivant*/
  dest->suivant = NULL;
  /*printf(" la ligne est %d \n" , source.line);*/

}

/* vérifie si la variable que l'on souhaite copier n'est pas déjà présente dans dest, cela peut arriver :

1 = elle est déjà là
0 = elle n'est pas là

*/


int var_already_present(List_args* dest, variable source){

  int i;
  /*printf(" la valeur de used : %d \n\n\n ", dest->used);*/
  for(i=0 ; i< dest->used; i++){

    /* la variable qu'on essaye de copier est déjà présente, on arrête le parcours */

    if(strcmp(dest->tab[i].nom, source.nom) == 0 && dest->tab[i].type == source.type){
      /*printf(" \n\n already PPPPP \n\n\n\n\n");*/
      return 1;

    }

  }
  /* la variable n'était pas présente, on peut la copier */

  return 0;
}

/* fonction qui gère la copie profonde d'une variable pour un tableau de type Listvar
elle renvoie -1 en cas d'échec de la copie et 1 si tout s'est bien passé */

int deep_copy_var_tab(List_args* dest, variable source){
  /* code d'erreur on ne peut plus faire de copie dans ce tableau*/
  /*printf(" vous utilisez déjà comme espace : %d \n" ,dest->used);*/
  if(dest->max <= dest->used){
    printf(" le maximum d'espace disponible est : %d et vous utilisez déjà : %d \n\n" ,dest->max, dest->used);
    printf("Le contenu est en effet : \n");
   show_list_args(*dest);
    return -1;
  }
  /* la copie n'est pas nécessaire car la variable est déjà là, tout s'est bien passé*/

  if( var_already_present(dest, source) == 1){

    return 1;
  }

  /* on fait la copie*/

  deep_copy_var(&dest->tab[dest->used], source);

  /* un emplacement du tableau a été utilisé en plus donc on augmente le nombre d'emplacement utilisés au total*/
  dest->used++;

  return 1;
}


/* fonction qui gère la copie profonde d'une variable pour un tableau de type Listvar pour le cas particulier d'une fonction :
une copie double d'un variable est possible 
elle renvoie -1 en cas d'échec de la copie et 1 si tout s'est bien passé */

int deep_copy_var_tabf(List_args* dest, variable source){
  /* code d'erreur on ne peut plus faire de copie dans ce tableau*/
  /*printf(" vous utilisez déjà comme espace : %d \n" ,dest->used);*/
  if(dest->max <= dest->used){
    printf(" le maximum d'espace disponible est : %d et vous utilisez déjà : %d \n\n" ,dest->max, dest->used);
    printf("Le contenu est en effet : \n");
   show_list_args(*dest);
    return -1;
  }

  /* on fait la copie*/

  deep_copy_var(&dest->tab[dest->used], source);

  /* un emplacement du tableau a été utilisé en plus donc on augmente le nombre d'emplacement utilisés au total*/
  dest->used++;

  return 1;
}






/* fonction qui gère l'ajout des params que contient une fonction à un tableau de taille MAX_ARGS
pos correspond à l'emplacement de la fonction dans la tab des symboles
params correspond aux paramètres de la tab des symboles
tab correspond à la table des symboles analysées
elle renvoie le nombre de variables copiées si tous ce passe bien et -1 sinon */

int ajout_params(List_args * params, Tab_symb tab, int pos){

  int i;

  variable * var1;

  i = 0;

  if(pos >= tab.nb_fonc || pos < 0){

    printf(" Erreur Vous cherchez une fonction qui n'est pas présente dans la table des symboles \n");

    return -1;

  }

  /* on copie d'abord les infos concernant la fonction elle-même : type de retour, ident*/


  var1 = &(tab.tab_fonc[pos][FONCTION]);

  if(deep_copy_var_tabf(params, *var1) == -1) {

        printf("Erreur : échec de la copie de la fonction, aucun emplacement disponible 4444 \n");
        return -1;
  }

  /* on copie ensuite les paramètres de la fonction*/
  else{

    /* à chaque fois qu'on trouve un paramètre on avance*/

    for(var1 = &(tab.tab_fonc[pos][ARGS]) ; var1 != NULL && var1->used == 2 ; var1 = var1->suivant) {

      if(deep_copy_var_tabf(params, *var1) == -1){

        printf("Erreur : échec lors de la copie des arguments de la fonction, aucun emplacement disponible \n");
        return -1;
      }

      i++;

    }

  }

  /*printf(" on a trouvé %d paramètres \n" ,i);*/
  /* on renvoie le nombre de paramètres trouvés */
  return i;
}

/* fonction qui gère l'ajout des variables utilisées lors d'un appel de fonction à un tableau de taille MAX_ARGS
pos correspond à l'emplacement de la fonction appelante dans la tab des symboles
args correspond à la structure qui enregistrera les infos des variables utilisées lors de l'appel.
tab correspond à la table des symboles analysées
var correspond à l'identificateur de la variable à copier
ligne correspond à la ligne où a été appelé l'argument
elle renvoie 1 si la copie s'est bien faite.
-1 si on a trouvé la variable mais qu'on manquait d'espace mémoire pour la copier
0 si la variable n'était pas présente pour cette fonction ni en global. */

int ajout_args(List_args * args, Tab_symb tab, int pos, char * nom_var, int ligne){
  int code;

  /* variable qui sert à faire de la recherche */

  variable * var1;

  /* variable créé au cas où le user a entré un nom de variable faux*/
  variable var2;


  code = hashcode(nom_var);
   /*printf("passage dans ajout_args pour la variable : %s  et pos vaut : %d \n" ,nom_var,pos);
   printf(" args est de taille : %d \n", args->used);*/

  /* on vérifie que le numéro de fonction existe*/
  if(pos >= tab.nb_fonc || pos < 0){

    printf(" Erreur Vous cherchez une fonction qui n'est pas présente dans la table des symboles \n");

    return -1;

  }
 

  else{

      /* à chaque fois qu'on trouve une variable à cet emplacement, on avance tant que son nom n'est pas le bon. Si c'est le bon nom, on s'arrête et on copie ses infos */

      /* on commence par chercher aux emplacements associés aux variables de la fonction */

      for(var1 = &(tab.tab_fonc[pos][code]) ; var1 != NULL && var1->used == 2 && strcmp(var1->nom, nom_var) != 0 ; var1 = var1->suivant) {

      }
      /* cas où on a trouvé l'ident parmi les variables de la fonction : on lance une copie */

      if(var1 != NULL && strcmp(var1->nom, nom_var) == 0) {

        /*printf("%s est une var locale \n", nom_var);
        printf(" et nous sommes a la ligne %d \n",ligne);*/

        /*printf("%s est une variable locale \n", nom_var);
        printf("ses infos : \n");*/

        /* échec de copie*/
        if(deep_copy_var_tabf(args, *var1) == -1) {

            printf("Erreur : échec de la copie, aucun emplacement disponible 5555 \n");

            return -1;

        }

        

        /* réussite de copie*/
        else {

          args->tab[args->used-1].line = ligne;

          return 1;

        }
      }

      /* on a pas trouvé l'ident parmi les noms de variable locale, on le cherche parmi les paramètres */


      /* on cherche dans l'emplacement associé aux paramètres de la fonction en position "pos" */

      for(var1 = &(tab.tab_fonc[pos][ARGS]) ; var1 != NULL && var1->used == 2 && strcmp(var1->nom, nom_var) != 0 ; var1 = var1->suivant) {

      }


      /* cas où on a trouvé l'ident parmi les paramètres de la fonction : on lance une copie */

      if(var1 != NULL && strcmp(var1->nom, nom_var) == 0) {

        printf("%s est un paramètre \n", nom_var);
        
        /* échec de copie*/

        if(deep_copy_var_tabf(args, *var1) == -1) {

            printf("Erreur : échec de la copie, aucun emplacement disponible 888 \n");

            return -1;

        }

        /* réussite de copie*/

        else {

          return 1;

        }

      }

      /* on a pas trouvé l'ident parmi les noms des paramètres ni des varaibles locale, on le cherche parmi les variables globales */


      /* on cherche dans l'emplacement associé aux variables globales */

      for(var1 = &(tab.tab_fonc[GLOBALE][code]) ; var1 != NULL && var1->used == 2 && strcmp(var1->nom, nom_var) != 0 ; var1 = var1->suivant) {

      }


      /* cas où on a trouvé l'ident parmi les variables globales du fichier : on lance une copie */

      if(var1 != NULL && strcmp(var1->nom, nom_var) == 0) {

        printf("%s est une globale \n", nom_var);
        
        /* échec de copie*/

        if(deep_copy_var_tabf(args, *var1) == -1) {

            printf("Erreur : échec de la copie, aucun emplacement disponible 999 \n");

            return -1;

        }

        /* réussite de copie*/

        else {

          return 1;

        }

      }


  }
  /* cas où la variable n'a pas été trouvée : elle a été inventée par l'utilisateur : on l'averti en créant une variable de type MY_NONE associé à son nom */
  create_variable(nom_var, MY_NONE, ligne, &var2);

    if(deep_copy_var_tabf(args, var2) == -1) {

        printf("Erreur : échec de la copie, aucun emplacement disponible 100000 \n");

            return -1;

    }
    
    /* réussite de création de variable de type NONE_TYPE*/

    return 0;

}

/* initialise une structure du type List_args*/

void init_list_args(List_args * args){

  int i;

  args->max = MAX_ARGS;

  args->used = 0;

  for(i=0;i<args->used;i++){

    args->tab[i].used = 0;
    args->tab[i].line = 0;

    args->tab[i].nom[0] = '\0';

    args->tab[i].type = MY_NONE;
    args->tab[i].cat = MY_NONE;

    /*on pas reconnu de type pour l'instant*/

     args->tab[i].type_rec = -1;
  }

}

/* fonction qui affecte à la variable var le type "type" et le nom "nom" et remplit ses autres champs 

elle renvoie si tout s'est bien passé et 0 sinon */

int create_variable(char * nom, int type, int ligne, variable * var){

  strcpy(var->nom, nom);

  var->cat = MY_VARIABLE;

  var->line = ligne;

  var->type = type;

  var->suivant = NULL;

  var->used = 2;

  var->type_rec = -1;

  return 1;

}

/* affiche le contenu d'une structure du type list_args*/

void show_list_args(List_args args){

  if(args.used == 0){
    printf(" la liste qui contient la fonction appelée et ses arguments ou simplement les éléments constitutifs d'une expression  est vide \n");
    return;
  }
  int i;

  /* on montre les infos de la fonction*/

  printf(" On montre les éléments de la structure de type list_args : \n");

  printf("nom de la fonction/de la variable 0 : %s \n ", args.tab[0].nom );

  printf(" son type de retour est/son type: ");

  show_type(args.tab[0].type);

  printf("\n");

  printf("la ligne où elle est appelée/déclarée : %d \n ", args.tab[0].line );

  /* on montre les infos concernant ses paramètres ou ses arguments*/
  printf(" le nombre d'éléments présent : %d  \n",args.used);
  for(i = 1 ; i<args.used ; i++) {

    printf("nom de la variable : %s \n ", args.tab[i].nom );

    printf(" son type est : ");

    show_type(args.tab[i].type);

     printf("\n");

    printf("la ligne où elle est appelée/déclarée : %d \n ", args.tab[i].line );

  }

}

/* fonction qui renvoie la valeur la plus faible entre deux valeurs*/
int min(int x, int y){
  if(x >= y)
    return y;
  return x;
}

/* fonction qui renvoie la valeur la plus haute entre deux valeurs*/

int max(int x, int y){

  if(x <= y)
    return y;
  return x;

}

/* fonction qui écrit le message d'erreur de s et qui précise la ligne (line)*/
void yyerror2(char * s, int line, int type_error){

  if(type_error == 1){

      fprintf(stderr, "\033[1;31mERROR \033[0m: %s | \033[1mLine : %d\033[1m\n", s, line);

      has_semantical_err = 1;

  }else{

      fprintf(stderr, "\033[1;35mWarning \033[0m: %s | \033[1mLine : %d\033[1m\n", s, line);

  }
	
  printf("\n");

  
}

/* fonction qui va comparer les paramètres attendus pour une fonction et les arguments utilisés par cette fonction lors d'un appel.
Elle renvoie 0 en cas de problème et écrit des msgs d'erreur sur la sortie standard.
Elle renvoie 1 si tout va bien */

int compare_arg_param(List_args args, List_args params){
  /*printf(" le  \n");*/
  /* variable qui indique si les choses se sont biens passées, c'est la val de retour*/

  int success;
  int i;
  int lower;

  success = 1;

  /* on regarde si la fonction, lors de l'appel, a autant de paramètres que ce qu'elle attendait. Si non, on écrit un message d'erreur*/

  if(params.used != args.used) {
      

      success = 0 ;

      {

        char msg[200];
				char buff[100];


        /* on recopie le nom de la fonction appelée*/

        strcpy(msg," ' ");
        strcat(msg,args.tab[0].nom);
        strcat(msg," ' ");


        strcat(msg," expected ");
				sprintf(buff,"%d",params.used-1);

				strcat(msg, buff); 
				strcat(msg, " arguments but  ");
				sprintf(buff,"%d",args.used-1);

				strcat(msg, buff);
				strcat(msg, "  were given.");

        yyerror2(msg, args.tab[0].line, 1);

      }


  }
  
  /* on récupère le plus petit nombre d'éléments utilisé : soit lors de l'appel l'utilisateur a entré moins d'éléments que ce qui était attendus, soit trop, soit exactemnt ce qu'il fallait*/

  lower = min(params.used, args.used);

  /* ici on test les types entrés lors de l'appel*/

  for(i =1; i < lower ;i++) {

            /* le type utilisé est différent du type attendus à cet emplacement de la fonction : on écrit un msg d'erreur*/

            if(params.tab[i].type != args.tab[i].type) {

                /* donne le type attendu (expected = ex) pour l'argument et le type donné (give) lors de l'appel*/

                char type_ex[10];
                char type_give[10];
                /* numéro de l'argument*/
                char num[100];

                char msg[200];

                /* on enregistre sous forme de chaine de caractère le type donné par le user et le type attendu en réalité*/

                type_to_char(args.tab[i].type, type_give);
                type_to_char(params.tab[i].type, type_ex);
                
                /*on écrit le message d'erreur*/
                strcpy(msg," expected ");
                strcat(msg, type_ex); 
                strcat(msg, " for argument ");
                /* on indique le numéro de l'argument*/
                sprintf(num, "%d", i);
                strcat(msg, num);
                /*on copie précisément le nom de l'argument*/
                strcat(msg, " '  ");
                strcat(msg, args.tab[i].nom);
                strcat(msg, "  ' ");
                strcat(msg, " but ");
                strcat(msg, type_give);
                strcat(msg, "  was given.");



                if(params.tab[i].type == MY_CHAR && args.tab[i].type == MY_INT){
                    yyerror2(msg, args.tab[i].line, 0);

                }else if(!(params.tab[i].type == MY_INT && args.tab[i].type == MY_CHAR)){

                    yyerror2(msg, args.tab[i].line, 1);
                }
                
                
                /*on met à jour success pour dire qu'il y a eu une erreur*/
                success =0;
            }
            

  }
  

  return success;

}
/* 


vérifie qu'une expression respecte les conventions
node correspond au noeud associé à la première composante de l'expression
curr correspond à la fonction appelante
tab_symb est la tab des symboles
renvoie 0 si il y a un pb, 
1 si tout s'est bien passé.
-1 échec lors d'une copie

*/
int checkExpr(Node *node, Node * curr, Tab_symb tab){

      /* contient la valeur de retour*/
      int ret;
      /* par défaut tout s'est bien passsé*/
      ret = 1;
      /* variable qui contient l'indice de la table des symboles contenant la fonction appelée*/

        int pos;

        variable var1;

        Node *child;

        /* variable qui contient l'indice de la fonction appelante, c'est à dire celle depuis la quelle le user appelle une autre fonction*/

        int pos2;

        /* on récupère la position de la fonction dans laquelle on est actuellement dans la table des symboles */

        pos2 = foncpos(tab, curr->value.val);

        List_args args;
        List_args param;

        init_list_args(&args);    /*Arguments donnés*/
        init_list_args(&param);   /*Paramètres attendus*/


        /*La fonction n'existe pas*/
        if((pos = foncpos(tab, node->value.val)) == -1){

          char msg[200];

          strcpy(msg,"use of an undefined function name : ' ");

          strcat(msg, node->value.val);
          strcat(msg," ' ");

          yyerror2(msg, node->line, 1);
          
        }
        else {   /*La fonction existe*/

            /* tableau qui contient les paramètres d'une fonction*/
            /* on suppose raisonnablement qu'elle aura au maximum 50 paramètres*/

            
            variable * var2;

            

            /* on ajoute d'abord la fonction et ses propriétés à args*/
            var2 = &(tab.tab_fonc[pos][FONCTION]);

            /* si la copie se passe bien, pas d'erreur*/
            if(deep_copy_var_tabf(&args, *var2) == -1) {

                  printf("Erreur : échec de la copie de la fonction, aucun emplacement disponible 222 \n");
                  return -1;
            }

            /* on doit toute fois modifier la ligne d'appel de la fonction car ce n'est pas la même que lors de la déclaration*/
            args.tab[0].line = node->line;


            /*Fonction sans arguments*/
            if(node->firstChild == NULL){

              /* on ajoute les variables qui constituent les paramètres de la fonction en plus de la fonction elle-même */
              if(ajout_params(&param, tab, pos) == -1) {

                  printf(" Echec lors de l'ajout des paramètres de la fonction %s  \n" , node->value.val);

                  return 0;

              }

              /* si le user a donné 0 arguments à la fonction lors de l'appel alors qu'elle en attendait, cela entraine un message d'erreur qui l'avertit
              attention l'argument 1 est la fonction elle-même (elle a tjrs "un argument") */

              if(param.used > 1) {

                  char msg[200];
                  char a[100];

                  strcpy(msg,"0 argument given but ");
                  sprintf(a, "%d", param.used-1);

                  strcat(msg, a);

                  strcat(msg, "  were expected");
 
                  yyerror2(msg, args.tab[0].line, 1);
                  /* on indique qu'il ya eu une erreur*/
                  ret = 0;
              }



            }
            
            else{


                child = node->firstChild->firstChild;

                
                /* ret sert à récupérer la valeur de retour de la fonction */
                int ret;



                /* on ajoute les variables qui constituent les paramètres de la fonction*/
                if(ajout_params(&param, tab, pos) == -1) {

                  printf(" Echec lors de l'ajout des paramètres \n");

                  return 0;

                }


                /* on ajoute les arguments utilisés par le user lors de l'appel dans la structure args*/
                while(child != NULL) {

                    /*L'argument est une variable (x1, x2, y1...) */
                    if(strcmp(StringFromLabel[child->label], "variable : ") == 0 && child->value.val != NULL) {
                      
                      /* on copie les infos sur la variable (type + nom) */
                      
                      /*printf("on copie la variable : %s \n" ,child->value.val);
                      printf(" sa ligne est %d \n", child->line);*/

                      ret = ajout_args(&args, tab, pos2, child->value.val, child->line);

                       if(ret == -1 ) {

                          printf(" Echec lors de l'ajout des arguments car plus de place\n");

                          return 0;

                        }

                        else if(ret == -2){

                          /*printf(" variable %s inconnue \n" ,child->value.val);*/
                        }

                       /* printf("Variable : %s\n", child->value.val);*/

                        /*deep_copy_var_tabf(&args, variable source);*/
                    }



                    /*L'argument est une fonction */
                    if(strcmp(StringFromLabel[child->label], "EXP") == 0 && strcmp(StringFromLabel[child->firstChild->label], "fonction : ") == 0 && child->firstChild->value.val != NULL) {
                      
                      /* on copie les infos sur la variable (type + nom) */
                      
                      /*printf("on copie la variable : %s \n" ,child->value.val);
                      printf(" sa ligne est %d \n", child->line);*/

                      variable var1;

                      var1 = search_fonction(tab , child->firstChild->value.val);

                      /* on ajoute la fonction à la liste des arguments utilisés */


                      deep_copy_var_tabf(&args, var1);


                       /* printf("Variable : %s\n", child->value.val);*/

                        /*deep_copy_var_tabf(&args, variable source);*/
                    }




                    /* Cas des opérateurs 
                    (à finir) */

                    
                    
                    if(strcmp(StringFromLabel[child->label], "operateur : ") == 0 && child->value.val != NULL) {
                      /*permet de voir si il y a eu au nom une incohérence de type pour l'expression (exemple : void +int)*/

                        int type;

                        type = MY_NULL;

                        variable var1;

                        /* on infère un type pour toute l'expression et on le donne à "type"*/
                        
                        auxExpr(child, tab, &type, curr->value.val);


                        create_variable("EXPR", type, child->line, &var1);

                        /* ajout à la liste des arguments à analyser */
                        deep_copy_var_tabf(&args, var1);









                        /* on ajoute la fonction à la liste des arguments utilisés */


                        /*deep_copy_var_tabf(&args, var1);*/
                      }
                      
                      /* soit c'est :

                      -variable
                      -caractère
                      -entier
                      -fonction
                      */

                      #if 0 

                      modèle à supprimer 
                      else if (strcmp(StringFromLabel[node->label], "operateur : ") == 0 ) {              

                              node2 = node->firstChild;

                              node3 = node->nextSibling;

                              /* on lance un appel récursif sur l'arbre   */

                              checkReturnedType(node2, fonction, ret2, ret1, pos, tab_symb);
                              

                             
                              /* on lance un appel récursif sur l'arbre   */

                              checkReturnedType(node3, fonction, ret2, ret1, pos, tab_symb);


                          }
                      #endif


                       /* printf("Variable : %s\n", child->value.val);*/

                        /*deep_copy_var_tabf(&args, variable source);*/
                    




                    /*L'argument est une valeur brute entière (Ex : 19, -5, ...)*/

                    if(strcmp(StringFromLabel[child->label], "valeur : ") == 0){

                        

                        /* on ajoute le nombre aux arguments utilisés en le traitant comme une sorte de variable de type int dont le nom serait sa valeur */

                        char a[100];

                        /* on crée une variable pour enregister les infos de la constante, elle aura pour nom la valeur de la constante*/

                        sprintf(a, "%d", child->value.entier);


                        create_variable(a, MY_INT, child->line, &var1);

                        /* on précise que c'est une constante */

                        var1.cat = MY_CONST;


                        /*printf("Valeur : %d\n", child->value.entier);*/

                        /* on ajoute le nombre aux arguments en tant que variable particulière "constante" */

                        deep_copy_var_tabf(&args, var1);


                    }

                    /*L'argument est une valeur brute caractère (Ex : 'c', 'a', ...)*/

                    if (strcmp(StringFromLabel[child->label], "caractère : ") == 0) {

                      char a[2];

                      /* on crée une variable pour enregister les infos de la constante, elle aura pour nom la valeur de la constante*/

                      a[0] =  child->value.caractere;
                      a[1] = '\0';

                      /* on ajoute le caractère aux arguments utilisés en le traitant comme une sorte de variable de type char dont le nom serait sa valeur */

                      create_variable(a, MY_CHAR, child->line, &var1);

                      /* on précise que c'est une constante */

                      var1.cat = MY_CONST;


                      /* on ajoute le caractère e aux arguments en tant que variable particulière "constante" de type char */

                      deep_copy_var_tabf(&args, var1);


                        /*printf("Caractère : %c\n", child->value.entier);*/


                    }


                    child = child->nextSibling;
                }

            }

            ret = compare_arg_param(args, param);
            /*printf(" appel \n_\n\n");
            show_list_args(args);*/
            /*printf(" prototype \n_\n\n");
            show_list_args(param);*/
           

        }

        /* il faut créer une version de type copie spéciale de variable qui existe que pour les fonctions et qui accepte 2x la même variable
        pb : risque de reproduire le pb d'overflow : à vérifier...
        *   
                -solution :système de numérotation des variables avec un numéro de série pour savoir précisément si on copie la même au même endroit (très bourrin, à éviter qd même)
        */

  return ret;
}



/* 

vérifie qu'une affectation se fait correctement
curr correspond à la fonction appelante
tab_symb correspond à la tab des symboles
node correspond '='
list correspond à la ou les valeurs gauches.
list2 correspond aux valeurs droites qu'on remplit recursivement
pos indique la fonction dans laquelle on est actuellement

*/

int checkAffArbre(Node *node, Node * curr, Tab_symb tab, List_args * list, List_args * list2){

  /*    indique la position de la fonction dans la tab des symboles   */

  int pos;

  /*   noeud qui permet de chercher les frères et les fils d'un ident/une const/opérateur dans l'arbre par une recherche récursive   */

  Node * node2;
  Node * node3;

  /*   variable qui permet de s'assurer qu'on est encore dans le premier appel.
  cela permetttra de savoir dans quel cas on est vraiment en mesure de dire que les appels récursifs sont finis et qu'on peut 
  désormais passer à l'analyse du tableau  */

  int trait1;

  
  
  /* on récupère la position de la fonction appelante (celle dans laquelle on est)*/
  /* normalement pos est tjrs cohérent (différent de -1) */
  if((pos = foncpos(tab , curr->value.val)) == -1){

    printf(" erreur fonction appelante inconnue \n");

    return 0;
  }
  /*cela signifie qu'on est encore dans un appel récursif*/
  trait1 = 0;

  /* pour éviter d'ajouter plusieurs fois la même variable en valeur gauche lors des appels récursifs, on s'assure que celle-ci n'a pas déjà
  été ajoutée (DÉBUT)
  */

  /* on copie la left-value */

  if(list->used <= 0){
    /* cela signifie qu'on est dans le premier appel parmi tous les appels récursifs*/
    trait1 = 1;
    /* on copie ensuite la valeur gauche et ses infos*/

        int res2;

        variable v5;
        int type1;
        type1 = istype(tab, node->value.val, pos);

        create_variable(node->value.val, type1, node->line, &v5);

        /* manque d'espace pour copier la variable : échec malloc
        
        il y a une erreur ici, on ne devrait pas utiliser ajout_args, elle sert pour les arguments de fonctions mais plutôt deepcopyvartab*/
        if( (res2 = deep_copy_var_tab(list, v5)) == -1){

          

          printf(" échec de la copie errreur ! \n");

          return 0;
       }
      /* la variable n'existait pas mais on a quand créé une variable de type nonetype pour ne pas stopper totalement le process. On lance un message d'erreur */
      /* msg d'erreur car la variable n'a jamais été déclarée : sera géré plus tard dans la fonction check_lr_value) donc on ne l'écrit plus ici pour éviter les doublons de msgs d'erreurs 
      
      strcpy(msg,"use of an undefined variable name : ' ");
            
            strcat(msg, list->tab[0].nom);
            strcat(msg," ' ");

            yyerror2(msg, list->tab[0].line);
      */

      else if (res2 == 0){

            /*char msg[200];
            strcpy(msg, " j'entends rien");*/
            /*printf("j'entends rien \n\n \n");*/

    }
  }

  /*(FIN)*/

/* on passe ensuite au traitement des right-values (DEBUT) */

  /* à chaque fois qu'on tomberait sur un élément, il faudrait segmenter en deux : d'une part on chercherait l'opérateur ou une valeur/identificateur suivant qui serait le fils, d'autre part, on chercherait 
l'identficateur/valeur suivante tout court, qui serait le sibling
lorsqu'on tombe sur un ident on se met à chercher seulement son frère qui est en fait le nombre avec lequel il s'applique un opérateur*/
  
  if(node != NULL){


    node2 = node->firstChild;

    node3 = node->nextSibling;

    /* on tombe sur une variable, on la copie */
    
    if (strcmp(StringFromLabel[node->label], "variable : ") == 0 ) {   


        int res3;

        variable v5;
        int type1;
        type1 = istype(tab, node->value.val, pos);

        create_variable(node->value.val, type1, node->line, &v5);


        /* manque d'espace pour copier la variable : échec malloc*/

        if( (res3 =  deep_copy_var_tab(list2, v5)) == -1) {

            printf(" échec de la copie errreur !!! \n");

            return 0;
        }
        
        

      
        /* la variable n'existait pas mais on a quand créé une variable de type nonetype pour ne pas stopper totalement le process. On lance un message d'erreur */
        else if (res3 == 0){

              /* msg d'erreur car la variable n'a jamais été déclarée : sera géré plus tard (dans la fonction check_lr_value) donc on ne l'écrit plus ici pour éviter les doublons de msgs d'erreurs */

              /*char msg[200];
              show_type(list2->tab[list2->used-1].type);
              strcpy(msg,"use of an undefined variable name : ' ");

              strcat(msg, list2->tab[list2->used-1].nom);
              strcat(msg," ' ");

              yyerror2(msg, list2->tab[list2->used-1].line);*/

        }
        
        

        /* on lance un appel récursif sur l'arbre*/

        checkAffArbre(node2, curr, tab, list, list2);
        

        /* on lance un appel récursif sur l'arbre   */

        checkAffArbre(node3, curr, tab, list, list2);



    }
    
    
    /* on tombe sur un opérateur, on fait seulement un appel récursif */

    else if (strcmp(StringFromLabel[node->label], "operateur : ") == 0 ) {              

        node2 = node->firstChild;

        node3 = node->nextSibling;

        /* 
        
        on lance un appel récursif sur l'arbre
        
        */

        checkAffArbre(node2, curr, tab, list, list2);
        

        /* 

        on lance un appel récursif sur l'arbre   
        
        */

        checkAffArbre(node3, curr, tab, list, list2);


    }
    /* cas d'une fonction*/

    else if(strcmp(StringFromLabel[node->label], "fonction : ") == 0 && node->value.val != NULL ){

        /* noeud actuellement traité*/

        Node * curr2;

        curr2 = node;

        /* on vérifie que la fonction en elle-même respecte la forme du langage C
        checkExpr(curr2, curr, tab); -->Ce n'est plus nécessaire, le programme CheckArbre via passe de lui même via checkexpr sur la fonction qui est en right-value.
        */
        
        /* ensuite on ajoute en particulier la fonction à la liste des éléments de l'expression, pour vérifier que son type de retour colle bien aux aattentes.
        Si la fonction n'existe pas alors elle est de type non-type*/

        add_fonclist(curr2, tab, list2);

        return 1;
        
        
      }
      /* cas où on tombe sur un argument, on arrête le parcours*/
      else if(strcmp(StringFromLabel[node->label], "ARGUMENTS") == 0 && node->value.val != NULL ){
        return 1;
        
        
      }


    /* on tombe sur une constante, on crée une variable spéciale pour les constantes et on la copie */

    else {

          variable var1;

          node2 = node->firstChild;

          node3 = node->nextSibling;



          

          /* chaine de caractère constitué à partir de la constante */

          char consta[100];
                        
                      if(strcmp(StringFromLabel[node->label], "valeur : ") == 0){

                            /* le problème est lié au nombre qui sont entre parenthèse il crée des stack smashing detected*/

                            /* on copie dans une chaine de caractère le nom de la constante */
                            
                            sprintf(consta,"%d",node->value.entier);

                            create_variable(consta, MY_INT, node->line, &var1);
                            
                            /* on vérifie qu'il n'y pas d'erreur lors de l'ajout de la constante dans le tableau*/
                            
                            if(deep_copy_var_tab(list2, var1) != 1){

                              printf("erreur lors de la copie d'une constante ");

                              return 0;
                            }
                            
                            

                        }
                        /* remplacer le switch avec show par caractere : et valeur : fait !!*/
                        
                        else if(strcmp(StringFromLabel[node->label],  "caractère : ") == 0){
                              
                              strcpy(consta, &(node->value.caractere));

                              create_variable(consta, MY_CHAR, node->line, &var1);
                              
                              if(deep_copy_var_tab(list2, var1) != 1){

                                printf("erreur lors de la copie d'une constante ");

                                return 0;
                              }
                          }
                        

        }


        checkAffArbre(node2, curr, tab, list, list2);

        /* 
        on lance un appel récursif sur l'arbre sur le frère*/

        checkAffArbre(node3, curr, tab, list, list2);

    }

    /* on passe ensuite au traitement des right-values (FIN) */
  
    if(trait1 == 1){

        /* on lance la fonction d'analyse du tableau car on est dans le premier appel, on sait donc que les traitements récursifs ont été terminés*/
        /*printf(" left value : \n\n\n");


        show_list_expr(*list);


        printf(" \n\n right value : \n\n\n");


        show_list_expr(*list2);*/

        /* On revoie différentes valeures selon si tout s'est bien passé où non*/
        return check_lr_value(*list, *list2);
    
    }
  
  

  /* cas par défaut on est dans un traitement récursif, il n'est donc pas pertinent d'anaylser le tableau*/

  return 1;
}


/* fonction qui ajoute la fonction donnée à list1
node correspond au noeud associé à la première composante de l'expression
curr correspond à la fonction appelante
tab_symb est la tab des symboles
renvoie 0 si il y a un pb (une erreur qui s'affichera aussi en rouge), 
1 si tout s'est bien passé.
-1 échec lors d'une copie

*/

int add_fonclist(Node *node, Tab_symb tab, List_args * list1){
      
      /* variable qui contiendra la fonction appelée (nom + type retour) */

      variable * var2;

      /* variable qui contient l'indice de la fonction appelée dans la table ees symbôles */

      int pos;

        /*La fonction n'existe pas*/
        if((pos = foncpos(tab, node->value.val)) == -1 ){
          /* message d'erreur*/
          char msg[200];

          strcpy(msg,"use of an undefined function name : ' ");

          strcat(msg, node->value.val);
          strcat(msg," ' ");

          yyerror2(msg, node->line, 1);

          /* on crée tout de même une fonction de type de retour undefined*/
          

          return 0;
        }

        /*La fonction existe*/

            /* on ajoute d'abord la fonction et son type de retour à list1*/

            var2 = &(tab.tab_fonc[pos][FONCTION]);
            /* si la copie se passe bien, pas d'erreur*/
            if(deep_copy_var_tab(list1, *var2) == -1) {

                  printf("Erreur : échec de la copie de la fonction, aucun emplacement disponible 333 \n");
                  return -1;
            }

            /* on doit toute fois modifier la ligne d'appel de la fonction car ce n'est pas la même que lors de la déclaration*/

            list1->tab[list1->used-1].line = node->line;

    return 1;
}

/* affiche le contenu d'une right-value/left-value d'une expr*/

void show_list_expr(List_args expr){

  int i;

  if(expr.used == 0){

    printf(" La liste qui contient les éléments de l'expression est vide \n");

  }
  

  /* on montre les infos concernant ses paramètres ou ses arguments*/
  printf(" le nombre d'éléments présent : %d  \n",expr.used);
  for(i = 0 ; i<expr.used ; i++) {

    printf("nom de la variable/fonction : %s \n ", expr.tab[i].nom );

    printf(" son type est : ");

    show_type(expr.tab[i].type);

     printf("\n");

    printf("la ligne où elle est appelée/déclarée : %d \n ", expr.tab[i].line );

  }

}

/* fonction qui dit si oui ou non deux types sont compatibles dans le cas d'une left value et d'une right value
elle renvoie 1 si oui
0 si non
var1 est la valeur gauche
var2 est la valeur droite
*/

int are_compatiblelr(variable var1, variable var2){

  /* cas simple les types sont exactement les mêmes*/
  if(var1.type == var2.type)
    return 1;
  /* la valeur gauche est un nombre et la droite est un caractère : cela fonctionne car un caractère est un nombre*/
  if(var1.type == MY_INT && var2.type == MY_CHAR)
    return 1;

  return 0;
}

/* 

fonction qui vérifie que les valeurs gauches et droites 
d'une expression.
Elle vérifie la compatibilité entre les valeurs gauches et droites.
elle renvoie  1 si tout s'est bien passé.
Elle renvoie 0 si des erreurs liées aux types ont eu lieu.


*/

int check_lr_value(List_args lv, List_args rv){
    
    int ret;
    int i,j;

    /* par défaut tout s'est bien passé*/

    ret = 1;
    
    /* pour chaque valeur droite on regarde*/

    for(i=0; i<rv.used;i++){

      /* on vérifie pour chaque valeur gauche, en principe il n'y en aura qu'une seule pour cet analyseur.
      Mais si on souhaite aller plus loin, avec plusieurs valeurs gauches, ce sera déjà géré*/

        for(j= 0 ; j<lv.used; j++) {

          /* valeur gauche null, on avait déjà écrit un msg d'erreur donc on se contente de mettre à jour la valeur de retour*/

          if(lv.tab[j].type == MY_NONE || lv.tab[j].type ==  MY_NULL){
            ret = 0;
          }


          if(are_compatiblelr(lv.tab[j], rv.tab[i]) == 0){

            /* les types enregistrés sont incompatibles : on lance un msg d'erreur tout erreur*/

            {

              char msg[200];
              char buff[10];
              char buff2[10];

              /* ligne de la variable*/
              char l2[100];


              /* on recopie le nom de la leftvalue qui pose problème et son type */

              strcpy(msg," The left value : '  ");
              strcat(msg,lv.tab[j].nom);
              strcat(msg," ' ");
              strcat(msg," is of type ");
              type_to_char(lv.tab[j].type, buff);
              strcat(msg, buff);

              sprintf(l2,"%d", lv.tab[j].line);

              /*strcat(msg, " | Line : ");
              strcat(msg, l2);*/

              
              

              /* on recopie le nom de la rightvalue qui pose problème et son type */

              strcat(msg,"   but the right value :  '  ");
              
              strcat(msg,rv.tab[i].nom);
              strcat(msg," ' ");
              strcat(msg," is of type  ");

              type_to_char(rv.tab[i].type, buff2);

              strcat(msg, buff2);



              strcat(msg,"  ");



              if(strcmp(buff2, "int") == 0 && strcmp(buff, "char") == 0){

                yyerror2(msg, rv.tab[i].line, 0);

                /* on précise qu'il y a eu au moins une erreur pour la valeur de retour*/

                ret = 1;
              }
              else{
                
                yyerror2(msg, rv.tab[i].line, 1);

                /* on précise qu'il y a eu au moins une erreur pour la valeur de retour*/

                ret = 0;
              }

          }

        }

      }
    }
    
    

    return ret;

}

/* vérifie que le type retourné correspond à celui attendu par la fonction :

lv = corrspond à la fonction appelante avec son type attendu
rv = correspond à l'expression donée par le user

-1 si il y a eu un problème : pas la bonne valeur de retour ou type de valeur de retour qu'on ne voulait pas.

On est obligé de quand même enregistré le résultat car certaines fonctions contiendront un return; alors qu'elles ne renverront rien et d'autres 

n'auront pas de return alors qu'elles sont censées en avoir. On mettra donc à jour le champ de la fonction avec la valeur de retour dans la tab des symboles.

Sinon renvoie le type de retour trouvé et qui correspond à celui attendu : void, int, char...

c'est un doublon de check_lr seulement les messages affichés chagent donc on est obligé d'en faire une autre.
*/

int check_returned_value(List_args lv, List_args rv){

    
    int ret;
    int i,j;

   /* on récupère le type de retour attendu par défaut */
    
    ret = lv.tab[0].type;
    
    
    /* pour chaque valeur droite on regarde*/

    for(i=0; i<rv.used;i++){

        /* on vérifie pour tout le tableau (normalement un seul élément car il contient juste la fonction appelante dont on teste le retour) */

        for(j= 0 ; j<lv.used; j++) {


          /* valeur de retour espérée aucune mais on lui en a donné une, on avait déjà écrit un msg d'erreur donc on se contente de mettre à jour la valeur de retour*/

          if(lv.tab[j].type == MY_NONE || lv.tab[j].type ==  MY_NULL){
            ret = -1;
          }

         

          if(are_compatiblelr(lv.tab[j], rv.tab[i]) == 0){

            /* les types enregistrés sont incompatibles : on lance un msg d'erreur tout erreur*/

            {

              char msg[200];
              char buff[10];
              char buff2[10];

              /* ligne de la variable*/

              char l2[100];


              /* on recopie le nom de la leftvalue qui pose problème et son type */

              strcpy(msg," The return value of '  ");
              strcat(msg,lv.tab[j].nom);
              strcat(msg," ' ");
              strcat(msg," is suppose to be of type ");
              type_to_char(lv.tab[j].type, buff);



              strcat(msg, buff);

              sprintf(l2,"%d", lv.tab[j].line);

              /*strcat(msg, " | Line : ");
              strcat(msg, l2);*/

              
              

              /* on recopie le nom de la rightvalue qui pose problème et son type */

              strcat(msg,"   but you have given a return value  '  ");
              
              strcat(msg,rv.tab[i].nom);
              strcat(msg," ' ");
              strcat(msg,"  which is of type  ");

              type_to_char(rv.tab[i].type, buff2);

              strcat(msg, buff2);



              strcat(msg,"  ");

              /* ligne où est utilisée la right value*/



              if(rv.tab[i].type == MY_INT && lv.tab[i].type == MY_CHAR){

                yyerror2(msg, rv.tab[i].line, 0);

                /* on précise qu'il y a eu au moins une erreur pour la valeur de retour*/

                ret = MY_CHAR;
              }
              else{

                yyerror2(msg, rv.tab[i].line, 1);

                /* on précise qu'il y a eu au moins une erreur pour la valeur de retour*/

                ret = -1;
              }

          }
        }

      }
    }

    /* on a pas reçu de valeur de retour alors qu'on devait en recevoir
    : erreur*/
    if( (lv.tab[0].type != MY_VOID) && rv.used == 0)
      return -1;


    /* On renvoie le type de retour obtenu au final : -1 si c'est une erreur*/
    return ret;


}

/* renvoie 0 si il y a un problème et 1 si tout s'est bien passé : vérifie si les fonctions qui attendaient qqc ont bien eu un type de 
retour.
La vérification de l'adéquation du type avec ce qui est attendu est déjà géré avant*/

int checkReturns2(Tab_symb tab){
  int i;
  /* il faudra gérer le cas en mettant un message avec yyparse2, pour le cas où la variable attendait qqc mais n'a même pas vu le mot return s'afficher
  le cas où elle attendait rien mais où elle a eu un return incohérent est quant à lui déjà géré par une autre fonction*/

  /* variable qui indique si tout s'est bien passé : par défaut tout s'est bien passé */

  int ok;

  ok = 1;

  for(i= 0; i<tab.nb_fonc;i++){

      /* une fonction n'a jamais eu de return présent alors qu'elle en attendait un avec un type précis : on renvoie un msg d'erreur*/

      if(( tab.tab_fonc[i][FONCTION].type_rec == -1) && (tab.tab_fonc[i][FONCTION].type != MY_VOID)   && strcmp(tab.tab_fonc[i][FONCTION].nom, "globale") != 0 ){
        ok = 0;

        {

        char msg[200];
				char buff[100];


        /* on recopie le nom de la fonction appellante */

        strcpy(msg," ' ");
        strcat(msg,tab.tab_fonc[i][FONCTION].nom);
        strcat(msg," ' ");

        /* on ajoute le type de retour attendu*/

        strcat(msg," expected a return value of type : ' ");

        /* on met sous forme de chaine de caractère le type de retour attendu normalement*/
        type_to_char(tab.tab_fonc[i][FONCTION].type, buff);

				strcat(msg, buff); 



				strcat(msg, " '  but nothing or an inaccurate type has been given ");

        /*printf(" indeed we have : %d ")*/

        yyerror2(msg, tab.tab_fonc[i][FONCTION].line, 1);

      }


      }

  }

  return ok;
}









Cases_Values * init_cases_values(){

    Cases_Values *lst = (Cases_Values *) malloc(sizeof(Cases_Values));
    Value *elem = (Value *) malloc(sizeof(Value));

    if (lst == NULL || elem == NULL){
        exit(EXIT_FAILURE);
    }

    lst->premier = NULL;
    lst->taille = 0;

    return lst;
}






void insertion_int(Cases_Values *lst, int elem){

    Value *new_element = (Value *) malloc(sizeof(Value));

    if (lst == NULL || new_element == NULL){
        exit(EXIT_FAILURE);
    }

    new_element->type = MY_INT;
    new_element->value.integer = elem;

    new_element->suivant = lst->premier;
    lst->premier = new_element;
    lst->taille ++;
}



int find_int(Cases_Values *lst, int elem){

    int i = 0;

    if (lst == NULL){
        exit(EXIT_FAILURE);
    }

    Value *tmp = lst->premier;

    while (i < lst->taille){

        printf("-> %d\n", tmp->value.integer);
        
        if(tmp->value.integer == elem){

          return 1;
        }

        tmp = tmp->suivant;

        i++;
    }
    
    return 0;
}






void insertion_char(Cases_Values *lst, char elem){

    Value *new_element = (Value *) malloc(sizeof(Value));

    if (lst == NULL || new_element == NULL){
        exit(EXIT_FAILURE);
    }

    new_element->type = MY_CHAR;
    new_element->value.character = elem;

    new_element->suivant = lst->premier;
    lst->premier = new_element;
    lst->taille ++;
}



int find_char(Cases_Values *lst, char elem){

    int i = 0;

    if (lst == NULL){
        exit(EXIT_FAILURE);
    }

    Value *tmp = lst->premier;

    while (i < lst->taille){
        
        if(tmp->value.character == elem){

          return 1;
        }

        tmp = tmp->suivant;

        i++;
    }
    
    return 0;
}






int aux_switch(Node * tree, Cases_Values * lst, unsigned int * nb_default){

  if(tree == NULL || strcmp(StringFromLabel[tree->label], "CORPSWITCH") == 0){
    return 0;
  }

  
  if(strcmp(StringFromLabel[tree->label], "case") == 0){

    if(tree->nextSibling->show == MY_INT){

      if(find_int(lst, tree->nextSibling->value.entier) == 1){

        yyerror2("There is already a case with this value", tree->nextSibling->line, 1);

      }else{

        insertion_int(lst, tree->nextSibling->value.entier);
      }


        
    }else{
      


      if(find_char(lst, tree->nextSibling->value.caractere) == 1){

        yyerror2("There is already a case with this value", tree->nextSibling->line, 1);

      }else{

        insertion_char(lst, tree->nextSibling->value.caractere);
      }


    }

  }


  if(strcmp(StringFromLabel[tree->label], "default") == 0){

    *nb_default = *nb_default + 1;

    if(*nb_default >= 2){

        yyerror2("Multiple default in the switch, only one is alowed", tree->line, 1);
    }
  }


  for (Node *child = tree->firstChild; child != NULL; child = child->nextSibling) {
    aux_switch(child, lst, nb_default);
  }

  return 0;
}




int checkSwitch(Node * tree){

  unsigned int nb_default;
  Cases_Values * vals_cases;
  

  if(tree == NULL){
    return 0;
  }


   /*On tombe sur un switch*/
   if(tree->firstChild != NULL && strcmp(StringFromLabel[tree->firstChild->label], "switch") == 0){

      nb_default = 0;
      vals_cases = init_cases_values();

      aux_switch(tree, vals_cases, &nb_default);
   }



  for (Node *child = tree->firstChild; child != NULL; child = child->nextSibling) {
    checkSwitch(child);
  }

  
  return 0;
}

















/* 
Cette fonction renvoie une fonction qui est présente dans la table des symboles avec ses informations
si elle n'est pas présente, elle renvoie une "variable vide"
*/
variable search_fonction(Tab_symb tab_symb , char * nom_fonc){

  int i;
  variable var2;

  var2.cat = -1;
  var2.line = -1;
  var2.type = -1;
  var2.nom[0] = '\0';
  var2.type_rec = -1;
  var2.suivant = NULL;

   for(i=0;i<tab_symb.nb_fonc;i++){

      /* cas où le nom de la fonction a été trouvé parmi les noms des fonctions */
      /*si on est sur l'emplacement associé fichier "globale" alors on ignore cet emplacement d'où le i != GLOBALE*/

      if(i != GLOBALE){

      if(strcmp(tab_symb.tab_fonc[i][0].nom, nom_fonc) == 0){
          return tab_symb.tab_fonc[i][0];

      }

      }
   }

   /* la fonction n'a pas été trouvée on renvoie la fonction vide*/

   return var2;
}


/* cette fonction indique si des éléments sont en double 
dans la liste des args qui est tout simplement une liste d'élémnent qui peuvent être des constantes ou des variables ou des fonctions ou les 3 en même temps.
Et si oui, elle écrira un msg d'erreur.

1 = un doublon est présent,
0 = non */

int twin_elem(List_args l1){

  int i;

  int j;

  int ok;

  /* par défaut il n'y a pas de doublon */
  ok = 0;

  /* il y a moins de deux éléments donc il ne peut pas y avoir de doublon*/

  if(l1.used <= 1)
    return 0;

  /* on parcourt l1 et on cherche en comparant chaque élément à ceux qui suivent */
  else{

      for(i =0;i<l1.used;i++){

        /* on commence la comparaison à partir de l'élément qui suit celui qu'on regarde dans le tableau*/

        for(j = i+1 ; j<l1.used;j++){

          /* un élément est présent en deux fois dans le switch : erreur*/

          if( strcmp(l1.tab[i].nom, l1.tab[j].nom) == 0){

                /* on précise qu'il y a au moins un doublon avec le code d'erreur*/

                ok = 1;
                
                /* message d'erreur*/

                {

                  

                  char msg[300];
                  
                  char nb[10];

                  strcpy(msg, "Use of two 'cases' with the same value : ' ") ;

                  /* on l'ajoute au msg d'erreur le nom de la constante */

                  strcat(msg, l1.tab[i].nom);

                  sprintf(nb, "%d" , l1.tab[i].line);

                  strcat(msg, " ' | line : ");

                  /* on ajoute la ligne*/

                  strcat(msg, nb);

                  strcat(msg, " and ");

                  /* on affiche le msg d'erreur*/
                                          
                  yyerror2(msg, l1.tab[j].line,1);
              }


          }

        }

      }


  }


  /* on renvoie si oui ou non on a trouvé un doublon */

  return ok;
}

/*fonction auxililaire qui est utilisée pour analyser le type d'une expression dans
les cas où il y des opérateurs à l'intérieur 
renvoie 1 si la copie d'un type s'est bien faite et 0 sinon.
*/
int auxExpr(Node * node, Tab_symb tab, int * type, char * func_name){


  if(node == NULL || strcmp(StringFromLabel[node->label], "ARGUMENTS") == 0){
    return 0;
  }

  /*Valeur entière de l'expression*/
  if(strcmp(StringFromLabel[node->label], "valeur : ") == 0){
      
      if(*type == MY_NULL){

          *type = MY_INT;

      }else{
          
          if(*type != MY_INT){

            *type = MY_INT;

          }
      }
  }



  /*Caractère*/
  else if(strcmp(StringFromLabel[node->label], "caractère : ") == 0){

      if(*type == MY_NULL){

          *type = MY_CHAR;

      }
  }

  /*Fonctions*/
  else if(strcmp(StringFromLabel[node->label], "fonction : ") == 0){

      int func_type;

      func_type = (search_fonction(tab, node->value.val)).type;

      if(func_type == MY_VOID){

          yyerror2("Void function in arithmetic expression", node->line, 1);

      }else{
          if(*type == MY_NULL){

              *type = func_type;

          }else{
          
              if(*type == MY_CHAR && func_type == MY_INT){

                *type = MY_INT;

            }
        }

      }
  }


  /*Cas des variables*/
  else if(strcmp(StringFromLabel[node->label], "variable : ") == 0){

      int var_type;
      int pos;

      /* on récupère la position de la fonction appelante dans laquelle on est pour connaitre 
      les variables autorisées dans celle-ci*/
      pos = foncpos(tab, func_name);

      /* on récupère le type de la variable utilisée */

      var_type = istype(tab, node->value.val, pos);

      if(*type == MY_NULL){

          *type = var_type;

      }else{
          
          if(*type == MY_CHAR && var_type == MY_INT){

            *type = MY_INT;

          }
      }
  }


  for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
    auxExpr(child, tab, type, func_name);
  }

  return 0;


}
