/*
 * Lince99
 */
/*
 * library that provide various functions that elaborate strings
 */

#ifndef STRING_MANAGER_H
#define STRING_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//signatures
int get_pos(char* data, int start, char find);
char* substring(char* str, int start, int end);
char* trim_string(char* str);
char* trim_xml(char* str);



/*
 * funzione che cerca il carattere find
 * nella stringa data a partire da start
 * e ritorna -1 in caso non trovi il carattere
 */
int get_pos(char* data, int start, char find) {
    int lung = 0;

    if(data == NULL)
        return -1;
    lung = (int) strlen(data);
    if(start >= lung)
        return -1;
    for(; start < lung; start++) {
        if(data[start] == find)
            return start;
    }

    return -1;
}

/*
 * funzione che restituisce la stringa estratta dalla posizione start alla end
 */
char* substring(char* str, int start, int end) {
    char* new_s = NULL;
    int i = 0;

    if(start > end || str == NULL ||
       start == end || end > (int) strlen(str))
        return NULL;
    if(start == 0 && end == (int) strlen(str))
        return str;
    new_s = (char*) malloc(sizeof(char)*(end-start+1));
    while(start < end) {
        new_s[i] = str[start];
        ++start;
        ++i;
    }
    new_s[i] = '\0';

    return new_s;
}

/*
 * rimuove dalla stringa gli spazi, tab e newline all'inizio e alla fine
 */
char* trim_string(char* str) {
    int i = 0;
    int start = 0;
    int end = (int) strlen(str);

    if(str == NULL)
        return NULL;
    for(; i < (int) strlen(str); i++) {
        if(str[i] == '\t' || str[i] == ' ' || str[i] == '\n')
            ++start;
        else
            break;
    }
    for(i = (int) strlen(str)-1; i > start; i--) {
        if(str[i] == '\t' || str[i] == ' ' || str[i] == '\n')
            --end;
        else
            break;
    }
    str = substring(str, start, end);

    return str;
}

/*
 * rimuove dalla stringa gli spazi, tab e newline tra i tag
 */
char* trim_xml(char* str) {
    int i = 0;
    int j = 0;
    int out_tag = 0;
    int save = 1;
    char* copy = NULL;

    if(str == NULL || strlen(str) == 0)
        return NULL;
    copy = (char*) calloc(sizeof(char), strlen(str));
    for(i = 0; i < (int) strlen(str); i++) {
        //se sono uscito dal tag allora controllo per gli spazi vuoti
        if(str[i] == '>')
            out_tag = 1;
        //altrimenti salvo normalmente tutti i caratteri
        if(str[i] == '<')
            out_tag = 0;
        //se sono fuori e incontro altri tag/valori li salvo
        if(out_tag) {
            if(str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
                save = 0;
            else
                save = 1;
        }
        //se sono dentro un tag o sono un valore salvo i caratteri
        if(!out_tag || save) {
            copy[j] = str[i];
            j++;
        }
    }
    copy = (char*) realloc(copy, sizeof(char)*(j+1));
    copy[j] = '\0';

    return copy;
}

#endif //STRING_MANAGER_H
