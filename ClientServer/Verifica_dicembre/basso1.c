/*
 * Basso Nicola
 * 5^AI
 * 10/12/19
 */
/*
 * Realizzare in C un multi-server, in ascolto sulla porta 9002,
 * che ricevuta una stringa la restituisca rovesciata (Es. Ambulanza, aznalubmA)
 * e stampi lato server il numero di caratteri elaborati.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <signal.h>

#define DEFAULT_PORT 9002
#define MAX_BUFFER_LEN 256
#define MAX_LISTEN 10

int server_socketfd = 0;

//gestisce i segnali d'uscita chiudendo tutte le connessioni
void signalHandler(int signo) {
	fprintf(stderr, "\tClosing server...\n");
	fflush(stderr);
	//chiude il socket
	if(close(server_socketfd) < 0) {
		fprintf(stderr, "FAILURE on close() server socket!\n");
		fflush(stderr);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

//funzione che inverte la stringa
char* strrevert(char* str) {
	char* newstr;
	int i = strlen(str);
	int x = 0;

	for(; i >= 0; i--) {
		newstr[x] = str[i];
		x++;
		//se ha finito di leggere la stringa esce
		if(newstr[x] == EOF)
			break;
	}

	return newstr;
}

int main(int argc, char** argv) {
	//gestisce SIGINT
	struct sigaction act;
	act.sa_handler = signalHandler;
	sigaction(SIGINT, &act, NULL);

	int porta = DEFAULT_PORT;
	char buffer[MAX_BUFFER_LEN];
	struct sockaddr_in server_addr, client_addr;
	int client_socketfd;
	int client_len = 0;
	pid_t pid;

	//riceve la porta da parametro (opzionale)
	if(argc > 1)
		porta = atoi(argv[1]);
	if(porta <= 1023 || porta >= 65535) {
		fprintf(stderr, "Wrong port selection! Using default %d...\n", DEFAULT_PORT);
		porta = DEFAULT_PORT;
	}
	//crea il socket
	server_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_socketfd < 0) {
		fprintf(stderr, "FAILURE on socket()!\n");
		exit(EXIT_FAILURE);
	}
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(porta);
	//gestisce l'errore del socket già in ascolto
	int reuse_opt = 0;
	if(setsockopt(server_socketfd, SOL_SOCKET, SO_REUSEADDR, &reuse_opt, sizeof(int)) < 0) {
		fprintf(stderr, "FAILURE on setsockopt() reuse socket option!\n");
		exit(EXIT_FAILURE);
	}
	int bind_ret = 0;
	bind_ret = bind(server_socketfd, (struct sockaddr*) &server_addr, (socklen_t)sizeof(server_addr));
	if(bind_ret < 0) {
		fprintf(stderr, "FAILURE on bind()!\n");
		exit(EXIT_FAILURE);
	}
	//rimane in ascolto
	listen(server_socketfd, MAX_LISTEN);

	//ascolta più client
	while(1) {
		//diventa un multi-server
		usleep(1);
		//si connette al socket del client
		client_len = sizeof(client_addr);
		client_socketfd = accept(server_socketfd, (struct sockaddr*)&client_addr, &client_len);
		if(client_socketfd < 0) {
			fprintf(stderr, "%d - FAILURE on accept()!\n", getpid());
			fflush(stderr);
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if(pid < 0) {
			fprintf(stderr, "%d - FAILURE on fork() creation!\n", getpid());
			fflush(stderr);
			exit(EXIT_FAILURE);
		}
		//esegue la richiesta del client
		if(pid == 0) {
			fprintf(stderr, "INFO server with pid=%d listening...\n", getpid());
			//stampa il numero di caratteri letti
			int recv_len = 0;
			recv_len = recv(server_socketfd, (void*) &buffer, MAX_BUFFER_LEN, 0);
			if(recv_len <= 0) {
				fprintf(stderr, "%d - WARNING on recv()!\n", getpid());
				fflush(stderr);
			}
			fprintf(stderr, "%d - Received string: %s\n", getpid(), buffer);
			fflush(stderr);
			//restituisce la stringa al client invertita
			char* ret_str = strrevert(buffer);
			int ret_str_size = strlen(ret_str);
			send(client_socketfd, ret_str, (size_t) ret_str_size, 0);
			//chiude il socket per questo client
			close(client_socketfd);
			exit(EXIT_SUCCESS);
		}
		else {
			close(server_socketfd);
		}
	}

	return 0;
}
