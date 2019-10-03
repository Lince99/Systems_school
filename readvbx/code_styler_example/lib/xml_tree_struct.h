/*
 * Lince99
 */
/*
 * library that provides xml tree structure and utility functions
 */

#ifndef XML_TREE_STRUCT_H
#define XML_TREE_STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include "string_manager.h"

//globals configurations
static unsigned short int GLO_omit_print_doc = 0;

//structs definitions
typedef struct XMLDOC xmlDoc;
typedef struct XMLNODE xmlNode;
typedef struct XMLNODEATTR xmlNodeAttr;
typedef struct STACK stack;
//xml to struct functions
xmlNodeAttr* init_nodeAttr(void);
xmlNode* init_node(void);
xmlDoc* init_doc(void);
void free_attributes(xmlNode* node);
void free_node(xmlNode* node);
void free_xml(xmlDoc* doc);
void print_separator(const char* sep, int max_width);
void print_doc(xmlDoc* doc);
void print_node(xmlNode* node);
void print_tree(xmlNode* root, int level);
void print_xml(xmlDoc* doc);
xmlNode* add_child(xmlNode* root, xmlNode* node);
xmlNode* get_child(xmlNode* root, int pos);
//stack of xml nodes
stack* init_stack_node(xmlNode* val);
stack* push(stack* head, xmlNode* val);
stack* pop(stack* head);
xmlNode* get_last(stack* head);
int count_stack(stack* head);
void print_stack_XML(stack* head);



struct XMLDOC {
    char* name; /* file name */
    char* content; /* all xml content copied into this var */
    xmlNode* root; /* first root tag */
};
struct XMLNODE {
    int is_comment; /* flag if equal to 1 this node is a simple comment */
    char* tag; /* <tag> */
    char* tag_value; /* <tag> val </tag> */
    xmlNodeAttr** attributes; /* <tag attr[0]="val" attr[1]="val"> </tag> */
    int n_attributes; /* number of tag childs */
    xmlNode** childs; /* <tag> <tag[0]> </tag[0]> </tag> */
    int n_childs; /* number of tag childs */
};
struct XMLNODEATTR {
    char* attr; /* <tag attr> */
    char* attr_val; /* <tag attr="val"> */
};
struct STACK {
    xmlNode* value;
    stack* next;
};



/*
 * funzione che inizializza un attributo per un nodo
 */
xmlNodeAttr* init_nodeAttr(void) {
    xmlNodeAttr* node = NULL;

    node = (xmlNodeAttr*) malloc(sizeof(xmlNodeAttr));
    if(node == NULL) {
        printf(ANSI_RED "Error on alloc xmlNodeAttr!" ANSI_RESET "\n");
        return NULL;
    }
    node->attr = NULL;
    node->attr_val = NULL;

    return node;
}

/*
 * funzione che inizializza un nuovo nodo xml
 */
xmlNode* init_node(void) {
    xmlNode* node = NULL;

    node = (xmlNode*) malloc(sizeof(xmlNode));
    if(node == NULL) {
        printf(ANSI_RED "Error on alloc xmlNode!" ANSI_RESET "\n");
        return NULL;
    }
    node->is_comment = 0;
    node->tag = NULL;
    node->tag_value = NULL;
    node->attributes = NULL;
    node->n_attributes = 0;
    node->childs = NULL;
    node->n_childs = 0;

    return node;
}

/*
 * funzione che inizializza un nuovo nodo xml
 */
xmlDoc* init_doc(void) {
    xmlDoc* doc = NULL;

    doc = (xmlDoc*) malloc(sizeof(xmlDoc));
    if(doc == NULL) {
        printf(ANSI_RED "Error on alloc xmlDoc!" ANSI_RESET "\n");
        return NULL;
    }
    doc->name = NULL;
    doc->content = NULL;
    doc->root = NULL;

    return doc;
}

/*
 * procedura che libera la memoria
 * occupata dagli attributi del nodo passato come parametro
 */
void free_attributes(xmlNode* node) {

    if(node == NULL)
        return;
    if(node->attributes != NULL)
        free(node->attributes);

}

/*
 * procedura che libera la memoria
 * occupata da il nodo passato
 */
void free_node(xmlNode* node) {

    if(node == NULL)
        return;
    free(node);

}

/*
 * procedura che libera la memoria
 * completamente occupata dall'albero xml
 */
void free_xml(xmlDoc* doc) {

    if(doc == NULL)
        return;
    if(doc->root != NULL)
        free_node(doc->root);
    free(doc);

}

/*
 * semplice funzione di stampa di una riga di separazione
 */
void print_separator(const char* sep, int max_width) {
    int i = 0;

    for(i = 0; i < (int)(max_width/strlen(sep)); i++)
        printf("%s", sep);
    printf("\n");

}

/*
 * stampa le proprieta' e il contenuto del file xml
 */
void print_doc(xmlDoc* doc) {
    int i = 0;
    int length = 0;
    int trace = 0;
    char* data = NULL;

    if(doc == NULL) {
        printf(ANSI_YELLOW "Void document!" ANSI_RESET "\n");
        return;
    }
    printf("File name = " ANSI_CYAN "\"%s\"" ANSI_RESET "\n", doc->name);
    //print colorized xml
    data = doc->content;
    length = strlen(data);
    /*
     * 0 = BLUE = tag
     * 1 = CYAN = tag_value
     * 2 = RED = attribute
     * 3 = MAGENTA == attribute_value
     * 4 = GREEN = comment
     * 5 = YELLOW = close tag
     * WHITE = uknown
     */
    for(; i < length; i++) {
        //open tag
        if(data[i] == '<' || (trace == 3 && data[i] == '>'))
            trace = 0;
        //comment
        if(data[i+1] == '!' && trace == 0)
            trace = 4;
        //attribute
        if(data[i] == ' ' && (trace == 0 || trace == 3))
            trace = 2;
        //attribute value
        if(data[i] == '=' && trace == 2)
            trace = 3;
        //close tag
        if(data[i-1] == '>')
            trace = 1;
        //stampa
        switch(trace) {
            case 0:
                printf(ANSI_BLUE);
                break;
            case 1:
                printf(ANSI_CYAN);
                break;
            case 2:
                printf(ANSI_RED);
                break;
            case 3:
                printf(ANSI_MAGENTA);
                break;
            case 4:
                printf(ANSI_GREEN);
                break;
            default:
                printf(ANSI_WHITE);
                break;
        }
        printf("%c", data[i]);
    }
    printf(ANSI_RESET "\n");

    printf("Tree structrure is: ");
    if(doc->root != NULL)
        printf(ANSI_CYAN "SAVED" ANSI_RESET "\n");
    else
        printf(ANSI_YELLOW "NOT SAVED" ANSI_RESET "\n");

}

/*
 * procedura che stampa il nodo, le sue proprieta' e i tag delle foglie
 */
void print_node(xmlNode* node) {
    int i = 0;

    if(node == NULL) {
        printf(ANSI_YELLOW "Void node!" ANSI_RESET "\n");
        return;
    }
    //stampa il tag corrente al centro
    for(; i < node->n_childs-1; i++)
        printf("  ");
    if(node->is_comment)
        printf(ANSI_ITALIC ANSI_MAGENTA "\"%s\"" ANSI_RESET "\n", node->tag);
    else {
        if(node->tag == NULL)
            printf(ANSI_BOLD ANSI_CYAN "null" ANSI_RESET "\n");
        else
            printf(ANSI_BOLD ANSI_BLUE "\"%s\"" ANSI_RESET "\n", node->tag);
        if(node->n_attributes != 0) {
            printf(ANSI_BLUE);
            for(i = 0; i < node->n_attributes; i++)
                printf("%s = %s\t",
                       node->attributes[i]->attr,
                       node->attributes[i]->attr_val);
            printf("\n" ANSI_RESET);
        }
        if(node->tag_value != NULL)
            printf(ANSI_BLUE "\t\"%s\"" ANSI_RESET "\n", node->tag_value);
    }
    //se non ci sono foglie allora lo comunica
    if(node->n_childs == 0) {
        //printf(ANSI_CYAN "nil " ANSI_RESET "\n");
        return;
    }
    //se ci sono allora le stampa tutte
    for(i = 0; i < node->n_childs; i++) {
        if(node->childs[i] != NULL) {
            if(node->childs[i]->is_comment)
                printf(ANSI_MAGENTA);
            else
                printf(ANSI_CYAN);
            printf("\t\"%s\"\n", node->childs[i]->tag);
        }
        else
            printf(ANSI_CYAN " nil ");
    }
    printf(ANSI_RESET "\n");

}

/*
 * procedura di stampa formattata dell'intero albero xml
 */
void print_tree(xmlNode* root, int level) {
    int i = 0;

    if(root == NULL) {
        if(level == 0)
            printf(ANSI_YELLOW "Void tree!" ANSI_RESET "\n");
        return;
    }
    //se la radice attuale ha piu' foglie allora ne stampa i valori
    if(root->n_childs != 0){
        if(root->is_comment)
            printf(ANSI_ITALIC ANSI_MAGENTA "\"%s\"" ANSI_RESET "\n", root->tag);
        else {
            printf(ANSI_BLUE ANSI_BOLD ANSI_UNDERLINE);
            //se sono al livello 0 stampo ROOT, altrimenti stampo il tag
            (level == 0) ? printf("ROOT") : printf("%s", root->tag);
            printf(ANSI_RESET "\n");
            //se il tag ha degli attributi allora li stampa
            if(root->n_attributes != 0) {
                printf("Attributes:\t");
                for(i = 0; i < root->n_attributes; i++)
                    printf(ANSI_BLUE "%s = %s" ANSI_RESET "\t",
                           root->attributes[i]->attr,
                           root->attributes[i]->attr_val);
                printf("\n");
            }
        }
        //poi stampa i nodi figli di ogni tag aperto
        printf("Childs:\n");
        for(i = 0; i < root->n_childs; i++) {
            if(root->childs[i] != NULL) {
                //differenzia i tag dai commenti
                if(root->childs[i]->is_comment)
                    printf("\t" ANSI_MAGENTA "\"%s\"" ANSI_RESET,
                           root->childs[i]->tag);
                else
                    printf("\t" ANSI_CYAN "\"%s\""  ANSI_RESET,
                           root->childs[i]->tag);
            }
            else
                printf("\t" ANSI_RED "Null" ANSI_RESET);
            //stampa formattata della lista dei tag figli
            (i < root->n_childs-1) ? printf(";\n") : printf(".\n");
        }
        printf(ANSI_RESET "\n");
    }
    //incrementa il livello per passare alla ricorsione successiva
    ++level;
    //stampa ricorsiva delle foglie che diventano a loro volta radici
    for(i = 0; i < root->n_childs; i++) {
        if(root->n_childs != 0)
            print_tree(root->childs[i], level);
    }

}

/*
 * procedura di stampa formattata dell'intero albero xml
 */
void print_tree_no_color(xmlNode* root, int level) {
    int i = 0;

    if(root == NULL) {
        if(level == 0)
            printf("Void tree!\n");
        return;
    }
    //se la radice attuale ha piu' foglie allora ne stampa i valori
    if(root->n_childs != 0){
        if(root->is_comment)
            printf("\"%s\"\n", root->tag);
        else {
            //se sono al livello 0 stampo ROOT, altrimenti stampo il tag
            (level == 0) ? printf("ROOT") : printf("%s", root->tag);
            printf("\n");
            //se il tag ha degli attributi allora li stampa
            if(root->n_attributes != 0) {
                printf("Attributes:\t");
                for(i = 0; i < root->n_attributes; i++)
                    printf("%s = %s\t",
                           root->attributes[i]->attr,
                           root->attributes[i]->attr_val);
                printf("\n");
            }
        }
        //poi stampa i nodi figli di ogni tag aperto
        printf("Childs:\n");
        for(i = 0; i < root->n_childs; i++) {
            if(root->childs[i] != NULL) {
                //differenzia i tag dai commenti
                if(root->childs[i]->is_comment)
                    printf("\t\"%s\"", root->childs[i]->tag);
                else
                    printf("\t\"%s\"", root->childs[i]->tag);
            }
            else
                printf("\tNull");
            //stampa formattata della lista dei tag figli
            (i < root->n_childs-1) ? printf(";\n") : printf(".\n");
        }
        printf(ANSI_RESET "\n");
    }
    //incrementa il livello per passare alla ricorsione successiva
    ++level;
    //stampa ricorsiva delle foglie che diventano a loro volta radici
    for(i = 0; i < root->n_childs; i++) {
        if(root->n_childs != 0)
            print_tree(root->childs[i], level);
    }

}

/*
 * print xml tree as a pre-order list
 */
void print_tree_preorder(xmlNode* root) {
    int i = 0;
    int casted = 0;
    int lung = 0;
    const char* cast = "..";
    int max = 10; //max chars per node

    if(root == NULL)
        return;

    //stampa la radice
    if(root->tag != NULL) {
        //stampa solo lung caratteri del tag (casting per risparmiare spazio)
        lung = (int) strlen(root->tag);
        if(lung > max) {
            lung = max - (int) strlen(cast);
            casted = 1;
        }
        //i commenti sono in magenta, i tag in blu
        (root->is_comment) ? printf(ANSI_MAGENTA) : printf(ANSI_BLUE);
        printf("\"%s", substring(root->tag, 0, lung));
        if(casted)
            printf(ANSI_BOLD "%s", cast);
        printf("\"" ANSI_RESET);
    }
    //solo la radice dell'xml puo' avere tag a NULL
    else
        printf(ANSI_CYAN "ROOT" ANSI_RESET);

    //stampa le foglie
    printf(", ");
    for(; i < root->n_childs; i++) {
        print_tree_preorder(root->childs[i]);
    }

}

/*
 * print xml tree as a post-order list
 */
void print_tree_postorder(xmlNode* root) {
    int i = 0;
    int casted = 0;
    int lung = 0;
    const char* cast = "..";
    int max = 10; //max chars per node

    if(root == NULL)
        return;

    //stampa le foglie
    printf(", ");
    for(; i < root->n_childs; i++) {
        print_tree_preorder(root->childs[i]);
    }

    //stampa la radice
    if(root->tag != NULL) {
        //stampa solo lung caratteri del tag (casting per risparmiare spazio)
        lung = (int) strlen(root->tag);
        if(lung > max) {
            lung = max - (int) strlen(cast);
            casted = 1;
        }
        //i commenti sono in magenta, i tag in blu
        (root->is_comment) ? printf(ANSI_MAGENTA) : printf(ANSI_BLUE);
        printf("\"%s", substring(root->tag, 0, lung));
        if(casted)
            printf(ANSI_BOLD "%s", cast);
        printf("\"" ANSI_RESET);
    }
    //solo la radice dell'xml puo' avere tag a NULL
    else
        printf(ANSI_CYAN "ROOT" ANSI_RESET);

}

/*
 * procedura che stampa tutte le informazioni estratte sul documento xml
 */
void print_xml(xmlDoc* doc) {
    const char* sep = "- ";

    if(doc == NULL) {
        printf(ANSI_RED "NOTHING TO PRINT!" ANSI_RESET "\n");
        return;
    }
    print_separator(sep, 80);
    printf("\t\t\t\tDocument data:\n");
    //TODO at end remove comment to print doc
    if(!GLO_omit_print_doc)
        print_doc(doc);
    else
        printf(ANSI_YELLOW "XML CONTENT OMITTED" ANSI_RESET "\n");
    print_separator(sep, 80);
    printf("\t\t\t\tXML Tree Structure:\n");
    //stampa a partire dalla radice
    print_tree(doc->root, 0);
    printf("\n");
    print_separator(sep, 80);
    printf("\n");
}

/*
 * funzione che data la radice e il nuovo nodo,
 * assegna quest'ultimo alla radice come figlio
 */
xmlNode* add_child(xmlNode* root, xmlNode* node) {

    if(root == NULL)
        return node;
    //assegna il nodo come figlio di root passato per parametro
    //se questo e' il primo nodo allora alloca l'array di foglie
    if(root->n_childs == 0) {
        root->childs = (xmlNode**) malloc(sizeof(xmlNode*));
        root->n_childs = 1;
        root->childs[0] = node;
    }
    //altrimenti rialloca l'array e assegna node all'ultima posizione
    else {
        root->n_childs++;
        root->childs = (xmlNode**) realloc(root->childs,
                                           sizeof(xmlNode*)*(root->n_childs));
        root->childs[root->n_childs-1] = node;
    }

    return root;
}

/*
 * funzione che data la radice e la posizione del nodo figlio
 * da estrarre, se presente, restituisce quest'ultimo
 */
xmlNode* get_child(xmlNode* root, int pos) {
    xmlNode* node = NULL;

    if(root == NULL)
        return NULL;
    if(pos >= root->n_childs)
        pos = root->n_childs-1;
    //salva il valore richiesto
    node = root->childs[pos];

    return node;
}

/*
 * function that initialize one new node with val as value
 * return NULL if the program can't allocate the memory for the node
 */
stack* init_stack_node(xmlNode* val) {
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
stack* push(stack* head, xmlNode* val) {
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
xmlNode* get_last(stack* head) {

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

/*
 * procedura che stampa la pila di nodi
 */
void print_stack_XML(stack* head) {

    if(head == NULL)
        printf(ANSI_RED "Void stack!" ANSI_RESET "\n");
    while(head != NULL) {
        if(head->value == NULL)
            return;
        if(head->value->tag == NULL)
            printf("NULL");
        else
            printf("\"%s\"", head->value->tag);
        if(head->next == NULL)
            printf(".\n");
        else
            printf(",\t");
        head = head->next;
    }

}

#endif //XML_TREE_STRUCT_H
