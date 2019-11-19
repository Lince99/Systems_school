all: clean compile run_server

clean:
	rm -f client server

compile:
	gcc -o client client.c
	gcc -o server server.c

run_server:
	./server 5678

run_client:
	./client localhost 5678 messaggio
