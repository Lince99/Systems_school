/*
 * Basso Nicola aka Lince99
 * 5^AI
 */
/*
 * Refer to README.md for the full description and usage examples
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/xmloperations.h"
#include "include/getarg.h"
#include "include/printout.h"

//where magic happens
int main(int argc, char** argv) {
    int i = 0;
    char* file_content = NULL; //where XML content reside
    char* filename_in = NULL; //input file name
    char* filename_out = NULL; //output file name
    int quantity_mode = 0;
    int output_mode = 0;
    xml_tree* xmldoc = NULL;

    //check for arg contents
    if(argc < 1) {
        fprintf(stderr, "Error on argc parsing! argc < 1!\n");
        return -1;
    }
    //no arguments = STDIN reading, output to STDOUT
    if(argc == 1) {
        file_content = read_stdin();
        filename_in = "readvbx_stdin.txt";
    }
    //search for command line arguments' content
    else {
        printf("args:\n");
        for(i = 1; i < argc; i++) {
            printf("%d : %s\n", i, argv[i]);
            //user-selected filename to read
            if(strcmp(argv[i], "-i") == 0) {
                if(i+1 == argc)
                    return 1;
                else {
                    i++;
                    filename_in = argv[i];
                }
            }
            else if(strcmp(argv[i], "-o") == 0) {
                if(i+1 == argc)
                    return 1;
                else {
                    i++;
                    filename_out = argv[i];
                }
            }
            else if(strcmp(argv[i], "-html") == 0)
                output_mode = 1;
            else if(strcmp(argv[i], "-xml") == 0)
                output_mode = 2;
            else if(strcmp(argv[i], "-rtf") == 0)
                output_mode = 3;
            else if(strcmp(argv[i], "-txt") == 0)
                output_mode = 4;
            else if(strcmp(argv[i], "-1") == 0)
                quantity_mode = 1;
            else if(strcmp(argv[i], "-2") == 0)
                quantity_mode = 2;
            else if(strcmp(argv[i], "-3") == 0)
                quantity_mode = 3;
        }
        //Read data from input
        if(filename_in != NULL)
            file_content = read_file(filename_in);
        if(file_content == NULL) {
            fprintf(stderr, "Error on reading file content!\n");
            return 2;
        }
    }
    //translate string to xml_tree
    if(file_content == NULL || !strlen(file_content)) {
        fprintf(stderr, "No content inside %s file!\n", filename_in);
        return 3;
    }
    //TODO REMOVE filename_in PARAM
    xmldoc = xml_to_tree(file_content, filename_in);
    if(quantity_mode > 0)
        xmldoc = modify_data_level(xmldoc, quantity_mode);

    //if no output file name is specified, copy the input file name
    if(output_mode != 0 || filename_out == NULL)
        filename_out = remove_extension(filename_in);
    //generate output
    switch (output_mode) {
        case 0:
            xml_to_stdout(xmldoc);
            break;
        case 1:
            xml_to_html(xmldoc, strcat(filename_out, ".html"));
            break;
        case 2:
            xml_to_xml(xmldoc, strcat(filename_out, ".xml"));
            break;
        case 3:
            xml_to_rtf(xmldoc, strcat(filename_out, ".rtf"));
            break;
        case 4:
            xml_to_txt(xmldoc, strcat(filename_out, ".txt"));
            break;
        default:
            return 3;
    }

    //free xml structure & co
    free_xml(xmldoc);
    
    return 0;
}
