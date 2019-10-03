/*
 * Basso Nicola
 * aka Lince99
 */
/*
 * this library contains functions that manage and check input from stdin
 */

#ifndef INPUT_CHECK_H
#define INPUT_CHECK_H

#include <stdio.h> //printf
#include <stdlib.h> //atoi, malloc
#include <string.h> //strlen
#include <limits.h> //INT_MAX
#include "colors.h" //printf colors

//max number of char per string
#ifndef MAX_CHAR
    #define MAX_CHAR 64
#endif

//signatures
void getInt(int* x);
void getLimitInt(int* x, int min, int max);
void getFloat(float *x);
int getChar(char *x);
int checkNumber(char* str, size_t dim);
int getString(char** str);



/*
 * procedure that request and control the user input from stdin
 * using getString() function (defined in signatures sector).
 * The param requires the & operand to get the address of the variable x
 */
void getInt(int* x) {
    char* str = NULL; /* the user input will be saved here */
    register int strDim = 0; /* length of the user input with fast access */
    register int valid = 0; /* flag that can only be 0 = not valid, 1 = valid */

    //re-request the user input until it's a number
    do {
        strDim = getString(&str);
        //check if it's a number (only digits, max 1 comma)
        valid = checkNumber(str, strDim);
        if(!valid)
            printf(ANSI_RED "Invalid number!" ANSI_RESET "\n");
        //if it is, convert the string into integer
        else
            *x = atoi(str);
    } while(!valid);

    free(str);
}

/*
 * procedure that control if the number inserted by user
 * is in range of limits min and max passed by argument
 */
void getLimitInt(int* x, int min, int max) {

    //re-request the number until it's in range
    do {
        getInt(x);
        if(*x < min || *x > max)
            printf(ANSI_RED "Invalid number!"
                   ANSI_YELLOW " (It has to be from %d to %d)"
                   ANSI_RESET "\n", min, max);
    } while(*x < min || *x > max);

}


/*
 * procedure that request and control the user input from stdin
 * using getString() function (defined in signatures sector).
 * The parameter requires the & operand to get the address of the variable x
 */
void getFloat(float* x) {
    char* str = NULL; /* the user input will be saved here */
    register int strDim = 0; /* length of the user input with fast access */
    register int valid = 0; /* flag that can only be 0 = not valid, 1 = valid */

    //re-request the user input until it's a number
    do {
        strDim = getString(&str);
        //check if it's a number (only digits, max 1 comma)
        valid = checkNumber(str, strDim);
        if(!valid)
            printf(ANSI_RED "Invalid number!" ANSI_RESET "\n");
        //if it is, convert the string into integer
        else
            *x = strtod(str, NULL);
    } while(!valid);

    free(str);
}

/*
 * function that require the address of the char to save.
 * It takes the first stdin char wrote by user, ignoring all next chars.
 * Also It returns the integer value of the char
 */
int getChar(char* x) {
    char* str = NULL; /* the user input will be saved here */
    register int strDim = 0; /* length of the user input with fast access */
    register int valid = 0; /* flag that can only be 0 = not valid, 1 = valid */
    int digit = 0; /* conversion of char to integer following ascii table */

    //re-request the user input until it's a char
    do {
        strDim = getString(&str);
        if(strDim <= 0)
            valid = 0;
        //takes the first char of the input
        else {
            *x = str[0];
            valid = 1;
        }
    } while(!valid);
    free(str);
    //covert char to int
    digit = (int)*x;
    if(digit >= 48 && digit <= 57)
        digit -= 48;

    return digit;
}

/*
 * function that check if the string str contains only digits
 * and maximum 1 comma, then return 1 if it's valid or 0 if not
 */
int checkNumber(char* str, size_t dim) {
    register unsigned int i = 0; /* general counter */
    register unsigned int nDot = 0; /* accept only 1 dot for decimals */

    //scan chars one by one
    for(i = 0; i < dim-1; i++) {
        //convert commas in dots for floating point numbers
        if(str[i] == ',')
            str[i] = '.';
        //if the current char isn't a number, check if it's a dot
        if(str[i] < 47 || str[i] > 57) {
            //count how many dots is in the string
            if(str[i] == '.')
                nDot++;
            //if the current char isn't number or dot, return false
            else
                return 0;
            //if there are many dots, return false
            if(nDot > 1)
                return 0;
        }
    }

    //if the number is ok return true
    return 1;
}

/*
 * function that request an user input from stdin and check it,
 * than if it's valid, it stores the string in the arg array
 * passed with & operand
 * return -1 if there are some errors
 */
int getString(char** str) {
    unsigned int lung = 0; /* length of the inserted string */

    //try to pre-alloc the string for avoding seg faults
    if( !(*str = (char*) malloc(sizeof(char)*MAX_CHAR)) ) {
        printf(ANSI_RED "Error on allocating string!"
               ANSI_RESET "\n");
        *str = NULL;
        return -1;
    }
    //control the string, if it isn't ok, re-ask the input from stdin
    do {
        printf(ANSI_GREEN "-->\t" ANSI_RESET);
        *str = fgets(*str, MAX_CHAR, stdin);
    	//if the user sended only a return character, the string isn't valid
        lung = strlen(*str);
        //replace the return char with string-terminating char
        if (lung > 1 && (*(*str+lung-1) == '\n'))
            *(*str+lung-1) = '\0';
        //re-ask the user input if the string is void or NULL
        if(*str == NULL || lung == 1)
            printf(ANSI_RED "Invalid string! Re-insert it"
                   ANSI_RESET "\n");
    } while(*str == NULL || lung == 1);

    //return the length of the valid string
    return lung;
}

#endif //INPUT_CHECK_H
