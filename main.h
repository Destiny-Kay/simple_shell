#ifndef MAIN_H
#define MAIN_H
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
/*STRUCT FOR HOLDING COMMAND AND FUNCTION*/
/**
 *
*/
typedef struct builtin_command
{
	const char *command;
	int (*function)(char **args);
} command_table;


char **tokenize_input(const char *input, const char *delim);
#endif
