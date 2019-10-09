#ifndef PRINTOUT_H
#define PRINTOUT_H

#include "xmlstruct.h"
#include "xmlstack.h"
#include "colors.h"

int xml_to_html(xml_tree* doc, char* filename);
void print_xmlstruct_html(xml_node* node, FILE* fp);
int xml_to_xml(xml_tree* doc, char* filename);
int xml_to_rtf(xml_tree* doc, char* filename);
int xml_to_txt(xml_tree* doc, char* filename);
void print_xmlstruct_txt(xml_node* node, FILE* fp);
int xml_to_stdout(xml_tree* doc);
void print_node(xml_node* node);
void print_xml_tree(xml_tree* doc);
void print_tree(xml_node* root, int level);
void print_stack(stack* head);


/*
 * print xml tree with html format, return 1 on errors, 0 if it's ok
 */
int xml_to_html(xml_tree* doc, char* filename) {
    FILE* fp = NULL;

    //open file
    fp = fopen(filename, "w+");
    if(fp == NULL) {
        fprintf(stderr, "Error on opening %s file!", filename);
        return 1;
    }
    printf("nome file html: %s\n", filename);
    //stampa head
    fprintf(fp,
"<!DOCTYPE html>\
<html lang=\"it\" dir=\"ltr\">\
    <head>\
        <meta charset=\"utf-8\">\
        <meta name = \"viewport\" content = \"width=device-width, initial-scale=1.0\">\
        <meta name = \"keywords\" content = \"xml, htmloutput, parsing\"/>\
        <meta name = \"description\" content = \"%s\"/>\
        <title>%s</title>\
    </head>\
    <body>", doc->name, doc->name);
    //stampa content
    fprintf(fp, "<div class=\"content\"><h1>%s xml structure:</h1>", doc->name);
    fprintf(fp, "<ul>");
    print_xmlstruct_html(doc->root, fp);
	fprintf(fp, "</ul>");
	//stampa footer
    fprintf(fp, "\
        <div class=\"footer\">\
            <a href=\"#\"> RETURN TOP </a>\
            <p><span> (C) Copyright 2019</span><br><br></p>\
        </div>\
    </body>\
</html>");

    return 0;
}

/*
 * recursive funtion that print xml nodes one by one, with innested lists
 */
void print_xmlstruct_html(xml_node* node, FILE* fp) {
	int i = 0;

	if(node == NULL)
		return;
	//se è root passa direttamente ai figli
	if(node->tag != NULL) {
		//satmpa nome e valore del tag
		fprintf(fp, "<li");
		if(node->is_comment)
			fprintf(fp, " class=\"comment\" ");
		fprintf(fp, ">%s<br/>", node->tag);
		if(node->tag_value != NULL)
			fprintf(fp, "<p>%s</p>", node->tag_value);
		//stampa gli attributi del tag
		if(node->attributes != NULL) {
			fprintf(fp, "<ul>");
			for(i = 0; i < node->n_attributes; i++)
				fprintf(fp, "<li>%s = %s</li>",
						node->attributes[i]->attr,
						node->attributes[i]->attr_val);
			fprintf(fp, "</ul>");
		}
	}
	//apre i tag figli
	for(i = 0; i < node->n_childs; i++) {
		fprintf(fp, "<ul>");
		print_xmlstruct_html(node->childs[i], fp);
		fprintf(fp, "</ul>");
	}
	fprintf(fp, "</li>");
}

int xml_to_xml(xml_tree* doc, char* filename) {
    return 0;
}

int xml_to_rtf(xml_tree* doc, char* filename) {
    return 0;
}

int xml_to_txt(xml_tree* doc, char* filename) {
    FILE* fp = NULL;

    //open file
    fp = fopen(filename, "w+");
    if(fp == NULL) {
        fprintf(stderr, "Error on opening %s file!", filename);
        return 1;
    }
    print_xmlstruct_txt(doc->root, fp);

    return 0;
}

/*
 * recursive funtion that print xml nodes one by one, with innested lists
 */
void print_xmlstruct_txt(xml_node* node, FILE* fp) {
	int i = 0;

	if(node == NULL)
		return;
	//se è root passa direttamente ai figli
	if(node->tag != NULL) {
		//satmpa nome e valore del tag
		if(node->is_comment)
			fprintf(fp, "!-- ");
		fprintf(fp, "%s", node->tag);
		if(node->tag_value != NULL)
			fprintf(fp, ": %s", node->tag_value);
        fprintf(fp, "\n");
		//stampa gli attributi del tag
		if(node->attributes != NULL) {
			for(i = 0; i < node->n_attributes; i++)
				fprintf(fp, "\t%s = %s\n",
						node->attributes[i]->attr,
						node->attributes[i]->attr_val);
			fprintf(fp, "\n");
		}
	}
	//apre i tag figli
	for(i = 0; i < node->n_childs; i++)
		print_xmlstruct_txt(node->childs[i], fp);
}

int xml_to_stdout(xml_tree* doc) {

    if(doc == NULL)
        return -1;
    print_xml_tree(doc);

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

/*
 * print a neat version for the stdout
 */
void print_stack(stack* head) {

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

#endif
