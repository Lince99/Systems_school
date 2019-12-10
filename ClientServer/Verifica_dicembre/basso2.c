/*
 * Basso Nicola
 * 5^AI
 * 10/12/2019
 */
/*
 * Realizzare in C un piccolo client che dato come parametro da riga di comando
 * un indirizzo ip effettui una connessione in porta 22 all'host indicato.
 *
 * Se presente nell'host indicato un servizio ssh
 * questo di solito risponde con una stringa del tipo:
 * SSH-2.0-OpenSSH_6.7p1 Debian-3
 * SSH-1.99-Cisco-1.25
 * SSH-1.99-3Com OS-5.20
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>

#define DEFAULT_PORT "22"
#define MAX_BUFFER_LEN 256

int main(int argc, char** argv) {
	struct addrinfo hints;
	struct addrinfo* result;
	int server_socketfd, server_address;
	int con_ret = 0;
	int n_read = 0;
	char* ip = NULL;
	char* port = DEFAULT_PORT;
	char buffer[MAX_BUFFER_LEN];

	if(argc == 1) {
		fprintf(stdout, "Usage: %s IP [port]\n", argv[0]);
		exit(EXIT_SUCCESS);
	}
	//ottiene l'ip da parametro
	if(argc > 1)
		ip = argv[2];
	if(argc > 2)
		port = argv[3];
	//crea il socket per connettersi al server (TCP)
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;
	//trasforma l'ip da stringa a struttura indirizzo di rete
	server_address = getaddrinfo(ip, port, &hints, &result);
	if(server_address != 0) {
		fprintf(stderr, "FAILURE on getaddrinfo() wrong IP!\n");
		exit(EXIT_FAILURE);
	}
	server_socketfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if(server_socketfd < 0) {
		fprintf(stderr, "FAILURE on socket()!\n");
		exit(EXIT_FAILURE);
	}
	//si connette al server
	con_ret = connect(server_socketfd, result->ai_addr, result->ai_addrlen);
	if(con_ret < 0) {
		fprintf(stderr, "FAILURE on connect()!\n");
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(result);
	//stampa il messaggio ricevuto dal server
	n_read = read(server_socketfd, buffer, MAX_BUFFER_LEN);
	if(n_read <= 0)
		fprintf(stdout, "WARNING! Nothing received form server %s on port %s\n", ip, port);
	else
		fprintf(stdout, "Received: %s\n", buffer);

	return 0;
}
