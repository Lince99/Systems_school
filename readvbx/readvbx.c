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
    int quantity_mode = -1;
    int output_mode = -1;
    int in_check = 0;
    int out_check = 0;
    xml_tree* xmldoc = NULL;

    //check for arg contents
    if(argc < 1) {
        fprintf(stderr, "Error on argc parsing! argc < 1!\n");
        return -1;
    }
    //no arguments = STDIN reading, output to STDOUT
    if(argc == 1) {
        file_content = read_stdin();
    }
    //search for command line arguments' content
    else {
        printf("args:\n");
        for(i = 1; i < argc; i++) {
            printf("%d : %s\n", i, argv[i]);
            //user-selected filename to read
            if(in_check == 0) {
                if(strcmp(argv[i], "-i")) {
                    in_check = 1;
                    filename_in = argv[i];
                }
            }
            else {
                fprintf(stderr, "Too many input arguments!\n");
                return 1;
            }
        }
    }

    //Read data from input
    if(in_check && filename_in != NULL)
        file_content = read_file(filename_in);
    else {
        fprintf(stderr, "Error on reading file content!\n");
        return 2;
    }


    //translate string to xml_tree
    if(file_content == NULL || !strlen(file_content)) {
        fprintf(stderr, "No content inside %s file!\n", filename_in);
        return 3;
    }
    xmldoc = xml_to_tree(file_content, filename_in);

    //generate output
    filename_out = remove_extension(filename_in);
    //if no output file name is specified, copy the input file name
    xml_to_html(xmldoc, strcat(filename_out, ".html"));
    xml_to_txt(xmldoc, strcat(filename_out, ".txt"));

    //free xml structure
    free_xml(xmldoc);

    return 0;
}
