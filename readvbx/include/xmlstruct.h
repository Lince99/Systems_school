#ifndef XMLSTRUCT_H
#define XMLSTRUCT_H

#include "stdlib.h"

typedef struct XMLTREE xml_tree;
typedef struct XMLNODE xml_node;
typedef struct XMLNODEATTR xml_node_attr;

xml_tree* init_xml_tree();
xml_node* init_xml_node();
xml_node_attr* init_xml_node_attr();
void free_attributes(xml_node* node);
void free_node(xml_node* node);
void free_xml(xml_tree* doc);

struct XMLTREE {
    char* name; /* file name */
    char* content; /* all xml content linked to this var */
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



/*
 * initialize xml document structure to NULL
 */
xml_tree* init_xml_tree() {
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

/*
 * initialize xml node to NULL
 */
xml_node* init_xml_node() {
    xml_node* xml = NULL;

    xml = (xml_node*) malloc(sizeof(xml_node));
    if(xml == NULL) {
        fprintf(stderr,"Error on alloc xml node!\n");
        return NULL;
    }
    xml->is_comment = 0;
    xml->tag = NULL;
    xml->tag_value = NULL;
    xml->attributes = NULL;
    xml->n_attributes = 0;
    xml->childs = NULL;
    xml->n_childs = 0;

    return xml;
}

/*
 * initialize xml node to NULL
 */
xml_node_attr* init_xml_node_attr() {
    xml_node_attr* xml = NULL;

    xml = (xml_node_attr*) malloc(sizeof(xml_node_attr));
    if(xml == NULL) {
        fprintf(stderr,"Error on alloc xml node attributes list!\n");
        return NULL;
    }
    xml->attr = NULL;
    xml->attr_val = 0;

    return xml;
}

/*
 * procedura che libera la memoria
 * occupata dagli attributi del nodo passato come parametro
 */
void free_attributes(xml_node* node) {

    if(node == NULL)
        return;
    if(node->attributes != NULL)
        free(node->attributes);

}

/*
 * procedura che libera la memoria
 * occupata da il nodo passato
 */
void free_node(xml_node* node) {

    if(node == NULL)
        return;
    free(node);

}

/*
 * procedura che libera la memoria
 * completamente occupata dall'albero xml
 */
void free_xml(xml_tree* doc) {

    if(doc == NULL)
        return;
    if(doc->root != NULL)
        free_node(doc->root);
    free(doc);

}

#endif
