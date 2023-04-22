/* tree.h */

#ifndef __TREE__
#define __TREE__

static const char *StringFromLabel[] = {
  "PROG",
  "DECLVARS",
  "DECLFONCTS",
  "DECLARATEURS",
  "DECLFONCT",
  "CORPS",
  "ENTETEFONCT",
  "PARAMETRES",
  "LIST_TYP_VAR",
  "SUITEINSTR",
  "INSTR",
  "LVALUE",
  "ARGUMENTS",
  "LISTEXP",
  "EXP",
  "tb",
  "fb",
  "f",
  "t",
  "e",
  "m",
  "INSTRSWITCH",
  "CORPSWITCH",
  "==",
  "int",
  "char",
  "!=",
  "<",
  ">",
  ">=",
  "<=",
  "+",
  "-",
  "*",
  "/",
  "%",
  "switch",
  "non",
  "and",
  "eq",
  "comparateur : ",
  "operateur : ",
  "or",
  "else",
  "while",
  "return",
  "if",
  "=",
  ";",
  "void",
  "identificateur : ",
  "valeur : ",
  "caractère : ",
  "type : ",
  "*",
  ",",
  "{",
  "}",
  "(",
  ")",
  ":",
  "break",
  "case",
  "default", 
  "fonction : ", 
  "variable : "
  /* list all other node labels, if any */
  /* The list must coincide with the label_t enum in tree.h */
  /* To avoid listing them twice, see https://stackoverflow.com/a/10966395 */
};

typedef enum {
  PROG,
  DECLVARS,
  DECLFONCTS,
  DECLARATEURS,
  DECLFONCT,
  CORPS,
  ENTETEFONCT,
  PARAMETRES,
  LIST_TYP_VAR,
  SUITEINSTR,
  INSTR,
  LVALUE,
  ARGUMENTS,
  LISTEXP,
  EXP,
  TB,
  FB,
  F,
  T,
  E,
  M,
  INSTRSWITCH,
  CORPSSWITCH,
  double_eq,
  Int,
  Char,
  no_eq,
  lt,
  gt,
  gt_eq,
  lt_eq,
  add,
  sub,
  star,
  Div,
  mod,
  Switch,
  non,
  and,
  eq,
  order,
  operateur,
  or,
  Else,
  While,
  Return,
  If,
  affectation,
  point_virgule,
  voide,
  ident,
  num,
  character,
  type,
  divstar,
  virgule,
  acc_ouvrante,
  acc_fermante,
  par_ouvrante,
  par_fermante,
  deux_points,
  Break,
  Case,
  Default, 
  fcnt, 
  var
  /* list all other node labels, if any */
  /* The list must coincide with the string array in tree.c */
  /* To avoid listing them twice, see https://stackoverflow.com/a/10966395 */
} label_t;












#define NB_FONC_INIT 25
#define MAX_TYPE_NAME 100
#define BLOC 2
#include <string.h>
/* on autorise mille variables pour permettre au hashcode d'être sur une vaste étendue. En réalité cela servira
surtout à disperser les valeurs, les emplacements ne seront pas réellement utilisés*/
#define NB_VAR 4096
#define BUFFISIZE_INIT 10
#define MAX_ARGS 50

/*début des champs associés à la fonction, ses arguments, aux variables de la fonction*/
/* il faudrait corriger le code pour que ARGS soit en 1 et VARIABLES SOIT EN 2*/
#define ARGS 1
#define VARIABLES 2
#define FONCTION 0

/* 

Les 4 premières cases du tableau sont réservées aux fonctions de la librairies standard.
GLOBALES correspond à l'emplacement où sont situées les variables globales

*/
#define GLOBALE 4
/* line définie arbitrairement comme étant la ligne où a été définie une fonction importée (getchar, getint, etc...)*/
#define LINE_IMPORT 0



typedef struct Value Value;



struct Value {

  struct Value *suivant;

  int type;

  union {

      char character;
      int integer;

  } value;

};



typedef struct Cases_Values Cases_Values;

struct Cases_Values{

  Value * premier;

  int taille;
  
};






typedef struct Node {
  label_t label;

  struct Node *firstChild, *nextSibling;

  int line;

  int type;
  
  /* indique s'il s'agit d'une variable ou d'une fonction*/
  int categorie;
  /* indique le champ qu'il faut afficher dans showtree*/
  int show;


  union {

        char * val;
        int entier;
        char caractere;

  }value;

} Node;




/* type qui permet d'indiquer le type d'une fonction ou d'une variable par un énum*/
enum my_type{

  MY_INT,
  MY_CHAR,
  MY_NULL,
  MY_VOID,
  MY_NONE

};

/* type qui permet d'indiquer si on est dans le cas d'une variable, d'une fonction ou d'un fichier par un énum en ce qui concerne la tab des symboles */
enum type_ident{

  MY_FUNCTION,
  MY_VARIABLE,
  MY_PARAMETRE,
  MY_FILE,
  MY_CONST
  
};

typedef struct Variable{

  /* type de la variable*/
  /* les types des variables sont des my_types */
  int type;
   /* nom de la variable*/
   /* on limite les noms des variables raisonnablement à 100 caractères*/
  char nom[100];


  /* indique si l'emplacement est utilisé*/
  /* (POUR une fonction) 2 signifie que l'emplacement est totalement utilisé, 1 signifie que seul le type de la fonction a été ajouté, et 0 signifie que rien a été ajouté */
  /* mais normalement il faut ajouter le type et le nom de la fonction en même temps*/


   /* (POUR une variable) 2 signifie que l'emplacement est totalement utilisé, 1 signifie que seul le nom de la variable a été ajouté, et 0 signifie que rien a été ajouté */
   /* à noter que dans le cas d'un argument vide, on considérera que l'argument n'est pas à ajouter et que l'emplacement n'est pas à remplir : l'absence d'argument n'estp pas un argument*/
  int used;
  /* catégorie précise s'il s'agit d'une fonction ou d'une variable*/
  int cat;

  /* indique si un type de retour a été reçu : -1 signifie non et le reste veut dire oui.
  si la fonction attendait un type retour mais qu'elle n'a rien reçu, on le fera signalé grâce à ce champ.
  si elle n'attendait rien mais qu'elle a reàu qqc : ce champ n'est pas utile car la fonction check_return gère déjà ce cas.
  */
  int type_rec;

  /* suivant de la variable*/
  struct Variable * suivant;

  /* champ indiquant où se trouve la variable au niveau du fichier C*/
  int line;

   /* adresse de stockage pour nasm, elle va de 8 en 8 peu importe le type choisi */

  int adresse;




}variable;


typedef struct Tab_symbole{
  /* compte le nombre de fonction enregistrée dans la table des symboles.
    on donne tjrs à nb_fonc le nombre de fonction que l'on a avant l'ajout de la fonction.
    Par exemple si la table des symboles contient 1 fonction, sa valeur sera de un, ce qui parait logique, seulement on donnera la valeur 1 juste avant l'ajout de la fonction dans la table 
    et pas après*/
  int nb_fonc;
  /* indique le nombre de fonction acceptable au maximum*/
  int max;
  /* enregistre les variables des fonctions, les arguments et les noms des fonctions*/
  /* la première case [x][0] ,avec x un numéro de case quelconque, correspond à la fonction et son type de retour, la deuxèime case [x][2] est une liste chainée qui contient les 
  arguments et les types des arguments de la fonction , le reste [x][3,4,...,n] correspondent aux variables dans la fonction*/
  /* à noter que dans le cas d'un argument vide (VOID), on considérera que l'argument n'est pas à ajouter et que l'emplacement n'est pas à remplir : l'absence d'argument n'est pas un argument*/
  variable **tab_fonc;
  /* cet emplacement contient le hashcode nom d'une variable qu'on essaye d'ajouter.
  Comme on ne connait pas directement son type on met donc l'emplacement où la mettre, on la met
  dans attempt provisoirement*/
  int attempt;
  /* champ qui vérifie qu'un main est présent
  0 : signifie non
  1 signifie oui*/
  int main;
 

}Tab_symb;

typedef struct listtype{
  /* donne le nombre d'emplacements utilisés par le tableau*/
  int used;
  /* donne le nombre d'emplacement maximum utilisables*/
  int max;
  /* tableau qui contient les types des variables : un type est associé à son code qui est un int*/
  int tab[MAX_TYPE_NAME];
} List_type;

typedef struct listarg{
  /* donne le nombre d'emplacements utilisés par le tableau*/
  int used;
  /* donne le nombre d'emplacement maximum utilisables*/
  int max;
  /* tableau qui contient  la fonction utilisée + ses args et ses paramètres + */
  variable tab[MAX_TYPE_NAME];
} List_args;


/* fonction qui initialise un tableau de type list_type*/

void init_list_type(List_type * tab);

/* ajoute un le type de variable parmi les types des arguments attendus*/

void add_typevar(Tab_symb tab2,  List_type * tab1, char *nom);


/* affiche le type d'une variable*/
void show_type(int type);
/* initialise la table des symboles*/
/* elle renvoie 1 si tout s'est bien passé et 0 sinon*/

int init_tab_symb(Tab_symb *tab_symb);

/* réinitialise le tableau de char d'une variable de type Variable*/

void init_tab_attempt(Tab_symb * tab);

/* fonction de réallocation*/
/* renvoie 1 si tout s'est bien passé et 0 sinon*/

int realloue_tab_symb(Tab_symb *tab_symb);

/* libère un élément de type variable*/

void free_suivant_var(variable * var1);

/* libère la table des symboles*/

void free_tab_symb(Tab_symb *tab_symb);

/* ajoute une fonction à la table des symboles*/
/* renvoie 0 en cas de problème*/

int add_fonc(Tab_symb *tab , char *nom_var, int type_var, int ligne);

/* ajoute une variable à la table des symboles*/

int add_var(Tab_symb *tab_symb, char * nom_var, int type_var, int ligne);

/* fonction d'ajout général qui va appeler soit la fonction d'ajout d'une fonction soit celle d'une variable suivant les cas
renvoie 0 en cas de problème
renvoie 1 si tout s'est bien passé*/
/* il faut d'abord ajoutr le nom de la fonction (rec. variable) puis lors d'un second appel le type*/

int add_varfonc(Tab_symb *tab_symb, char * nom_var, int type_var, int ligne);

/* affiche une liste chainée de variable*/
void show_liste_var(variable var, int code);

/* affiche la table des symboles*/
void show_tab_symb(Tab_symb tab_symb);

/* 

vérifie qu'une affectation se fait correctement
curr correspond à la fonction appelante
tab_symb correspond à la tab des symboles
node correspond '='
list correspond à la ou les valeurs gauches.
list2 correspond aux valeurs droites qu'on remplit recursivement

*/

int checkAffArbre(Node *node, Node * curr, Tab_symb tab, List_args * list, List_args * list2);

/* vérifie qu'une expression respecte les conventions
node correspond au noeud associé à la première composante de l'expression
curr correspond à la fonction appelante
tab_symb est la tab des symboles
*/
int checkExpr(Node *node, Node * curr, Tab_symb tab_symb);

/*Fonction qui evalue le type d'une expression (variable, appel fonction, valeurs brutes)*/
int expression_type(Node * node, Tab_symb tab, int pos);

/* crée un noeud avec le label "label" et précise la ligne ou a été trouvée l'élément (line)*/
Node *makeNode(label_t label, int line);
void addSibling(Node *node, Node *sibling);
void addChild(Node *parent, Node *child);
void deleteTree(Node*node);
void printTree(Node *node);
















/* ajoute un numéro de type (int/char) à un noeud sous forme d'entier en fonction du type donné en argument*/
void add_type_node(Node * node, char * type);

/* ajoute un paramètre de la fonction et son type à la table des symboles*/
/* elle renvoie 1 si tout s'est bien passé, et 0 sinon*/
int add_param(Tab_symb *tab_symb, char * nom_var, int type_var, int ligne);


/* 
Cette fonction indique si cette fonction a déjà été ajoutée pour cette table des symboles
renvoie 1 si la fonction est déjà dedans sous forme de fonction.
2 si elle est déjà là sous forme de variable globale.
et renvoie 0 sinon*/
int isherefonc(Tab_symb tab_symb , char * nom_fonc);

/* trouve dans la tab des symboles tab, le type des arguments de la fonction choisie (nom) en respectant leur ordre d'apparition et les ajoute à tablist*/
int find_types_fonc(Tab_symb tab, char * nom,  List_type * tablist);

/* 
Cette fonction indique l'emplacement d'une fonction dans la tab des symboles.
Elle renvoie -1 si la fonction n'a pas été trouvée. */
int foncpos(Tab_symb tab_symb , char * nom_fonc);

/* 
Cette fonction indique si cette variable a déjà été ajouté pour cette fonction
renvoie 1 si la variable est déjà dedans
et renvoie 0 sinon*/
int ishere(Tab_symb tab_symb , char * nom_var, int pos);

/* fonction qui compare les types des arguments utilisés pour un appel de fonction et les paramètres attendues par celle-ci.
pb contient l'emplacement qui a posé problème c'est à dire l'emplacement des variables avec le mauvais type*/
int compare_arg_appel(List_type tablist, List_type tablist2, int * pb);

/* enregistre le type "type" sous forme de chaine de caractère dans tab*/
void type_to_char(int type, char tab[10]);


/* 
Cette fonction indique si une variable a déjà été ajouté parmi les variables globales
renvoie 1 si la variable est déjà dedans
et renvoie 0 sinon*/
int ishereglobale(Tab_symb tab_symb , char * nom_var);

/* Ajoute toutes les fonctions prédéfinies demandées : getchar(), ...*/
int add_usual_fonct(Tab_symb * tab_symb);

/*fonction qui vérifie que la fonction a un main et si oui s'il est au bon endroit
elle renvoie 1 si le main est bien situé.
 elle renvoie 0 si il n'y a pas de main 
elle renvoie -1 si le main est mal situé*/
int has_main(Tab_symb tab);

/* fonction qui renvoie le type de retour d'une fonction
la tab1 est la table dans laquelle on cherche la fonction et nom_fonc et la fonction que l'on cherche
on renvoie 0 si la fonction n'existe pas, -1 si son type de retour est void, et sinon on renvoie le type de retour la fonction*/
int retourne(Tab_symb tab1, char * nom_fonc);


/* affiche la catégorie d'un identificateur*/
void show_categorie(int categorie);



/*
remplit la tab des symboles avec les éléments de l'arbre node*/
void remplir_tab(Node *node, Tab_symb * tab);

/* affiche les liens entre les noeuds (siblings, fils,....)*/
/*void printLink(Node *node) ;*/

/* Analyse l'arbre, pour vérifier que les actions réalisées dans le fichier .c sont valides
curr correspond à la current fonction, c'est à dire la fonction (appelante) dans laquelle le user est actuellement
node correspond au noeud sur lequel on est acutellement dans l'arbre 
tab est la tab des symboles

curr correspond au noeud dans lequel le user est actuellement.
Node correspond au noeud de la fonction appelante.


 */
int checkArbre(Node * curr, Node * node, Tab_symb * tab);


int checkReturns(Node * node, Tab_symb tab);


/* trouve dans la tab des symboles tab, le type des arguments de la fonction choisie (nom) en respectant leur ordre d'apparition et les ajoute à tablist*/
int find_types_fonc(Tab_symb tab, char * nom,  List_type * tablist);

/* 
Cette fonction indique l'emplacement d'une fonction dans la tab des symboles.
Elle renvoie -1 si la fonction n'a pas été trouvée. */
int foncpos(Tab_symb tab_symb , char * nom_fonc);

/* fonction qui compare les types des arguments utilisés pour un appel de fonction et les paramètres attendues par celle-ci.
pb contient l'emplacement qui a posé problème c'est à dire l'emplacement des variables avec le mauvais type*/
int compare_arg_appel(List_type tablist, List_type tablist2, int * pb);

/* enregistre le type "type" sous forme de chaine de caractère dans tab*/
void type_to_char(int type, char tab[10]);

/* fonction qui renvoie le type de retour d'une fonction
la tab1 est la table dans laquelle on cherche la fonction et nom_fonc et la fonction que l'on cherche
on renvoie 0 si la fonction n'existe pas, -1 si son type de retour est void, et sinon on renvoie le type de retour la fonction*/
int retourne(Tab_symb tab1, char * nom_fonc);

/* compte le nombre d'argument d'une fonction dans la table des symboles
 pos correspond à l'emplacement de la fonction dans la tab des symboles 
 elle renfoie le nombre d'arguments si tout se passe bien, et 0 en cas d'erreur.*/

int nb_param(Tab_symb tab, int pos);

/* fonction qui gère l'ajout des paramètres que contient une fonction à un tableau de taille MAX_ARGS
pos correspond à l'emplacement de la fonction dans la tab des symboles
param correspond  à la structure qui enregistrera les infos des variables la tab des symboles
tab correspond à la table des symboles analysées
elle renvoie le nombre de variables copiées si tous ce passe bien et -1 sinon */

int ajout_params(List_args * params, Tab_symb tab, int pos);

/* fonction qui gère la copie profonde d'une variable sauf de son suivant*/

void deep_copy_var(variable * dest, variable source);

/* initialise une structure du type List_args*/
void init_list_args(List_args * args);

int checkExpressions(Node * node, Tab_symb tab);

/* fonction qui gère la copie profonde d'une variable pour un tableau de type Listvar
elle renvoie -1 en cas d'échec de la copie et 1 si tout s'est bien passé */

int deep_copy_var_tab(List_args* dest, variable source);

/* fonction qui gère la copie profonde d'une variable pour un tableau de type Listvar pour le cas particulier d'une fonction :
une copie double d'un variable est possible 
elle renvoie -1 en cas d'échec de la copie et 1 si tout s'est bien passé */

int deep_copy_var_tabf(List_args* dest, variable source);


/* fonction qui gère l'ajout des variables utilisées lors d'un appel de fonction à un tableau de taille MAX_ARGS
pos correspond à l'emplacement de la fonction appelante dans la tab des symboles
args correspond à la structure qui enregistrera les infos des variables utilisées lors de l'appel.
tab correspond à la table des symboles analysées
var correspond à l'identificateur de la variable à copier
ligne correspond à la ligne où a été appelé l'argument
elle renvoie 1 si la copie s'est bien faite.
-1 si on a trouvé la variable mais qu'on manquait d'espace mémoire pour la copier
0 si la variable n'était pas présente pour cette fonction ni en global. */

int ajout_args(List_args * params, Tab_symb tab, int pos, char * var, int ligne);

/* fonction qui affecte à la variable var le type "type" et le nom "nom" et la ligne où elle a été trouvée dans le fichier "ligne" et remplit ses autres champs */
int create_variable(char * nom, int type, int ligne, variable * var);

/* affiche le contenu d'une structure du type list_args
si elle correspond à une fonction et ses arguments */

void show_list_args(List_args args);

/* affiche le contenu d'une right-value/left-value d'une expr*/

void show_list_expr(List_args expr);

/* fonction qui va comparer les paramètres attendus pour une fonction et les arguments utilisés par cette fonction lors d'un appel.
Elle renvoie 0 en cas de problème et écrit des msgs d'erreur sur la sortie standard.
Elle renvoie 1 si tout va bien */

int compare_arg_param(List_args args, List_args params);

/* fonction qui renvoie la valeur la plus faible entre deux valeurs*/
int min(int x, int y);

/* fonction qui écrit le message d'erreur de s et qui précise la ligne (line)*/
void yyerror2(char * s, int line, int type_error);

/* fonction qui renvoie la valeur la plus haute entre deux valeurs*/
int max(int x, int y);


/* fonction qui gère l'ajout des éléments appartenant à une expression
tab correspond à la table des symboles analysées
var correspond à l'identificateur de la variable à copier
ligne correspond à la ligne où a été appelé l'argument
elle renvoie 1 si la copie s'est bien faite.
-1 si on a trouvé la variable mais qu'on manquait d'espace mémoire pour la copier
0 si la variable n'était pas présente pour cette fonction ni en global. */

int ajout_expr(List_args * params, Tab_symb tab, int pos, char * var, int ligne);

/* fonction qui ajoute la fonction donnée à list1
node correspond au noeud associé à la première composante de l'expression qui est la fonction appelante
tab_symb est la tab des symboles
renvoie 0 si il y a un pb (une erreur qui s'affichera aussi en rouge), 
1 si tout s'est bien passé.
-1 échec lors d'une copie

*/

int add_fonclist(Node *node, Tab_symb tab, List_args * list1);

/* fonction qui dit si oui ou non deux types sont compatibles dans le cas d'une left value et d'une right value
elle renvoie 1 si oui
0 si non
*/

int are_compatiblelr(variable var1, variable var2);

/* fonction qui vérifie que les valeurs gauches et droites 
d'une expression.
Elle vérifie la compatibilité entre les valeurs gauches et droites
elle renvoie  1 si tout s'est bien passé.
Elle renvoie 0 si des erreurs liées aux types ont eu lieu
*/
int check_lr_value(List_args lv, List_args rv);

/* vérifie si la variable que l'on souhaite copier n'est pas déjà présente dans dest, cela peut arriver :

1 = elle est déjà là
0 = elle n'est pas là
*/


int var_already_present(List_args* dest, variable source);


/* 
Cette fonction indique le type de la varialbe recherchée
pos correspond à l'emplacement de la fonction depuis laquelle on cherche la variable (on cherhera aussi dans les variables globales)*/
int istype(Tab_symb tab_symb , char * nom_var, int pos);







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


int checkReturnedType(Node * node, Node * fonction, List_args * ret2, List_args * ret1, int pos, Tab_symb tab_symb);




/* vérifie que le type retourné correspond à celui attendu par la fonction :

lv = corrspond à la fonction avec son type attendu
rv = correspond 

on renvoie 0 si il y a eu un problème et 1 si tout s'est bien passé

c'est un doublon de check_lr seulement les messages affichés chagent donc on est obligé d'en faire une autre.
*/


int check_returned_value(List_args lv, List_args rv);

/* renvoie 0 si il y a un problème et 1 si tout s'est bien passé : vérifie si les fonctions qui attendait qqc ont bien eu un type de 
retour.
La vérification de l'adéquation du type avec ce qui est attendu est déjà géré avant*/

int checkReturns2(Tab_symb tab);

/* 
Cette fonction renvoie une variable qui est présente dans la table des symboles avec ses informations
si elle n'est pas présente, elle renvoie une "variable vide"
*/
variable search_variable(Tab_symb tab_symb , char * nom_var, int pos);

/* 
Cette fonction renvoie une fonction qui est présente dans la table des symboles avec ses informations
si elle n'est pas présente, elle renvoie une "variable vide"
*/
variable search_fonction(Tab_symb tab_symb , char * nom_fonc);

/* fonction qui vanalyse une structure de type switch avec tous ses composants :

elle renvoie 0 en cas d'erreur et 1 si tout s'est bien passé

curr = fonction appelante

node = noeud actuellement traité

tab est la tab des symboles

*/

int checkSwitch(Node * tree);

/* cette fonction indique si des éléments sont en double 
dans la liste des args qui est tout simplement une liste d'élémnent qui peuvent être des constantes ou des variables ou des fonctions ou les 3 en même temps*/
int twin_elem(List_args l1);

/*fonction auxililaire qui est utilisée pour analyser le type d'une expression dans
les cas où il y des opérateurs à l'intérieur 
renvoie 1 si la copie d'un type s'est bien faite et 0 sinon.

Func_name est le nom de la fonction appelante.
*/
int auxExpr(Node * node, Tab_symb tab, int * type, char * func_name);

#define FIRSTCHILD(node) node->firstChild
#define SECONDCHILD(node) node->firstChild->nextSibling
#define THIRDCHILD(node) node->firstChild->nextSibling->nextSibling


#endif