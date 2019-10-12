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
    int save_comments_cmd = 0;
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
        for(i = 1; i < argc; i++) {
            if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
                printf("\
Usage: %s [-i FILENAME] [-o FILENAME] [OPTION...]\n\
\n\
 Use -i or -o to parse a document to produce -o file, or use stdin or stdout\n\
  -i, --input  FILENAME\tFile to read (.vbox)\n\
  -o, --output FILENAME\tCustom output filename (no extension)\n\
\n\
 Use only 1 command (if -o isn't used, it'll take the name from stdin)\n\
  -xml, \t\txml output from data extracted from stdin or -i\n\
  -html, \t\thtml+css output from data extracted from stdin or -i\n\
  -rtf, \t\told rtf output from data extracted from stdin or -i\n\
  -txt, \t\tsimple txt output from data from stdin or -i\n\
\n\
 General commands:\n\
  -h, --help\t\tShow this help and quit\n\
  --comments\t\tSave comments read from -i file\n\
  --license \t\tPrint program's license\n\
\n\
%s  Copyright (C) 2019  Lince99\n\
Make a pull request to Lince99 on github for bugs or optimizations\n",
argv[0], argv[0]);
                return 0;
            }
            if(strcmp(argv[i], "--license") == 0) {
                printf("\
This program is free software: you can redistribute it and/or modify\n\
it under the terms of the GNU General Public License as published by\n\
the Free Software Foundation, either version 3 of the License, or\n\
(at your option) any later version.\n\
\n\
This program is distributed in the hope that it will be useful,\n\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
GNU General Public License for more details.\n\
\n\
You should have received a copy of the GNU General Public License\n\
along with this program.  If not, see <https://www.gnu.org/licenses/>.\n");
                return 0;
            }
            if(strcmp(argv[i], "--comments") == 0) {
                if(save_comments_cmd)
                    return 1;
                SAVE_COMMENTS = 1;
                save_comments_cmd = 1;
            }
            //user-selected filename to read
            if(strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
                if(i+1 == argc || filename_in != NULL)
                    return 1;
                else {
                    i++;
                    filename_in = argv[i];
                }
            }
            else if(strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
                if(i+1 == argc || filename_out != NULL)
                    return 1;
                else {
                    i++;
                    filename_out = argv[i];
                }
            }
            else if(strcmp(argv[i], "-html") == 0) {
                if(output_mode != 0)
                    return 1;
                output_mode = 1;
            }
            else if(strcmp(argv[i], "-xml") == 0) {
                if(output_mode != 0)
                    return 1;
                output_mode = 2;
            }
            else if(strcmp(argv[i], "-rtf") == 0) {
                if(output_mode != 0)
                    return 1;
                output_mode = 3;
            }
            else if(strcmp(argv[i], "-txt") == 0) {
                if(output_mode != 0)
                    return 1;
                output_mode = 4;
            }
            else if(strcmp(argv[i], "-1") == 0) {
                if(quantity_mode != 0)
                    return 1;
                quantity_mode = 1;
            }
            else if(strcmp(argv[i], "-2") == 0) {
                if(quantity_mode != 0)
                    return 1;
                quantity_mode = 2;
            }
            else if(strcmp(argv[i], "-3") == 0) {
                if(quantity_mode != 0)
                    return 1;
                quantity_mode = 3;
            }
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
        xmldoc = modify_data_level(xmldoc, quantity_mode); //TODO: implement it :3

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
