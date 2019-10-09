#ifndef XMLTREE_H
#define XMLTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getarg.h"
#include "printout.h"
#include "xmlstruct.h"
#include "xmlstack.h"
#include "colors.h"

xml_tree* xml_to_tree(char* content, char* fname);
xml_node* extract_root(char* data);
char* extract_tag_val(char* text, int dim);
xml_node_attr** extract_attributes(char* text, int dim, int* n_attr);
xml_node* save_tag(char* data, int data_len, int* pos);
xml_node* add_child(xml_node* root, xml_node* node);
xml_node* get_child(xml_node* root, int pos);
xml_tree* modify_data_level(xml_tree* doc, int level);

static int SAVE_COMMENTS = 0;

/*
 * return new xml tree structure from string with unparsed xml
 */
xml_tree* xml_to_tree(char* content, char* fname) {
    xml_tree* doc = NULL;

    doc = init_xml_tree();
    doc->name = fname;
    doc->content = content;
    doc->root = extract_root(content);

    return doc;
}

/*
 * ritorna la radice dell'albero estratto leggendo da data i tag
 */
xml_node* extract_root(char* data) {
    xml_node* root = init_xml_node();
    xml_node* node = NULL;
    xml_node* tmp = NULL;
    stack* root_stack = NULL;
    int i = 0;
    int data_len = 0;
    int whats_next = 0;
    //int autoclose = 0;

    if(data == NULL)
        return NULL;
    //inizializza la radice con tag a NULL poiche' conterra' solo foglie
    //per supportare i commenti iniziali e i tag della versione/doctype
    tmp = root;
    root_stack = push(root_stack, tmp);
    //pulisce la lettura dell'xml
    data = trim_xml(data);
    data_len = strlen(data);

    while(i < data_len-1) {
        //se e' un commento allora diventera' suo figlio
        if(data[i+1] == '!' || data[i+1] == '?')
            whats_next = 0;
        //se node sara' chiuso allora torna al padre precedente
        //else if(data[i+1] == '/')
        else if(data[i] == '<' && data[i+1] == '/')
            whats_next = 1;
        //se il prossimo e' un nuovo tag allora node diventa padre
        else
            whats_next = 2;
        //salva il tag corrente se e' un tag aperto o commento
        if(whats_next != 1) {
            node = save_tag(data, data_len, &i);
            if(data[i-2] == '/' && data[i-1] == '>')
                whats_next = 3;
        }
        //se e' un tag aperto lo aggiunge alla coda in attesa di una chiusura
        if(whats_next == 2) {
            //if(!node->is_comment && !autoclose)
            if(!node->is_comment)
                root_stack = push(root_stack, node);
        }
        //se e' una chiusura del tag torna indietro con i tag padri nella coda
        else if(whats_next == 1) {
            //per ogni chiusura tag
            do {
                //e passa al prossimo inizio nodo
                for(i = i+1; data[i] != '<' && i < data_len-1; i++);
                //torna al precedente padre
                root_stack = pop(root_stack);
            }while(data[i] == '<' && data[i+1] == '/');
        }

        //e la rende figlia della radice attuale (inizia con "null")
        //se e' un tag aperto oppure un commento e si vuole salvarlo
        if(whats_next == 2 || whats_next == 3 || (whats_next == 0 && SAVE_COMMENTS))
            tmp = add_child(tmp, node);
        //l'ultimo nodo aperto e' il padre per i successivi nodi
        tmp = get_last(root_stack);
    }

    //toglie la radice principale
    root_stack = pop(root_stack);
    //se ci sono ancora tag aperti c'e' un errore e cancella la struttura
    //BRUTAL TIME
    if(count_stack(root_stack) > 0) {
        free_node(root);
        return NULL;
    }

    return root;
}

/*
 ° funzione che ritorna solamente la stringa del tag (no attributi)
 */
char* extract_tag_val(char* text, int dim) {
    char* out = NULL;
    int out_dim = 0;
    int i = 0;

    if(text == NULL || dim == 0)
        return NULL;
    for(; out_dim < dim; out_dim++) {
        if(text[out_dim] == ' ')
            break;
    }
    if(out_dim == 0)
        return NULL;
    out = (char*) malloc(sizeof(char)*(out_dim+1));
    if(out == NULL)
        return NULL;
    for(; i < out_dim; ++i)
        out[i] = text[i];
    out[i] = '\0';

    return out;
}

/*
 * funzione che estrae da un tag i vari attributi
 */
//TODO FIX ESTRAZIONE VALORE DELL'ATTRIBUTO CON / NEI TAG AUTOCHIUDENTI
xml_node_attr** extract_attributes(char* text, int dim, int* n_attr) {
    xml_node_attr** out = NULL;
    int i = 0;
    int j = 0;
    int n_at = 0;

    for(; i < dim; i++) {
        if(text[i] == ' ' && i < dim-1) {
            while(text[i] == ' ' || text[i] == '\t')
                i++;
            //ottiene la lunghezza dell'attributo
            while(i+j < dim && text[i+j] != '=')
                j++;
            if(n_at == 0) {
                out = (xml_node_attr**) malloc(sizeof(xml_node_attr*));
            }
            else {
                out = (xml_node_attr**) realloc(out, sizeof(xml_node_attr*)*n_at*2);
            }
            //printf("\tBroke %d\n", n_at);
            if(out == NULL)
                break;
            //salva l'attributo
            out[n_at] = init_xml_node_attr();
            out[n_at]->attr = substring(text, i, i+j);
            //ottiene la lunghezza del valore dell'attributo
            i += j;
            j = 0;
            if(text[i] == '=')
                i++;
            while(i+j < dim && text[i+j] != ' ') {
                j++;
            }
            out[n_at]->attr_val = substring(text, i, i+j);
            //passa al successivo
            n_at++;
            i += j-1;
            j = 0;
        }
    }

    *n_attr = n_at;
    return out;
}

/*
 * salva tag e attributi estratti da data
 * a partire dal carattere in posizione start
 * e lo rende il nodo figlio della radice passata,
 * ritorna poi la posizione aggiornata in cui e' arrivato a estrarre
 */
xml_node* save_tag(char* data, int data_len, int* pos) {
    xml_node* node = NULL;
    char* text = NULL;
    char* tmp = NULL;
    const char* start_cmt = "<!--";
    const char* end_cmt = "-->";
    const char* start_def = "<?";
    const char* end_def = "?>";
    int start = *pos;
    int i = start;

    //controlli sui parametri
    if(start >= data_len-1 || start < 0)
        return NULL;
    //e inizializzo il nuovo nodo e la posizione dei caratteri
    node = init_xml_node();

    //porta il contatore di caratteri a '>' per estrarre il tag da < a >
    for(; data[i] != '>' && i < data_len; i++);
    text = substring(data, start, i+1);
    text = trim_string(text);

    //se il tag corrente e' un commento allora lo estrae
    if(strncmp(text, start_cmt, strlen(start_cmt)) == 0) {
        tmp = substring(text, strlen(start_cmt),
                         strlen(text)-strlen(end_cmt));
        tmp = trim_string(tmp);
        node->tag = tmp;
        node->is_comment = 1;
    }
    //se il tag corrente e' una dichiarazione allora lo estrae come commento
    else if(strncmp(text, start_def, strlen(start_def)) == 0) {
        tmp = substring(text, strlen(start_def),
                         strlen(text)-strlen(end_def));
        tmp = trim_string(tmp);
        node->tag = tmp;
        node->is_comment = 1;
    }
    //altrimenti e' un tag aperto con possibili attributi
    else {
        tmp = substring(text, 1, strlen(text)-1);
        tmp = trim_string(tmp);
        //estrae il nome del tag con la relativa funzione
        node->tag = extract_tag_val(tmp, strlen(tmp));
        //estrae gli attributi con la relativa funzione
        node->attributes = extract_attributes(tmp, strlen(tmp),
                                              &(node->n_attributes));
        //estrae il valore del tag attuale
        start = i;
        for(; data[i] != '<' && i < data_len; i++);
        i--;
        if(start != i) {
            tmp = substring(data, start+1, i+1);
            node->tag_value = trim_string(tmp);
        }
    }
    *pos = i+1;

    return node;
}

/*
 * funzione che data la radice e il nuovo nodo,
 * assegna quest'ultimo alla radice come figlio
 */
xml_node* add_child(xml_node* root, xml_node* node) {

    if(root == NULL)
        return node;
    //assegna il nodo come figlio di root passato per parametro
    //se questo e' il primo nodo allora alloca l'array di foglie
    if(root->n_childs == 0) {
        root->childs = (xml_node**) malloc(sizeof(xml_node*));
        root->n_childs = 1;
        root->childs[0] = node;
    }
    //altrimenti rialloca l'array e assegna node all'ultima posizione
    else {
        root->n_childs++;
        root->childs = (xml_node**) realloc(root->childs,
                                           sizeof(xml_node*)*(root->n_childs));
        root->childs[root->n_childs-1] = node;
    }

    return root;
}

/*
 * funzione che data la radice e la posizione del nodo figlio
 * da estrarre, se presente, restituisce quest'ultimo
 */
xml_node* get_child(xml_node* root, int pos) {
    xml_node* node = NULL;

    if(root == NULL)
        return NULL;
    if(pos >= root->n_childs)
        pos = root->n_childs-1;
    //salva il valore richiesto
    node = root->childs[pos];

    return node;
}

//TODO
xml_tree* modify_data_level(xml_tree* doc, int level) {
    return doc;
}

#endif
