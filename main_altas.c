#include "altas.h"

int main (int argc, char * argv[])
{
	FILE * stock_file;
	FILE * update_file;
	FILE * output_file;

	status_t status;

	if((status = validate_args( argv, argc)) != OK)
	{
		print_errors(status);
		return EXIT_FAILURE;
	}

	if((status = open_files(&stock_file, &update_file, &output_file, argv)) != OK)
	{
		print_errors(status);
		return EXIT_FAILURE;
	}

	if((status = compare_struct(stock_file,update_file,output_file)) != OK)
	{
		print_errors(status);
		return EXIT_FAILURE;
	}

	if((status = close_files(stock_file, update_file, output_file, argv)) != OK)
	{
		print_errors(status);
		return EXIT_FAILURE;
	}		
	return EXIT_SUCCESS;
}



















