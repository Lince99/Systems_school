/*
 * Libreria di debug
 * 
 * 
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
	
	db_q_HEAD = (err_q*) malloc(sizeof(err_q));
	if(db_q_HEAD == NULL)
		exit(1);
	db_q_HEAD->level = value;
	db_q_HEAD->db_q = NULL;
 
}

void printdblevel(FILE* stream) {
	fprintf(stream, "Current debug level: %d\n", db_q->level);
}

void printfdb()

void setlevel(int lvl) {

}

void pushlevel() {
	
}

int poplevel() {
	
}

int restore() {
	
}

#endif
