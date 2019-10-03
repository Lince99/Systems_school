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

//TODO
xml_tree* init_xml_tree(char* content) {
    xml_tree* xmldoc = NULL;
    return xmldoc;
}

int xml_to_html(xml_tree* doc, char* filename) {
    return 0;
}

int xml_to_xml(xml_tree* doc, char* filename) {
    return 0;
}

int xml_to_rtf(xml_tree* doc, char* filename) {
    return 0;
}

int xml_to_txt(xml_tree* doc, char* filename) {
    return 0;
}

int xml_to_stdout(xml_tree* doc) {
    return 0;
}

int xml_to_user(xml_tree* doc, char* filename) {
    return 0;
}

#endif
