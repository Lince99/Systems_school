/*
 * Basso Nicola
 * 5^AI
 * 20/11/2019
 */
 
/*
 * 
 * Scrivere un programma in C che generi dieci processi 
 * ed attenda il loro termine.
 * Per ogni processo che termina stamperà il codice di terminazione. 
 * Ogni processo generato, che svolge il compito del processo figlio 
 * sarà numerato da 1 a 10.
 * Dopo una breve attesa (circa 50 ms) ogni figlio 
 * stamperà un messaggio di presentazione, 
 * contenete l'indice del figlio. 
 * Dopo altri 500 ms terminerà dando come 
 * codice di terminazione 100 + l'indice dell'istanza.
 * 
 * 	Per fare un ritardo breve in maniera semplice possiamo usare la 
 *    funzione usleep (int microsecondi);. 
 *    Come parametro indicheremo il numero di microsecondi 
 *    di ritardo che vogliamo fare.
 * 
 * 	Per attendere la terminazione di un figlio, 
 *    si può utilizzare la funzione wait (int* status);. 
 *    Nella variabile intera status, 
 *    il cui indirizzo verrà passato alla funzione, 
 *    verranno inserite una serie di informazioni 
 *    su come il programma è stato terminato.
 * 
 * 	Per conoscere il codice di terminazione 
 *    potremo usare la macro WEXITSTATUS(status).
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define DEFAULT_N_PROC 10

void print_proc_info(int id) {
	
	fprintf(stdout, "Son Index: %d\n", id);
	fflush(stdout);
}

int main(int argc, char **argv)
{
	int n_proc = 0;
	int n_wait = 0;
	int i = 0;
	pid_t* pid_arr = NULL;
	
	//ottiene il numero di processi da fare
	if(argc > 0)
		n_proc = atoi(argv[1]);
	else
		n_proc = DEFAULT_N_PROC;
	pid_arr = (pid_t*) malloc(sizeof(pid_t)*n_proc);
	if(pid_arr == NULL)
		exit()
	
	//esegue i fork
	for(i= 0; i < n_proc; i++) {
		pid = fork();
		//operazioni del figlio
		if(pid == 0) {
            exit(0);
        }
        //operazioni del padre
        else if(pid > 0 && i == nProc-1) {
            //waitpid(pid, NULL, 0);
            wait(NULL);
        }
        //errore
        else if(pid < 0){
            fprintf(stderr, "Fork error on cycle %d!\n", i);
            fflush(stderr);
            exit();
        }
		
	}
	//il padre aspetta che l'ultimo processo termini
    waitpid(pid, NULL, 0);
	
	
	return 0;
}

