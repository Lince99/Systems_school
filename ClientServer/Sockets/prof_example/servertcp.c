#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/times.h>

#include <signal.h>
#include <stdlib.h>

#define SERVER_PORT 1314          // numero di porta del server
#define LINESIZE 80               // dimensione della linea di caratteri
#define SOCKET_ERROR   ((int)-1)  // codice di errore

static void catch_function(int signo) {
    fprintf(stdout, "Interactive attention signal caught.");
}


void CharMaiuscola(int i, int o)
{
	char ch, chMaiu;
	int len, asciiVal;

	while((len = recv(i, &ch, 1, 0)) > 0) //Riceve un carattere
	{
		chMaiu = toupper(ch);
		asciiVal = (unsigned int)ch;
		printf("\n Il carattere ricevuto e' %c con valore ASCII %d", ch, asciiVal);
		printf(" maiuscolo %d \n", (unsigned int)chMaiu);
		send(o, &chMaiu, 1, 0);
		asciiVal = (unsigned int)ch;
		if (asciiVal == 120) break;
	}
}

int main (int argc, char **argv) {

  

  int socketfd, client_len, fd;
  struct sockaddr_in servizio,cliente;   //  record con gli indirizzi
                                         //  del server  e del client

  /* impostazione del transport endpoint */
  printf ("socket()\n");
  if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("chiamata alla system call socket fallita");
    return(1);
  }
  /* indicando INADDR_ANY viene collegato il socket all'indirizzo locale IP     */
  /* dell'interaccia di rete che verr� utilizzata per inoltrare il datagram IP  */
  servizio.sin_family = AF_INET;
  servizio.sin_addr.s_addr = htonl(INADDR_ANY);
  servizio.sin_port = htons(SERVER_PORT);

  /* leghiamo l'indirizzo al transport endpoint */
   printf ("bind()\n");
  if (bind(socketfd, (struct sockaddr *)&servizio, sizeof servizio) == -1)
  {
    perror("chiamata alla system call bind fallita");
    return(2);
  }

  /* poniamo il server in ascolto delle richieste dei client */
  printf ("listen()\n");
  listen(socketfd, 10); //era 1

  /* gestione delle connessioni dei client */
  printf ("accept()\n");
  while (1) {
    client_len = sizeof(cliente);
    if ((fd = accept(socketfd, (struct sockaddr*)&cliente, (socklen_t*) &client_len)) < 0)
    {
      perror("connessione non accettata");
      return(3);
    }

  /* inizio dialogo tra server e client */
  fprintf(stderr, "Aperta connessione col server.\n");  // echo nel client
  send(fd, "Hello al ServerMaiu: trasformo caratteri in mauscolo!\n", 56, 0);
  CharMaiuscola(fd,fd);
  close(fd);
  fprintf(stderr, "Chiusa connessione col server.\n");  // echo nelclient
  }
}






