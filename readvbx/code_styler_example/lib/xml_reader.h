/*
 * Lince99
 */
/*
 * library that provide various function that read, write and manage xml files
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "colors.h"
#include "xml_tree_struct.h"
#include "xml_extract_tags.h"
#include "xml_save_tags.h"
#include "xml_default_rules.h"

#ifndef XML_READER_H
#define XML_READER_H

//signatures
xmlDoc* read_xml(char* file_name, char* mode);
xmlRule* get_rules_xml(xmlDoc* doc);

/*
 * funzione che restituisce la struttura documento
 * con il nome del file salvato,
 * ogni carattere dell'xml (per elaborazioni successive su stringhe)
 * e la struttura ad albero partendo da root
 */
xmlDoc* read_xml(char* file_name, char* mode) {
    xmlDoc* xml = NULL;
    FILE* fp = NULL;
    long dim = 0;

    //apre il file seguendo mode come modalita'
    fp = fopen(file_name, mode);
    if(fp == NULL) {
        printf(ANSI_RED "Error on read %s file!" ANSI_RESET "\n", file_name);
        return NULL;
    }
    //alloca il documento
    xml = init_doc();
    //salva il nome del file
    xml->name = file_name;
    //ottiene la dimensione
    fseek(fp, 0, SEEK_END);
    dim = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if(dim) {
        //e salva l'intero contenuto nella variabile della struttura
        xml->content = (char*) malloc(sizeof(char)*dim);
        if (xml->content != NULL) {
            if(!fread(xml->content, sizeof(char), dim, fp))
                printf(ANSI_RED "Error on save xml text into buffer!"
                       ANSI_RESET "\n");
        }
    }
    fclose(fp);
    //crea l'albero dei tag
    xml->root = xml_to_tree(xml->content);

    return xml;
}

xmlRule* get_rules_xml(xmlDoc* doc) {
    xmlRule* rules = NULL;

    rules = init_rule();
    //TODO CONTINUA QUI

    return rules;
}

#endif //XML_READER_H
