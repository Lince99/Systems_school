/*
 * Libreria di debug
 * 
 * va_arg serve a gestire i parametri
 * https://www.tutorialspoint.com/c_standard_library/c_macro_va_arg.htm
 * https://stackoverflow.com/questions/4339412/how-to-use-va-args-inside-a-c-function-instead-of-macro
 */

#ifndef BIGGIDY_BUGGIDY_H

#include <stdio.h>

#define CRITICAL 5
#define ERROR 4
#define WARNING 3
#define NOTICE 2
#define INFO 1

//coda per la modifica temporanea del livello di errore
typedef struct err_queue err_q;

struct err_queue {
	int level;
	err_q* next;
};


err_q* db_q_HEAD = NULL;
err_q* db_q = NULL;
int default_level = 4;

/*
 * Nothing (0)
 * Default (5, 4)
 * Verbose (5, 4, 3, 2)
 * All (5, 4, 3, 2, 1)
 */


/*
 * Must call before use
 */
void init_queue(int value) {
	
	

}

err_q* init_node(int lvl) {
	err_q* node = NULL;
	
	node = (err_q*) malloc(sizeof(err_q));
	if(node == NULL)
		exit(1);
	node->level = value;
	node->db_q = NULL;
	
	return node;
}

void printdblevel(FILE* stream) {
	fprintf(stream, "Current debug level: %d\n", db_q->level);
}

void printfdb(...) {
	fprintf(stdout, "COLOR" ...);
}

void setlevel(int lvl) {
	
}

void pushlevel() {
	
}

int poplevel() {
	
}

int restore() {
	
}

#endif
