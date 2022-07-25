#include "common.h"
#include "types.h"


status_t validate_args(char * argv[], size_t l)
{
	if (argv == NULL)
		return ERROR_NULL_POINTER;

	if( l != MAX_ARGC)
		return ERROR_AMOUNT_ARGUMENTS;

	return OK;
}

status_t open_files( FILE ** stock_file, FILE ** crud_file, FILE ** output_file, char * argv[])
{
	if (stock_file == NULL || crud_file == NULL || output_file == NULL)
		return ERROR_NULL_POINTER;

	if((*stock_file = fopen (argv[STOCK_FILE_POSITION], "rt")) == NULL)
		return ERROR_CORRUPT_FILE;

	if((*crud_file = fopen (argv[CRUD_FILE_POSITION], "rt")) == NULL)
		return ERROR_CORRUPT_FILE;

	if((*output_file = fopen("stocklist_update.txt", "wt")) == NULL)
		return ERROR_CORRUPT_FILE; 

	return OK;
}

status_t read_struct(FILE * fi, stocklist_t * stocklist, bool_t *eof)
{
	char * file_line;
	char **string_array;
	size_t amount_fields;

	if(fi == NULL || stocklist == NULL)
		return ERROR_NULL_POINTER;

	if(read_line_to_string(fi, &file_line,eof) == OK && (strlen(file_line))!=0)
	{

			if(split(file_line, DELIMITER, &amount_fields, &string_array) != OK)
			{
				return ERROR_PROCESS;
			}

			if(create_struct(string_array, stocklist) != OK)
			{
				return ERROR_PROCESS;
			}

	}
	return OK;
}

status_t split (const char * s, char del, size_t * l , char *** string_array)
{
	char * str, * q, * p;
	char delims[2];
	size_t i;

	if ( s == NULL || l == NULL || string_array == NULL)
		return ERROR_NULL_POINTER;
	
	delims[0] = del;

	delims[1] = '\0';

	if(strdupl (s,&str) != OK )
	{
		*l = 0;
		return ERROR_MEMORY;
	}

	for(i = 0, *l = 0; str[i]; i++)
	{
		if(str[i] == del)
			(*l)++; 
	
	}
	(*l)++;

	if((* string_array = (char **)malloc((*l) * sizeof(char *))) == NULL)
	{
		free(str);
		*l=0;
		return ERROR_MEMORY;
	}

	for( i=0, q=str; (p = strtok(q, delims))!= NULL; q=NULL, i++)
	{
		if((strdupl(p,&(* string_array)[i])) != OK)
		{
			free(str);
			destroy_strings(string_array, l);
			*l=0;
			return ERROR_MEMORY;
		}
	}
	free(str);

	if((*string_array)[2]==NULL)
	{	
		(*string_array)[2]=(*string_array)[1];
		
		(*string_array)[1] = "";
	}
	return OK;
}

status_t strdupl(const char *s, char **t)
{
	size_t i;

	if( s == NULL || t == NULL)
		return ERROR_NULL_POINTER;

	if((*t =(char *)malloc((strlen(s)+sizeof(char))*sizeof(char))) == NULL)
		return ERROR_MEMORY;

	for( i=0; ((*t)[i] = s[i]) ; i++);

	return OK;
}

status_t read_line_to_string(FILE * fi, char ** created_string, bool_t *eof)
{
	char c;
	size_t CHOP_SIZE;
	size_t alloc_size, used_size;
	char * aux;

	CHOP_SIZE = sizeof(size_t)+sizeof(float)+(RESOURCES_DESCRIPTION_AMOUNT+4)*sizeof(char); 

	if (created_string == NULL || fi == NULL)
		return ERROR_NULL_POINTER;

	if((*created_string=(char *)malloc(CHOP_SIZE))== NULL)
		return ERROR_MEMORY;

	alloc_size = CHOP_SIZE;
	used_size = 0;
	
	while((c = fgetc(fi)) != '\n' && c != EOF)
	{
		if(used_size == alloc_size-1)
		{
			if((aux=(char*)realloc(*created_string,alloc_size + CHOP_SIZE)) == NULL)
			{
				free(*created_string);
				return ERROR_MEMORY;
			}
			*created_string = aux;
			alloc_size += CHOP_SIZE; 
		}
		(*created_string)[used_size ++] = c;
	}
	
	*eof=(c==EOF)?TRUE:FALSE;

	(*created_string)[used_size]='\0';

	return OK;	
}

status_t create_struct(char ** string_array, stocklist_t *stocklist)
{
	char * endp;
	
	if(string_array == NULL || stocklist == NULL)
		return ERROR_NULL_POINTER;

	(stocklist)->id = strtoul((string_array[ID_POSITION]), &endp, 10);

	if(!*endp)
	{
		return ERROR_INVALID_ID;
	}

	if(string_array[RESOURCE_DESCRIPTION_POSITION] == NULL)
		strcpy((stocklist)->resources_description , "");
	
	else
		strcpy( (stocklist)->resources_description , string_array[RESOURCE_DESCRIPTION_POSITION]);

	if( string_array[USED_TIME_POSITION] == NULL)
	{	
		(stocklist)->used_time = 0.0;	
	}
	else
	{	
		(stocklist)->used_time = strtod((string_array[USED_TIME_POSITION]), &endp);
				
			if(*endp)
			{
				return ERROR_INVALID_USED_TIME;
			}
	}
	return OK;
}

status_t destroy_strings(char *** string_array, size_t *l)
{
	size_t i;

	if(string_array == NULL)
		return ERROR_NULL_POINTER;

	for(i=0; i < *l; i++)
	{
		free(*string_array[i]);
		(*string_array)[i]=NULL;
	}
	
	free(*string_array);
	
	*string_array = NULL;
	
	*l=0;
	
	return OK;
}

status_t print_struct(stocklist_t structure, FILE * fo)
{
	if(fo == NULL)
		return ERROR_NULL_POINTER;

	fprintf(fo,"%lu",structure.id);

	fprintf(fo,"%c",DELIMITER);

	fprintf(fo,"%s",structure.resources_description);

	fprintf(fo,"%c",DELIMITER);

	fprintf(fo,"%f",structure.used_time);

	fprintf(fo, "\n");
	return OK;
}

void print_errors(status_t status)
{
	char* errors_dictionary[ERRORS_AMOUNT]=
		{
			"Error: null pointer.",
			"Error: insufficient memory.",
			"Error: duplicated ID.",
			"Error: missing ID.",
			"Error: incorrect amount of arguments.",
			"Error: unable to open file.",
			"Error: incorrect ID.",
			"Error: incorrect USED TIME.",
			"Error: unable to create struct array.",
			"Error: unable to write in file",
		};

	fprintf(stderr, "%s\n", errors_dictionary[status]);
}

status_t close_files(FILE * stock_file, FILE * crud_file, FILE * output_file, char *argv[])
{
	if(stock_file == NULL || crud_file == NULL || output_file == NULL)
		return ERROR_NULL_POINTER;

	fclose(stock_file);
	fclose(crud_file);

	if(fclose(output_file) == EOF)
		return ERROR_WRITING_FILE;

	remove(argv[STOCK_FILE_POSITION]);
	
	rename(output_file, "stocklist_update.txt");

	return OK;
}