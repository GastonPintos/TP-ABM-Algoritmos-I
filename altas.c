#include "altas.h"

status_t compare_struct(FILE * stock_file,FILE * crud_file, FILE * output_file)
{
	stocklist_t stock, update;
	status_t status;
	bool_t eof_stock, eof_crud;
	
	if(stock_file == NULL || crud_file == NULL || output_file == NULL)
		return ERROR_NULL_POINTER;
	
	if((status=read_struct(stock_file,&stock, &eof_stock))!=OK)
		return status; 
	
	if((status=read_struct(crud_file,&update, &eof_crud))!=OK)
		return status; 


	while(!eof_crud && !eof_stock)
	{	
			if (stock.id == update.id)
				return ERROR_DUPLICATED_KEY;
			
			if (stock.id < update.id)
			{

				if((status=read_struct(stock_file,&stock, &eof_stock))!=OK)
					return status; 	
			}

			else 
			{

				if((status=read_struct(crud_file,&update, &eof_crud))!=OK)
					return status; 
			}
	}
	
	while(!eof_stock)
	{
		print_struct(stock,output_file);

		if((status=read_struct(stock_file,&stock, &eof_stock))!=OK)
			return status;
	}

	while(!eof_crud)
	{
		print_struct(update,output_file);

		if((status=read_struct(crud_file,&update, &eof_crud))!=OK)
			return status; 	
	}

	return OK;	
} 
