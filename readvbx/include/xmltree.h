#ifndef XMLTREE_H
#define XMLTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structs definitions
typedef struct XMLTREE xml_tree;
typedef struct XMLNODE xml_node;
typedef struct XMLNODEATTR xml_node_attr;
typedef struct STACK stack;

struct XMLTREE {
    char* name; /* file name */
    char* content; /* all xml content copied into this var */
    xml_node* root; /* first root tag */
};
struct XMLNODE {
    int is_comment; /* flag if equal to 1 this node is a simple comment */
    char* tag; /* <tag> */
    char* tag_value; /* <tag> val </tag> */
    xml_node_attr** attributes; /* <tag attr[0]="val" attr[1]="val"> </tag> */
    int n_attributes; /* number of tag childs */
    xml_node** childs; /* <tag> <tag[0]> </tag[0]> </tag> */
    int n_childs; /* number of tag childs */
};
struct XMLNODEATTR {
    char* attr; /* <tag attr> */
    char* attr_val; /* <tag attr="val"> */
};
struct STACK {
    xml_node* value;
    stack* next;
};

/*
 * initialize xml document structure to NULL
 */
xml_tree* init_xml_tree(char* content) {
    xml_tree* xmldoc = NULL;

    xmldoc = (xml_tree*) malloc(sizeof(xml_tree));
    if(xmldoc == NULL) {
        fprintf(stderr,"Error on alloc xml document tree!\n");
        return NULL;
    }
    xmldoc->name = NULL;
    xmldoc->content = NULL;
    xmldoc->root = NULL;

    return xmldoc;
}

//TODO


#endif
