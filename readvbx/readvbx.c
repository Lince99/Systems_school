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
#include "include/xmltree.h"
#include "include/getarg.h"
#include "include/printout.h"

//where magic happens
int main(int argc, char** argv) {
    int i = 0;
    char* file_content = NULL; //where XML reside
    char* filename_in = NULL; //input file name
    char* filename_out = NULL; //output file name
    char* file_content_out = NULL; //where output content reside
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
        argc++; //ignore command name
        for(; i < argc; i++) {
            if(quantity_mode == -1) {
                if(strcmp(argv[i], "-0"))
                    quantity_mode = 0;
                else if(strcmp(argv[i], "-1"))
                    quantity_mode = 1;
                else if(strcmp(argv[i], "-2"))
                    quantity_mode = 2;
            }
            else {
                fprintf(stderr, "Too many data quantity mode arguments!\n");
                return 1;
            }
            if(output_mode == -1) {
                if(strcmp(argv[i], "-html"))
                    output_mode = 0;
                else if(strcmp(argv[i], "-xml"))
                    output_mode = 1;
                else if(strcmp(argv[i], "-rtf"))
                    output_mode = 2;
                else if(strcmp(argv[i], "-txt"))
                    output_mode = 3;
            }
            else {
                fprintf(stderr, "Too many output format arguments!\n");
                return 1;
            }
            //user-selected filename to read
            if(in_check == 0) {
                if(strcmp(argv[i], "-i")) {
                    in_check = 1;
                    if(i < argc-1)
                        strcpy(filename_in, argv[i+1]);
                }
            }
            else {
                fprintf(stderr, "Too many input arguments!\n");
                return 1;
            }
            //user-selected output
            if(out_check == 0) {
                if(strcmp(argv[i], "-o")) {
                    out_check = 1;
                    if(i < argc-1) {
                        strcpy(filename_out, argv[i+1]);
                        output_mode = 5;
                    }
                }
            }
            else {
                fprintf(stderr, "Too many output arguments!\n");
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
    print_xml_tree(xmldoc); //TODO: REMOVE ON RELEASE
    
    //choose level of data updating xml_tree
    if(quantity_mode == -1)
        quantity_mode = 0; //default value
    xmldoc = modify_data_level(xmldoc, quantity_mode);
    
    //if no output file name is specified, copy the input file name
    if(filename_out == NULL)
        strcpy(filename_out, filename_in);
    if(output_mode == -1)
        output_mode = 4; //default value
    //produce output
    switch(output_mode) {
        //html
        case 0:
            xml_to_html(xmldoc, filename_out);
            break;
        //xml (.out_xml)
        case 1:
            xml_to_xml(xmldoc, filename_out);
            break;
        //rtf
        case 2:
            xml_to_rtf(xmldoc, filename_out);
            break;
        //txt
        case 3:
            xml_to_txt(xmldoc, filename_out);
            break;
        //no file output, only terminal
        case 4:
            xml_to_stdout(xmldoc);
            break;
        //user defined output
        case 5:
            xml_to_user(xmldoc, filename_out);
        default:
            fprintf(stderr, "Error on selecting output format!\n");
            return 3;
    }

    return 0;
}
