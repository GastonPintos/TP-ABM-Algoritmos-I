#include "modif.h"

int main (int argc, char * argv[])
{
	FILE * stock_file;
	FILE * crud_file;
	FILE * output_file;

	status_t status;

	if((status = validate_args( argv, argc)) != OK)
	{
		print_errors(status);
		return EXIT_FAILURE;
	}

	if((status = open_files(&stock_file, &crud_file, &output_file, argv)) != OK)
	{
		print_errors(status);
		return EXIT_FAILURE;
	}

	if((status = compare_struct(stock_file,crud_file,output_file)) != OK)
	{
		print_errors(status);
		return EXIT_FAILURE;
	}

	if((status = close_files(stock_file, crud_file, output_file, argv)) != OK)
	{
		print_errors(status);
		return EXIT_FAILURE;
	}		
	return EXIT_SUCCESS;
}







