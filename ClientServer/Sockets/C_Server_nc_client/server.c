/*
 * Basso Nicola
 * 5^AI
 * Start: 29/10/2019
 */
/*
 * Creare un server UDP che riceve un carattere
 * in minuscolo e lo trasforma in maiuscolo,
 * poi lo restituisce al client
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char** argv) {
    int server_port = 0;
    //indirizzo del server
    struct sockaddr_in server_address;

    if(argc <= 1) {
        fprintf(stdout, "Usage: %s PORT\n", argv[0]);
        return 1;
    }
    server_port = atoi(argv[1]);
    //creazione socket
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    //bind
    //listen
    //print
    //close

    return 0;
}
