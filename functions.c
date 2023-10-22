#include "main.h"

/**
 * prompt - prints the prompt and updates the line and status in data
 * @data: the data struct
 *
 * Returns: nothing
 */
void prompt(data_t *data)
{
	size_t size = 0;
	char *buf = NULL;

	printf("$ ");
	data->chars_read = getline(&buf, &size, stdin);
	if (data->chars_read == -1)
	{
		printf("\n");
		exit(data->status);
	}

	data->line = buf;
}

/**
 * parse - tokenizes the line
 * @data: the data struct
 *
 * Return: nothing
 */
void parse(data_t *data)
{
	char *token;
	int token_count = 0;
	int i;
	char *line_copy;

	/* first we need a copy of the line for strtok*/
	line_copy = malloc(sizeof(char)*(data->chars_read));
	if (line_copy == NULL)
	{
		exit(EXIT_FAILURE); /*TODO: find an appropriate error message?*/
	}
	strcpy(line_copy, data->line);

	/* loop to count the number of tokens/ words in the line*/
	token = strtok(line_copy, " \n");
	while (token != NULL)
	{
		token_count++;
		token = strtok(NULL, " \n");
	}
	token_count++;
	
	/* setting the argument vector to hold the tokens*/
	data->argv = malloc(sizeof(char*) * token_count);

	token = strtok(data->line, " \n");
	for (i = 0; token != NULL; i++)
	{
		data->argv[i] = malloc(sizeof(char*) * strlen(token));
		strcpy(data->argv[i], token);
		token = strtok(NULL, " \n");
	}
	data->argv[i] = NULL;
	
	/* free everything */
	free(line_copy);

}
