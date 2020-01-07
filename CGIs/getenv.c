

#include <stdio.h>

int main(int argc, char **argv, char** env) {
	char* querystring = NULL;

    while (*env) {
        printf("%s\n", *env++);
		if(strcasecmp(*env, "QUERY_STRING"))
	}

    return 0;
}
