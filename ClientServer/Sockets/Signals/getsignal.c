#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static volatile sig_atomic_t stop = 0;

void signalHandler(int signo) {
	fprintf(stdout, "SIGNAL CATCH\n");
	fflush(stdout);
	exit(signo);
}

int main(int argc, char** argv) {
	struct sigaction act;

	act.sa_handler = signalHandler;
	sigaction(SIGINT, &act, NULL);

	while(!stop) {
		puts("Running...\n");
		sleep(100);
	}

	return EXIT_SUCCESS;
}
