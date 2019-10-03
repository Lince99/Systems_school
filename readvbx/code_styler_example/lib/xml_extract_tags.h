/*
 * Lince99
 */

#ifndef XML_EXTRACT_TAGS_H
#define XML_EXTRACT_TAGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include "colors.h"
#include "xml_tree_struct.h"

//0 = separatori e tag, 1 = minime info, 2 = info estrazioni, 3 = tutte info
//-1 = nulla
//GREEN = operations, BLUE = output, RED = errors, WHITE = input & counters
#define DBG -1

//globals configurations
static unsigned short int GLO_save_comments = 1;

//signatures
char* extract_tag_val(char* text, int dim);
xmlNodeAttr** extract_attributes(char* text, int dim, int* n_attr);
xmlNode* save_tag(char* data, int data_len, int* pos);
xmlNode* xml_to_tree(char* data);
void print_bsoc(unsigned short int n);



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
xmlNodeAttr** extract_attributes(char* text, int dim, int* n_attr) {
    xmlNodeAttr** out = NULL;
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
            if(n_at == 0)
                out = (xmlNodeAttr**) malloc(sizeof(xmlNodeAttr*));
            else
                out = (xmlNodeAttr**) realloc(out,
                                              sizeof(xmlNodeAttr*)*n_at);
            //salva l'attributo
            out[n_at] = init_nodeAttr();
            if(out == NULL)
                break;
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
xmlNode* save_tag(char* data, int data_len, int* pos) {
    xmlNode* node = NULL;
    char* text = NULL;
    char* tmp = NULL;
    const char* start_cmt = "<!--";
    const char* end_cmt = "-->";
    int start = *pos;
    int i = start;

    //controlli sui parametri
    if(start >= data_len-1 || start < 0)
        return NULL;
    //e inizializzo il nuovo nodo e la posizione dei caratteri
    node = init_node();

    //porta il contatore di caratteri a '>' per estrarre il tag da < a >
    for(; data[i] != '>' && i < data_len; i++);
    if(DBG > 2) printf("start[%d] = %c\tstart+1 = %c\t\ti[%d] = %c\n",
                       start, data[start], data[start+1], i, data[i]);
    if(DBG > 1) printf(ANSI_GREEN "Extracting tag...\n" ANSI_RESET);
    text = substring(data, start, i+1);
    text = trim_string(text);
    if(DBG > 0) printf("TAG = " ANSI_BOLD "\"%s\"" ANSI_RESET "\n", text);

    //se il tag corrente e' un commento allora lo estrae
    if(strncmp(text, start_cmt, strlen(start_cmt)) == 0) {
        tmp = substring(text, strlen(start_cmt),
                         strlen(text)-strlen(end_cmt));
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
        if(DBG > 2) printf("start = %d i = %d max = %d\n", start, i, data_len);
        if(start != i) {
            tmp = substring(data, start+1, i+1);
            node->tag_value = trim_string(tmp);
        }
    }
    if(DBG > 1) printf(ANSI_GREEN "Extracted node:" ANSI_RESET "\n");
    if(DBG > 0) print_node(node);
    *pos = i+1;

    return node;
}

/*
 * ritorna la radice dell'albero estratto leggendo da data i tag
 */
xmlNode* xml_to_tree(char* data) {
    xmlNode* root = init_node();
    xmlNode* node = NULL;
    xmlNode* tmp = NULL;
    stack* root_stack = NULL;
    int i = 0;
    int data_len = 0;
    int whats_next = 0;

    if(data == NULL)
        return NULL;
    //inizializza la radice con tag a NULL poiche' conterra' solo foglie
    tmp = root;
    root_stack = push(root_stack, tmp);
    //pulisce la lettura dell'xml
    data = trim_xml(data);
    data_len = strlen(data);

    while(i < data_len-1) {
        if(DBG > 1) print_bsoc(1);
        if(DBG > 0) print_separator("- ", 80);
        if(DBG > 0) printf("Stack before: ");
        if(DBG > 0) print_stack_XML(root_stack);
        if(DBG > 1) printf("\n");

        //se e' un commento allora diventera' suo figlio
        if(data[i+1] == '!') {
            if(DBG > 0) printf(ANSI_BOLD "Found new comment!"
                               ANSI_RESET "\n");
            whats_next = 0;
        }
        //se node sara' chiuso allora torna al padre precedente
        else if(data[i+1] == '/') {
            whats_next = 1;
        }
        //se il prossimo e' un nuovo tag allora node diventa padre
        else {
            if(DBG > 0) printf(ANSI_BOLD "Found new tag!"
                               ANSI_RESET "\n");
            whats_next = 2;
        }

        //salva il tag corrente se e' un tag aperto o commento
        if(whats_next != 1)
            node = save_tag(data, data_len, &i);
        //se e' un tag aperto lo aggiunge alla coda in attesa di una chiusura
        if(whats_next == 2) {
            if(!node->is_comment)
                root_stack = push(root_stack, node);
        }
        //se e' una chiusura del tag torna indietro con i tag padri nella coda
        else if(whats_next == 1) {
            //per ogni chiusura tag
            do {
                if(DBG > 0) printf(ANSI_BOLD "Found close tag!"
                                   ANSI_RESET "\n");
                //e passa al prossimo inizio nodo
                for(i = i+1; data[i] != '<' && i < data_len-1; i++);
                //torna al precedente padre
                root_stack = pop(root_stack);
                if(DBG > 1) printf("Modified stack: ");
                if(DBG > 1) print_stack_XML(root_stack);
            }while(data[i] == '<' && data[i+1] == '/');
        }

        //e la rende figlia della radice attuale (inizia con "null")
        //se e' un tag aperto oppure un commento e si vuole salvarlo
        if(whats_next == 2 || (whats_next == 0 && GLO_save_comments)) {
            if(DBG > 0) printf("\nAdding son " ANSI_BOLD "\"%s\"" ANSI_RESET
                               " to \"%s\" ...\n", node->tag, tmp->tag);
            if(DBG > 1) printf(ANSI_CYAN "%d son!"
                               ANSI_RESET "\n", tmp->n_childs+1);
            tmp = add_child(tmp, node);
        }
        //l'ultimo nodo aperto e' il padre per i successivi nodi
        tmp = get_last(root_stack);

        if(DBG > 1) printf("\n");
        if(DBG > 1) printf("Stack after: ");
        if(DBG > 1) print_stack_XML(root_stack);
    }

    //toglie la radice principale
    root_stack = pop(root_stack);
    //se ci sono ancora tag aperti c'e' un errore e cancella la struttura
    if(count_stack(root_stack) > 0) {
        if(DBG > 0) printf(ANSI_RED "Stack not void! Some tags aren't closed!"
                           ANSI_RESET "\n");
        free_node(root);
        return NULL;
    }

    return root;
}

/*
 * procedura di pulizia del terminale per stampe sovrapposte e temporeggiate
 */
void print_bsoc(unsigned short int n) {

    //attende n secondi
    for(int xsec = 0; xsec < n; xsec++)
        sleep(1);
    //ripulisce il terminale (80 colonne x 40 righe)
    printf(ANSI_RESET);
    for(int row = 0; row < 40; row++) {
        for(int col = 0; col < 80; col++)
            printf(ANSI_BG_BLACK " ");
        printf(ANSI_RESET "\n");
    }
    //e torna all'inizio
    gotoxy(0, 0);

}

#endif //XML_EXTRACT_TAGS_H
