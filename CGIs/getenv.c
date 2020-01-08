#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* da catturare:
 * QUERY_STRING
 * REQUEST_METHOD 
 */

void stampaHTML();

int main(int argc, char **argv, char** env) {
	char* querystring = NULL;
    stampaHTML(argv[0]);

    /*while (*env) {
        printf("%s\n", *env++);
		
	}*/
    //if(strcasecmp(*env, "QUERY_STRING", strlen("QUERY_STRING")))

    return 0;
}

void stampaHTML(char* nomeProgramma) {
    fprintf(stdout, "Content-type: text/html\n\n");
    fprintf(stdout, "<!DOCTYPE html>\n\n");
    fflush(stdout);
    fprintf(stdout, "<html><title>CGI form</title><body>");
    fprintf(stdout, "<div><h6>Data di oggi:");
    system("date");
    fprintf(stdout, "</h6></div>");
    //form
    fprintf(stdout, "<div><form action=\"%s\" method=\"get\">", nomeProgramma);
    fprintf(stdout, "<div>");
    fprintf(stdout, "<input type=\"text\" placeholder=\"Nome\" name=\"nome\" value=\"\">");
    fprintf(stdout, "<input type=\"text\" placeholder=\"Cognome\" name=\"cognome\" value=\"\">");
    fprintf(stdout, "</div>");
    //invio
    fprintf(stdout, "<div>");
    fprintf(stdout, "<button type=\"submit\">Invia dati</button>");
    fprintf(stdout, "</div>");

    fprintf(stdout, "</form></div>");
    fprintf(stdout, "</body></html>");
}
