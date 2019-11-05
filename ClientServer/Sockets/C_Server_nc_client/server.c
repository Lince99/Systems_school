/*
 * Basso Nicola
 * 5^AI
 * Start: 29/10/2019
 */
/*
 * Creare un server TCP che riceve un carattere
 * in minuscolo e lo trasforma in maiuscolo,
 * poi lo restituisce al client
 * https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm
 * https://stackoverflow.com/questions/24194961/how-do-i-use-setsockoptso-reuseaddr#24194999
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char** argv) {
    int server_port = 0;
    int socketfd, client_socketfd;
    int client_len = 0;
    int n = 0;
    char buffer[256];
    struct sockaddr_in server, client;

    //porta del server come argomento
    if(argc <= 1) {
        fprintf(stderr, "Usage: %s PORT\n", argv[0]);
        return 1;
    }
    server_port = atoi(argv[1]);
    if(server_port <= 1023 || server_port >= 65535) {
        fprintf(stderr, "PORT OUT OF RANGE!\n");
        return 1;
    }

    //creazione socket
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(server_port);
    
    //gestisce il TIME-WAIT
    int enable = 1;
	if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
		error("setsockopt(SO_REUSEADDR) failed");
    //bind
    if(bind(socketfd, (struct sockaddr*) &server,
            (socklen_t)sizeof(server)) < 0) {
        fprintf(stderr, "BIND ERROR!\n");
        return 2;
    }
    //listen
    listen(socketfd, 10);
    //gestisce le connessioni dei client
    client_len = sizeof(client);
    if((client_socketfd = accept(socketfd,
                                (struct sockaddr*)&client,
                                &client_len)) < 0) {
        fprintf(stderr, "ACCEPT ERROR!\n");
        return 3;
    }

    //communicate
    bzero(buffer, 256);
    //read
    if((n = read(client_socketfd, buffer, 255)) < 0) {
        fprintf(stderr, "READ ERROR!\n");
        return 4;
    }
    fprintf(stdout, "Received: %s\n", buffer);
    //write
    if((n = write(client_socketfd, "Server received your message, ty and bye",
                strlen("Server received your message, ty and bye"))) < 0) {
        fprintf(stderr, "READ ERROR!\n");
        return 4;
    }

    //close
    close(client_socketfd);

    return 0;
}
