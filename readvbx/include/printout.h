#ifndef PRINTOUT_H
#define PRINTOUT_H

#include "xmlstruct.h"

int xml_to_html(xml_tree* doc, char* filename);
int xml_to_xml(xml_tree* doc, char* filename);
int xml_to_rtf(xml_tree* doc, char* filename);
int xml_to_txt(xml_tree* doc, char* filename);
int xml_to_stdout(xml_tree* doc);
int xml_to_user(xml_tree* doc, char* filename);
void print_node(xml_node* node);
void print_xml_tree(xml_tree* doc);
void print_tree(xml_node* root, int level);



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

/*
 * procedura che stampa il nodo, le sue proprieta' e i tag delle foglie
 */
void print_node(xml_node* node) {
    int i = 0;

    if(node == NULL) {
        fprintf(stderr, "Void node!\n");
        return;
    }
    fprintf(stdout, "STAMPA NODO:\n");
    //stampa il tag corrente al centro
    for(; i < node->n_childs-1; i++)
        fprintf(stdout, "  ");
    if(node->is_comment)
        fprintf(stdout, "!-- \"%s\"\n", node->tag);
    else {
        if(node->tag == NULL)
            fprintf(stdout, "null\n");
        else
            fprintf(stdout, "\"%s\"\n", node->tag);
        if(node->n_attributes != 0) {
            for(i = 0; i < node->n_attributes; i++)
                fprintf(stdout, "%s = %s\t",
                       node->attributes[i]->attr,
                       node->attributes[i]->attr_val);
            fprintf(stdout, "\n");
        }
        if(node->tag_value != NULL)
            fprintf(stdout, "\t\"%s\"\n", node->tag_value);
    }
    //se non ci sono foglie allora lo comunica
    if(node->n_childs == 0)
        return;
    //se ci sono allora le stampa tutte
    fprintf(stdout, "STAMPA NODI FIGLI:\n");
    for(i = 0; i < node->n_childs; i++) {
        if(node->childs[i] != NULL) {
            if(node->childs[i]->is_comment)
                fprintf(stdout, "!-- ");
            fprintf(stdout, "\t\"%s\"\n", node->childs[i]->tag);
        }
        else
            fprintf(stdout, " nil ");
    }
    fprintf(stdout, "\n\n\n");

}

/*
 * procedura che stampa tutte le informazioni estratte sul documento xml
 */
void print_xml_tree(xml_tree* doc) {
    const char* sep = "- ";

    if(doc == NULL) {
        fprintf(stderr, "NOTHING TO PRINT!\n");
        return;
    }
    fprintf(stdout, "\t\t\t\tXML Tree Structure:\n");
    //stampa a partire dalla radice
    print_tree(doc->root, 0);
    fprintf(stdout, "\n");
}

/*
 * procedura di stampa formattata dell'intero albero xml
 */
void print_tree(xml_node* root, int level) {
    int i = 0;

    if(root == NULL) {
        if(level == 0)
            fprintf(stderr, "Void tree!\n");
        return;
    }
    //se la radice attuale ha piu' foglie allora ne stampa i valori
    if(root->n_childs != 0){
        if(root->is_comment)
            fprintf(stdout, "\"%s\"\n", root->tag);
        else {
            //se sono al livello 0 stampo ROOT, altrimenti stampo il tag
            (level == 0) ? fprintf(stdout, "ROOT") : fprintf(stdout, "%s", root->tag);
            fprintf(stdout, "\n");
            //se il tag ha degli attributi allora li stampa
            if(root->n_attributes != 0) {
                fprintf(stdout, "Attributes:\t");
                for(i = 0; i < root->n_attributes; i++)
                    fprintf(stdout, "%s = %s\t",
                           root->attributes[i]->attr,
                           root->attributes[i]->attr_val);
                fprintf(stdout, "\n");
            }
        }
        //poi stampa i nodi figli di ogni tag aperto
        fprintf(stdout, "Childs:\n");
        for(i = 0; i < root->n_childs; i++) {
            if(root->childs[i] != NULL) {
                //differenzia i tag dai commenti
                if(root->childs[i]->is_comment)
                    fprintf(stdout, "\t\"%s\"",
                           root->childs[i]->tag);
                else
                    fprintf(stdout, "\t\"%s\"",
                           root->childs[i]->tag);
            }
            else
                fprintf(stdout, "\tNull");
            //stampa formattata della lista dei tag figli
            (i < root->n_childs-1) ? fprintf(stdout, ";\n") : fprintf(stdout, ".\n");
        }
        fprintf(stdout, "\n");
    }
    //incrementa il livello per passare alla ricorsione successiva
    ++level;
    //stampa ricorsiva delle foglie che diventano a loro volta radici
    for(i = 0; i < root->n_childs; i++) {
        if(root->n_childs != 0)
            print_tree(root->childs[i], level);
    }

}

#endif
