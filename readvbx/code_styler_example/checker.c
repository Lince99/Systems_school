/*
 * Basso Nicola
 * aka Lince99
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/xml_tree_struct.h"
#include "lib/colors.h"
#include "lib/xml_reader.h"
#include "lib/xml_default_rules.h"



//where magic happens
int main(int argc, char** argv) {
    xmlDoc* xml = NULL;
    xmlDoc* xml_rules = NULL;
    GLO_save_comments = 0;
    GLO_omit_print_doc = 1;

    //char file_name[] = "styles/example_style.xml";
    char file_name[] = "styles/example_style.xml";
    //char file_name_out[] = "styles/c_style.xml";
    char mode[] = "r";
    //read xml recursively
    xml = read_xml(file_name, mode);
    //print a tree format for all content
    print_xml(xml);
    //save modified xml
    //save_xml(xml, file_name_out);


    free_xml(xml);

    return 0;
}
