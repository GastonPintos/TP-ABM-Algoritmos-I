#include "modif.h"


status_t compare_struct(FILE * stock_file,FILE * crud_file, FILE * output_file)
{

	stocklist_t stock, modif, aux_stock, stock_backup;
	status_t status;
	bool_t eof_stock, eof_crud;
	size_t equal;

	if(stock_file == NULL || crud_file == NULL || output_file == NULL)
		return ERROR_NULL_POINTER;
	
	if((status=read_struct(stock_file,&stock, &eof_stock))!=OK)
		return status; 
	
	if((status=read_struct(crud_file,&modif, &eof_crud))!=OK)
		return status; 
	
	equal=0;

	while(!eof_crud && !eof_stock)
	{		
			if (stock.id == modif.id)
			{
				equal++;

				aux_stock = modif;
				stock_backup = modif;

				while(!eof_crud && aux_stock.id ==modif.id)
				{
					aux_stock = modif;

					if((status=read_struct(crud_file,&modif, &eof_crud))!=OK)
						return status; 
				}

				stock.used_time = (stock.used_time + aux_stock.used_time + stock_backup.used_time);

				print_struct(stock, output_file);
			}

			else
			{
				print_struct(stock, output_file);

				if((status=read_struct(stock_file,&stock, &eof_stock))!=OK)
					return status;
			}		
			
	}

	if(!equal)
		return ERROR_MISSING_KEY;


	while(!eof_stock)
	{

		if((status=read_struct(stock_file,&stock, &eof_stock))!=OK)
			return status;	

		print_struct(stock,output_file);
	}

	return OK;	

} 


