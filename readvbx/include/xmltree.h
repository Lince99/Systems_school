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
struct STACK {
    xml_node* value;
    stack* next;
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
 * return new xml tree structure from string with unparsed xml
 */
xml_tree* xml_to_tree(char* content, char* fname) {
    xml_tree* doc = NULL;

    doc = init_xml_tree();
    doc->name = fname;
    doc->content = content;
    //doc->root = extract_root(content); TODO

    return doc;
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











//TODO
int print_xml_tree(xml_tree* xmldoc) {
    
    return 0;
}

/*
 * function that initialize one new node with val as value
 * return NULL if the program can't allocate the memory for the node
 */
stack* init_stack_node(xml_node* val) {
    stack* node = NULL;

    node = (stack*) malloc(sizeof(stack));
    if(node == NULL)
        return NULL;
    node->value = val;
    node->next = NULL;

    return node;
}

/*
 * function that add 1 new node valued with val at the tail of head
 * return always the head
 */
stack* push(stack* head, xml_node* val) {
    stack* node = NULL;
    stack* old_head = head;

    node = init_stack_node(val);
    if(node == NULL)
        return NULL;
    if(head == NULL)
        return node;
    while(head->next != NULL)
        head = head->next;
    head->next = node;

    return old_head;
}

/*
 * function that remove the last node of the stack
 */
stack* pop(stack* head) {
    stack* old_head = head;
    stack* prev = NULL;

    if(head == NULL)
        return NULL;
    while(head->next != NULL) {
        prev = head;
        head = head->next;
    }
    if(prev == NULL)
        return NULL;
    prev->next = NULL;

    return old_head;
}

/*
 * funzione che ritorna l'ultimo nodo presente nella pila
 */
xml_node* get_last(stack* head) {

    if(head == NULL)
        return NULL;
    while(head->next != NULL)
        head = head->next;

    return head->value;
}

/*
 * funzione che restituisce il numero di elementi presenti nello stack
 */
int count_stack(stack* head) {
    int x = 0;

    if(head == NULL)
        return 0;
    while(head->next != NULL) {
        x++;
        head = head->next;
    }

    return x;
}

#endif
