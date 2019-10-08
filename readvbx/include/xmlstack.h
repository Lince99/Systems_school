#ifndef XMLSTACK_H
#define XMLSTACK_H

#include "xmlstruct.h"

typedef struct STACK stack;

stack* init_stack_node(xml_node* val);
stack* push(stack* head, xml_node* val);
stack* pop(stack* head);
xml_node* get_last(stack* head);
int count_stack(stack* head);


struct STACK {
    xml_node* value;
    stack* next;
};



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
