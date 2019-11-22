/*
 * Basso Nicola
 * 5^AI
 * 20/11/2019
 */

/*
 *
 * Si vuole realizzare un programma in linguaggio C in grado di:
 * Generare due processi padre/figlio in cui:
 * - Il processo padre scrive la sequenza di caratteri [A-Z][a-z] in
 * un file di testo (aperto prima di eseguire la fork) e
 * successivamente chiude e rimuove il file creato
 * - Il processo figlio attende 5 secondi (tramite la funzione “sleep
 * (num_secs)”) e stampa il contenuto del file precedentemente
 * gestito dal processo padre
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define DEFAULT_WAIT 5000

int main(int argc, char **argv) {
	int n_wait = 0;
	int i = 0;
	char c = 0;
	pid_t pid;
	FILE* fp = NULL;
	char* filename = NULL;

	//ottiene il tempo che il figlio deve attendere e il nome del file
	if(argc > 0)
		n_wait = atoi(argv[1]);
	else
		n_wait = DEFAULT_WAIT;
	if(argc > 1)
		filename = argv[2];
	else
		filename = "un_file_di_testo.txt";

	//apre il file in lettura+scrittura
	if((fp = fopen(filename, "w+")) == NULL) {
		fprintf(stderr, "Impossibile aprire il file %s!\n", filename);
		exit(1);
	}

	//crea i due processi
	pid = fork();
	//operazioni del figlio
	if(pid == 0) {
		fprintf(stdout, "Figlio (pid=%d) rimane in attesa...\n", getpid());
		fflush(stdout);
		usleep(n_wait);
		//legge il contenuto del file
		rewind(fp);
		while((c = fgetc(fp))!= EOF)
			fprintf(stdout, "%c", c);
        exit(0);
    }
    //operazioni del padre
    else if(pid > 0) {
		//stampa l'alfabeto nel file
		for(i = 65; i <= 90; i++)
			fprintf(fp, "%c ", (char)i);
		for(i = 97; i <= 122; i++) {
			fprintf(fp, "%c", (char)i);
			if(i < 122)
				fprintf(fp, " ");
		}
    }
    //errore nel fork
    else if(pid < 0){
        fprintf(stderr, "Fork error on cycle %d!\n", i);
        fflush(stderr);
        exit(1);
    }

	//chiude e rimuove il file
	fclose(fp);
	remove(filename);

	return 0;
}
