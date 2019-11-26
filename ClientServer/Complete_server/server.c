/*
 * Server WEB in C
 * 
 * 
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <signal.h>


/*
 * gestione del segnale d'uscita, chiude tutte le connessioni e termina
 */
void signalHandler(int signo) {
	fprintf(stderr, "\tClosing webserver...\n");
    fflush(stderr);
    //if(close(sfd) == -1)
	//	exit(EXIT_FAILURE);
    fprintf(stderr, "Bye\n");
    fflush(stderr);
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
	//manage SIGINT signal interrupt
	struct sigaction act;
	act.sa_handler = signalHandler;
	sigaction(SIGINT, &act, NULL);
	
	char buffer[256];
	int server_port = 0;
	struct sockaddr_in server_addr, client_addr;
	int server_socketfd, client_socketfd;
	int client_len = 0;
	pid_t pid;
	
	
	
	//gestione argomento da linea di comando
    if(argc <= 1) {
        fprintf(stderr, "Usage: %s PORT\n", argv[0]);
        return 1;
    }
    //porta del server come argomento
    server_port = atoi(argv[1]);
    if(server_port <= 1023 || server_port >= 65535) {
        fprintf(stderr, "PORT OUT OF RANGE!\n");
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
	
	
	
	//creazione del server in TCP
	server_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_socketfd < 0) {
		fprintf(stderr, "Error on socket()!\n");
		fflush(stderr);
		exit(EXIT_FAILURE);
	}
	//inizializzo la struttura del socket
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(server_port);
    //gestione degli errori collegati al socket già in uso
    int enable = 1;
	if(setsockopt(server_socketfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		fprintf(stderr, "setsockopt(SO_REUSEADDR) failed\n");
		fflush(stderr);
		exit(EXIT_FAILURE);
	}
    
    //bind del server con la porta scelta
    if(bind(server_socketfd, (struct sockaddr*) &server_addr,
            (socklen_t)sizeof(server_addr)) < 0) {
        fprintf(stderr, "BIND ERROR!\n");
        return 2;
    }
    
    //inizia ad ascoltare le richieste dei client
    listen(server_socketfd, 10);
    
    while(1) {
		//accetta la connessione di un client
		client_len = sizeof(client_addr);
		client_socketfd = accept(server_socketfd, (struct sockaddr*)&client_addr, &client_len);
		if(client_socketfd < 0) {
			fprintf(stderr, "accept() error!\n");
			fflush(stderr);
			exit(EXIT_FAILURE);
		}
		//il figlio viene assegnato ad un nuovo processo
		pid = fork();
		if(pid < 0) {
			fprintf(stderr, "fork() error!\n");
			fflush(stderr);
			exit(EXIT_FAILURE);
		}
		//sono nel processo dedicato al client
		if(pid == 0) {
			close(server_socketfd);
			//DO THINGS
			exit(EXIT_SUCCESS);
		}
		else {
			close(client_socketfd);
		}
	}
    
    
	
	return 0;
}

