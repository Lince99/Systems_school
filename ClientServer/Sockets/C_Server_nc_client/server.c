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
    
    //bind
    //listen
    //print
    //close

    return 0;
}
