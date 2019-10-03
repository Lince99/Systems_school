/*
 * Basso Nicola
 * aka Lince99
 */

#ifndef XML_DEFAULT_RULES_H
#define XML_DEFAULT_RULES_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <malloc.h>
#include "colors.h"
#include "xml_rules.h"
#include "xml_tree_struct.h"
#include "xml_extract_tags.h"

//signatures
xmlNode* find_rule(xmlNode* root, char* rule);



/*
 * search for the first occurence of string rule inside tags and attributes
 * of the xml tree
 */
xmlNode* find_rule(xmlNode* root, char* rule) {
    int i = 0;
    xmlNode* tmp = NULL;

    //basic controls
    if(root == NULL || rule == NULL) {
        return NULL;
    }

    //return this node if the tag is equal to the rule
    if(root->tag != NULL) {
        if(strcasecmp(root->tag, rule) == 0)
            return root;
    }

    //check in the attributes for the rule str
    for(i = 0; i < root->n_attributes; i++) {
        if(strcasecmp(root->attributes[i]->attr, rule) == 0)
            return root;
    }

    //otherwise use recursion to find the rule
    for(i = 0; i < root->n_childs; i++) {
        if((tmp = find_rule(root->childs[i], rule)) != NULL)
            return tmp;
    }

    return NULL;
}



#endif //XML_DEFAULT_RULES_H
