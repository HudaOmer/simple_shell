#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


extern char **environ;

typedef struct data
{
	ssize_t chars_read;
	char *line;
	int status;
	char **argv;
}data_t;

#define DATA_INIT \
{0, NULL, 0, NULL}



/*functions.c*/
void prompt(data_t *data);
void parse(data_t *data);
void execute(data_t *data);

/*functions_1.c*/
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _getenv(char *envp[]);

#endif
