/*
 * Lince99
 */

#ifndef XML_SAVE_TAGS_H
#define XML_SAVE_TAGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include "colors.h"
#include "xml_tree_struct.h"

//signatures
void save_xml(xmlDoc* doc, char* new_file);
void write_tags(FILE* fp, xmlNode* node, int level);



//signatures
void save_xml(xmlDoc* doc, char* new_file) {
    FILE* fp = NULL;
    xmlNode* node = NULL;

    if(doc == NULL || new_file == NULL)
        return;
    //open the file to write
    fp = fopen(new_file, "w");
    if(fp == NULL) {
        printf(ANSI_RED "Error on open %s file!" ANSI_RESET "\n", new_file);
        return;
    }
    node = doc->root;
    if(node == NULL) {
        printf(ANSI_RED "Nothing to save!" ANSI_RESET "\n");
        return;
    }
    //write down every saved tag
    write_tags(fp, node, 0);
    printf(ANSI_BLUE "Saved xml file: %s" ANSI_RESET "\n", new_file);

    fclose(fp);
}

/*
 * write on an already opened file stream all xml tree starting from node
 * level is required for indentation
 */
void write_tags(FILE* fp, xmlNode* node, int level) {
    int i = 0;
    int j = 0;

    if(node->tag != NULL) {
        //insert tabs for indentation
        for(j = 0; j < level; j++)
            fprintf(fp, "\t");
        //if the current node is a comment print olny its content
        if(node->is_comment)
            fprintf(fp, "<!-- %s -->\n", node->tag);
        else {
            //print tag name
            fprintf(fp, "<%s", node->tag);
            //print attributes
            for(i = 0; i < node->n_attributes; i++)
                fprintf(fp, " %s=%s",
                       node->attributes[i]->attr,
                       node->attributes[i]->attr_val);
            fprintf(fp, ">");
            //print tag value
            if(node->tag_value != NULL)
                fprintf(fp, " %s ", node->tag_value);
        }
    }
    if(node->n_childs != 0 && level != 0)
        fprintf(fp, "\n");
    //print tag childs
    for(i = 0; i < node->n_childs; i++) {
        write_tags(fp, node->childs[i], level+1);
    }
    //print close tag if is required
    if(node->tag != NULL) {
        if(!node->is_comment) {
            //with the right indentation
            for(j = 0; j < level && node->n_childs != 0; j++)
                fprintf(fp, "\t");
            fprintf(fp, "</%s>\n", node->tag);
        }
    }

}

#endif //XML_SAVE_TAGS_H
