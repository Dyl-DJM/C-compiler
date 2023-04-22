%{
/* tpcas.y */


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

#include "src/tree.h"
#include "src/make_anonymous.h"


void yyerror(char * s);
int yylex();
int yyparse();
extern int lineno;
extern FILE *yyin;
extern Tab_symb tab_symb1;


char * path;

/* noeud temporaire qui contient l'adresse des noeuds qui attendent leurs types qui sera récupéré plus tard*/
Node * tmp_node;

int arbre;
int symtab;

extern int has_semantical_err;




%}

%token TYPE
%token IDENT
%token VOID
%token RETURN
%token WHILE
%token IF
%token OR
%token AND
%token EQ
%token ORDER
%token ADDSUB
%token DIVSTAR
%token NUM
%token CHARACTER
%token ELSE
%token SWITCH
%token CASE
%token DEFAULT
%token BREAK

%union {
	Node * node;
	char * val;	/*identificateurs*/
	int entier;
	char caractere;
}


%type <node> Prog  DeclVars DeclFoncts
Declarateurs DeclFonct Corps EnTeteFonct
Parametres ListExp ListTypVar Arguments
LValue Instr SuiteInstr Exp TB FB F T E M InstrSwitch CorpsSwitch Val_constant

%type <val> IDENT ADDSUB DIVSTAR ORDER EQ TYPE

%type <entier> NUM

%type <caractere> CHARACTER


%%

Prog
	:  DeclVars DeclFoncts {

		$$ = makeNode(PROG, lineno);

		addChild($$, $1);
		addChild($$, $2);
		
		/* pointeur qui sera utile pour savoir la fonction actuellement traité par checkArbre*/
		Node * curr;
		int len;
		

		/* créé des bugs dans cette version donc à corriger remplir_tab($$, &tab_symb1);*/
		init_tab_symb(&tab_symb1);


 		/*Remplit Table des symboles avec les données de l'arbre*/
 		remplir_tab($$, &tab_symb1);


		/* si aucun main n'a été trouvé, on renvoie un code d'erreur*/
		int pos;

		/*	
		récupérer la position :  et ensuite récupérer le type de retour en allant regarder dans la tab des symboles
		*/
		pos = foncpos(tab_symb1 , "main");

		if(pos == -1 ||  (retourne(tab_symb1, "main") != MY_INT)){
			yyerror2("main function with int type return isn't defined \n", -1, 1);
		}
		
		

		/* on remplit curr avec la fonction "globale" en point de départ*/

		curr = makeNode(DECLFONCTS, lineno);
		len = strlen(tab_symb1.tab_fonc[GLOBALE][0].nom);
		curr->value.val = (char *) malloc((len+1)*sizeof(char));
		strcpy(curr->value.val, tab_symb1.tab_fonc[GLOBALE][0].nom);
		curr->categorie = tab_symb1.tab_fonc[GLOBALE][0].cat;
		curr->type = tab_symb1.tab_fonc[GLOBALE][0].type;


		/*Si l'option d'affichage de la table est présente*/
		if(symtab ==  1){

			printf("\n------------------------------------ Table des symboles -------------------------------------\n\n");
			show_tab_symb(tab_symb1);
			printf("\n\n");
		}

		/*Si l'option d'affichage de l'arbre est présente*/
		if(arbre == 1){

			printf("\n------------------------------------ Arbre abstrait -------------------------------------\n\n");
			printTree($$);
		}

		
		/*Verifie les appels de fonction (en vérification)*/
 		checkArbre(curr, $$, &tab_symb1);

 		/*Verifie les retours de fonction (pas fini)*/
 		checkReturns2(tab_symb1);

 		/*Vérifie les switchs*/
 		checkSwitch($$);

		/*Traduction NASM*/
		/* la traduction en assembleur n'est pas complète, donc elle peut causer des segfault
		néanmoins la partie analyse syntaxique et sémantique sont censées fonctionner parfaitement :
		sans segfault et en trouvant toutes les erreurs.
		Si toutefois vous voulez tester la partie assembleur veuillez décommenter ce bout de code.
		Des exemples de code qui fonctionnent en assembleur sont présents dans le dossier : ./test/Fichiers_Compilables
		
		*/
		/*
 		if(yyin == NULL){
		
 			ecriture_fichier($$, NULL, tab_symb1);
 		}else{

			ecriture_fichier($$, path, tab_symb1);
 		}*/
 		

		/*Suppression de l'arbre en mémoire*/
		deleteTree($$);

		/*Libération de la table en mémoire*/
		free_tab_symb(&tab_symb1);

	}
	;

DeclVars
	:  DeclVars TYPE Declarateurs ';' {
		$$ = makeNode(DECLVARS, lineno);
		addChild($$, $1);

		if(strcmp($2, "int") == 0){

			addChild($$, makeNode(Int, lineno));
		}

		if(strcmp($2, "char") == 0){
		
			addChild($$, makeNode(Char,lineno));
		}

		if(tmp_node != NULL){
			add_type_node(tmp_node, $2);

			/* on s'occupe des fils du noeud qui ont le même type que le père*/
			/* il faudrait ajouter ici la partie ou pour chaque frère de tmp_node, on les parcours et on leur donne le type de $2 et aussi la catégorie VARIABLE*/
			if(tmp_node->firstChild != NULL){
				tmp_node =tmp_node->firstChild;
				while(tmp_node != NULL){
					add_type_node(tmp_node, $2);
					tmp_node->categorie = MY_VARIABLE;
					tmp_node =tmp_node->nextSibling;
				}
			}
		}

		

		/* on vide tmp_node*/
		tmp_node = NULL;
		$$->show = 1;

		addChild($$, $3);

	}
	| {
		$$ = NULL;
	}
	;
Declarateurs
	: Declarateurs ',' IDENT {

		Node * n;

		n = makeNode(var, lineno);

		n->value.val = (char *) malloc(sizeof(char) * strlen($3) + 1);
		strcpy(n->value.val, $3);
		n->show = 2;

		$$ = $1;
		addChild($$, n);
	}
	|  IDENT {

		Node * n;

		n = makeNode(var, lineno);

		n->value.val = (char *) malloc(sizeof(char) * strlen($1) + 1);
		strcpy(n->value.val, $1);
		n->show = 2;

		/* l'élément trouvé est une variable*/
		n->categorie = MY_VARIABLE;

		$$ = n;

		/* on remplit le noeud tmp pour pouvoir ajouter par la suite à la variable son type*/
		tmp_node = n;
	}
	;
DeclFoncts
	:  DeclFoncts DeclFonct {
		$$ = makeNode(DECLFONCTS, lineno);
		addChild($$, $1);
		addChild($$, $2);
	}
	|  DeclFonct {
		$$ = makeNode(DECLFONCTS, lineno);
		addChild($$, $1);
	}
	;
DeclFonct
	: EnTeteFonct Corps {
		$$ = $1;
		addChild($$, $2);
	}
	;
EnTeteFonct
	:  TYPE IDENT '(' Parametres ')'  {

		Node * n;

		n = makeNode(ident, lineno);
		n->value.val = (char *) malloc(sizeof(char) * strlen($2) + 1);
		strcpy(n->value.val, $2);
		/*n->type = 2;*/

		n->show = 2;

		/* on précise qu'il s'agit d'une fonction*/
		n->categorie = MY_FUNCTION;

		$$ = n;

		if(strcmp($1, "int") == 0){

			addChild($$, makeNode(Int, lineno));
		}

		else if(strcmp($1, "char") == 0){
			addChild($$, makeNode(Char, lineno));
		}

		addChild($$, $4);

	}
	|  VOID IDENT '(' Parametres ')' {
		Node * n;

		n = makeNode(ident, lineno);

		n->value.val = (char *) malloc(sizeof(char) * strlen($2) + 1);
		strcpy(n->value.val, $2);
		n->show = 2;
		n->categorie = MY_FUNCTION;

		$$ = n;
		addChild($$, makeNode(voide, lineno));
		addChild($$, $4);
	}
	;
Parametres
	: VOID {
		$$ = makeNode(PARAMETRES, lineno);
		addChild($$, makeNode(voide, lineno));
	}
	|  ListTypVar {
		$$ = makeNode(PARAMETRES, lineno);
		addChild($$, $1);
	}
	;
ListTypVar
	:  ListTypVar ',' TYPE IDENT {

		Node * n, * n_two;

		if(strcmp($3, "int") == 0){

			n_two = makeNode(Int, lineno);
		}

		if(strcmp($3, "char") == 0){
		
			n_two = makeNode(Char, lineno);
		}



		n = makeNode(var, lineno);

		/* on ajoute le nom de l'ident à n*/

		n->value.val = (char *) malloc(sizeof(char) * strlen($4) + 1);
		strcpy(n->value.val, $4);

		/* on précise la catégorie*/
		n->categorie = MY_PARAMETRE;

		n->show = 2;

		$$ = $1;

		addChild(n, n_two);
		addSibling($$, n);
	}
	|  TYPE IDENT {

		Node * n, * n_two;

		n = makeNode(var, lineno);

		if(strcmp($1, "int") == 0){

			n_two = makeNode(Int, lineno);
		}

		if(strcmp($1, "char") == 0){
		
			n_two = makeNode(Char, lineno);
		}
		

		n->value.val = (char *) malloc(sizeof(char) * strlen($2) + 1);
		strcpy(n->value.val, $2);

		n->show = 2;
		n->categorie = MY_PARAMETRE;

		$$ = n;

		addChild($$, n_two);
	}
	;
Corps
	: '{' DeclVars SuiteInstr '}' {
		$$ = makeNode(CORPS, lineno);
		addChild($$, $2);
		addChild($$, $3);
	}
	;
SuiteInstr
	:  SuiteInstr Instr {
		$$ = makeNode(SUITEINSTR, lineno);
		addChild($$, $1);
		addChild($$, $2);
	}
	| {
		$$ = NULL;
	}
	;
Instr
	:  LValue '=' Exp ';' {
		$$ = makeNode(affectation, lineno);
		addChild($$, $1);
		addChild($$, $3);
	}
	|  IF '(' Exp ')' Instr {
		$$ = makeNode(If, lineno);
		addChild($$, $3);
		addChild($$, $5);
	}
	|  IF '(' Exp ')' Instr ELSE Instr {
		$$ = makeNode(If, lineno);
		addChild($$, $3);
		addChild($$, $5);
		addChild($$, makeNode(Else, lineno));
		addChild($$, $7);
	}
	|  WHILE '(' Exp ')' Instr {
		$$ = makeNode(While, lineno);
		addChild($$, $3);
		addChild($$, $5);
	}
	|  SWITCH '(' Exp ')' '{' InstrSwitch '}'{
		$$ = makeNode(INSTR, lineno);
		addChild($$, makeNode(Switch, lineno));
		addChild($$, $3);
		addChild($$, $6);
	}
	|  SWITCH '(' Exp ')' '{' Instr InstrSwitch '}'{
		$$ = makeNode(INSTR, lineno);
		addChild($$, makeNode(Switch, lineno));
		addChild($$, $3);
		addChild($$, $6);
		addChild($$, $7);
	}
	|  IDENT '(' Arguments  ')' ';' {

		Node * n;

		n = makeNode(fcnt, lineno);

		n->value.val = (char *) malloc(sizeof(char) * strlen($1) + 1);
		strcpy(n->value.val, $1);
		n->show = 2;

		$$ = n;

		addChild($$, $3);
	}
	|  RETURN Exp ';' {
		$$ = makeNode(Return, lineno);
		addChild($$, $2);
	}
	|  RETURN ';' {
		$$ = makeNode(Return, lineno);
	}
	|  '{' SuiteInstr '}' {
		$$ = $2;
	}
	|  ';' {
		$$ = NULL;
	}
	;

InstrSwitch
	:  CASE Val_constant ':' '{' CorpsSwitch '}' InstrSwitch{
		$$ = makeNode(INSTRSWITCH, lineno);
		addChild($$, makeNode(Case, lineno));
		addChild($$, $2);
		addChild($$, $5);
		addChild($$, $7);
	}
	|  CASE Val_constant ':' CorpsSwitch InstrSwitch{
		$$ = makeNode(INSTRSWITCH, lineno);
		addChild($$, makeNode(Case, lineno));
		addChild($$, $2);
		addChild($$, $4);
		addChild($$, $5);
	}
	|   DEFAULT ':' CorpsSwitch InstrSwitch{
		$$ = makeNode(INSTRSWITCH, lineno);
		addChild($$, makeNode(Default, lineno));
		addChild($$, $3);
		addChild($$, $4);
	}
	|   DEFAULT ':' '{' CorpsSwitch '}' InstrSwitch{
		$$ = makeNode(INSTRSWITCH, lineno);
		addChild($$, makeNode(Default, lineno));
		addChild($$, $4);
		addChild($$, $6);
	}
	|{
		$$ = NULL;
	}
	;

CorpsSwitch
	:  Instr CorpsSwitch {
		$$ = makeNode(CORPSSWITCH, lineno);
		addChild($$, $1);
		addChild($$, $2);
	}
	| BREAK ';' CorpsSwitch {

		$$ = makeNode(INSTRSWITCH, lineno);
		addChild($$, makeNode(Break, lineno));
		addChild($$, $3);
	}
	| {
		$$ = NULL;
	}
	;


Exp
	:  Exp OR TB {
		$$ = makeNode(or, lineno);
		addChild($$, $1);
		addChild($$, $3);
	}
	|  TB {
		$$ = $1;
	}
	;
TB
	:  TB AND FB {
		$$ = makeNode(and, lineno);
		addChild($$, $1);
		addChild($$, $3);
	}
	|  FB {
		$$ = $1;
	}
	;
FB
	:  FB EQ M {

		Node * n;

		n = makeNode(order, lineno);
		n->value.val = $2;

		n->show = 2;

		$$ = n;

		addChild($$, $1);
		addChild($$, $3);
	}
	|  M {
		$$ = $1;
	}
	;
M
	:  M ORDER E {

		Node * n;

		n = makeNode(order, lineno);
		n->value.val = $2;
		n->show = 2;

		$$ = n;

		addChild($$, $1);
		addChild($$, $3);
	}
	|  E {
		$$ = $1;
	}
	;
E
	:  E ADDSUB T {

		Node * n;

		n = makeNode(operateur, lineno);
		n->value.val = $2;

		n->show = 2;

		$$ = n;

		addChild($$, $1);
		addChild($$, $3);
	}
	|  T {
		$$ = $1;
	}
	;
T
	:  T DIVSTAR F {
		Node * n;

		n = makeNode(operateur,lineno);
		n->value.val = $2;
		n->show = 2;

		$$ = n;

		addChild($$, $1);
		addChild($$, $3);
	}
	|  F {
		$$ = $1;
	}
	;
F
	:  ADDSUB F {

		$$ = makeNode(operateur,lineno);
		addChild($$, $2);
	}
	|  '!' F {
		$$ = makeNode(non, lineno);
		addChild($$, $2);
	}
	|  '(' Exp ')' {
		$$ = $2;
	}
	|  NUM {
		Node * n;

		n = makeNode(num, lineno);
		n->value.entier = $1;
		n->show = 0;

		$$ = n;

	}
	|  CHARACTER {

		Node * n;

		n = makeNode(character, lineno);
		n->value.caractere = $1;
		n->show = 1;

		$$ = n;
	}
	|  LValue {
		$$ = $1;
	}
	|  IDENT '(' Arguments  ')' {

		Node * n, * father;

		father = makeNode(EXP, lineno);

		n = makeNode(fcnt, lineno);
		n->value.val = (char *) malloc(sizeof(char) * strlen($1) + 1);

		strcpy(n->value.val, $1);
		n->show = 2;

		n->categorie = MY_FUNCTION;

		$$ = father;

		addChild(n, $3);
		addChild($$, n);

	}
	;
LValue
	:  IDENT{

		Node * n;

		n = makeNode(var, lineno);

		n->value.val = (char *) malloc(sizeof(char) * strlen($1) + 1);
		strcpy(n->value.val, $1);
		n->show = 2;
		$$ = n;
	}
	;
Arguments
	: ListExp {
		$$ = makeNode(ARGUMENTS, lineno);
		addChild($$, $1);
	}
	| {
		$$ = NULL;
	}
	;
ListExp
	:  ListExp ',' Exp {
		$$ = $1;
		addSibling($$, $3);
	}
	|  Exp {
		$$ = $1;
	}
	;































Val_constant
	:  ADDSUB Val_constant {

		$$ = makeNode(operateur,lineno);
		addChild($$, $2);
	}
	|  NUM {
		Node * n;

		n = makeNode(num, lineno);
		n->value.entier = $1;
		n->show = 0;

		$$ = n;

	}
	|  CHARACTER {

		Node * n;

		n = makeNode(character, lineno);
		n->value.caractere = $1;
		n->show = 1;

		$$ = n;
	};




%%


void afficheDesc(){
	printf("\n------------------------------------ Utilisation -------------------------------------\n\n");

	printf("Il y a deux manières d'utiliser le programme on peut lancer la commande : ./tpcc [FICHIER]    => Lance l'analyseur sur le fichier donné\n");
	printf("On peut sinon y ajouter des options : \n\n   --tree (ou -t) => Affiche l'arbre\n   --help (ou -h) => Permet d'arriver sur cette section\n   --symtabs (ou -s) => Permet l'affichage de la table des symboles\n");
	printf("\nLors du lancement avec options on execute alors : ./tpcc [OPTIONS] [FICHIER]\n");
	printf("\nDes erreurs sont signifiées si : Le fichier est inexistant, plusieurs fichiers sont donnés, des options sont écrites après la mention du fichier, ou des options inexistantes sont données\n");
	printf("\nEnfin, si aucun fichier n'est donné sur la ligne de commande, c'est la sortie standard qui est analysée : ./tpcc [OPTIONS] => Analyse de l'entrée standard\n\n");
}





void yyerror(char * s){
	fprintf(stderr, "\033[1;31mERROR \033[0m: %s | \033[1mLine : %d\033[1m\n", s, lineno);
}





int ligne_commande (int argc, char *argv[], int *hflag, int *tflag, int *sflag){

    int c, val;

    opterr = 0;


    if(argc > 5){
        printf("Erreur sur la ligne de commande\n");
        return -1;
    }


    while ((c = getopt (argc, argv, "hst-")) != -1){

        if(argc < optind){

            continue;
        }

        if(optind == 1){
            val = optind;
        }else{
            val = optind - 1;
        }

        if(strcmp(argv[val], "-s") == 0 || strcmp(argv[val], "--symtabs") == 0){

            *sflag = 1;
            continue;
        }
        else if(strcmp(argv[val], "-t") == 0 || strcmp(argv[val], "--tree") == 0){

            *tflag = 1;
            continue;
        }
        else if(strcmp(argv[val], "-h") == 0 || strcmp(argv[val], "--help") == 0){

            *hflag = 1;
            continue;
        }

        fprintf(stderr, "L'option : %s n'existe pas + afficher manuel\n", argv[val]);
        return -1;
    }


    if (argc - optind > 1){
        fprintf(stderr, "Erreur sur la ligne de commande\n");
        return -1;

    }else if(argc - optind == 1){

        path = argv[optind];

    }else if(argc - optind == 0){

        path = NULL;
    }

    return 0;
}





int main(int argc, char * argv[]){

    int hflag = 0;
    int tflag = 0;
    int sflag = 0;

    arbre = 0;
    symtab = 0;


    if(ligne_commande(argc, argv, &hflag, &tflag, &sflag) == -1){
        return 3;	/*Erreur sur la ligne de commande*/
    }

    if(hflag){
        afficheDesc();
        return 0;
    }

    if(tflag){
        arbre = 1;
    }

    if(sflag){
        symtab = 1;
    }


    if(path == NULL){
        yyin = stdin;

    }else{
        yyin = fopen(path, "r");

        if(yyin == NULL){
        	fprintf(stderr, "Erreur de fichier\n");
        	return 3;
        }
    }


    /*On lance l'analyse*/
    if(yyparse() == 1){
	return 1;	/*Erreur syntaxique dans le fichier*/

    }else{

	if(has_semantical_err == 1){
		return 2;	/*Erreur sémantique dans le fichier*/
	}
    }


    return 0;	/*Aucune erreur dans le fichier*/
}





