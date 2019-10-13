#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readfile(char* filename) {
	FILE* fp = NULL;
	char* str = NULL;
	int c = 0;
	int pos = 0;

	//open file
    fp = fopen(filename, "r");
    if(fp == NULL) {
        fprintf(stderr, "Error on opening %s file!\n", filename);
        return NULL;
    }
	while((c=fgetc(fp)) != EOF) {
		if(str == NULL)
            str = (char*) malloc(sizeof(char));
        else
            str = (char*) realloc(str, sizeof(char)*(pos+1));
        str[pos] = c;
		pos++;
	}
	fclose(fp);

	return str;
}

char* readstdin() {
	char* str = NULL;
	int c = 0;
	int pos = 0;

	while((c=fgetc(stdin)) != EOF) {
		if(str == NULL)
            str = (char*) malloc(sizeof(char));
        else
            str = (char*) realloc(str, sizeof(char)*(pos+1));
        str[pos] = c;
		pos++;
	}

	return str;
}

void printfile(char* filename, char* content) {
	FILE* fp;

	//open file
    fp = fopen(filename, "w+");
    if(fp == NULL) {
        fprintf(stderr, "Error on opening %s file!\n", filename);
        return;
    }
	fprintf(fp, "%s", content);

	fclose(fp);
}

void printout(char* content) {
	fprintf(stdout, "%s", content);
}

int main(int argc, char** argv) {
	char* str = NULL;
	int i = 0;
	int printflag = 0;
	int outname = 0;

	//check for arg contents
    if(argc < 1) {
        fprintf(stderr, "Error on argc parsing! argc < 1!\n");
        return -1;
    }
    //no arguments = STDIN reading, output to STDOUT
    if(argc == 1) {
        str = readstdin();
    }
	else {
		for(i = 1; i < argc; i++) {
            printf("%d : %s\n", i, argv[i]);
            if(strcmp(argv[i], "-i") == 0) {
				printf("Read from file input\n");
				str = readfile(argv[i+1]);
			}
			if(strcmp(argv[i], "-o") == 0) {
				printf("Write to file output\n");
				printflag = 1;
				outname = i+1;
			}
        }
		if(printflag) {
			printf("Writing...\n");
			printfile(argv[outname], str);
		}
		else {
			printf("String content:\n");
			printout(str);
		}
	}


	return 0;
}
