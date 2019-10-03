/*
 * Basso Nicola
 * aka Lince99
 */
/*
 * library that contains all rules used by Code_styler
 * when something is NULL means that is not defined in the xml, so:
 *   if the rule is an integer it means false or not required
 *   if the rule is a string means it isn't required
 *   if the rule is other is the same as string ones
 */
/*
 * CHAR_RULES:
 * A = only alphabet
 * a = accept alphabet
 * N = only numbers
 * n = accept numbers
 * X = only special chars
 * x = accept special chars
 * L = only lowercase
 * U = only uppercase
 * _ = only underscore
 * s = only spaces
 * t = only tabs, no spaces
 * c = only camelCase, no spaces or _
 * ! = negate the next char rule
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include "colors.h"
#include "xml_tree_struct.h"

#ifndef XML_RULES_H
#define XML_RULES_H

//general structure
typedef struct XMLRULE xmlRule;
//specialized structures
typedef struct XMLRULE_LANGUAGE xmlRule_language;
typedef struct XMLRULE_COMMENT xmlRule_comment;
typedef struct XMLRULE_CODE xmlRule_code;
typedef struct XMLRULE_INDENT xmlRule_indent;
typedef struct XMLRULE_GLOBALVAR xmlRule_globalVar;
typedef struct XMLRULE_FUNCTION xmlRule_function;
typedef struct XMLRULE_BRACKET xmlRule_bracket;
typedef struct XMLRULE_VAR xmlRule_var;
typedef struct XMLRULE_FILE xmlRule_file;
typedef struct XMLRULE_LANGUAGE xmlRule_dir;
typedef struct XML_RULE_DIR xmlRule_source;
typedef struct XML_RULE_LIB xmlRule_lib;
typedef struct XML_RULE_OTHER xmlRule_library;
typedef struct XML_RULE_OTHER xmlRule_other;
//signatures
xmlNode* find_rule(xmlNode* root, char* rule);



struct XMLRULE { //this struct contains all rules
    char* language; //language that use that rules
    char** extensions; //supported extenions
    //code rules
    unsigned short int* code_required; //0 = false, 1 = true
    //comment rules
    unsigned short int* cmt_required; //0 = false, 1 = true
    unsigned short int* cmt_position; //0 = before, 1 = mid, 2 = after
    char* cmt_start; //what charset is used to start a comment
    char* cmt_mid; //what charset is used in the middle of a comment
    char* cmt_end; //what charset is used to end a comment
    //indentation rules
    unsigned short int* ind_required; //0 = false, 1 = true
    char* ind_type; //s = space, t = tab, m = mixed
    unsigned int* ind_count; //number of "type" char used to indent
    unsigned short int* ind_spacing; //space between operators
    unsigned short int* ind_params; //0 = aligned, 1 = only 1 param per line
    //globals rules
    unsigned short int* glo_required; //0 = false, 1 = true
    char* glo_startChar; //follow CHAR_RULES comment
    char* glo_naming; //follow CHAR_RULES comment
    //functions/methods/procedures rules
    unsigned short int* fnc_required; //0 = false, 1 = true
    char* fnc_startChar; //follow CHAR_RULES comment
    char* fnc_naming; //follow CHAR_RULES comment
     //open bracket rules
    unsigned short int* obk_required; //0 = false, 1 = true
    unsigned short int* obk_position;
    //close bracket rules
    unsigned short int* cbk_required; //0 = false, 1 = true
    unsigned short int* cbk_position;
    unsigned short int* var_required; //0 = false, 1 = true
    //variables naming rules
    char* var_startChar; //follow CHAR_RULES comment
    char* var_naming; //follow CHAR_RULES comment
    //source file naming rules
    unsigned short int* src_required; //0 = false, 1 = true
    char* src_startChar; //follow CHAR_RULES comment
    char* src_naming; //follow CHAR_RULES comment
    //directory/folders naming rules
    unsigned short int* dir_required; //0 = false, 1 = true
    char* dir_startChar; //follow CHAR_RULES comment
    char* dir_naming; //follow CHAR_RULES comment
    //executable naming rules
    unsigned short int* exe_required; //0 = false, 1 = true
    char* exe_startChar; //follow CHAR_RULES comment
    char* exe_naming; //follow CHAR_RULES comment
    //library naming rules
    unsigned short int* lib_required; //0 = false, 1 = true
    char* lib_startChar; //follow CHAR_RULES comment
    char* lib_naming; //follow CHAR_RULES comment

    //other rules
    unsigned short int* o_copyright_required; //0 = false, 1 = true
    unsigned short int* o_copyright_per_source; //0 = only in 1 source,
                                                //1 = every source need it
    char* o_encoding; //encoding charset (like "UTF-8", "ASCII", ...)
    char* o_newline_type; //line feed style (GNU/Linux use "LF", ...)
    void* o_user_rule; //use this pointer to add more rules
};

/*struct XMLRULE_LANGUAGE {
    char* language; //language that use that rules
    char** extensions; //supported extenions
    xmlRule_comment* comment; //comment rules
    xmlRule_code* code; //code rules
    xmlRule_file* file; //file naming rules
    xmlRule_other* other; //other user-defined rules
};

struct XMLRULE_COMMENT {
    unsigned short int* required; //0 = false, 1 = true
    unsigned short int* position; //0 = before, 1 = mid, 2 = after
    char* start; //what charset is used to start a comment
    char* mid; //what charset is used in the middle of a comment
    char* end; //what charset is used to end a comment
};

struct XMLRULE_CODE {
    unsigned short int* required; //0 = false, 1 = true
    xmlRule_indent* indentation; //indentation rules
    xmlRule_globalVar* globalVar; //globals rules
    xmlRule_function* function; //functions/methods/procedures rules
    xmlRule_var* var; //variables naming rules
};

struct XMLRULE_INDENT {
    unsigned short int* required; //0 = false, 1 = true
    char* type; //s = space, t = tab, m = mixed
    unsigned int* count; //number of "type" char used to indent
    unsigned short int* spacing; //space between operators
    unsigned short int* params; //0 = aligned, 1 = only 1 param per line
};

struct XMLRULE_GLOBALVAR {
    unsigned short int* required; //0 = false, 1 = true
    char* startChar; //follow CHAR_RULES comment
    char* naming; //follow CHAR_RULES comment
};

struct XMLRULE_FUNCTION {
    unsigned short int* required; //0 = false, 1 = true
    char* startChar; //follow CHAR_RULES comment
    char* naming; //follow CHAR_RULES comment
    xmlRule_bracket* open_bracket; //open bracket position
    xmlRule_bracket* close_bracket; //close bracket position
};

struct XMLRULE_BRACKET {
    unsigned short int* required; //0 = false, 1 = true
    unsigned short int* position; //0 = before, 1 = mid, 2 = after
};

struct XMLRULE_VAR {
    unsigned short int* required; //0 = false, 1 = true
    char* startChar; //follow CHAR_RULES comment
    char* naming; //follow CHAR_RULES comment
};

struct XMLRULE_FILE {
    unsigned short int* required; //0 = false, 1 = true
    xmlRule_dir* directory; //directory/folders naming rules
    xmlRule_source* src; //source file naming rules
    xmlRule_library* lib; //library naming rules
};

struct XML_RULE_DIR {
    unsigned short int* required; //0 = false, 1 = true
    char* startChar; //follow CHAR_RULES comment
    char* naming; //follow CHAR_RULES comment
};

struct XML_RULE_SOURCE {
    unsigned short int* required; //0 = false, 1 = true
    char* startChar; //follow CHAR_RULES comment
    char* naming; //follow CHAR_RULES comment
};

struct XML_RULE_LIB {
    unsigned short int* required; //0 = false, 1 = true
    char* startChar; //follow CHAR_RULES comment
    char* naming; //follow CHAR_RULES comment
};

struct XML_RULE_OTHER {
    unsigned short int* copyright_required; //0 = false, 1 = true
    unsigned short int* copyright_per_source; //0 = only in 1 source,
                                                //1 = every source need it
    char* encoding; //encoding charset (like "UTF-8", "ASCII", ...)
    char* newline_type; //line feed style (GNU/Linux use "LF", ...)
    void* user_rule; //use this pointer to add more rules
};/*

/*
 * function that initialize all rules
 */
xmlRule* init_rule(void) {
    xmlRule* rule = NULL;

    rule = (xmlRule*) malloc(sizeof(xmlRule));
    if(rule == NULL) {
        printf(ANSI_RED "Error on alloc xmlRule!" ANSI_RESET "\n");
        return NULL;
    }
    rule->language = NULL;
    rule->extensions = NULL;
    rule->language = NULL;
    rule->extensions = NULL;
    rule->code_required = NULL;
    rule->cmt_required = NULL;
    rule->cmt_position = NULL;
    rule->cmt_start = NULL;
    rule->cmt_mid = NULL;
    rule->cmt_end = NULL;
    rule->ind_required = NULL;
    rule->ind_type = NULL;
    rule->ind_count = NULL;
    rule->ind_spacing = NULL;
    rule->ind_params = NULL;
    rule->glo_required = NULL;
    rule->glo_startChar = NULL;
    rule->glo_naming = NULL;
    rule->fnc_required = NULL;
    rule->fnc_startChar = NULL;
    rule->fnc_naming = NULL;
    rule->obk_required = NULL;
    rule->obk_position = NULL;
    rule->cbk_required = NULL;
    rule->cbk_position = NULL;
    rule->var_required = NULL;
    rule->var_startChar = NULL;
    rule->var_naming = NULL;
    rule->src_required = NULL;
    rule->src_startChar = NULL;
    rule->src_naming = NULL;
    rule->dir_required = NULL;
    rule->dir_startChar = NULL;
    rule->dir_naming = NULL;
    rule->exe_required = NULL;
    rule->exe_startChar = NULL;
    rule->exe_naming = NULL;
    rule->lib_required = NULL;
    rule->lib_startChar = NULL;
    rule->lib_naming = NULL;
    rule->o_copyright_required = NULL;
    rule->o_copyright_per_source = NULL;
    rule->o_encoding = NULL;
    rule->o_newline_type = NULL;
    rule->o_user_rule = NULL;

    return rule;
}

/*
xmlRule_language* init_xmlRule_language(void) {
    xmlRule_language* rule = NULL;

    rule = (xmlRule_language*) malloc(sizeof(xmlRule_language));
    if(rule == NULL) {
        printf(ANSI_RED "Error on alloc xmlRule_language!" ANSI_RESET "\n");
        return NULL;
    }
    rule->language = NULL;
    rule->extensions = NULL;
    rule->code = NULL;
    rule->file = NULL;
    rule->other = NULL;

    return rule;
}


xmlRule_comment* init_xmlRule_comment(void) {
    xmlRule_comment* rule = NULL;

    rule = (xmlRule_comment*) malloc(sizeof(xmlRule_comment));
    if(rule == NULL) {
        printf(ANSI_RED "Error on alloc xmlRule_language!" ANSI_RESET "\n");
        return NULL;
    }
    rule->required = NULL;
    rule->position = NULL;
    rule->start = NULL;
    rule->mid = NULL;
    rule->end = NULL;

    return rule;
}


xmlRule_code* init_xmlRule_code(void) {
    xmlRule_code* rule = NULL;

    rule = (xmlRule_code*) malloc(sizeof(xmlRule_code));
    if(rule == NULL) {
        printf(ANSI_RED "Error on alloc xmlRule_code!" ANSI_RESET "\n");
        return NULL;
    }
    rule->required = NULL;
    rule->indentation = NULL;
    rule->globalVar = NULL;
    rule->function = NULL;
    rule->var = NULL;

    return rule;
}
*/

#endif //XML_RULES_H
