#ifndef TYPES_H
#define TYPES_H

#define RESOURCES_DESCRIPTION_AMOUNT 128

typedef enum
{
	OK,
	ERROR_NULL_POINTER,
	ERROR_MEMORY,
	ERROR_DUPLICATED_KEY,
	ERROR_MISSING_KEY,
	ERROR_AMOUNT_ARGUMENTS,
	ERROR_CORRUPT_FILE,
	ERROR_INVALID_ID,
	ERROR_INVALID_USED_TIME,
	ERROR_PROCESS,
	ERROR_WRITING_FILE
	
}status_t;

typedef struct
{
	size_t id;
	char resources_description[RESOURCES_DESCRIPTION_AMOUNT];
	float used_time;

}stocklist_t;

typedef enum{
	FALSE,
	TRUE
}bool_t;

#endif


