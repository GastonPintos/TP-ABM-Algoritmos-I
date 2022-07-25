#ifndef COMMON_H
#define COMMON_H
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_ARGC 3

#define STOCK_FILE_POSITION 1
#define CRUD_FILE_POSITION 2
#define ERRORS_AMOUNT 10
#define RESOURCE_DESCRIPTION_POSITION 1
#define ID_POSITION 0
#define USED_TIME_POSITION 2

#define INIT_SIZE 5
#define GROWTH_FACTOR 2

#define DELIMITER '|' 

status_t validate_args(char * argv[], size_t l);

status_t open_files( FILE ** stock_file, FILE ** crud_file, FILE ** output_file, char * argv[]);

status_t read_struct(FILE * fi, stocklist_t * stocklist, bool_t *eof);

status_t split (const char * s, char del, size_t * amount_fields , char *** string_array);

status_t strdupl(const char *s, char **t);

status_t read_line_to_string(FILE * fi, char ** created_string, bool_t *eof);

status_t create_struct(char ** string_array, stocklist_t * stocklist);

status_t destroy_strings(char *** string_array, size_t *l);

status_t print_struct(stocklist_t structure, FILE * fo);

void print_errors(status_t status);

status_t close_files(FILE * stock_file, FILE * crud_file, FILE * output_file, char * argv[]);


#endif



