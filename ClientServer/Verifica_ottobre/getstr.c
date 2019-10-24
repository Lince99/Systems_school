/*
 * Basso Nicola 5^AI
 * 24/10/2019
 * Esercizio 2
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	char* str = NULL;
	int c = 0;
	int pos = 0;

	//ottiene la stringa da stdin finchè non trova EOF
	while((c=fgetc(stdin))!=EOF) {
		if(str == NULL)
			str = (char*) malloc(sizeof(char));
		else
			str = (char*) realloc((void*)str, sizeof(char)*pos);
		str[pos] = c;
		pos++;
	}
	//stampa stringa ricevuta se ha ricevuto il messaggio
	if(str == NULL) {
		fprintf(stderr, "Stringa NON ricevuta!\n");
		return 1;
	}
	//stampa localmente Stringa ricevuta
	fprintf(stderr, "Stringa ricevuta\n");
	fprintf(stdout, "RICEVUTO: %s\n", str);

	return 0;
}
