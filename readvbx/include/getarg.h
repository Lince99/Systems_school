#ifndef GETARG_H
#define GETARG_H

/*
 * read from stdin
 */
char* read_stdin() {
    char* str = NULL;
    int pos = 0;
    char c = 0;
    
    fprintf(stdout, "Waiting for stdin...\n"); //TODO: REMOVE ON RELEASE
    while((c=fgetc(stdin)) != EOF) {
        if(str == NULL)
            str = (char*) malloc(sizeof(c));
        else
            str = (char*) realloc(str, ++pos);
        str[pos] = c;
    }
    //add string terminator
    str = (char*) realloc(str, ++pos);
    str[pos] = '\0';
    
    return str;
}

/*
 * read content from filename
 */
char* read_file(char* filename) {
    char* str = NULL;
    int pos = 0;
    char c = 0;
    FILE* fp = NULL;
    
    //open file
    fp = fopen(filename, "r");
    if(fp == NULL) {
        fprintf(stderr, "Error on opening %s file!", filename);
        return NULL;
    }
    //read file content
    while((c=fgetc(fp)) != EOF) {
        if(str == NULL)
            str = (char*) malloc(sizeof(c));
        else {
            pos++;
            str = (char*) realloc(str, pos);
        }
        str[pos] = c;
    }
    //add string terminator
    str = (char*) realloc(str, ++pos);
    str[pos] = '\0';
    
    return str;
}

//TODO
xml_tree* modify_data_level(xml_tree* doc, int level) {
    return doc;
}

#endif
