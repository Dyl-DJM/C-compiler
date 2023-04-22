
#ifndef __MAKEANONYMOUS__
#define __MAKEANONYMOUS__

	#include "tree.h"
	#include <unistd.h>
	#include <sys/types.h>
    #include <sys/wait.h>
	
	int ecriture_fichier(Node * tree, char * path, Tab_symb tab);


#endif
